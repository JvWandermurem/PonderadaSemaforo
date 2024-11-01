#include <Servo.h>

const int vermelho = 6; // Pino do LED vermelho
const int amarelo = 4;  // Pino do LED amarelo
const int verde = 2;    // Pino do LED verde
const int servoPin = 9;

unsigned long tempoVermelho = 5000; // Tempo que o LED vermelho permanece ligado (em milissegundos)
unsigned long tempoAmarelo = 2000;  // Tempo que o LED amarelo permanece ligado
unsigned long tempoVerde = 4000;    // Tempo que o LED verde permanece ligado

unsigned long tempoAnterior = 0; // Armazena o tempo em que o estado mudou
int estado = 0; // Estado atual da máquina: 0 - vermelho, 1 - amarelo (antes do verde), 2 - verde, 3 - amarelo (após o verde)
Servo meuServo;

void setup()
{
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  
  meuServo.attach(servoPin); // Conecta o servo ao pino definido
  meuServo.write(0);     
  
  // Inicia com o LED vermelho ligado e os outros desligados
  digitalWrite(vermelho, HIGH);
  digitalWrite(amarelo, LOW);
  digitalWrite(verde, LOW);
  
  tempoAnterior = millis(); // Armazena o tempo inicial
}

void loop()
{
  unsigned long tempoAtual = millis(); // Obtém o tempo atual

  switch(estado) {
    case 0: // Estado do LED vermelho
      if (tempoAtual - tempoAnterior >= tempoVermelho) {
        // Transição para o estado amarelo (antes do verde)
        digitalWrite(vermelho, LOW);   // Desliga o vermelho
        digitalWrite(amarelo, HIGH);   // Liga o amarelo
         meuServo.write(0); 
        tempoAnterior = tempoAtual;    // Atualiza o tempo da transição
        estado = 1;                    // Muda para o estado amarelo (antes do verde)
      }else {
        meuServo.write(90);            // Gira o servo para 90 graus enquanto está no vermelho
      }
      break;
      
    case 1: // Estado do LED amarelo (antes do verde)
      if (tempoAtual - tempoAnterior >= tempoAmarelo) {
        // Transição para o estado verde
        digitalWrite(amarelo, LOW);    // Desliga o amarelo
        digitalWrite(verde, HIGH);     // Liga o verde
        tempoAnterior = tempoAtual;    // Atualiza o tempo da transição
        estado = 2;                    // Muda para o estado verde
      }
      break;
      
    case 2: // Estado do LED verde
      if (tempoAtual - tempoAnterior >= tempoVerde) {
        // Transição para o estado amarelo (após o verde)
        digitalWrite(verde, LOW);      // Desliga o verde
        digitalWrite(amarelo, HIGH);   // Liga o amarelo
        tempoAnterior = tempoAtual;    
        estado = 3;
    }                    
      break;
  
    case 3: // Estado do LED amarelo (após o verde)
      if (tempoAtual - tempoAnterior >= tempoAmarelo) {
        // Transição para o estado vermelho
        digitalWrite(amarelo, LOW);      // Desliga o amarelo
        digitalWrite(vermelho, HIGH);    // Liga o vermelho
        tempoAnterior = tempoAtual;      // Atualiza o tempo da transição
        estado = 0;                      // Volta para o estado vermelho
    }
      break;
  }
}