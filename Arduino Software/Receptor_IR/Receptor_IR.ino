#define LEDPIN 13

#define maxLen 800  // Pode-se aumentar esse valor para Arduinos com SRAM maiores que 2k

volatile unsigned int irBuffer [maxLen]; // Armazena os tempos, eh volatil pois eh alterado pela ISR (Interrupt Service Routine)
volatile unsigned int x = 0;  // Ponteiro que percorre o irBuffer , eh volatil pois tambem eh alterado pela ISR


void setup(){
  Serial.begin(9600);

  //Plugue no pino digital 3
  attachInterrupt (digitalPinToInterrupt(3), rxIR_Interrupt_Handler, CHANGE); // Configurar o ISR para receber o signal IR

}

void loop (){
  Serial.println(F("Envie o sinal infra-vermelho agora - apenas um sinal"));
  delay(5000);  // Espere 5 segundos
  if (x){ // Se receber um sinal
    digitalWrite(LEDPIN, HIGH); // Acender o LED para mostrar que um sinal foi recebido
    Serial.println();
    Serial.print(F("Raw: ("));  // Despejar o RAW format - no formato da biblioteca
    Serial.print((x-1));
    Serial.print(F(") "));
    detachInterrupt(0); // Stop interrupts e captura ate acabar
    for (int i=1; i<x; i++){  // Agora despeje os tempos
      if (!(i & 0x1)) Serial.print(F(""));
      Serial.print(irBuffer[i] - irBuffer [i - 1]);
      Serial.print(F(", "));
    }
    x = 0;
    Serial.println();
    Serial.println();
    digitalWrite(LEDPIN, LOW); //Apaga o LED para esse tempo
    attachInterrupt(0, rxIR_Interrupt_Handler, CHANGE); // Re-habilita ISR para receber sinal IR
  }
}

void rxIR_Interrupt_Handler(){
  if (x>maxLen) return;      // Ignora se o irBuffer ja estiver cheio
  irBuffer[x++] = micros();  // Apenas grave continuamente os tempos das transicoes dos sinais
}
