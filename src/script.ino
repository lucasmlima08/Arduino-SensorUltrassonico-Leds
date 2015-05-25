/* Sensor ultrasônico + Display 7 segmentos + Display LCD. */

#include <LiquidCrystal.h> // carrega a biblioteca do display LCD.
#include <Ultrasonic.h>

// Definições do display LCD.
const int Luz_Fundo = 4;
LiquidCrystal lcd(14, 15, 16, 17, 18, 19);

// Definições do sensor ultrassônico.
const int pinoEcho = 11;
const int pinoTrig = 10;
Ultrasonic ultrasonic(10, 11);

// Definições do display de 7 segmentos.
const int pinoPonto = 9;

// Mensagens do display.
String mensagem_1[11] = {"Totalmente", "Inseguro", "Quase", "Parcialmente", "Alvo Em", "Alvo Em", "Alvo Em", "Parcialmente", "Seguro", "Totalmente", "Sem Alvo"};
String mensagem_2[10] = {"Inseguro", "", "Inseguro", "Inseguro", "Observacao", "Observacao", "Observacao", "Seguro", "", "Seguro"};

// Tabela de bits para segmentos do display de 7 segmentos.
byte segmentos[10][7] = {{ 1, 1, 1, 1, 1, 1, 0 }, // = Digito 0
                         { 0, 1, 1, 0, 0, 0, 0 }, // = Digito 1
                         { 1, 1, 0, 1, 1, 0, 1 }, // = Digito 2
                         { 1, 1, 1, 1, 0, 0, 1 }, // = Digito 3
                         { 0, 1, 1, 0, 0, 1, 1 }, // = Digito 4
                         { 1, 0, 1, 1, 0, 1, 1 }, // = Digito 5
                         { 1, 0, 1, 1, 1, 1, 1 }, // = Digito 6
                         { 1, 1, 1, 0, 0, 0, 0 }, // = Digito 7
                         { 1, 1, 1, 1, 1, 1, 1 }, // = Digito 8
                         { 1, 1, 1, 0, 0, 1, 1 }, // = Digito 9
};

void setup(){

  Serial.begin(9600);

  // Pinos do display LCD.
  lcd.begin(16, 2); // informa o tamanho do display.
  pinMode(Luz_Fundo, OUTPUT); // define este como pino de saida.
  digitalWrite(Luz_Fundo, HIGH); // libera energia para acender o display.

  // Pinos do sensor ultrasônico
  pinMode(pinoEcho, INPUT);
  pinMode(pinoTrig, OUTPUT);

  // Pinos do display de 7 segmentos.
  for (int acm = 2; acm <= 9; acm++)
    pinMode(acm, OUTPUT);

}

String mensagemAux = "";

void controleDisplays(int numero){
  
  if (numero > 9){ // Sem alvo na distância de monitoramento.
    // Impressão do LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(mensagem_1[10]);
    // Chama função de escrita na serial.
    escritaSerial(mensagem_1[10]);
    // Animação do ponto no display de 7 segmentos.
    apagarDigito();
    digitalWrite(pinoPonto, HIGH);
    delay(500);
    digitalWrite(pinoPonto, LOW);
  
  } else if (numero <= 9) { // Alvo encontrado na distância de monitoramento.
    // Libera energia para segmentos do display de 7 segmentos.
    acenderSegmentos(numero);
    // Impressão do LCD.
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(mensagem_1[numero]);
    lcd.setCursor(0, 1);
    lcd.print(mensagem_2[numero]);
    // Chama função de escrita na serial.
    mensagemAux = mensagem_1[numero] + " " + mensagem_2[numero];
    escritaSerial(mensagemAux);
  }
}

void acenderSegmentos(int numero){
  // Acende os segmentos a partir da tabela.
  for (byte acm = 0; acm < 7; acm++)
    digitalWrite(acm + 2, segmentos[numero][acm]);
}

void apagarDigito(){
  // Apaga todos os segmentos.
  for (byte acm = 0; acm < 7; acm++)
    digitalWrite(acm + 2, LOW);
}

String mensagemAtual = "";

void escritaSerial(String mensagem){
  // Escreve na serial a mensagem se for alterada.
  if (mensagemAtual != mensagem){
    mensagemAtual = mensagem;
    Serial.print(mensagemAtual);
    Serial.println();
  }
}

void definir(int valCentimetros){
  // Conversão de valores.
  int resto = valCentimetros % 20;
  int valor = (valCentimetros - resto) / 20;
  // Chama a função de controle dos displays.
  controleDisplays(valor);
}

void loop(){
  // Lê a distância em centímetros
  int cm = ultrasonic.Ranging(CM);
  // Chama a função de conversão de segurança.
  definir(cm);
  // Espera 500 microssegundos.
  delay(500);
}
