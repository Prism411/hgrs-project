// ----------------------------------------------------------------------------
// Project: Hand Gesture Recognition System (HGRS Project)
// ----------------------------------------------------------------------------
// University: Universidade Federal de Rondônia (UNIR)
// ----------------------------------------------------------------------------
// Students: 
//   - Andrey Riça
//   - Jáder Louis
//   - Nicolas Sales
//   - Samih Santos
//   - Nicolas Sales
//   - Wyllgner França
// ----------------------------------------------------------------------------
// Project Sponsor: NAVETECH
// ----------------------------------------------------------------------------
// Sponsorship: Samsung in partnership with Fundação de Apoio ao Desenvolvimento 
// do Ensino, Ciência e Tecnologia do Estado de Rondônia (FUNDAPE)
// ----------------------------------------------------------------------------
#include <LiquidCrystal.h>

// Define LCD and sensor pins
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;

void setup() {
  // Set up the LCD
  lcd_1.begin(16, 2); 

  // Initial message on the LCD
  lcd_1.print("Nenhuma Letra");

  // Set up sensor pins
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() { 
  // Read sensor values
  a = analogRead(A4); // dedao
  c = analogRead(A1); // indicador
  d = analogRead(A2); // middle
  b = analogRead(A3); // anelar
  e = analogRead(A0); // mindinho

  // Set LCD cursor position
  lcd_1.setCursor(0, 1);

  // Check each gesture pattern
  if (a > 850 && b > 850 && c > 850 && d > 850 && e > 850 && a > 850) {
    Serial.println("a");
    lcd_1.clear();  // Clear the LCD screen
    lcd_1.print("Letra feita: a");
  }

  if (a > 850 && b < 850 && c < 850 && e < 850) {
    Serial.println("b");
    lcd_1.clear();
    lcd_1.print("Letra feita: b");
  }

  // (Continue with other gesture patterns...)

  // Delay for stability
  delay(250);
  lcd_1.setCursor(0, 0);
  lcd_1.print("Nenhuma Letra");
  lcd_1.setCursor(0, 1);
}
