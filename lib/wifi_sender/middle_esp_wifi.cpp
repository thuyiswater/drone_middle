#include <esp_now.h>
#include <WiFi.h>
#include <Middle_esp_UART.h>
 
// MAC Address of the receiver - Slave ESP32
uint8_t slaveAddress[] = {0xB0, 0xA7, 0x32, 0x16, 0x1E, 0x24};

// PMK and LMK keys
static const char* PMK_KEY_STR = "_A_H_L_T_T_T_ED3";
static const char* LMK_KEY_STR = "_SON_DINH_VU_ED3";

// Define a UART message structure
typedef struct {
  int8_t LeftY;
  int8_t RightX;
  int8_t RightY;
  int8_t Left1;
  int8_t Right1;
} UART_receivedMessage;

// Define a GPS message structure
typedef struct {
  int8_t Long;
  int8_t Lat;
} GPS_receivedMessage;
 
// Create an object for UART
UART_receivedMessage UART_receivedData;

// Create an object for GPS
GPS_receivedMessage gpsData;
 
// Create a slave peer object
esp_now_peer_info_t slavePeer;
 
// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  // Serial.print("\r\nLast Packet Send Status:\t");
  // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery SUCCESS!" : "Delivery FAIL...");
}

// Callback function called when data is sent
// void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
//   memcpy(&gpsData, incomingData, sizeof(gpsData));
//   Serial.print("Longtitude: ");
//   Serial.println(gpsData.Long);
//   Serial.print("Latitude: ");
//   Serial.println(gpsData.Lat);
// }

void init_ESPNOW_sender()
{ 
  // Set Middle ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW...");
    return;
  }

  // Set PMK key for Middle ESP32
  esp_now_set_pmk((uint8_t *)PMK_KEY_STR);

  // Register Slave ESP32 peer
  memcpy(slavePeer.peer_addr, slaveAddress, 6);
  slavePeer.channel = 0;

    ///*** Set the Slave ESP32's LMK ***///
    for (uint8_t i = 0; i < 16; i++)
    {
      slavePeer.lmk[i] = LMK_KEY_STR[i];
    }

  slavePeer.encrypt = true; // Only Slave ESP32 peer is accessible
  
  // Add Slave ESP32 peer as receiver    
  if (esp_now_add_peer(&slavePeer) != ESP_OK)
  {
    Serial.println("Failed to add peer...");
    return;
  }

  // Register the callback for sent data
  esp_now_register_send_cb(OnDataSent);

  // Register the callback for received data
  // esp_now_register_recv_cb(OnDataRecv);
}
 
void sendingUART_throughESPNOW()
{ 
  // Format structured UART data
  UART_receivedData.LeftY = LJSY;
  UART_receivedData.RightX = RJSX;
  UART_receivedData.RightY = RJSY;
  UART_receivedData.Left1 = L1;
  UART_receivedData.Right1 = R1;
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(slaveAddress, (uint8_t *) &UART_receivedData, sizeof(UART_receivedData));
  
  // if (result == ESP_OK)          /// DEBUG ONLY ///
  // {
  //   Serial.println("Sending is CONFIRMED!");
  // }
  // else
  // {
  //   Serial.println("Sending is ERROR...");
  // }
}