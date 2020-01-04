/*  ---- VERIFICAR A PRESENÇA DE PESSOAS ----
 * Autor: Matheus Dias
 * Início: 25/03/2018 
 * 
 * Last_Att: 25/03/2018
 * Utilidade: Testar o DS1307;
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

// ----- Configurações para o RTC ----- //
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
void SelecionaDataeHora();
// ----- Configurações para o RTC ----- //

byte tomada1 = 7;

void setup(){
  pinMode(tomada1, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  
  //A linha abaixo pode ser retirada apos setar a data e hora
  //SelecionaDataeHora();
}


void loop(){

  if (Serial.available()){
      char cmd = Serial.read(); // lê o valor digitado e enviado pela serial monitor.
  
      if (cmd == 'l'){
        Serial.println();
        Serial.println("Ligar");
        Serial.println();
        digitalWrite(tomada1, HIGH);
        cmd = 0;
      }
      if (cmd == 'd'){
        Serial.println();
        Serial.println("Desligar");
        Serial.println();
        
        digitalWrite(tomada1, LOW);
        cmd = 0;
      }
      
      
     
  }
  
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
    Serial.print("Terça");
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

  delay(1000);
    
    
}

void SelecionaDataeHora()   //Seta a data e a hora do DS1307
{
  byte segundos = 00; //Valores de 0 a 59
  byte minutos = 26; //Valores de 0 a 59
  byte horas = 01; //Valores de 0 a 23
  byte diadasemana = 4; //Valores de 0 a 6 - 0=Domingo, 1 = Segunda, etc.
  byte diadomes = 1; //Valores de 1 a 31
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


