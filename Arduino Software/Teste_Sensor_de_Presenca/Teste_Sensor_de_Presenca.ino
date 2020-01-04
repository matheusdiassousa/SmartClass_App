/*  -- VERIFICAR ATIVIDADE HUMANA --
 *  Autor: Matheus Dias
 * Início: 07/02/2018 
 * Last_Att: 25/02/2018
 * Utilidade: Lógica de verificação de estados de um sensor de presença
 * utilizando interrupt.
 */

/*
boolean      8 bits    lógica true / false;
byte        8 bits    número sem sinal 0 a 255;
char        8 bits    número com sinal de -128 a 127;
unsigned char 8 bits    o mesmo que 'byte';
word      16 bits   número sem sinal 0 a 65535;
int       16 bits   número com sinal de -32768 a 32767;
unsigned int  16 bits   o mesmo que "word";
long      32 bits   número com sinal de -2.147.483.648 a 2.147.483.647;
unsigned long 32 bits   número sem sinal de 0 a 4,294,967,295;
float     32 bits   número com sinal de -3.4028235E38 para 3.4028235E38.
*/

byte sensorPres = 2;
const byte led13 = 13;
bool estadoSensor;

void setup() {
  pinMode(sensorPres, INPUT);             // Lógica PullUP - Input -> High (digRead = 0);
  pinMode(13, OUTPUT);                  // Sinal de saída para o resultado da verificação de presença.
  Serial.begin(9600);
  
}//end_setup()

void loop() {
  estadoSensor = digitalRead(sensorPres);
  if (estadoSensor == HIGH){
    digitalWrite(13, estadoSensor);
    Serial.println("Presenca Detectada!");
    }
    
  if (estadoSensor == LOW){
      Serial.println("--------------");
      digitalWrite(13, estadoSensor);
  }
}
