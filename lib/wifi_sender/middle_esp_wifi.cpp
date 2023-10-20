#include <esp_now.h>
#include <WiFi.h>

#include "../UART_receiver/middle_esp_UART.h"
 
// MAC Address of the receiver - Slave ESP32
uint8_t slaveAddress[] = {0xB0, 0xA7, 0x32, 0x16, 0x1E, 0x24};

// PMK and LMK keys
static const char* PMK_KEY_STR = "_A_H_L_T_T_T_ED3";
static const char* LMK_KEY_STR = "_SON_DINH_VU_ED3";

// Define a testing message structure
typedef struct {
  int8_t joystick;
} UART_receivedMessage;
 
// Create a testing data object
UART_receivedMessage UART_receivedData;
 
// Create a slave peer object
esp_now_peer_info_t slavePeer;
 
// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery SUCCESS!" : "Delivery FAIL...");
}
 
void init_espnow_sender()
{ 
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW...");
    return;
  }

  // Set PMK key
  esp_now_set_pmk((uint8_t *)PMK_KEY_STR);

  // Register peer
  memcpy(slavePeer.peer_addr, slaveAddress, 6);
  slavePeer.channel = 0;
    ///*** Set the slave device's LMK ***///
    for (uint8_t i = 0; i < 16; i++)
    {
      slavePeer.lmk[i] = LMK_KEY_STR[i];
    }
  slavePeer.encrypt = true; // Only slave peer is accessible
  
  // Add slave peer as receiver    
  if (esp_now_add_peer(&slavePeer) != ESP_OK)
  {
    Serial.println("Failed to add peer...");
    return;
  }

  // Register the send callback
  esp_now_register_send_cb(OnDataSent);
}
 
void sendingUART_throughESPNOW()
{ 
  // Format structured UART data
  UART_receivedData.joystick = data2;
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(slaveAddress, (uint8_t *) &UART_receivedData, sizeof(UART_receivedData));
  
  if (result == ESP_OK)
  {
    Serial.println("Sending is CONFIRMED!");
  }
  else
  {
    Serial.println("Sending is ERROR...");
  }
  delay(20);
}