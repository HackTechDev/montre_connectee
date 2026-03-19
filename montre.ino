#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

unsigned long previousMillis = 0;
unsigned long elapsedSeconds = 0;

// Date simulée de départ
int jour = 16;
int mois = 3;
int annee = 26;

// Pour éviter d’incrémenter plusieurs fois dans la même minute
unsigned long lastMinuteHandled = 0;

// Déclaration écran OLED I2C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(40, 20);
  display.println("HACKLAB");
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setCursor(40, 20);
  display.println("ILARD");
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setCursor(40, 20);
  display.println("SAM");
  display.display();
  delay(2000);

  display.clearDisplay();
  display.drawCircle(64, 20, 5, SSD1306_WHITE);
  display.display();
  delay(2000);

  display.clearDisplay();
  display.drawRect(32, 16, 64, 16, SSD1306_WHITE);
  display.drawLine(32, 24, 128, 24, SSD1306_WHITE);
  display.drawLine(64, 16, 64, 48, SSD1306_WHITE);
  display.display();
  delay(2000);

  display.clearDisplay();
}

void loop() {
  unsigned long currentMillis = millis();

  // Mise à jour de l'heure chaque seconde
  if (currentMillis - previousMillis >= 1000) {
    previousMillis += 1000;
    elapsedSeconds++;
  }

  int heures = (elapsedSeconds / 3600) % 24;
  int minutes = (elapsedSeconds / 60) % 60;
  int secondes = elapsedSeconds % 60;

  // Nombre total de minutes écoulées depuis le démarrage
  unsigned long totalMinutes = elapsedSeconds / 60;

  // Mise à jour de la date UNE SEULE FOIS par minute
  if (totalMinutes != lastMinuteHandled) {
    lastMinuteHandled = totalMinutes;

    jour++;

    if (jour % 3 == 0) {
      mois++;

      if (mois == 3 || mois == 6 || mois == 9 || mois == 12) {
        annee++;
      }

      // Optionnel : revenir à 1 après 12
      if (mois > 12) {
        mois = 1;
      }
    }

    // Optionnel : revenir à 1 après 31
    if (jour > 31) {
      jour = 1;
    }
  }

  char dateBuffer[9];
  char timeBuffer[9];

  sprintf(dateBuffer, "%02d/%02d/%02d", jour, mois, annee);
  sprintf(timeBuffer, "%02d:%02d:%02d", heures, minutes, secondes);

  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(40, 16);
  display.println(dateBuffer);

  display.setCursor(40, 25);
  display.println(timeBuffer);

  display.display();
}