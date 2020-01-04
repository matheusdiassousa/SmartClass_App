/*  ---- SENSOR DE TENSÃO TESTE ----
 * Autor: Matheus Dias
 * Início: 19/07/2018 
 * Last_Att: 25/07/2018
 * Utilidade: Testar o circuito sensor de tensão
 * Dispositivos disponíveis: 4N25 como sensor de tensão

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

int v_s_1 = A0; //Digital_5
int led = 7;
void setup() {
  pinMode(v_s_1, INPUT);
  pinMode(led, OUTPUT);
  
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  if(tensao() == true){
    digitalWrite(led, HIGH);
    //Serial.println("Ligado!");
  }
  if(tensao() == false){
    digitalWrite(led, LOW);
    //Serial.println("Desligado!");
  }
  
  
  // put your main code here, to run repeatedly:

}

boolean tensao(){
  for(int i=1; i < 100; i++){
    if(analogRead(v_s_1) > 10){
      return true;
    }
  }
  return false;
  
}

