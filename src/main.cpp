#include <Arduino.h>

#include <Middle_esp_UART.h>
#include <Middle_esp_wifi.h>

void setup()
{
  // Set up UART 2 for Middle ESP32
  init_UART();

  // Set up EPS-NOW for Middle ESP32
  init_ESPNOW_sender();
}

void loop()
{
  // Receiving UART from Master ESP32
  receiveUART();

  // Sending UART data from Middle to Slave
  sendingUART_throughESPNOW();
}