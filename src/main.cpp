// #include <Adafruit_MPU6050.h>
#include <Arduino.h>
#include "../lib/esp_wifi/init_esp_wifi.h"
#include <HardwareSerial.h>
#include <ESP32Servo.h>

HardwareSerial SerialPort(2); // use UART2
Servo ESC;
int data = 0;
int LED = 15;
int EscPin = 5;
int Throttle = 0;
void setup()
{
  // Start serial with platform baudrate/monitor speed
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  // Initiate UART2 for Intermediate ESP32
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
  // Check if the data has received yet to initiate the ESP-NOW protocol
  ESC.attach(EscPin,1000,2000);
}

void loop(){



  if (SerialPort.available()) {
      data = SerialPort.read();
      Serial.printf("%d\n",data);
      if(data == 1){
        Throttle = 0;
      } else if(data ==2) {
        Throttle = 100;
      } else if (data == 3){
        Throttle = 150;
      } else if (data == 4){
        Throttle = 200;
      }
  } 
  int ControlPWM = map(Throttle, 0, 1023, 0 ,100);
  ESC.write(ControlPWM);

}