/*-----CÓDIGO DA ROBOCORE-----
 * LINK: https://www.robocore.net/modules.php?name=RC_Tutoriais&id=41
 * para entrar no modo AT - ligue o sistema e abra a SerialMonitor, aperte o botão do HC e digite AT e aperte Enter
 * Ultima BaudRate = 9600 // ID_NAME = CONROLE SALA // Senha de pareamento = UFT tudo maiusculo;
 */
//Include the SoftwareSerial library
#include "SoftwareSerial.h"

//Create a new software  serial
SoftwareSerial mySerial = SoftwareSerial(10, 11);   // Define o pino 10 como TX do Bluetooth e o 11 como RX do Bluetooth

void setup() {
  pinMode(10, INPUT); //pino 10 como entrada - RX do Arduíno e TX do HC-05
  pinMode(11, OUTPUT);//pino 11 como entrada - TX do Arduíno e RX do HC-05 
  
  //Initialize the hardware serial
  Serial.begin(9600);
  Serial.println(F("Type the AT commands:"));

  //Initialize the software serial
  mySerial.begin(9600);
}

void loop() {
  //Check received a byte from hardware serial
  if (Serial.available()) {
    char r = Serial.read(); //Read and save the byte
    mySerial.print(r);  //Send the byte to bluetooth by software serial
    Serial.print(r);  //Echo
  }
  //Check received a byte from bluetooth by software serial
  if (mySerial.available()) {
    char r = mySerial.read(); //Read and save the byte
    Serial.print(r); //Print the byte to hardware serial
  }
}
