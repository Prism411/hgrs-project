
void setup() {
  pinMode(4, INPUT);
  Serial.begin(9600);
}

int medio = 210;
int alto = 620;
// medio 210~620
// 1~210 valor rebaixado
// 620~1023 valor extendido 
void loop() {
    //for (int i = 0; i < 10; i++) {
    //Serial.println();
  //}

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

  if (mindinho < 210 && anelar < 210 && meio < 210 && indicador < 210 && dedao > 523){
    Serial.println("A");
  }
  if (mindinho > alto && anelar > alto && meio > alto && indicador > alto && dedao < medio){
    Serial.println("B");
  }
  if ((mindinho > 400 && mindinho < 800) && (anelar > 400 && anelar < 800) && (meio > 400 && meio < 800) && (indicador > 400 && indicador < 800) && (dedao > 210 && dedao < 800)){
    Serial.println("C");
  }
    if ((mindinho > 210 && mindinho < 620) && (anelar > 210 && anelar < 620) && (meio > 210 && meio < 620) && (indicador > 620) && (dedao > 210 && dedao < 620)){
    Serial.println("D");
  }
    if (mindinho < 210 && anelar < 210 && meio < 210 && indicador < 210 && dedao < 210){
    Serial.println("E");
  }
    if (mindinho > 712 && anelar > 712 && meio > 712 && indicador < 210 && dedao > 712){
    Serial.println("F");
  }
    if (mindinho < 210 && anelar < 210 && meio < 210 && indicador > 712 && (dedao > 400 && dedao < 620)){
    Serial.println("G");
  }

  //Ajustar Isso aqui no futuro (dedao)  (Mesma coisa de K) (Conflito com K e H)
    if (mindinho < 210 && anelar < 210 && meio > 712 && indicador > 712 && dedao > 550){
    Serial.println("H");
  }

  //Ajustar Isso aqui no futuro (dedao)
    if (mindinho > 712 && anelar < 210 && meio < 210 && indicador < 210 && (dedao > 210 && dedao < 620)){
    Serial.println("I");
  }

    //Ajustar Isso aqui no futuro (dedao)
    if (mindinho > 712 && anelar < 210 && meio < 210 && indicador < 210 && (dedao < 210)){
    Serial.println("J");
  }

    //Ajustar Isso aqui no futuro (dedao) (Mesma coisa de H) (Conflito com K e H)
    if (mindinho < 210 && anelar < 210 && meio > 712 && indicador > 712 && dedao > 550){
    Serial.println("K");
  }


    if (mindinho < 210 && anelar < 210 && meio < 210 && indicador > 800 && dedao > 820){
    Serial.println("L");
  }

  
    if (mindinho < 210 && anelar > 712 && meio > 712 && indicador > 712 && dedao < 210){
    Serial.println("M");
  }
      if (mindinho < 210 && anelar < 210 && meio > 712 && indicador > 712 && dedao < 210){
    Serial.println("N");
  }

  if ((mindinho > 200 && mindinho < 400) && (anelar > 210 && anelar < 420) && (meio > 210 && meio < 420) && (indicador > 210 && indicador < 420) && (dedao > 210 && dedao < 620)){
    Serial.println("O");
  }


  //Aqui ele precisa estar na vertical (deitado) (Conflito com K e H)
   if (mindinho < 210 && anelar < 210 && meio > 712 && indicador > 712 && (dedao > 210 && dedao < 620)){
    Serial.println("P");
  }


}