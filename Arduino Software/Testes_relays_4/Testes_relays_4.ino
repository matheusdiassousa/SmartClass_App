/*  -- TESTE EM RELAYS --
 *  Autor: Matheus Dias
 * Início: 29/09/2018 
 * Last_Att: 29/09/2018
 * Utilidade: Testar circuitos de acionamentode relays.
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

void lamp_1();
void lamp_2();
void lamp_3();
void tomadas();

const byte lampada1 = 4;
const byte lampada2 = 5;
const byte lampada3 = 6;
const byte contatora = 7;

void setup(){
  pinMode(lampada1,OUTPUT);
  pinMode(lampada2,OUTPUT);
  pinMode(lampada3,OUTPUT);
  pinMode(contatora,OUTPUT);
  
  Serial.begin(9600);
}

void loop(){
  if(Serial.available()){
    char cmd = Serial.read(); // lê o valor digitado e enviado pela serial monitor.
    if(cmd == 'q'){
      Serial.println("Lamp1");
      lamp_1();
      cmd = 0;
    }

    if(cmd == 'w'){
      Serial.println("Lamp2");
      lamp_2();
      cmd = 0;
    }
    
    if(cmd == 'e'){
      Serial.println("Lamp3");
      lamp_3();
      cmd = 0;
    }
    
    if(cmd == 'r'){
      Serial.println("Tomadas");
      tomadas();
      cmd = 0;
    }    
  
}
}
void lamp_1(){
  digitalWrite(lampada1, 1);
  delay(2000);
  digitalWrite(lampada1, 0);
  Serial.println("Lamp1_fim");
}
void lamp_2(){
  digitalWrite(lampada2, 1);
  delay(2000);
  digitalWrite(lampada2, 0);
  Serial.println("Lamp2_fim");
}

void lamp_3(){
  digitalWrite(lampada3, 1);
  delay(2000);
  digitalWrite(lampada3, 0);
  Serial.println("Lamp3_fim");  
}

void tomadas(){
  digitalWrite(contatora, 1);
  delay(2000);
  digitalWrite(contatora, 0);
  Serial.println("contatora_fim");
}




