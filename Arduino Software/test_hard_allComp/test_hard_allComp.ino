/*  ---- Testar os componentes do Hardware em Conjunto ----
 * Autor: Matheus Dias
 * Início: 25/03/2018 
 * 
 * Last_Att: 07/11/2018
 * 
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


// ----- Emissor IR ----- //
#include <IRremote.h>
IRsend irsend;
void _emissor1();   // Para ligar o comando é: 'l'
void _emissor2();  // Para aumentar o volume é: 'u'
void _emissor3();  // Para diminuir o volume é: 'd'
const byte ir_1 = 8; //emissor 1
const byte ir_2 = 9;  //emissor 2
const byte ir_3 = 13; //emissor 3
int khz = 38; // 38kHz carrier frequency for the NEC protocol
// ----- Emissor IR ----- //

// ----- Recursos para utilizar o Bluetooth ----- //
#include <SoftwareSerial.h>
SoftwareSerial bluetooth = SoftwareSerial(10, 11); //Pino 10 como entrada RX do Arduíno e TX do HC-05, pino 11 como saída TX do Arduíno e RX do HC-05
String comandoBT_recebido;                            //Comando recebido via bluetooth;
//byte f_ModoOper, f_Ilum1, f_Ilum2, f_Ilum3, f_Central1, f_Central2, f_DataShow;

void receber_Bluetooth();       // Função para receber valores do Aplicativo via Bluetooth;
// ----- Recursos para utilizar o Bluetooth ----- //



// ----- Configurações para o RTC ----- //
#include <Wire.h>
#define DS1307 0x68     //Endereço I2C do RTC
byte sec;                    //Variável responsável por receber os Segundos
byte minu;                   //Variável responsável por receber os Minutos
byte hour;                   //Variável responsável por receber as Horas
byte weekday;                //Variável responsável por receber o Dia da Semana
byte monthday;               //Variável responsável por receber o Dia do Mês
byte month;                  //Variável responsável por receber o Mes
int year;                   //Variável responsável por receber o ano

byte zero = 0x00;

byte ConverteParaBCD(byte val);
byte ConverteparaDecimal(byte val);
void SelecionaDataeHora();
void _relogio();
// ----- Configurações para o RTC ----- //

// ----- Sensor de Tensão ----- //
int sensor_tensao_1 = A0;
int sensor_tensao_2 = A1;
int sensor_tensao_3 = A2;

bool _tensao1();
bool _tensao2();
bool _tensao3();
// ----- Sensor de Tensão ----- //

// ----- Sensor de Presença ----- //
const byte sensorPres = 2;
byte estadoSensor;
void _presenca();
// ----- Sensor de Presença ----- //

// ----- Relés ----- //
const byte lamp1 = 4;
const byte lamp2 = 5;
const byte lamp3 = 6;
const byte contatora = 7;
// ----- Relés ----- //

// ----- Fechadura ----- //
const byte fechadura = 12;
// ----- Fechadura ----- //






void setup(){

//---RTC
  Wire.begin();
//---RTC

//---Sensor de Presença
  pinMode(sensorPres, INPUT);             // Sensor de Presença na piodig2
//---Sensor de Presença

//---Emissor IR
  pinMode(ir_1, OUTPUT);
  pinMode(ir_2, OUTPUT);
  pinMode(ir_3, OUTPUT);
//---Emissor IR

// BLUETOOTH SETUP//
  pinMode(10, INPUT);           //Pino 10 como Entrada do arduíno - BlueTX e arduinoRX
  pinMode(11, OUTPUT);          //Pino 11 como Saída do arduíno - BlueRX e arduinoTX
  bluetooth.begin(9600);       //Iniciando a comunicação serial com o arduino e bluetooth;
// BLUETOOTH SETUP//

//---Sensor e Tensão
  pinMode(sensor_tensao_1, INPUT);
  pinMode(sensor_tensao_2, INPUT);
  pinMode(sensor_tensao_3, INPUT);
//---Sensor e Tensão

//---Relés
  pinMode(lamp1, OUTPUT);
  pinMode(lamp2, OUTPUT);
  pinMode(lamp3, OUTPUT);
  pinMode(contatora, OUTPUT);
//---Relés

//---Fechadura
  pinMode(fechadura, OUTPUT);
//---Fechadura
  


  Serial.begin(9600);
  
  //Descomentar a função abaixo para configurar a hora
  //SelecionaDataeHora();
}


void loop(){
  _serial();
  receber_Bluetooth();

}


void _serial(){
  if (Serial.available()){
      char recebido = Serial.read(); // lê o valor digitado e enviado pela serial monitor.
  
      if(recebido == 'q') _relogio();

      if(recebido == 'w') _presenca();

      if(recebido == 'e') _emissor1();
      if(recebido == 'r') _emissor2();
      if(recebido == 't') _emissor3();

      if(recebido == 'y'){ 
        if(_tensao1() == true){
          Serial.println("Sensor 1 = Tensao Detectada!");
        }
        else{
          Serial.println("Sensor 1 = Tensao Nao Detectada!");
        }
      }

      if(recebido == 'u'){ 
        if(_tensao2() == true){
          Serial.println("Sensor 2 = Tensao Detectada!");
        }
        else{
          Serial.println("Sensor 2 = Tensao Nao Detectada!");
        }
      }

      if(recebido == 'i'){ 
        if(_tensao3() == true){
          Serial.println("Sensor 3 = Tensao Detectada!");
        }
        else{
          Serial.println("Sensor 3 = Tensao Nao Detectada!");
        }
      }

      if(recebido == 'o') _lamp1();
      if(recebido == 'p') _lamp2();
      if(recebido == 'a') _lamp3();

      if(recebido == 's') _paralelo_lamp1();
      if(recebido == 'd') _paralelo_lamp2();
      if(recebido == 'f') _paralelo_lamp3();
      
      if(recebido == 'g') _contatora_1();
      if(recebido == 'h') _contatora_0();

      if(recebido == 'j') _fechadura();



      
     
  }
}

void receber_Bluetooth(){
   if (bluetooth.available() > 0) {
    char comandoBT = bluetooth.read();

    
    if( comandoBT == 'e'){
      _emissor1();
      bluetooth.println("Sinal IR 1 comandado por BT!");
      
    }

    if( comandoBT == 'r'){
      _emissor2();
      bluetooth.println("Sinal IR 2 comandado por BT!");
      
    }
    
    if( comandoBT == 't'){
      _emissor3();
      bluetooth.println("Sinal IR 3 comandado por BT!");
      
    }

    if( comandoBT == 'j'){
      _fechadura();
      bluetooth.println("Verifique se a porta esta aberta!");
    }
  }  
}//FIM-receber_Bluetooth();

void _relogio(){
  // Le os valores (data e hora) do modulo DS1307
  Wire.beginTransmission(DS1307);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 7);
  sec = ConverteparaDecimal(Wire.read());
  minu = ConverteparaDecimal(Wire.read());
  hour = ConverteparaDecimal(Wire.read() & 0b111111);
  weekday = ConverteparaDecimal(Wire.read());
  monthday = ConverteparaDecimal(Wire.read());
  month = ConverteparaDecimal(Wire.read());
  year = ConverteparaDecimal(Wire.read());

  
  Serial.println("");
  //Horas
  if(hour < 10){
    Serial.print("0");
  }
  Serial.print(hour);

  Serial.print(":");

  //Minutos
  if(minu < 10){
    Serial.print("0");
  }
  Serial.print(minu);
    
  Serial.print(":");

  //Segundos
  if(sec < 10){
    Serial.print("0");
  }
  Serial.print(sec);

  Serial.print("  ");

  //Dia da Semana
  switch(weekday){
    case 0:
    Serial.print("Domingo");
    break;

    case 1:
    Serial.print("Segunda");
    break;

    case 2:
    Serial.print("Terca");
    break;

    case 3:
    Serial.print("Quarta");
    break;

    case 4:
    Serial.print("Quinta");
    break;

    case 5:
    Serial.print("Sexta");
    break;

    case 6:
    Serial.print("Sabado");
    break;
  }

  Serial.print("  ");
  //Dia do Mês
  if(monthday < 10){
    Serial.print("0");
  }
  Serial.print(monthday);
    
  Serial.print("/");

  //Mês
  if(month < 10){
    Serial.print("0");
  }
  Serial.print(month);
    
  Serial.print("/");

  //Ano
  Serial.print(year);
  Serial.println();

}

void _presenca(){

  estadoSensor = digitalRead(sensorPres);
  if (estadoSensor == HIGH){
      Serial.println("Sensor de Presenca: Presenca Detectada!");
  }
    
  if (estadoSensor == LOW){
      Serial.println("Sensor de Presenca: Nada Detectado");
  }
}

void _emissor1(){
  digitalWrite(ir_1, 1);
  ligar();
  digitalWrite(ir_1, 0);
}

void _emissor2(){
  digitalWrite(ir_2, 1);
  aumentar_volume();
  digitalWrite(ir_2, 0);
    
}

void _emissor3(){
  digitalWrite(ir_3, 1);
  diminuir_volume();
  digitalWrite(ir_3, 0);
  
}

void ligar(){  
  
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0x20DF10EF, 32);
    delay(40);
  }
}//Fim_ligar_desligar();

void aumentar_volume(){  
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0x20DF40BF, 32);
    delay(40);
  }
}//Fim_aumentar_volume();

void diminuir_volume(){  
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0x20DFC03F, 32);
    delay(40);
  }
}//Fim_diminur_volume();



void SelecionaDataeHora(){   //Seta a data e a hora do DS1307

  byte segundos = 00; //Valores de 0 a 59
  byte minutos = 30; //Valores de 0 a 59
  byte horas = 04; //Valores de 0 a 23
  byte diadasemana = 2; //Valores de 0 a 6 - 0=Domingo, 1 = Segunda, etc.
  byte diadomes = 6; //Valores de 1 a 31
  byte mes = 11; //Valores de 1 a 12
  byte ano = 18; //Valores de 0 a 99
  Wire.beginTransmission(DS1307);
  Wire.write(zero); //Stop no CI para que o mesmo possa receber os dados

  //As linhas abaixo escrevem no CI os valores de
  //data e hora que foram colocados nas variaveis acima
  Wire.write(ConverteParaBCD(segundos));
  Wire.write(ConverteParaBCD(minutos));
  Wire.write(ConverteParaBCD(horas));
  Wire.write(ConverteParaBCD(diadasemana));
  Wire.write(ConverteParaBCD(diadomes));
  Wire.write(ConverteParaBCD(mes));
  Wire.write(ConverteParaBCD(ano));
  Wire.write(zero);
  Wire.endTransmission();
}

byte ConverteParaBCD(byte val)
{
  //Converte o número de decimal para BCD
  return ( (val/10*16) + (val%10) );
}

byte ConverteparaDecimal(byte val)
{
  //Converte de BCD para decimal
  return ( (val/16*10) + (val%16) );
}

String leStringSerial(){
  String conteudo = "";
  char caractere;
  
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
    
  Serial.print("Serial recebido: ");
  Serial.println(conteudo);
    
  return conteudo;
}

String leStringSerialbt(){
  String conteudo = "";
  char caractere;
  
  // Enquanto receber algo pela serial
  while(bluetooth.available() > 0) {
    // Lê byte da serial
    caractere = bluetooth.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
    
  Serial.print("comandoBT_recebido: ");
  Serial.println(conteudo);
    
  return conteudo;
}

bool _tensao1(){
  for(int i=1; i < 100; i++){
    if(analogRead(sensor_tensao_1) > 10){
      return true;
    }
  }
  return false;

}

bool _tensao2(){
  for(int i=1; i < 100; i++){
    if(analogRead(sensor_tensao_2) > 10){
      return true;
    }
  }
  return false;

}

bool _tensao3(){
  for(int i=1; i < 100; i++){
    if(analogRead(sensor_tensao_3) > 10){
      return true;
    }
  }
  return false;

}

void _lamp1(){
  digitalWrite(lamp1, 1);
  Serial.println("Rele1 Ligado!");
  delay(2000);
  digitalWrite(lamp1, 0);
  Serial.println("Rele1 Desligado!");

}

void _lamp2(){
  digitalWrite(lamp2, 1);
  Serial.println("Rele2 Ligado!");
  delay(2000);
  digitalWrite(lamp2, 0);
  Serial.println("Rele2 Desligado!");

}

void _lamp3(){
  digitalWrite(lamp3, 1);
  Serial.println("Rele3 Ligado!");
  delay(5000);
  digitalWrite(lamp3, 0);
  Serial.println("Rele3 Desligado!");

}

void _paralelo_lamp1(){
  digitalWrite(lamp1, !_tensao1());

}
void _paralelo_lamp2(){
  digitalWrite(lamp2, !_tensao2());
}
void _paralelo_lamp3(){
  digitalWrite(lamp3, !_tensao3());
}

void _contatora_1(){
  digitalWrite(contatora, 1);
}

void _contatora_0(){
  digitalWrite(contatora, 0);
}

void _fechadura(){
  digitalWrite(fechadura, 1);
  delay(20);
  digitalWrite(fechadura, 0);

}

/*

|| Aparelho   || Função    || Código     ||
------------------------------------------
|| TV LG CASA || On_Off    || 0x20DF10EF ||
|| TV LG CASA || Vol_Up    || 0x20DF40BF ||
|| TV LG CASA || Vol_Down  || 0x20DFC03F ||
|| TV LG CASA || Chan_Up   || 0x20DF00FF ||
|| TV LG CASA || Chan_Down || 0x20DF807F ||

*/
