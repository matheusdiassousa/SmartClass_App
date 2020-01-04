/*  ---- MAPEAMENTO DAS ÁREAS DE MOVIMENTO DAS SALAS ----
 * Autor: Matheus Dias
 * Início: 31/03/2018 
 * Last_Att: 31/03/2018
 * Utilidade: Descobrir o melhor posicionamento para os sensores de presença. Salvando os dados em um cartão de memória.
 * Anotação: O código é uma adaptação do exemplo "CardInfo" presenta na IDE do Arduino
 *  utilizado para inicialização e informações do cartão SD. A adaptação contempla
 *  a escrita de dados no cartão.

 */

/*
boolean     8 bits    lógica true / false;
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

/*
Módulo SD Pin Map   -  Arduíno PIN
      CS    - digPin 4
      SCK   - digPin 13
      MOSI  - digPin 11
      MISO  - digPin 12
      VCC   - 5V
      GND   - GND

      SensorPIr1 - digPin 5
      SensorPIr2 - digPin 6
      SensorPIr2 - digPin 7
      SensorPIr2 - digPin 8
                  
*/



//-------------------- Configurações para o RTC ----- //
#include <Wire.h>
#define DS1307 0x68     //Endereço I2C do RTC
int sec;                    //Variável responsável por receber os Segundos
int minu;                   //Variável responsável por receber os Minutos
int hour;                   //Variável responsável por receber as Horas
int weekday;                //Variável responsável por receber o Dia da Semana
int monthday;               //Variável responsável por receber o Dia do Mês
int month;                  //Variável responsável por receber o Mes
int year;                   //Variável responsável por receber o ano

byte zero = 0x00;

byte ConverteParaBCD(byte val);
byte ConverteparaDecimal(byte val);
void verificar_relogio();
//-------------------- Configurações para o RTC ----- //


//-------------------- Configurações para o Módulo SD ----- //
#include <SPI.h>
#include <SD.h>

Sd2Card card;
SdVolume volume;
SdFile root;

File dataFile;

int chipSelect = 4;

void sdinfo();  //Função inicializada no setup para verificar a funcionalidade do modulo SD;
void sdprint(); //Função para imprimir os dados no arquivo txt do sd card;
//-------------------- Configurações para o Módulo SD ----- //


//-----------------------------------------------------SENSORES DE PRESENÇA ----------------//
byte sensorPres1 = 5;
byte sensorPres2 = 6;
byte sensorPres3 = 7;
byte sensorPres4 = 8;


byte estadosensor1;
byte estadosensor2;
byte estadosensor3;
byte estadosensor4;


byte flag_sensor1 = 0;
byte flag_sensor2 = 0;
byte flag_sensor3 = 0;
byte flag_sensor4 = 0;


byte sensor_n;




void verificasensores(); //Função para verificar se os sensores foram ativados;
//-----------------------------------------------------SENSORES DE PRESENÇA - END -----------//


void setup() {
  pinMode(sensorPres1, INPUT);
  pinMode(sensorPres2, INPUT);
  pinMode(sensorPres3, INPUT);
  pinMode(sensorPres4, INPUT);
  

  Serial.begin(9600);

  //-------------------------------------------------- RTC SETUP ----------------------//
  Wire.begin();
  //-------------------------------------------------- RTC SETUP ----------------------//

  //sdinfo(); //Verifica se a pinagem do módulo está correta e se há um cartão sd válido inserido.
  inicio_reinicio();
}


void loop() {
  verificasensores();
}


