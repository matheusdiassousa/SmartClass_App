/*  ---- VERIFICAR A PRESENÇA DE PESSOAS ----
 * Autor: Matheus Dias
 * Início: 14/02/2018 
 * Last_Att: 09/09/2018
 * Utilidade: Verificar se há presença de pessoas em um ambiente equipado com PIR, utiliza o RTC como parametro de relógio;
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
SoftwareSerial bluetooth = SoftwareSerial(10, 11); // Pino 10 como entrada RX do Arduíno e TX do HC-05, pino 11 como saída TX do Arduíno e RX do HC-05
String comandoBT_recebido;                         // Comando recebido via bluetooth;
String _leStringSerial();                           // Função para ler uma palavra ou frase via serial
void _enviar_Bluetooth();                           // Função para enviar valores para o Aplicativo via Bluetooth;
void _receber_Bluetooth();                          // Função para receber valores do Aplicativo via Bluetooth;
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

byte _ConverteParaBCD(byte val);
byte _ConverteparaDecimal(byte val);
void _SelecionaDataeHora();
void _relogio();
void _relogioBT();
// ----- Configurações para o RTC ----- //


// ----- Sensor de Tensão ----- //
int sensor_tensao_1 = A0;
int sensor_tensao_2 = A1;
int sensor_tensao_3 = A2;

bool _tensao1();
bool _tensao2();
bool _tensao3();
// ----- Sensor de Tensão ----- //





//--- Verificar a Presença de Pessoas ---//
void _presenca();      // Função para setar a flag de detecção de movimento humano;
#define sensorPres 2      // Sensor de presença conectado ao pino Dig_2;
byte estado_sensor;
byte flag_presenca = 0;         // Flag responsável por guardar o valor de status OUT do PIR;
byte flag_controle = 1;         // ajustada no setup;
byte flag_presenca_efetiva;
byte minuto_entrada;
byte hora_entrada_ligar;
byte minuto_entrada_ligar;
//--- Verificar a Presença de Pessoas ---//

// ----- Relés ----- //
const byte lamp1 = 4;
const byte lamp2 = 5;
const byte lamp3 = 6;
const byte contatora = 7;
// ----- Relés ----- //



//--- Controle de Acesso ---//
void _porta();         // Função utilizada para enviar um pulso no fecho eletromagnético (Dig_12);
#define fechadura 12                 // fechadura controlada pelo pino Dig_12;
//--- Controle de Acesso ---//




//--- Natureza do Sistema ---//
void _natureza(); // Função responsável por ligar ou desligar os periféricos automaticamente, em função da presnça de pessoas
//--- Natureza do Sistema ---//


//void _inicio_ou_reinicio();      // Função chamada ao iniciar ou reiniciar o sistema;
//void _modo_Operacao();           // Função responsável por verificar modo Manual ou Automático;


//void _configurar_Relogio();      // Configurar a hora do RTC, caso esteja errada;
//void _verificar_Relogio();       // Função para verificar o Tempo;

void _escrita_Eeprom();          // Função para escrever estados na eeprom;
void _leitura_Eeprom();          // Função para ler estados na eeprom;

//void sensor_Tensao();           // Função para verificar as tensões nos aparelhos, se estão ligados ou desligados;





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
    


    //Serial.begin(9600);
    
    //Descomentar a função abaixo para configurar a hora
    //SelecionaDataeHora();

    //-- Verificação de Presença de Pessoas --//
    flag_presenca_efetiva = 0;
    //_natureza();
    flag_controle = 1;  // Avisando ao sistema que ele está sem presença de pessoas, esperando alguém aparecer;
    //-- Verificação de Presença de Pessoas --//

}

void loop(){
  _receber_Bluetooth();
  _relogio();
  //_presenca();

}

void _receber_Bluetooth(){
  if (bluetooth.available() > 0) {
    char comandoBT = bluetooth.read();

    

    //--------------------------------------------------------------
    if( comandoBT == 'q'){
      _porta();
      bluetooth.println("Verifique se porta foi destravada!");
    }

    if( comandoBT == 'w'){
      _ligards();
      //bluetooth.println("Verifique se porta foi destravada!");
    }

    if( comandoBT == 'e'){
      _paralelo_lamp1();
      //bluetooth.println("Verifique se porta foi destravada!");
    }
    if( comandoBT == 'r'){
      _paralelo_lamp2();
     //bluetooth.println("Verifique se porta foi destravada!");
    }
    if( comandoBT == 't'){
      _paralelo_lamp3();
      //bluetooth.println("Verifique se porta foi destravada!");
    }    

    if( comandoBT == 'y'){
      _ligarC1();
      //bluetooth.println("Verifique se porta foi destravada!");
    }

    if( comandoBT == 'u'){
      _desligarC1();
      //bluetooth.println("Verifique se porta foi destravada!");
    }
    
    if( comandoBT == 'i'){
      _temp17C1();
      //bluetooth.println("Verifique se porta foi destravada!");
    }

    if( comandoBT == 'o'){
      _temp18C1();
      //bluetooth.println("Verifique se porta foi destravada!");
    }

    if( comandoBT == 'p'){
      _temp19C1();
      //bluetooth.println("Verifique se porta foi destravada!");
    }

    if( comandoBT == 'a'){
      _temp20C1();
      //bluetooth.println("Verifique se porta foi destravada!");
    }

    if( comandoBT == 's'){
      _temp21C1();
      //bluetooth.println("Verifique se porta foi destravada!");
    }

    if( comandoBT == 'd'){
      _temp22C1();
      //bluetooth.println("Verifique se porta foi destravada!");
    }

    if( comandoBT == 'f'){
      _temp23C1();
      //bluetooth.println("Verifique se porta foi destravada!");
    }    

    if( comandoBT == 'g'){
      _temp24C1();
      //bluetooth.println("Verifique se porta foi destravada!");
    }

    if( comandoBT == 'h'){
      _ligarC2();
      //bluetooth.println("Verifique se porta foi destravada!");
    }

    if( comandoBT == 'j'){
      _desligarC2();
      //bluetooth.println("Verifique se porta foi destravada!");
    }

    if( comandoBT == 'k'){
      _temp18C2();
      //bluetooth.println("Verifique se porta foi destravada!");
    }    





  //--------------------------------------------------------------

  }//FIM-receber_Bluetooth();
}

//-------------------------------------------------------------- Modo de Operação ---//
//void inicio_ou_reinicio(){

//}
//-------------------------------------------------------------- Modo de Operação - FIM ---//


//-------------------------------------------------------------- RTC ---//
void _SelecionaDataeHora(){
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
  Wire.write(_ConverteParaBCD(segundos));
  Wire.write(_ConverteParaBCD(minutos));
  Wire.write(_ConverteParaBCD(horas));
  Wire.write(_ConverteParaBCD(diadasemana));
  Wire.write(_ConverteParaBCD(diadomes));
  Wire.write(_ConverteParaBCD(mes));
  Wire.write(_ConverteParaBCD(ano));
  Wire.write(zero);
  Wire.endTransmission();
}

void _relogio(){
  Wire.beginTransmission(DS1307);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 7);
  sec = _ConverteparaDecimal(Wire.read());
  minu = _ConverteparaDecimal(Wire.read());
  hour = _ConverteparaDecimal(Wire.read() & 0b111111);
  weekday = _ConverteparaDecimal(Wire.read());
  monthday = _ConverteparaDecimal(Wire.read());
  month = _ConverteparaDecimal(Wire.read());
  year = _ConverteparaDecimal(Wire.read());
   // Mostra a Data na Serial Monitor
    // Acrescenta um 0 se a hora for menor do que 10
    /*
    Serial.println(""); 
    if (hour <10){
      Serial.print("0");
    }
    Serial.print(hour);
    Serial.print(":");
    // Acrescenta um 0 se o minuto for menor do que 10
    if (min < 10){
      Serial.print("0");
    }
    Serial.print(min);
    Serial.print(":");
    //Acrescenta um 0 se o segundo for menor do que 10
    if (sec <10){
      Serial.print("0");
    }
    Serial.print(sec);

    // Mostra o dia da semana
    switch(weekday)
      {
        case 0:Serial.print(" Domingo");
        break;
        case 1:Serial.print(" Segunda");
        break;
        case 2:Serial.print(" Terça");
        break;
        case 3:Serial.print(" Quarta");
        break;
        case 4:Serial.print(" Quinta");
        break;
        case 5:Serial.print(" Sexta");
        break;
        case 6:Serial.print(" Sábado");
      }
    // Acrescenta um 0 se o dia do mes for menor do que 10
    if (monthday < 10){
      Serial.print(" 0");
    }
    Serial.print(monthday);
    Serial.print("/");
    // Acrescenta um 0 se mes o for menor do que 10
    if (month < 10){
      Serial.print("0");
    }
    Serial.print(month);
    Serial.print("/");
    Serial.print(year);
    */
}

