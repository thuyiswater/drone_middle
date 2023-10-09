// #include <Adafruit_MPU6050.h>
#include <Arduino.h>
#include "../lib/esp_wifi/init_esp_wifi.h"
#include <HardwareSerial.h>

HardwareSerial SerialPort(2); // use UART2

char number  = ' ';
int LED = 15;

void setup(){
  // Start serial with platform baudrate/monitor speed
  Serial.begin(115200);
  init_esp(); // Initialize ESP NOW protocol
  Serial.println("Ready.");

  // Initiate UART2 for Intermediate ESP32
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
  pinMode(LED, OUTPUT);
}

void loop()
{
  if (SerialPort.available())
  {
    char number = SerialPort.read();
    if (number == '1') {
      digitalWrite(LED, HIGH);
    }
  }
}