void verificasensores(){
    
//------------------------------------------------------ SENSOR PIR - 1
  estadosensor1 = digitalRead(sensorPres1);
  estadosensor2 = digitalRead(sensorPres2);
  estadosensor3 = digitalRead(sensorPres3);
  estadosensor4 = digitalRead(sensorPres4);


  if(estadosensor1 == 0 && flag_sensor1 == 1){
    flag_sensor1 = 0;
  }

  if(estadosensor1 == 1 && flag_sensor1 == 0){
    flag_sensor1 = 1;
    sensor_n = 1;
    verificar_relogio();
    sdprint();
  }

  //------------------------------------------------------ SENSOR PIR - 2

  if(estadosensor2 == 0 && flag_sensor2 == 1){
    flag_sensor2 = 0;
  }

  if(estadosensor2 == 1 && flag_sensor2 == 0){
    flag_sensor2 = 1;
    sensor_n = 2;
    verificar_relogio();
    sdprint();
  }

  //------------------------------------------------------ SENSOR PIR - 3

  if(estadosensor3 == 0 && flag_sensor3 == 1){
    flag_sensor3 = 0;
  }

  if(estadosensor3 == 1 && flag_sensor3 == 0){
    flag_sensor3 = 1;
    sensor_n = 3;
    verificar_relogio();
    sdprint();
  }

  //------------------------------------------------------ SENSOR PIR - 4

  if(estadosensor4 == 0 && flag_sensor4 == 1){
    flag_sensor4 = 0;
  }

  if(estadosensor4 == 1 && flag_sensor4 == 0){
    flag_sensor4 = 1;
    sensor_n = 4;
    verificar_relogio();
    sdprint();
  }

  
}


void sdprint(){

  String dataString = "";

  if(hour < 10){
    dataString += "0";
  }
  dataString += String(hour);

  dataString += ":";

  if(minu < 10){
    dataString += "0";
  }
  dataString += String(minu);

  dataString += ":";

  if(sec < 10){
    dataString += "0";
  }
  dataString += String(sec);

  dataString += " ";

  if(monthday < 10){
    dataString += "0";
  }
  dataString += String(monthday);

  dataString += "/";

  if(month < 10){
    dataString += "0";
  }
  dataString += String(month);

  dataString += "/";

  dataString += String(year);

  dataString += " ";

  switch(weekday){
    case 0:
    dataString += "Domingo";
    break;

    case 1:
    dataString += "Segunda";
    break;

    case 2:
    dataString += "Terça";
    break;

    case 3:
    dataString += "Quarta";
    break;

    case 4:
    dataString += "Quinta";
    break;

    case 5:
    dataString += "Sexta";
    break;

    case 6:
    dataString += "Sabado";
    break;
  }
  
  dataString += " ";

  switch(sensor_n){
    case 1:
    dataString += "Sensor 1";
    break;

    case 2:
    dataString += "Sensor 2";
    break;

    case 3:
    dataString += "Sensor 3";
    break;

    case 4:
    dataString += "Sensor 4";
    break;

    case 5:
    dataString += "Inicio ou Reinicio";
    break;
    
  }

  Serial.print("Realizando Escrita Normal SD Card...");

  if (!SD.begin(4)) {
    Serial.println("inicializacao falhou!");
    while (1);
  }
  Serial.println("Escrevendo...");
    
  dataFile = SD.open("movlog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);

  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("Error ao tentar abrir movlog.txt");
  }
}




void verificar_relogio(){
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


}

/*void SelecionaDataeHora(){   //Configura a data e a hora do DS1307

  byte segundos = 00; //Valores de 0 a 59
  byte minutos = 39; //Valores de 0 a 59
  byte horas = 18; //Valores de 0 a 23
  byte diadasemana = 1; //Valores de 0 a 6 - 0=Domingo, 1 = Segunda, etc.
  byte diadomes = 26; //Valores de 1 a 31
  byte mes = 3; //Valores de 1 a 12
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
}*/

byte ConverteParaBCD(byte val){
  //Converte o número de decimal para BCD
  return ( (val/10*16) + (val%10) );
}

byte ConverteparaDecimal(byte val){
  //Converte de BCD para decimal
  return ( (val/16*10) + (val%16) );
}


/*void sdinfo(){

  //-------------------------------------------------- INFORMAÇÕES SOBRE O CARTÃO SD -------//
  // Open serial communications and wait for port to open:

    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("\nIniciando o modulo SD...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("A Inicializacao falhou. Faca as seguintes checagens:");
    Serial.println("* Ha algum cartao sd inserido?");
    Serial.println("* As conexoes estao corretas?");
    Serial.println("* Voce mudou a pinagem do codigo para corresponder ao do modulo usado?");
    while (1);
  } else {
    Serial.println("A conexao esta correta e ha um cartao sd inserido!");
  }

  Serial.println("\nArquivos encontrados no cartao (nome, data e tamanho em bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
  //-------------------------------------------------- INFORMAÇÕES SOBRE O CARTÃO SD -------//

}
*/

void inicio_reinicio(){
  verificar_relogio();
    sensor_n = 5;
  sdprint();
}
