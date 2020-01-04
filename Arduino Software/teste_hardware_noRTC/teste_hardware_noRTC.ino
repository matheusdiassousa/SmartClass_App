/*  ---- TESTE HARDWARE 01_03_2018 ----
 * Autor: Matheus Dias
 * Início: 28/02/2018 
 * Last_Att: 01/03/2018
 * Utilidade: Realizar uma demonstração do Hardware sem o RTC
 * Dispositivos disponíveis: Bluetooth - Emissor IR - Sensor de Presença - Controle de Tomada - Sensor de Tensão

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


// -------------------------- Recursos para utilizar o Bluetooth ----- //
#include <SoftwareSerial.h>
SoftwareSerial bluetooth = SoftwareSerial(10, 11); //Pino 10 como entrada RX do Arduíno e TX do HC-05, pino 11 como saída TX do Arduíno e RX do HC-05
String comandoBT_recebido;                            //Comando recebido via bluetooth;
byte f_Ilum1, f_Ilum2, f_Ilum3, f_Central1, f_Central2, f_CentralT_18, f_CentralT_19, f_DataShow;
void receber_Bluetooth();       //Função para receber valores do Aplicativo via Bluetooth;
String leStringSerial();    //Função para ler uma string via comunicação serial;
// -------------------------- Recursos para utilizar o Bluetooth - FIM ---- //


// -------------------------- Recursos para utilizar o Emissor_IR ----- //
#include <IRremote.h>     //Biblioteca Infra Vermelho;
IRsend irsend;          //Objeto que instância o infra vermelho
int khz = 38;           //38kHz carrier frequency for the NEC protocol
// ------ O EMISSOR IR DEVE ESTAR LIGADO À PORTA DIGITAL 3 - ESTA BIBLIOTECA UTILIZA O INTERRUPT DESTE PINO -------//
// -------------------------- Recursos para utilizar o Emissor_IR - FIM ---- //


// --------------------------------- Recursos para utilizar o Sensor de Presença ----- //
const byte sensorPres = 4;    //Porta digital 4 do arduino sendo utilizada para ler o sensor.
void sensor_Presenca();     //Função para verificar se há presença de pessoas;
byte estadoSensor, f_Pres, f_print;   //Variável para armazenar o estado do sensor;
// --------------------------------- Recursos para utilizar o Sensor de Presença - FIM ---- //

// --------------------------------- Recursos para utilizar o Controlador de Tomada - Iluminação 1 ----- //
const byte modulo_CT_Ilum1 = 7; //Controle do módulo de tomada ligado à porta digital 7;
// --------------------------------- Recursos para utilizar o Controlador de Tomada - Iluminação 1 - FIM ---- //

// --------------------------------- Modo de Operação ----- //
void modo_Operacao();           //Função para verificar o modo de operação.
void modo_Automatico();     //Função executada no modo automático.
void modo_Manual();       //Função executada no modo manual
byte f_ModoOper, f_ligartudo;       // f_ModoOper = 1 AUTOMATICO ... f_ModoOper = 0 MANUAL
// --------------------------------- Modo de Operação - FIM ---- //

// ------ FUNÇÕES GERAIS ------ //
void controlar_Ilum1();
void controlar_Central();
void ligar_Central();
void desligar_Central();
void temp_Central18();
void temp_Central19();
// ------ FUNÇÕES GERAIS - FIM ----- //


void setup(){
  // SENSOR DE PRESENÇA SETUP //
  pinMode(4, INPUT);      //Porta digital 4 como entrada;
  f_Pres = 0;         //Inicia o Arduino zerando a Flag de presença
  // SENSOR DE PRESENÇA SETUP //

  // BLUETOOTH SETUP//
    pinMode(10, INPUT);           //Pino 10 como Entrada do arduíno - BlueTX e arduinoRX
    pinMode(11, OUTPUT);          //Pino 11 como Saída do arduíno - BlueRX e arduinoTX
    bluetooth.begin(38400);       //Iniciando a comunicação serial com o arduino e bluetooth;
    // BLUETOOTH SETUP//


    // MODO OPERAÇÃO SETUP //
    f_ModoOper = 1;       //Inicia o modo de operação no modo automático
    f_ligartudo = 1;      //Flag que indica que o sistema está iniciando com tudo desligado
    // MODO OPERAÇÃO SETUP //

    // Controlador de Tomada Iluminação 1 //
    pinMode(modulo_CT_Ilum1, OUTPUT);
    // Controlador de Tomada Iluminação 1 - FIM //

    // Serial Arduino SETUP //
  Serial.begin(38400);          //Iniciando a comunicação serial com o arduino e o pc;
  Serial.println("Iniciando Sistema..."); //Escrevendo uma mensagem na serial monitor do pc;
    // Serial Arduino SETUP //
}



void loop(){
  
  sensor_Presenca();
  receber_Bluetooth();
  modo_Operacao();      //Quando o sistema liga ele inicia com a f_ModoOper = 1 Automático

}


//-------------------------------------------------------------- Modo de Operação ---//
void modo_Operacao(){
  if(f_ModoOper == 1){
    modo_Automatico();    //Se a flag for = 1 o sistema está no modo automático;
  }
  else if(f_ModoOper == 0){
    modo_Manual();      //Se a flag for = 0 o sistema está no modo manual;
  }
}

void modo_Automatico(){
  if(f_Pres == 1 && f_ligartudo == 1){
    f_ligartudo = 0;      //Esta flag é setada para 0 para que o sistema não retorne nessa função antes de desligar tudo;
    f_Ilum1 = 1;        //Esta flag indica que a iluminação deve ser ligada;
    f_Central1 = 1;       //Esta flag indica que a central deve ser ligada;
    controlar_Ilum1();      //Ligar lâmpada 1
    controlar_Central();    //Ligar Central de Ar
  }

  if(f_Pres == 0 && f_ligartudo == 0){
    f_ligartudo = 1;      //Esta flag indica que tudo está sendo desligado;
    f_Ilum1 = 0;        //Esta flag indica que a iluminação irá ser desligada.
    f_Central1 = 0;       //Esta flag indica que a central irá ser desligada.
    controlar_Ilum1();
    controlar_Central();

  }


}

void modo_Manual(){
  if (bluetooth.available() > 0) {
      comandoBT_recebido = leStringSerial();

      //------------------------------------------- CONTROLAR ILUMINAÇÃO 1 ---//
      if( f_ModoOper == 0 && comandoBT_recebido == "lamp1_1") {
        bluetooth.println("Ligar Iluminação 1!");
        f_Ilum1 = 1;  // Ligar o sistema de iluminação 1;
        controlar_Ilum1();
      }

      else if( f_ModoOper == 0 && comandoBT_recebido == "lamp1_0" ){
        bluetooth.println("Desligar Iluminação 1!");
        f_Ilum1 = 0;  // Desligar o sistema de iluminação 1;
        controlar_Ilum1();

      }
      //------------------------------------------- CONTROLAR ILUMINAÇÃO 1 - FIM ---//    


      //-------------------------------------------- CENTRAL DE AR -----//
      else if( f_ModoOper == 0 && comandoBT_recebido == "central_1" ){
        bluetooth.println("Ligar Central de Ar!");
        f_Central1 = 1;
        controlar_Central();

      }
      else if( f_ModoOper == 0 &&comandoBT_recebido == "central_0" ){
        bluetooth.println("Desligar Central de Ar!");
        f_Central1 = 0;
        controlar_Central();

      }
      else if( comandoBT_recebido == "central_18" ){
        bluetooth.println("Ajustar Temperatura para 18 Graus!");
        f_CentralT_18 = 1;
        controlar_Central();

      }
      else if( comandoBT_recebido == "central_19" ){
        bluetooth.println("Ajustar Temperatura para 19 Graus!");
        f_CentralT_19 = 1;
        controlar_Central();

      }
      //------------------------------------ CENTRAL DE AR ---- FIM ---//


    }

}
//-------------------------------------------------------------- Modo de Operação - FIM ---//



//-------------------------------------------------------------- Sensor de Presença ---//
void sensor_Presenca(){
  estadoSensor = digitalRead(sensorPres);     //Lê o estado de saída do sensor de presença
  if (estadoSensor == HIGH){            //Se o estado de saída é alto, prossiga.
    if(f_Pres == 0){              //Se a flag f_Pres é 0 imprima;
      bluetooth.println("Presença Detectada!");//Imprime no aplicativo do celular "Presença Detectada!"
      f_Pres = 1;               //Seta a flag de impressão para 1, para não imprimir a mesma mensagem.
    }
  }
    
    else if (estadoSensor == LOW){          //Lê o estado de saída do sensor de presença
      if( f_Pres == 1){             //Se a flag f_Pres é 1 imprima;
        Serial.println("Não há mais Presença Detectada!");//Imprime no aplicativo do celular "Não há mais Presença Detectada!"
        f_Pres = 0;               //Seta a flag de impressão para 0, para que não fique a imprimir repetida vezes.
      }       
    }
}
//-------------------------------------------------------------- Sensor de Presença - FIM --//



//-------------------------------------------------------------- Comunicação Blueetooth ---//

void receber_Bluetooth() {

  if (bluetooth.available() > 0) {
      comandoBT_recebido = leStringSerial();

      //------------------------------------------- MODO DE OPERAÇÃO ---//
      if( comandoBT_recebido == "aut_1" ){
        bluetooth.println("Modo Automático Ativado!");
        f_ModoOper = 1; //Flag indicando que está no modo automático
      }

      else if( comandoBT_recebido == "aut_0" ){
        bluetooth.println("Modo Manual Ativado!");
        f_ModoOper = 0; //Flag indicando que está no modo manual
      }
      //-------------------------------------------- MODO DE OPERAÇÃO - FIM ---//
  }//FIM-if Geral;
}//FIM-receber_Bluetooth();
//-------------------------------------------------------------- Comunicação Blueetooth - FIM ---//
  
//-------------------------------------------------------------- Controlar Iluminação1 ---//
void controlar_Ilum1() {
  if(f_Ilum1 == 1){
    digitalWrite(7, 1);   //Coloca o pino digital 7 do arduino em estado alto.

  }
  else if(f_Ilum1 == 0){
    digitalWrite(7, 0);   //Coloca o pino digital 7 do arduino em estado alto.

  }

}
//-------------------------------------------------------------- Controlar Iluminação1 - FIM ---//


//-------------------------------------------------------------- Controlar Central ---//
void controlar_Central(){

  if(f_Central1 == 1){
    ligar_Central();
  }

  else if(f_Central1 == 0){
    desligar_Central();
  }

  else if(f_CentralT_18 == 1){
    temp_Central18();
  }

  else if(f_CentralT_19 == 1){
    temp_Central19();
  }

}

void ligar_Central(){  
  unsigned int irSignal[] = {8388, 4252, 620, 1636, 592, 508, 556, 604, 556, 528, 592, 1636, 596, 564, 500, 568, 616, 508, 592, 532, 536, 600, 588, 504, 532, 592, 596, 500, 624, 504, 592, 568, 560, 540, 588, 536, 560, 532, 596, 1632, 592, 1628, 624, 504, 592, 532, 536, 600, 584, 508, 532, 592, 532, 564, 564, 1688, 596, 1632, 588}; //AnalysIR Batch Export (IRremote) - RAW
  irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); //Note the approach used to automatically calculate the size of the array.
}//Fim_ligar_desligar();

void desligar_Central(){  
  unsigned int irSignal[] = {8336, 4280, 508, 1744, 480, 676, 452, 648, 476, 648, 452, 1740, 512, 648, 452, 672, 452, 648, 480, 1732, 492, 1736, 488, 676, 448, 648, 480, 648, 448, 676, 452, 648, 476, 648, 452, 676, 448, 648, 480, 648, 452, 672, 452, 648, 476, 1752, 472, 652, 476, 1740, 484, 648, 480, 620, 476, 652, 476, 1736, 488}; //AnalysIR Batch Export (IRremote) - RAW
  irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); //Note the approach used to automatically calculate the size of the array.
}//Fim_ligar_desligar();


void temp_Central19(){  
  unsigned int irSignal[] = {8352, 4264, 528, 1696, 528, 600, 524, 572, 556, 572, 528, 1696, 552, 576, 524, 600, 528, 572, 552, 572, 528, 596, 528, 572, 556, 572, 524, 1700, 552, 576, 524, 600, 524, 572, 556, 572, 528, 1696, 552, 576, 524, 600, 524, 576, 552, 572, 528, 600, 524, 572, 552, 1700, 528, 1696, 528, 600, 524, 572, 556}; //AnalysIR Batch Export (IRremote) - RAW
  irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); //Note the approach used to automatically calculate the size of the array.
}//Fim_aumentar_volume();


void temp_Central18(){  
  unsigned int irSignal[] = {8384, 4232, 560, 1688, 536, 564, 560, 600, 500, 624, 500, 1692, 536, 624, 500, 600, 524, 600, 500, 592, 596, 536, 528, 600, 496, 596, 532, 1696, 528, 628, 500, 568, 556, 600, 500, 592, 532, 600, 588, 1632, 532, 1692, 532, 596, 528, 568, 560, 600, 560, 568, 496, 1692, 532, 628, 500, 1688, 536, 1688, 560}; //AnalysIR Batch Export (IRremote) - RAW
  irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); //Note the approach used to automatically calculate the size of the array.
}//Fim_diminur_volume();
//-------------------------------------------------------------- Controlar Central - FIM ---//




//-------------------------------------------------------------- Função para Receber um String ---//

String leStringSerial(){
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
//-------------------------------------------------------------- Função para Receber um String - FIM ---//
