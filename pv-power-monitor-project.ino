#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_INA219 ina219;

void setup() {
  Serial.begin(9600);

  if (!ina219.begin()) {
    Serial.println("INA219 not found");
    while (1);
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 not found");
    while (1);
  }

  display.clearDisplay();
}

void loop() {

  float voltage = ina219.getBusVoltage_V();
  float current = ina219.getCurrent_mA();
  float power   = ina219.getPower_mW();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,0);
  display.print("Voltage: ");
  display.print(voltage,2);
  display.println(" V");

  display.print("Current: ");
  display.print(current,1);
  display.println(" mA");

  display.print("Power: ");
  display.print(power,1);
  display.println(" mW");

  display.display();

  delay(1000);
}