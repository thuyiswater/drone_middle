#include <HardwareSerial.h>

HardwareSerial SerialPort2(2); // use UART2

int8_t LJSX, LJSY, RJSX, RJSY;

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
    // Read the data sent
    LJSX = SerialPort2.read();
    LJSY = SerialPort2.read();
    RJSX = SerialPort2.read();
    RJSY = SerialPort2.read();
    Serial.printf("%d   %d   %d   %d\n", LJSX, LJSY, RJSX, RJSY); // Print out data
  }
}