# Projeto Semáforo com LEDs
Este repositório documenta a montagem e programação de um semáforo com LEDs em uma protoboard, incluindo o código, especificações dos componentes e os resultados dos testes.

---

## 1. Montagem Física

### Foto da Montagem
<div align="center">
<sub><a name="f"></a>Figura 1- circuito</sub>
<img src="..\PonderadaSemaforo\assets\circuito.jpg" width="100%">
<sup>Fonte: Material produzido pelos autores (2024)</sup>
</div>
<p> 

### Relato da Montagem
A montagem do semáforo foi feita conectando LEDs vermelho, amarelo e azul em uma protoboard. Cada LED foi conectado a um resistor para limitar a corrente e evitar danos ao LED e ao Arduino. Os LEDs foram então conectados aos pinos digitais do Arduino, com o LED vermelho no pino 6, o amarelo no pino 4, e o verde no pino 2.Além do mais foi conectado ao Arduino um servo que quando o semáforo acende a luz vermelha ele gira 90º. A programação controla os tempos de cada fase do semáforo para simular o funcionamento real.

---

## 2. Especificações dos Componentes

| Componente         | Especificação                 | Quantidade |
|--------------------|-------------------------------|------------|
| LED Vermelho       | 5mm, 2V                       | 1          |
| LED Amarelo        | 5mm, 2V                       | 1          |
| LED Azul          | 5mm, 2V                       | 1          |
| Resistor           | 220Ω                          | 3          |
| Protoboard         | 830 pontos                    | 1          |
| Fios Jumper        | Diversas Cores                | 9     |
| Microcontrolador   | Arduino Uno                   | 1          |
| MicroServo   |    MicroServo                | 1          |


---

## 3. Código de Programação

O código para o semáforo foi implementado em C++ e carrega no Arduino Uno. 

``` c++
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
```
---

## 4. Demonstração do Funcionamento

Veja abaixo o vídeo que demonstra o funcionamento do semáforo, com os LEDs acendendo e apagando conforme o código programado.

[Vídeo da Demonstração](https://youtu.be/YkOYKk8v-VI) 

---

## 5. Resultados dos Testes

### Avaliação das Fases do Semáforo
Os tempos de cada fase foram testados para garantir que estão de acordo com as especificações.

### Avaliador
**João Pedro Carbone**
| Critério                                                                                                   | Contempla (Pontos) | Contempla Parcialmente (Pontos) | Não Contempla (Pontos) | Observações do Avaliador                |
|-----------------------------------------------------------------------------------------------------------|---------------------|----------------------------------|-------------------------|----------------------------------------|
| Montagem física com cores corretas, boa disposição dos fios e uso adequado de resistores                  | Até 3              | Até 1,5                          | 0                    |                      3                  |
| Temporização adequada conforme tempos medidos com auxílio de algum instrumento externo                     | Até 3              | Até 1,5                          | 0                       |                 3                       |
| Código implementa corretamente as fases do semáforo e estrutura do código (variáveis representativas e comentários) | Até 3              | Até 1,5                          | 0                       |                   3                     |
| Ir além: Implementou um componente extra, fez com `millis()` ao invés do `delay()` e/ou usou ponteiros no código | Até 1              | Até 0,5                          | 0                       |       1                                 |
| **Pontuação Total**                                                                                       |                     |          10                        |                         |                                        |

---

