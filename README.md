**_ ESP32 TEMPERATURE & HUMIDITY MONITORING SYSTEM _**

This project shows how to use an ESP32-WROOM development board with a DHT11 / DHT22 sensor to measure temperature and humidity.
The results are printed on the Serial Monitor every 60 seconds.

It is designed to be simple and beginner-friendly, using the Arduino framework on PlatformIO.

**_ Features _**

Reads temperature (°C) and humidity (%) every 60 seconds

First reading happens immediately (no waiting for a full minute)

Uses millis() instead of delay() → allows adding other tasks later without blocking the loop

Error handling: if the sensor fails to read, it prints "Failed to read from DHT sensor!"

Works with both DHT11 and DHT22 sensors (just change one line in the code)

**_ Hardware Requirements _**

ESP32 DevKit V1 (ESP32-WROOM board)

DHT11 or DHT22 temperature & humidity sensor

Jumper wires

Breadboard (optional)

USB cable (for programming & powering ESP32)

**_ Wiring the Circuit _**

For DHT11/DHT22 (3-pin module):

VCC → 3.3V (ESP32)

GND → GND (ESP32)

DATA → GPIO 4 (ESP32)

**NB** If your sensor is a bare DHT11/DHT22 without a breakout board, you must add a 10kΩ resistor between DATA and VCC (pull-up resistor).

**_ Project Structure (PlatformIO) _**
Temperature_Humidity_Monitoring_System/
│── src/
│ └── main.cpp # Your main code file
│── platformio.ini # PlatformIO configuration
│── lib/ # (optional) extra libraries
│── README.md # Project documentation

**_ Software Requirements _**

VS Code

PlatformIO
extension for VS Code

DHT sensor library (PlatformIO auto-installs when you compile)

**_ Setup Instructions _**

1 Clone the Repository
git clone https://github.com/<username>/ESP32-DHT-Monitor.git
cd ESP32-DHT-Monitor

2 Open in VSCode + PlatformIO

Open the folder in VS Code

Ensure the PlatformIO extension is installed

3 Connect ESP32

Plug your ESP32 to your PC using a USB cable

Select the correct port (/dev/ttyUSB0 on Linux, COMx on Windows)

4 Build & Upload the Code

Run:

pio run --target upload

5 Open Serial Monitor

Run:

pio device monitor -b 115200

You should see something like:

Starting ESP32 DHT Sensor...
Temperature: 25.3 °C, Humidity: 60.1 %

**_ Code Overview _**

The main logic:

void setup() {
Serial.begin(115200);
delay(1000);

Serial.println("Starting ESP32 DHT Sensor...");
dht.begin();

delay(2000);

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

Key Concepts:

millis() → keeps track of time since boot (in ms), allows non-blocking delays.

isnan() → checks if the sensor gave a valid number.

**_ Common Issues & Fixes _**

No data in Serial Monitor?
→ Check baud rate = 115200.

Continuous “Failed to read from DHT sensor!”?
→ Wiring issue, wrong GPIO, or missing pull-up resistor.

Upload fails with Permission denied /dev/ttyUSB0 (Linux)?
→ Run: sudo usermod -aG dialout $USER then reboot.
