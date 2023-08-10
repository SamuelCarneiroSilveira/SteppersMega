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
#define X_step 5
#define X_dir 5
#define Y_step 5
#define Y_dir 5
#define Z_step 5
#define Z_dir 5
#define W_step 5
#define W_dir 5

#define enable 8

// GPIOs para controle dos botões
#define BUTTON_X 5
#define BUTTON_Y 5
#define BUTTON_Z 5
#define BUTTON_W 5
#define BUTTON_Card 5

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
bool pressed = false;
bool card = false;

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

void setup() {
  Serial.begin(9600);
  pinMode(enable, OUTPUT);
  pinMode(X_step, OUTPUT);
  pinMode(X_dir, OUTPUT);
  pinMode(Y_step, OUTPUT);
  pinMode(Y_dir, OUTPUT);
  pinMode(Z_step, OUTPUT);
  pinMode(Z_dir, OUTPUT);
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

  digitalWrite(enable, LOW);
}

void loop() {
  // DIGITAL E ANALOG vai depender dos pinos selecionados  

  // Para Debu
  if(analogRead(BUTTON_X) >= 1022){  
    Serial.println(analogRead(BUTTON_X));
  }
  if(analogRead(BUTTON_Y) >= 1022){  
    Serial.println(analogRead(BUTTON_Y));
  }
  if(analogRead(BUTTON_Z) >= 1022){  
    Serial.println(analogRead(BUTTON_Z));
  }
  if(analogRead(BUTTON_W) >= 1022){  
    Serial.println(analogRead(BUTTON_W));
  }
  if(analogRead(BUTTON_Card) >= 1022){  
    Serial.println(analogRead(BUTTON_Card));
  }
/**
  // Ouvir o botão, replicar 

  if(analogRead(BUTTON_X) >= 1022){
    digitalWrite(LED_X, HIGH);
    card = waitCard(); 

    if(card == true){
      girar(X_dir, X_step);
      digitalWrite(LED_X, LOW);
      card = false;
    }

  }
*/
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