void _relogioBT(){
    bluetooth.println(""); 
    if (hour <10){
      bluetooth.print("0");
    }
    bluetooth.print(hour);
    bluetooth.print(":");
    // Acrescenta um 0 se o minuto for menor do que 10
    if (minu < 10){
      bluetooth.print("0");
    }
    bluetooth.print(minu);
    bluetooth.print(":");
    //Acrescenta um 0 se o segundo for menor do que 10
    if (sec <10){
      bluetooth.print("0");
    }
    bluetooth.print(sec);

    // Mostra o dia da semana
    switch(weekday)
      {
        case 0:bluetooth.print(" Domingo");
        break;
        case 1:bluetooth.print(" Segunda");
        break;
        case 2:bluetooth.print(" Terça");
        break;
        case 3:bluetooth.print(" Quarta");
        break;
        case 4:bluetooth.print(" Quinta");
        break;
        case 5:bluetooth.print(" Sexta");
        break;
        case 6:bluetooth.print(" Sábado");
      }
    // Acrescenta um 0 se o dia do mes for menor do que 10
    if (monthday < 10){
      bluetooth.print(" 0");
    }
    bluetooth.print(monthday);
    bluetooth.print("/");
    // Acrescenta um 0 se mes o for menor do que 10
    if (month < 10){
      bluetooth.print("0");
    }
    bluetooth.print(month);
    bluetooth.print("/");
    bluetooth.print(year);
    bluetooth.println(" ");

}

