<!DOCTYPE html>
<html lang="pt-BR">
<head>
<meta charset="UTF-8" />
<meta name="viewport" content="width=device-width, initial-scale=1" />
</head>
<body>
  <h1>LED Jump Game 🎮</h1>
  
  <h2>Descrição ✨</h2>
  <p>
    O <strong>LED Jump Game</strong> é um jogo simples e divertido que utiliza uma matriz de LEDs WS2812B para criar uma experiência interativa. O jogador controla um personagem que deve pular sobre obstáculos que se aproximam. O objetivo é evitar colisões e acumular pontos ao passar pelos obstáculos.
  </p>

  <h2>Funcionalidades ⭐</h2>
  <ul>
    <li><strong>Controle do Jogador</strong>: O jogador pode pular pressionando um botão.</li>
    <li><strong>Obstáculos</strong>: Obstáculos aparecem na tela e se movem em direção ao jogador.</li>
    <li><strong>Pontuação</strong>: O jogador ganha pontos ao passar pelos obstáculos.</li>
    <li><strong>Game Over</strong>: O jogo termina se o jogador colidir com um obstáculo.</li>
    <li><strong>Aumento de Dificuldade</strong>: A velocidade do jogo aumenta conforme a pontuação incrementa.</li>
  </ul>

  <h2>Componentes Necessários 🛠️</h2>
  <ul>
    <li>1x Arduino (Uno, Nano, etc.)</li>
    <li>1x Matriz de LEDs WS2812B (30x20 LEDs)</li>
    <li>1x Botão</li>
    <li>1x Resistor de 10kΩ (para o botão)</li>
    <li>Fios de conexão</li>
    <li>Fonte de alimentação adequada para a matriz de LEDs</li>
  </ul>

  <h2>Instalação 🚀</h2>
  <ol>
    <li><strong>Configuração do Hardware</strong>:<br />
      Conecte a matriz de LEDs ao Arduino conforme:
      <ul>
        <li><strong>Data Pin</strong>: Pino <strong>6</strong> do Arduino</li>
        <li><strong>VCC</strong>: 5V da fonte de alimentação</li>
        <li><strong>GND</strong>: Terra comum entre Arduino e fonte</li>
      </ul>
      Conecte o botão ao pino <strong>2</strong> do Arduino, com resistor pull-up interno.
    </li>
    <li><strong>Instale a Biblioteca FastLED</strong>:<br />
      No Arduino IDE: <em>Sketch &gt; Incluir Biblioteca &gt; Gerenciar Bibliotecas</em>. Procure por <code>FastLED</code> e instale.
    </li>
    <li><strong>Carregue o Código</strong>:<br />
      Copie o código fonte para o Arduino IDE, conecte o Arduino, selecione a porta correta e clique em <em>Carregar</em>.
    </li>
  </ol>

  <h2>Como Jogar 🎯</h2>
  <p>
    - Pressione o botão para fazer o personagem pular.<br />
    - Evite os obstáculos que se aproximam.<br />
    - Acumule pontos ao passar pelos obstáculos.<br />
    - O jogo termina ao colidir com um obstáculo; pressione o botão para reiniciar.
  </p>

  <h2>Estrutura do Código 📚</h2>
  <ul>
    <li><strong>Definições de Hardware</strong>: Configura o pino de dados dos LEDs, botão, brilho e dimensões da matriz.</li>
    <li><strong>Variáveis do Jogo</strong>: Controle da posição do jogador, obstáculos, pontuação e estado atual.</li>
    <li><strong>Funções Principais</strong>:
      <ul>
        <li><code>setup()</code> - Inicializa o hardware e configura o estado inicial.</li>
        <li><code>loop()</code> - Executa a lógica de movimento, colisões e atualizações do jogo.</li>
        <li><code>renderGame()</code> - Desenha o estado do jogo na matriz de LEDs.</li>
        <li><code>resetGame()</code> - Reinicia o jogo após o fim.</li>
      </ul>
    </li>
  </ul>

  <h2>Contribuições 🤝</h2>
  <p>
    Sinta-se livre para contribuir com melhorias, correções ou novas funcionalidades.<br />
    Faça um fork deste projeto, envie suas modificações e abra um pull request!
  </p>

  <h2>Licença 📜</h2>
  <p>
    Este projeto está licenciado sob a <a href="https://opensource.org/licenses/MIT" target="_blank" rel="noopener noreferrer">MIT License</a>.
  </p>

  <footer>
    &copy; 2024 LED Jump Game project. Desenvolvido com dedicação e paixão por jogos eletrônicos e LEDs.
  </footer>
</body>
</html>
