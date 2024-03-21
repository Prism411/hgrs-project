
void setup() {
  pinMode(4, INPUT);
  Serial.begin(9600);
}

// 210~620 Valor dedo Medio
// 1~210 valor rebaixado
// 620~1023 valor extendido 
void loop() {
    for (int i = 0; i < 10; i++) {
    Serial.println();
  }

  // Lê o valor do pino analógico A0.
  int mindinho = analogRead(A0);
  // Lê o valor do pino analógico A1.
  int anelar = analogRead(A1);
  // Lê o valor do pino analógico A2.
  int meio = analogRead(A2);
  // Lê o valor do pino analógico A3.
  int indicador = analogRead(A3);
  // Lê o valor do pino analógico A4.
  int dedao = analogRead(A4);

  if (mindinho)

  delay(1000);
}