byte _ConverteParaBCD(byte val){
  //Converte o número de decimal para BCD
  return ( (val/10*16) + (val%10) );
}

byte _ConverteparaDecimal(byte val){
  //Converte de BCD para decimal
  return ( (val/16*10) + (val%16) );
}

//-------------------------------------------------------------- RTC - FIM ---//



//-------------------------------------------------------------- EEPROM ----//
void escrita_Eeprom();
void leitura_Eeprom();
//-------------------------------------------------------------- EEPROM - FIM ----//




//--------------------------------------- Verificação de Presença Humana ---//
void _presenca(){
  
  estado_sensor = digitalRead(sensorPres);

  if(estado_sensor == 1 && flag_controle == 1){ // Se o sensor de presença for ativado por movimentação
    flag_presenca = 1; // Seta a flag de presença para verdadeira;
    minuto_entrada = minu;
    //Serial.println("Presenca Detectada!");
  }
  if(estado_sensor == 0){ // Se o sensor não estiver ativo
    flag_presenca = 0; // Seta a flag para falsa;
    //Serial.println("Não há presença Detectada")
  }

  if(flag_presenca == 1 && flag_controle == 1){ // Significa que não havia pessoas anteriormente, agora há.
    hora_entrada_ligar = hour;
    minuto_entrada_ligar = minu;
    flag_presenca_efetiva = 1;
    _natureza();
    //Serial.println("Ligando disp. da Sala!");
    flag_controle = 0;
  }

  if(flag_controle == 0){ // Há presença de pessoas, deve-se verificar
    if (minuto_entrada > 55 && minuto_entrada < 60){ // Se o minuto de entrada for 59, verdadeiro!
      if((60 + minu - minuto_entrada) >= 4 && flag_presenca == 0){ // Se 60 - minuto lido - 55 à 59 = 5, verdadeiro!
        flag_presenca_efetiva = 0;
        _natureza();
        flag_controle = 1;
        //Serial.println("Desligando disp. da Sala");
        
      }
    }

    if ((minuto_entrada >= 0) && (minuto_entrada < 56)) { // Se o minuto de entrada for de 0 a 54, verdadeiro!
      if((60 + minu - minuto_entrada) >= 64 && flag_presenca == 0){
        flag_presenca_efetiva = 0;
        _natureza();
        flag_controle = 1;
        //Serial.println("Desligando disp. da Sala");        
      }

    }

  }
}
//--------------------------------- Verificação de Presença Humana - FIM ---//  


