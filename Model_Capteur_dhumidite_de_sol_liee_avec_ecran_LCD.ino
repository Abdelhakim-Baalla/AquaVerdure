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
