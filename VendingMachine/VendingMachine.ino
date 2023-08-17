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

// defines
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
#define BUTTON_X 32
#define BUTTON_Y 47
#define BUTTON_Z 45
#define BUTTON_W 43
#define BUTTON_Card 41

// GPIOs para controle dos LEDs
#define LED_X 39
#define LED_Y 37
#define LED_Z 35
#define LED_W 33
#define LED_Card 31

// Tempo Entre Passos
int millisBtwnSteps = 9000; 
const int stepsPerRev=200;
int pulseWidthMicros = 800;
int i = 0;

// Variáveis gerais
int timer = 0;
bool pressed = false;
bool card = false;

// functions
bool waitCard(){
  // Espera a leitura do botão  
  timer = 0;
  pressed = false;
  
  digitalWrite(LED_Card, HIGH);

  while(timer < 15000){
    delay(1);
    timer += 1;
    if(digitalRead(BUTTON_Card) == 1){
      pressed = true;
      break; // revisar, sair do while
    }
  }
  digitalWrite(LED_Card, LOW);
  return pressed;
}

void button(int direc, int step , int enable, int led){
 
    digitalWrite(led, HIGH);
 
    card = false;
    card = waitCard();

    if(card == true){
      girar(direc, step, enable);
    }
    card = false;
    digitalWrite(led, LOW);
}

void girar(int direc, int step, int enable){
  digitalWrite(enable, LOW);

  delayMicroseconds(50);
  digitalWrite(direc, HIGH); // Enables the motor to move in a particular direction
  for (int i = 0; i < stepsPerRev; i++) {
    digitalWrite(step, HIGH);
    delayMicroseconds(pulseWidthMicros);
    digitalWrite(step, LOW);
    delayMicroseconds(millisBtwnSteps);
  }
  delayMicroseconds(50);
  digitalWrite(enable, HIGH);
}

/**
int millisBtwnSteps = 1000; 
const int stepsPerRev=200;
int pulseWidthMicros = 800;
int i = 0;
*/


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

  digitalWrite(LED_X, LOW);
  digitalWrite(LED_Y, LOW);
  digitalWrite(LED_Z, LOW);
  digitalWrite(LED_W, LOW);
  digitalWrite(LED_Card, LOW);

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



// Para debug
int x = 0;
int y = 0;
int z = 0;
int w = 0;
int c = 0;

void loop() {


if(digitalRead(BUTTON_X) == 1){
  button(X_dir,X_step, X_enable, LED_X);
}

if(digitalRead(BUTTON_Y) == 1){
  button(Y_dir,Y_step, Y_enable, LED_Y);
}

if(digitalRead(BUTTON_Z) == 1){
  button(Z_dir,Z_step, Z_enable, LED_Z);
}

if(digitalRead(BUTTON_W) == 1){
  button(W_dir,W_step, W_enable, LED_W);
}

delay(1);

}