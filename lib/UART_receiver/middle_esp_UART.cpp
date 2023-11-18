#include <Arduino.h>
#include <HardwareSerial.h>

int8_t LJSY, RJSX, RJSY, L1, R1;

void init_UART()
{
  Serial.begin(115200);
  // Initiate UART1 for Intermediate ESP32
  // SerialPort1.begin(115200,SERIAL_8N1, 4, 2)

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
  }
}

void Print_PS4_Value (){
  Serial.print("\n [");
  Serial.printf("%4d", LJSY); // LY
  Serial.print ("  ");
  Serial.printf("%4d", RJSX); // RX
  Serial.print ("  ");
  Serial.printf("%4d", RJSY); // RY
  Serial.print("] ");

  Serial.print(" [");
  Serial.print(L1); // L1
  Serial.print ("  ");
  Serial.print(R1); // R1
  Serial.print ("]");
}