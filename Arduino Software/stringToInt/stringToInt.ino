void setup() {
 Serial.begin(9600);
  
  int valorInt;
  String valor;
  String frase = "1111 com feijao";
  
  valor.concat(frase[0]);
  valor.concat(frase[1]);
  Serial.println(valor);
  byte valor1 = frase[0] - '0';
  //int soma = valor + 12;
//Serial.println(soma);
  byte soma = valor1 + 12;
  Serial.println(soma);
  // put your main code here, to run repeatedly:
 

}

void loop() {
  

}
