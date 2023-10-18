#include <HardwareSerial.h>
#include "../wifi_sender/middle_esp_wifi.h"

// HardwareSerial SerialPort1(1); // use UART1
HardwareSerial SerialPort2(2); // use UART2

// int8_t data1;
uint8_t data2;

void init_UART()
{
  Serial.begin(115200);
  // Initiate UART1 for Intermediate ESP32
  // SerialPort1.begin(115200,SERIAL_8N1, 4, 2);

  // Initiate UART2 for Intermediate ESP32
  SerialPort2.begin(115200, SERIAL_8N1, 16, 17);
}

void receiveUART()
{
  // if(SerialPort1.available()) // Check whether data is sent from the Master through UART1
  // {
  //   data1 = SerialPort1.read(); // Read the data sent
  //   Serial.printf("%d\n", data1); // Print out data
  // }
  // else
  // {
  //   data1 = 0;
  //   Serial.printf("%d\n", data1); // Print out data
  //   delay(20);
  // }
  
  if (SerialPort2.available()) // Check whether data is sent from the Master through UART2
  {
    data2 = SerialPort2.read(); // Read the data sent
    Serial.printf("%d\n", data2); // Print out data
    delay(20);
  }
  else
  {
    data2 = 0;
    Serial.printf("%d\n", data2); // Print out data
    delay(20);
  }
}