//-------------------------------------------------------- Natureza do Sistema ------------//
void _natureza(){
  if(flag_presenca_efetiva == 1){ // Se a flag de presença for verdadeira
    _ligar_ilum();

    _ligarC1(); // Liga a primeira Central de Ar
    delay(200);

    _ligarC2(); // Liga a segunda Central de Ar
    delay(200);

    _temp17C1(); // Ajusta a temperatura da Central 1 para 20 Graus Celsius
    delay(200);

    _temp18C2(); // Ajusta a temperatura da Central 2 para 20 Graus Celsius
  }
  
  if(flag_presenca_efetiva == 0){ // Se a flag de ausencia for verdadeira
    _desligar_ilum();

    _desligarC1(); // Liga a segunda Central de Ar
    delay(200);

    _desligarC2(); // Liga a primeira Central de Ar
    delay(100);
  }
}
//-------------------------------------------------- Natureza do Sistema - FIM ------------//


//-------------------------------------------------------------- Comunicação Blueetooth ---//


//---------------------Função para Receber um String ---//
/*String leStringSerial(){
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
}*/
//---------------------Função para Receber um String - FIM ---//


//-------------------------------------------------------------- Comunicação Blueetooth - FIM ---//



//-------------------------------------------------------------- Ligar ou Desligar Dispositivos ---//
void _porta(){
  //O controle da Fec. está sendo realizado pela porta -> Dig 12
  //Esta função é chamada pelo comando BT -> 'q'
  digitalWrite(fechadura, 1);
  delay(20);
  digitalWrite(fechadura, 0);
  //Serial.println("destravar_porta()");
}

void _ligards(){ //comandado pelor emissorIR - 1
  digitalWrite(ir_1, 1);

  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0xC1AA09F6, 32);
    delay(40);
  }
  digitalWrite(ir_1, 0);

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

void _desligar_ilum(){
  if(_tensao1() == true){
    digitalWrite(lamp1, !_tensao1());
  }
  if(_tensao2() == true){
    digitalWrite(lamp2, !_tensao2());
  }
  if(_tensao3() == true){
    digitalWrite(lamp3, !_tensao3());
  }
}

void _ligar_ilum(){
  if(_tensao1() == false){
    digitalWrite(lamp1, !_tensao1());
    delay(500);
  }
  if(_tensao2() == false){
    digitalWrite(lamp2, !_tensao2());
    delay(500);
  }
  if(_tensao3() == false){
    digitalWrite(lamp3, !_tensao3());
  }
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

//----------------- CENTRAL 1 comandado pelor emissorIR - 2
  void _ligarC1(){ 
    digitalWrite(ir_2, 1);

    //for (int i = 0; i < 3; i++) {
      //irsend.sendNEC(0xB24DBF40, 32);
      //delay(40);
    //}
    unsigned int irSignal[] = {8348, 4268, 532, 1696, 524, 568, 556, 564, 532, 592, 532, 1688, 528, 600, 524, 560, 564, 560, 576, 548, 532, 588, 536, 560, 572, 552, 576, 520, 560, 564, 532, 588, 536, 564, 560, 568, 528, 588, 532, 1696, 524, 1712, 532, 568, 528, 592, 532, 568, 556, 564, 532, 588, 576, 532, 548, 1684, 536, 1696, 520}; //AnalysIR Batch Export (IRremote) - RAW
    irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); //Note the approach used to automatically calculate the size of the array.
    digitalWrite(ir_2, 0);

  }

  void _desligarC1(){ 
    digitalWrite(ir_2, 1);

    //for (int i = 0; i < 3; i++) {
      //irsend.sendNEC(0xB24D7B84, 32);
      //delay(40);
    //}
    unsigned int irSignal[] = {8348, 4244, 532, 1684, 604, 528, 564, 552, 572, 524, 560, 1684, 532, 568, 600, 524, 528, 592, 576, 1636, 540, 1680, 600, 536, 564, 552, 568, 524, 604, 520, 532, 596, 528, 564, 596, 524, 532, 592, 568, 528, 600, 528, 572, 544, 532, 1684, 580, 552, 528, 1692, 568, 548, 532, 564, 560, 560, 536, 1684, 560}; //AnalysIR Batch Export (IRremote) - RAW
    irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); //Note the approach used to automatically calculate the size of the array.

    digitalWrite(ir_2, 0);

  }

  void _temp17C1(){ 
    digitalWrite(ir_2, 1);

    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0x31992550, 32);
      delay(40);
    }
    digitalWrite(ir_2, 0);

  }  

  void _temp18C1(){ 
    digitalWrite(ir_2, 1);

    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0xD0AE2562, 32);
      delay(40);
    }
    digitalWrite(ir_2, 0);

  }

  void _temp19C1(){ 
    digitalWrite(ir_2, 1);

    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0x670550B3, 32);
      delay(40);
    }
    digitalWrite(ir_2, 0);

  }

  void _temp20C1(){ 
    digitalWrite(ir_2, 1);

    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0xCE4342CC, 32);
      delay(40);
    }
    digitalWrite(ir_2, 0);

  }

  void _temp21C1(){ 
    digitalWrite(ir_2, 1);

    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0x14357268, 32);
      delay(40);
    }
    digitalWrite(ir_2, 0);

  }

  void _temp22C1(){ 
    digitalWrite(ir_2, 1);

    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0x788A798C, 32);
      delay(40);
    }
    digitalWrite(ir_2, 0);

  }

  void _temp23C1(){ 
    digitalWrite(ir_2, 1);

    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0x194A9510, 32);
      delay(40);
    }
    digitalWrite(ir_2, 0);

  }

  void _temp24C1(){ 
    digitalWrite(ir_2, 1);

    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0xE1BF922C, 32);
      delay(40);
    }
    digitalWrite(ir_2, 0);

  }

  void _temp25C1(){ 
    digitalWrite(ir_2, 1);

    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0x42E98D26, 32);
      delay(40);
    }
    digitalWrite(ir_2, 0);

  }      

