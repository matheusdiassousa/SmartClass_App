/*  ---- BT_TEST COM STRING ----
 * Autor: Matheus Dias
 * Início: 28/02/2018 
 * Last_Att: 28/02/2018
 * Utilidade: Receber uma String via BT
 * Dispositivos necessários: Bluetooth HC-05

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


// ----- Recursos para utilizar o Bluetooth ----- //
#include <SoftwareSerial.h>
SoftwareSerial bluetooth = SoftwareSerial(10, 11); //Pino 10 como entrada RX do Arduíno e TX do HC-05, pino 11 como saída TX do Arduíno e RX do HC-05
String comandoBT_recebido;                            //Comando recebido via bluetooth;


// ----- Recursos para utilizar o Bluetooth ----- //

//---FUNÇÕES---//
void receber_Bluetooth();       // Função para receber valores do Aplicativo via Bluetooth;
String leStringSerial();    // Função para ler uma string via comunicação serial;


//---FUNÇÕES- FIM--//

void setup(){
  // BLUETOOTH SETUP//
  pinMode(10, INPUT);           //Pino 10 como Entrada do arduíno - BlueTX e arduinoRX
  pinMode(11, OUTPUT);          //Pino 11 como Saída do arduíno - BlueRX e arduinoTX
  bluetooth.begin(9600);       //Iniciando a comunicação serial com o arduino e bluetooth;
  // BLUETOOTH SETUP//

  // Serial Arduino SETUP //
  Serial.begin(9600);          //Iniciando a comunicação serial com o arduino e o pc;
  Serial.println("Iniciando Sistema..."); //Escrevendo uma mensagem na serial monitor do pc;
  // Serial Arduino SETUP //
}



void loop(){
  receber_Bluetooth();
}


//-------------------------------------------------------------- Comunicação Blueetooth ---//

void receber_Bluetooth(){
   if (bluetooth.available() > 0) {
    comandoBT_recebido = leStringSerialbt();

    //---- MODO DE OPERAÇÃO ---//
    if( comandoBT_recebido == "aut_1"){
      bluetooth.println("Modo Automático Ativado!");
      f_ModoOper = 1; //Flag indicando que está no modo automático
    }

    else if( comandoBT_recebido == "aut_0"){
      bluetooth.println("Modo Manual Ativado!");
      f_ModoOper = 0; //Flag indicando que está no modo manual
    }
    //---- MODO DE OPERAÇÃO - FIM ---//


    //---- CONTROLAR ILUMINAÇÃO 1 ---//
    else if( comandoBT_recebido == "lamp1_1"){
      bluetooth.println("Ligar Iluminação 1!");
    }

    else if( comandoBT_recebido == "lamp1_0"){
      bluetooth.println("Desligar Iluminação 1!");
    }
    //---- CONTROLAR ILUMINAÇÃO 1 - FIM ---//    


    else if( comandoBT_recebido == "aut_0"){
      bluetooth.println("Modo Manual Ativado!");
    }
    

  }
}//FIM-receber_Bluetooth();
//-------------------------------------------------------------- Comunicação Blueetooth - FIM ---//



//-------------------------------------------------------------- Função para Receber um String ---//

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
//-------------------------------------------------------------- Função para Receber um String - FIM ---//
