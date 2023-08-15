/**
 *      Vending Machine V0.0
 * 
 *  Hardware: A máquina terá 5 botões e 4 motores de passo nema 17 controlados por um arduino
 *  Mega com um shield CNC e 4 drivers. 
 * 
 *  Requisição: Quando um dos botoes de motor for apertado, o led do motor será aceso, e 
 *  entrará em uma função que acende(pisca?) o led do cartão aguarda por 15 seg o aperto 
 *  do botão do cartão, caso seja apertado, o motor selecionado gira 360, os leds apagam
 *  e o sistema volta a aguardar o botão inicial.
 * 
 *  Tratamento de erros: Caso aperte um botão na hora errada a maquina não responde
 * 
*/

#include <arduino.h>

// Definir Portas

// GPIOs para controle dos Steppers e da shield
#define X_step 54
#define X_dir 55
#define X_enable 38
#define Y_step 60
#define Y_dir 61
#define Y_enable 56
#define Z_step 46
#define Z_dir 48
#define Z_enable 62
#define W_step 26
#define W_dir 28
#define W_enable 24

// GPIOs para controle dos botões
#define BUTTON_X 16
#define BUTTON_Y 17
#define BUTTON_Z 23
#define BUTTON_W 25
#define BUTTON_Card 27

// GPIOs para controle dos LEDs
#define LED_X 5
#define LED_Y 5
#define LED_Z 5
#define LED_W 5
#define LED_Card 5

// Tempo Entre Passos
int millisBtwnSteps = 1000; 
const int stepsPerRev=200;
int pulseWidthMicros = 800;
int i = 0;

// Variáveis gerais
int timer = 0;
void butaum();
void girar();
bool pressed = false;
bool card = false;

void setup() {
  Serial.begin(9600);
  pinMode(X_enable, OUTPUT);
  pinMode(X_step, OUTPUT);
  pinMode(X_dir, OUTPUT);
  pinMode(Y_enable, OUTPUT);
  pinMode(Y_step, OUTPUT);
  pinMode(Y_dir, OUTPUT);
  pinMode(Z_enable, OUTPUT);
  pinMode(Z_step, OUTPUT);
  pinMode(Z_dir, OUTPUT);
  pinMode(W_enable, OUTPUT);
  pinMode(W_dir, OUTPUT);
  pinMode(W_step, OUTPUT);
  
  pinMode(LED_X, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_Z, OUTPUT);
  pinMode(LED_W, OUTPUT);
  pinMode(LED_Card, OUTPUT);

  pinMode(LED_X, LOW);
  pinMode(LED_Y, LOW);
  pinMode(LED_Z, LOW);
  pinMode(LED_W, LOW);
  pinMode(LED_Card, LOW);

  pinMode(BUTTON_X, INPUT);
  pinMode(BUTTON_Y, INPUT);
  pinMode(BUTTON_Z, INPUT);
  pinMode(BUTTON_W, INPUT);
  pinMode(BUTTON_Card, INPUT);

  digitalWrite(X_enable, LOW);
  digitalWrite(Y_enable, LOW);
  digitalWrite(Z_enable, LOW);
  digitalWrite(W_enable, LOW);
}

bool waitCard(){
  // Espera a leitura do botão  
  timer = 0;
  pressed = false;
  
  digitalWrite(LED_Card, HIGH);

  while(timer < 15000){
    delay(1);
    timer += 1;
    if(analogRead(BUTTON_Card) >= 1023){
      pressed = true;
      exit; // revisar, sair do while
    }
  }

  digitalWrite(LED_Card, LOW);
  return pressed;
}

void girar(int direc, int step){
  delayMicroseconds(50);
  digitalWrite(direc, HIGH); // Enables the motor to move in a particular direction
  for (int i = 0; i < stepsPerRev; i++) {
    digitalWrite(step, HIGH);
    delayMicroseconds(pulseWidthMicros);
    digitalWrite(step, LOW);
    delayMicroseconds(millisBtwnSteps);
  }
  delayMicroseconds(50);
}

void butaum(int direc, int step, int led){
    digitalWrite(led, HIGH);
    card = waitCard();

    if(card == true){
      girar(direc, step);
      digitalWrite(led, LOW);
    card = false;
  }
}

void loop() {
  // DIGITAL E ANALOG vai depender dos pinos selecionados  

  // Para Debu

  if(analogRead(BUTTON_X) >= 1022){  
    Serial.println(analogRead(BUTTON_X));
    butaum(X_dir, X_step, LED_X);
  }
  if(analogRead(BUTTON_Y) >= 1022){  
    Serial.println(analogRead(BUTTON_Y));
    butaum(Y_dir, Y_step, LED_Y);
  }
  if(analogRead(BUTTON_Z) >= 1022){  
    Serial.println(analogRead(BUTTON_Z));
    butaum(Z_dir, Z_step, LED_Z);
  }
  if(analogRead(BUTTON_W) >= 1022){  
    Serial.println(analogRead(BUTTON_W));
    butaum(W_dir, W_step, LED_W);
  }

  // Ouvir o botão, replicar 
}