//------------------ CENTRAL 1


//------------------ CENTRAL 2 comandado pelor emissorIR - 3
  void _ligarC2(){ 
    digitalWrite(ir_3, 1);

    //for (int i = 0; i < 3; i++) {
      //irsend.sendNEC(0xB24DBF40, 32);
      //delay(40);
    //}
    unsigned int irSignal[] = {8348, 4268, 532, 1696, 524, 568, 556, 564, 532, 592, 532, 1688, 528, 600, 524, 560, 564, 560, 576, 548, 532, 588, 536, 560, 572, 552, 576, 520, 560, 564, 532, 588, 536, 564, 560, 568, 528, 588, 532, 1696, 524, 1712, 532, 568, 528, 592, 532, 568, 556, 564, 532, 588, 576, 532, 548, 1684, 536, 1696, 520}; //AnalysIR Batch Export (IRremote) - RAW
    irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); //Note the approach used to automatically calculate the size of the array.
    digitalWrite(ir_3, 0);

 }  

  void _desligarC2(){ 
    digitalWrite(ir_3, 1);

    //for (int i = 0; i < 3; i++) {
      //irsend.sendNEC(0xB24D7B84, 32);
      //delay(40);
    //}
    unsigned int irSignal[] = {8348, 4244, 532, 1684, 604, 528, 564, 552, 572, 524, 560, 1684, 532, 568, 600, 524, 528, 592, 576, 1636, 540, 1680, 600, 536, 564, 552, 568, 524, 604, 520, 532, 596, 528, 564, 596, 524, 532, 592, 568, 528, 600, 528, 572, 544, 532, 1684, 580, 552, 528, 1692, 568, 548, 532, 564, 560, 560, 536, 1684, 560}; //AnalysIR Batch Export (IRremote) - RAW
    irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); //Note the approach used to automatically calculate the size of the array.
    digitalWrite(ir_3, 0);

}

  void _temp18C2(){ 
    digitalWrite(ir_3, 1);

    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0xD0AE2562, 32);
      delay(40);
    }
    digitalWrite(ir_3, 0);

  }     
//------------------ CENTRAL 2



