#include <HardwareSerial.h>

int8_t LJSY, RJSX, RJSY, L1, R1;

void init_UART()
{
  Serial.begin(115200);
  // Initiate UART1 for Intermediate ESP32
  // SerialPort1.begin(115200,SERIAL_8N1, 4, 2);

  // Initiate UART2 for Intermediate ESP32
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
}

void receiveUART()
{  
  if (Serial2.available()) // Check whether data is sent from the Master through UART2
  {
    // Read the data sent
    LJSY = Serial2.read();
    RJSX = Serial2.read();
    RJSY = Serial2.read();
    L1 = Serial2.read();
    R1 = Serial2.read();
    Serial.printf("%d   %d   %d   %d   %d\n", LJSY, RJSX, RJSY, L1, R1); // Print out data
  }
}