#include <Arduino.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const unsigned long READ_INTERVAL = 60000;
unsigned long lastReadTime = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Starting ESP32 DHT Sensor...");
  dht.begin();

  // small stabilization delay for the sensor
  delay(2000);

  // immediate first read
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  if (!isnan(hum) && !isnan(temp)) {
    Serial.print("Temperature: ");
    Serial.print(temp, 1);
    Serial.print(" °C, Humidity: ");
    Serial.print(hum, 1);
    Serial.println(" %");
  } else {
    Serial.println("Initial read failed (will try later).");
  }

  lastReadTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastReadTime >= READ_INTERVAL) {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
    } else {
      Serial.print("Temperature: ");
      Serial.print(temperature, 1);
      Serial.print(" °C, Humidity: ");
      Serial.print(humidity, 1);
      Serial.println(" %");
    }
    lastReadTime = currentTime;
  }
}