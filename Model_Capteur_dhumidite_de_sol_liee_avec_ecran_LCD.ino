#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adresse LCD (0x27 ou 0x3F)

int capteur = A0;        // Broche du capteur
int valeur;              // Valeur lue du capteur
int pourcentage;         // Pourcentage d'humidité
unsigned long dernierChangement = 0;  // Pour le changement d'affichage
int ecran = 0;           // Quel écran afficher

// Messages de conseils
const char* conseils[] = {
  "Arrose la plante!",
  "C'est parfait :)",
  "Arrosage OK!",
  "Trop d'eau!!!"
};

void setup() {
  Serial.begin(9600);
  lcd.init();            // Démarrer l'écran
  lcd.backlight();       // Allumer le rétro-éclairage
  
  // Animation de démarrage
  lcd.setCursor(0, 0);
  lcd.print("Bonjour! :)");
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 1);
    lcd.print(".");
    delay(100);
  }
  delay(500);
  lcd.clear();
}

void loop() {
  // Lire la valeur du capteur
  valeur = analogRead(capteur);
  
  // Convertir en pourcentage (0-100%)
  pourcentage = map(valeur, 1023, 0, 0, 100);
  if (pourcentage < 0) pourcentage = 0;
  if (pourcentage > 100) pourcentage = 100;
  
  // Changer d'écran toutes les 3 secondes
  if (millis() - dernierChangement > 3000) {
    ecran = (ecran + 1) % 2;
    dernierChangement = millis();
  }
  
  // Afficher les informations
  afficherInfos();
  
  delay(500);  // Petite pause
}

void afficherInfos() {
  lcd.clear();
  
  // Première ligne : Humidité et animation
  lcd.setCursor(0, 0);
  lcd.print("H:");
  lcd.print(pourcentage);
  lcd.print("% ");
  
  if (pourcentage < 30) {
    lcd.print("SEC");
    animationGoutte();
    if (ecran == 1) {
      lcd.setCursor(0, 1);
      lcd.print(conseils[0]);  // Arrose!
    }
  } 
  else if (pourcentage < 65) {
    lcd.print("BON");
    animationSmiley();
    if (ecran == 1) {
      lcd.setCursor(0, 1);
      lcd.print(conseils[1]);  // Parfait
    }
  } 
  else {
    lcd.print("HUM");
    animationPluie();
    if (ecran == 1) {
      lcd.setCursor(0, 1);
      // Choisir le bon conseil
      lcd.print(pourcentage > 85 ? conseils[3] : conseils[2]);
    }
  }
  
  // Deuxième ligne : Barre de progression
  if (ecran == 0) {
    lcd.setCursor(0, 1);
    int barres = map(pourcentage, 0, 100, 0, 16);
    for (int i = 0; i < 16; i++) {
      lcd.print(i < barres ? "|" : " ");
    }
  }
}

// Animation quand c'est trop sec
void animationGoutte() {
  static int etape = 0;
  lcd.setCursor(14, 0);
  etape = (etape + 1) % 4;
  switch(etape) {
    case 0: lcd.print("v "); break;
    case 1: lcd.print(" v"); break;
    case 2: lcd.print(". "); break;
    case 3: lcd.print(" ."); break;
  }
}

// Animation quand c'est bon
void animationSmiley() {
  static int etape = 0;
  lcd.setCursor(14, 0);
  etape = (etape + 1) % 3;
  switch(etape) {
    case 0: lcd.print(":)"); break;
    case 1: lcd.print("8)"); break;
    case 2: lcd.print(":]"); break;
  }
}

// Animation quand trop humide
void animationPluie() {
  static int etape = 0;
  lcd.setCursor(14, 0);
  etape = (etape + 1) % 4;
  switch(etape) {
    case 0: lcd.print("///"); break;
    case 1: lcd.print("\\|\\"); break;
    case 2: lcd.print("|||"); break;
    case 3: lcd.print("..."); break;
  }
}