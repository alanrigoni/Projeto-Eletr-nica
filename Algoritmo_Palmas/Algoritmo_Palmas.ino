#define tmpMaxPalma 100
#define tmpMaxPalmas 500
#define pinMicro 7
#define pinRelay 8
 
unsigned long tmpEspera = 0;
unsigned long tmpPalmas = 0;
int sensorMicro;
int contPalmas = 0;
 
void Action();
 
void setup() {
  pinMode(pinMicro, INPUT);
  pinMode(pinRelay, OUTPUT);
  digitalWrite(pinRelay, HIGH); //Ligar arduino com Relé desligado
}
 
void loop() {
  /*O sensor mantém sua porta ligada até que uma palma seja detectada.
    A função digitalRead() faz a leitura contínua do microfone.
  */
  sensorMicro = digitalRead(pinMicro);
  //Palma detectada
  if (sensorMicro == LOW) {
    /* É preciso um tempo para que uma palma não seja detectada novamente.
       o contador a cada detecção.
    */
    if ((millis() - tmpEspera) >= tmpMaxPalma) {
      tmpEspera = 0;
    } else if (tmpEspera == 0) {
      tmpEspera = tmpPalmas = millis();
      contPalmas++;
    }
  }
 
  //Para o tempo excedido zeramos o contador de palmas.
  if (((millis() - tmpPalmas) > 500) && (contPalmas != 0)) {
    Action();
    tmpPalmas = millis();
    contPalmas = 0;
  }
}
 
void Action() {
  if (contPalmas == 2) {
    digitalWrite(pinRelay, !digitalRead(pinRelay));
  }
}
