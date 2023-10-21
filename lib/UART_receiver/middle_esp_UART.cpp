#include <HardwareSerial.h>

HardwareSerial SerialPort2(2); // use UART2

int8_t data1, data2, data3;

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
  if (SerialPort2.available()) // Check whether data is sent from the Master through UART2
  {
    data1 = SerialPort2.read(); // Read the data sent
    delay(10);
    data2 = SerialPort2.read();
    delay(10);
    data3 = SerialPort2.read();
    delay(10);
    Serial.printf("%d   %d   %d\n", data1, data2, data3); // Print out data
  }
}