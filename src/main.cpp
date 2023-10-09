// #include <Adafruit_MPU6050.h>
#include <Arduino.h>
#include "../lib/esp_wifi/init_esp_wifi.h"

void setup(){
  // Start serial with platform baudrate/monitor speed
  Serial.begin(115200);
  init_esp(); // Initialize ESP NOW protocol
  Serial.println("Ready.");
}

void loop() {
  
}

