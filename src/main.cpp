#include <Arduino.h>

#include "../lib/wifi_sender/middle_esp_wifi.h"
#include "../lib/UART_receiver/middle_esp_UART.h"

void setup()
{
  // Set up UART 1 & 2 for middle ESP32
  init_UART();
  // Set up EPS-NOW for middle ESP32
  init_espnow_sender();
}

void loop()
{
  // Receiving UART from master ESP32
  receiveUART();

  // Sending UART data from middle to slave
  sendingUART_throughESPNOW();
}