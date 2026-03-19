#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32// OLED display height, in pixels

unsigned long previousMillis = 0;
unsigned long elapsedSeconds = 0;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
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
  
}

void loop() {
  
 unsigned long currentMillis = millis();

  // Incrémente toutes les secondes
  if (currentMillis - previousMillis >= 1000) {
    previousMillis += 1000;
    elapsedSeconds++;
  }

  int heures = (elapsedSeconds / 3600) % 24;
  int minutes = (elapsedSeconds / 60) % 60;
  int secondes = elapsedSeconds % 60;

  char buffer[9];
  sprintf(buffer, "%02d:%02d:%02d", heures, minutes, secondes);

  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(40, 16); // ajusté pour centrer
  display.println("16/03/26");

  display.setCursor(40, 25);
  display.println(buffer);
  
  display.display();


}