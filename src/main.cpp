// #include <Adafruit_MPU6050.h>
#include <Arduino.h>
#include "../lib/esp_wifi/init_esp_wifi.h"
#include <HardwareSerial.h>
#include <ESP32Servo.h>

HardwareSerial SerialPort2(2); // use UART2
HardwareSerial SerialPort1(1);
Servo ESC;

int8_t data1 = 0;
int data2 = 0;
int EscPin = 5;
int Throttle = 0;
void setup()
{
  // Start serial with platform baudrate/monitor speed
  Serial.begin (115200);
  SerialPort1.begin(115200,SERIAL_8N1, 4, 2 );
  // Initiate UART2 for Intermediate ESP32
  SerialPort2.begin(115200, SERIAL_8N1, 16, 17);
  // Check if the data has received yet to initiate the ESP-NOW protocol
  ESC.attach(EscPin,1000,2000);
}

void loop(){
  // This will be moved to slave (doi function do Slave nhan WiFi)
  if(SerialPort1.available()){
    data1 = SerialPort1.read();
    Serial.printf("%d\n", data1);
  }

  if (SerialPort2.available()) {
      data2 = SerialPort2.read();
      // Serial.printf("%d\n",data);
      if (data2 == 1){
        Throttle++;
        if (Throttle >= 255) {
          Throttle = 255;
        }
      };

      if (data2 == 2) {
        Throttle--;
        if (Throttle <=  0) {
          Throttle = 0;
        }
      };

    } 
    Serial.printf("%d\n", Throttle);
    int ControlPWM = map(Throttle, 0, 1023, 0 ,255);
    ESC.write(ControlPWM);
}