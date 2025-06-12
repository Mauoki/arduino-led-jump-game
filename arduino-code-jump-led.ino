#include <FastLED.h>

// Definições do display LED
#define LED_PIN     6
#define NUM_LEDS    600  // 30x20 = 600 LEDs
#define BRIGHTNESS  50
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define MATRIX_WIDTH 30
#define MATRIX_HEIGHT 20

// Definição do botão
#define BUTTON_PIN  2

// Cores - usando valores diretos para economizar memória
CRGB leds[NUM_LEDS];

// Variáveis do jogo
uint8_t playerX = MATRIX_WIDTH - 7;    // Posição X do jogador (mais à direita)
uint8_t playerY = MATRIX_HEIGHT - 4;   // Posição Y inicial do jogador (acima do chão)
#define PLAYER_SIZE 2                  // Tamanho do jogador (2x2) como constante
#define GROUND_Y (MATRIX_HEIGHT - 1)   // Posição Y do chão como constante
int8_t playerYVelocity = 0;            // Velocidade vertical do jogador
uint8_t buttonState = 0;               // Estado do botão

// Obstáculos - reduzido para economizar memória
#define MAX_OBSTACLES 3
struct {
  int8_t x;
  uint8_t height;
  uint8_t flags;  // Bit 0: counted
} obstacles[MAX_OBSTACLES];

// Variáveis do jogo
uint16_t gameSpeed = 120;              // Velocidade do jogo (ms)
uint8_t score = 0;
uint8_t gameState = 0;                 // 0: jogando, 1: game over

// Função otimizada para converter coordenadas XY para posição no array de LEDs
uint16_t XY(uint8_t x, uint8_t y) {
  if (x >= MATRIX_WIDTH || y >= MATRIX_HEIGHT) {
    return 0;
  }
  
  if (y & 0x01) {
    // Linha ímpar, da direita para a esquerda
    return (y * MATRIX_WIDTH) + (MATRIX_WIDTH - 1 - x);
  } else {
    // Linha par, da esquerda para a direita
    return (y * MATRIX_WIDTH) + x;
  }
}

void setup() {
  // Configuração dos LEDs
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  
  // Configuração do botão
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Inicializa os obstáculos (vindo da esquerda)
  for (uint8_t i = 0; i < MAX_OBSTACLES; i++) {
    obstacles[i].x = -5 - (i * 12);
    obstacles[i].height = random(2, 5);
    obstacles[i].flags = 0;  // Não contado
  }
  
  // Inicialização da semente aleatória
  randomSeed(analogRead(0));
}

void loop() {
  static uint32_t lastMoveTime = 0;
  static uint32_t lastObstacleTime = 0;
  uint32_t currentTime = millis();
  
  // Lê o botão
  uint8_t currentButtonState = !digitalRead(BUTTON_PIN);
  
  if (gameState == 0) {  // Jogando
    // Lógica de pulo
    if (currentButtonState && !buttonState && playerY == GROUND_Y - PLAYER_SIZE) {
      playerYVelocity = -4;  // Força do pulo
    }
    
    // Atualiza a posição do jogador com a física
    if (currentTime - lastMoveTime > gameSpeed) {
      lastMoveTime = currentTime;
      
      // Aplica gravidade
      playerYVelocity += 1;  // Gravidade
      playerY += playerYVelocity;
      
      // Limita a posição ao chão
      if (playerY + PLAYER_SIZE > GROUND_Y) {
        playerY = GROUND_Y - PLAYER_SIZE;
        playerYVelocity = 0;
      }
      
      // Move os obstáculos
      for (uint8_t i = 0; i < MAX_OBSTACLES; i++) {
        obstacles[i].x++;
        
        // Verifica se o obstáculo saiu da tela
        if (obstacles[i].x > MATRIX_WIDTH) {
          obstacles[i].x = -random(5, 15);
          obstacles[i].height = random(2, 6);
          obstacles[i].flags &= ~1;  // Marca como não contado
        }
        
        // Verifica colisão
        if (playerX < obstacles[i].x + 1 && 
            playerX + PLAYER_SIZE > obstacles[i].x && 
            playerY < GROUND_Y - obstacles[i].height + obstacles[i].height && 
            playerY + PLAYER_SIZE > GROUND_Y - obstacles[i].height + 1) {
          gameState = 1;  // Game over
        }
        
        // Conta pontos quando o jogador passa pelo obstáculo
        if (!(obstacles[i].flags & 1) && obstacles[i].x > playerX + PLAYER_SIZE) {
          score++;
          obstacles[i].flags |= 1;  // Marca como contado
          
          // Aumenta a velocidade a cada 5 pontos
          if (score % 5 == 0 && gameSpeed > 40) {
            gameSpeed -= 10;
          }
        }
      }
    }
    
  } else {  // Game over
    // Reinicia o jogo se o botão for pressionado durante o game over
    if (currentButtonState && !buttonState) {
      resetGame();
    }
  }
  
  buttonState = currentButtonState;  // Atualiza o estado do botão
  
  // Renderiza o jogo
  renderGame();
  
  // Atualiza os LEDs
  FastLED.show();
}

// Função para desenhar o jogo - otimizada para usar menos memória
void renderGame() {
  // Limpa o display
  FastLED.clear();
  
  // Desenha o chão
  for (uint8_t x = 0; x < MATRIX_WIDTH; x++) {
    leds[XY(x, GROUND_Y)] = CRGB(0, 200, 0);  // Verde
  }
  
  // Desenha os obstáculos
  for (uint8_t i = 0; i < MAX_OBSTACLES; i++) {
    if (obstacles[i].x >= 0 && obstacles[i].x < MATRIX_WIDTH) {
      for (uint8_t h = 0; h < obstacles[i].height; h++) {
        leds[XY(obstacles[i].x, GROUND_Y - h)] = CRGB(255, 0, 0);  // Vermelho
      }
    }
  }
  
  // Desenha o jogador
  if (gameState == 0 || (millis() / 250) % 2 == 0) {
    for (uint8_t y = 0; y < PLAYER_SIZE; y++) {
      for (uint8_t x = 0; x < PLAYER_SIZE; x++) {
        leds[XY(playerX + x, playerY + y)] = CRGB(0, 255, 255);  // Ciano
      }
    }
  }
  
  // Placar - mostra até 30 pontos
  uint8_t scoreDisplay = min(score, MATRIX_WIDTH - 1);
  if (gameState == 0 || (millis() / 500) % 2 == 0) {
    for (uint8_t i = 0; i < scoreDisplay; i++) {
      leds[XY(i, 0)] = CRGB(255, 255, 0);  // Amarelo
    }
  }
}

// Função para reiniciar o jogo
void resetGame() {
  playerY = MATRIX_HEIGHT - 4;
  playerYVelocity = 0;
  
  // Reinicia os obstáculos
  for (uint8_t i = 0; i < MAX_OBSTACLES; i++) {
    obstacles[i].x = -5 - (i * 12);
    obstacles[i].height = random(2, 5);
    obstacles[i].flags = 0;
  }
  
  score = 0;
  gameSpeed = 120;
  gameState = 0;
}
