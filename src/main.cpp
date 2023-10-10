// #include <Adafruit_MPU6050.h>
#include <Arduino.h>
#include "../lib/esp_wifi/init_esp_wifi.h"
#include <HardwareSerial.h>

HardwareSerial SerialPort(2); // use UART2

char number  = ' ';

void setup()
{
  // Start serial with platform baudrate/monitor speed
  Serial.begin(115200);

  // Initiate UART2 for Intermediate ESP32
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);

  // Check if the data has received yet to initiate the ESP-NOW protocol
  if (SerialPort.available())
  {
    char number = SerialPort.read();
    if (number == '0')
    {
      Serial.println("Disconnected with the Middle.");
    }
    if (number == '1')
    {
      // Initialize ESP-NOW protocol
      init_esp();
      Serial.println("Connected to the Middle.");
    }
  }
}

void loop(){}

