#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int sensorPin = A0; 
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();           
  lcd.backlight();      
  lcd.setCursor(0, 0);
  lcd.print("Humidite du sol: ");
}


void loop() {
  sensorValue = analogRead(sensorPin); 

  Serial.print("Humidite du sol: ");
  Serial.println(sensorValue);

  lcd.setCursor(0, 1); 

  if (sensorValue > 700) {  // Sol sec
    lcd.print("Sec   ");
  } else if (sensorValue > 400) { // Humidite moyenne
    lcd.print("Humide");
  } else {  // Sol tres humide
    lcd.print("Mouille");
  }

  delay(1000); // Attente 1 seconde
}