/*

|| Aparelho   || Função    || Código     ||
------------------------------------------
|| TV LG CASA || On_Off    || 0x20DF10EF ||
|| TV LG CASA || Vol_Up    || 0x20DF40BF ||
|| TV LG CASA || Vol_Down  || 0x20DFC03F ||
|| TV LG CASA || Chan_Up   || 0x20DF00FF ||
|| TV LG CASA || Chan_Down || 0x20DF807F ||

|| DATASHOW   || On_Off    || 0x8C73817E ||

|| CARRIER    ||    Off    || 0xB24D7B84 || Ar_Condicionado Pequeno 12mil BTUS Ligar ou Desligar
|| CARRIER    ||   On      || 0xB24DBF40 || Ar_Condicionado Pequeno 12mil BTUS Ligar ou Desligar
|| CARRIER    || temp_17   || 0x31992550 || Ar_Condicionado Pequeno 12mil BTUS 17 GRAUS
|| CARRIER    || temp_18   || 0xE29EFB2C || Ar_Condicionado Pequeno 12mil BTUS 17 GRAUS
|| CARRIER    || temp_19   || 0x329849F0 || Ar_Condicionado Pequeno 12mil BTUS 17 GRAUS
|| CARRIER    || temp_20   || 0xCE4342CC || Ar_Condicionado Pequeno 12mil BTUS 17 GRAUS
|| CARRIER    || temp_21   || 0x14357268 || Ar_Condicionado Pequeno 12mil BTUS 17 GRAUS
|| CARRIER    || temp_22   || 0x788A798C || Ar_Condicionado Pequeno 12mil BTUS 17 GRAUS
|| CARRIER    || temp_23   || 0x194A9510 || Ar_Condicionado Pequeno 12mil BTUS 17 GRAUS
|| CARRIER    || temp_24   || 0xE1BF922C || Ar_Condicionado Pequeno 12mil BTUS 17 GRAUS
|| CARRIER    || temp_25   || 0x42E98D26 || Ar_Condicionado Pequeno 12mil BTUS 17 GRAUS

|| FUJITSU    || On        || 0x5CD97072 || Ar_Condicionado Pequeno 32mil BTUS 17 GRAUS
|| FUJITSU    || Off       || 0xFB876668 || Ar_Condicionado Pequeno 32mil BTUS 17 GRAUS
|| FUJITSU    || temp_18   || 0x67131BB3 0xFFFFFFFF || Ar_Condicionado Pequeno 32mil BTUS 17 GRAUS
|| FUJITSU    || temp_19   || 0x5CD97072 0x2F3FF59C || Ar_Condicionado Pequeno 32mil BTUS 17 GRAUS
|| FUJITSU    || temp_20   || 0xB2C42DF9 0x5FB17384 || Ar_Condicionado Pequeno 32mil BTUS 17 GRAUS
|| FUJITSU    || temp_21   || 0x5CD97072 0xA71C19A7 || Ar_Condicionado Pequeno 32mil BTUS 17 GRAUS
|| FUJITSU    || temp_22   || 0xB46F7321            || Ar_Condicionado Pequeno 32mil BTUS 17 GRAUS

|| LG    || ligar      || 0xB288E94A            || Ar_Condicionado Pequeno 32mil BTUS 17 GRAUS
|| LG    || desligar   || 0x1035C9DA            || Ar_Condicionado Pequeno 32mil BTUS 17 GRAUS
|| LG    || temp_18    || 0xD0AE2562             || Ar_Condicionado Pequeno 32mil BTUS 17 GRAUS
|| LG    || temp_19    || 0x670550B3             || Ar_Condicionado Pequeno 32mil BTUS 17 GRAUS



*/





//LG DESLIGAR - Raw: (59) 8348, 4244, 532, 1684, 604, 528, 564, 552, 572, 524, 560, 1684, 532, 568, 600, 524, 528, 592, 576, 1636, 540, 1680, 600, 536, 564, 552, 568, 524, 604, 520, 532, 596, 528, 564, 596, 524, 532, 592, 568, 528, 600, 528, 572, 544, 532, 1684, 580, 552, 528, 1692, 568, 548, 532, 564, 560, 560, 536, 1684, 560, 
//LG LIGAR -    Raw: (59) 8348, 4268, 532, 1696, 524, 568, 556, 564, 532, 592, 532, 1688, 528, 600, 524, 560, 564, 560, 576, 548, 532, 588, 536, 560, 572, 552, 576, 520, 560, 564, 532, 588, 536, 564, 560, 568, 528, 588, 532, 1696, 524, 1712, 532, 568, 528, 592, 532, 568, 556, 564, 532, 588, 576, 532, 548, 1684, 536, 1696, 520, 


