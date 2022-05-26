/* *********************************************************************************** *
 * Author : Elektro Project
 * Date   : 16 Mei 2022
 * Desc.  : using RFID Card Reader to scan UID Card 
 *          
 *          Microcontroller Board Setting Tools
 *          - Board       --> NodeMCU 1.0 (ESP-12E Module)
 *          - Upload Speed--> 921600
 *          - Port        --> COM__ ??? (listen list on your device)
 *          
 *          Pin configuration RFID-MFRC522
 *          - D0 (GPIO16) --> RST
 *          - D8 (GPIO15) --> SDA/SS
 *          - D5 (GPIO12) --> SCK
 *          - D6 (GPIO14) --> MISO
 *          - D7 (GPIO13) --> MOSI
 *          
 *    Support we on YouTube channel: https://www.youtube.com/c/ElektroProject
 * 
 * *********************************************************************************** */
#include <SPI.h>
#include <MFRC522.h> 

#define SS_PIN        15      // D8 NodeMCU
#define RST_PIN       16      // D0 NodeMCU

byte uid[4];
String cardID;

MFRC522 rfid(SS_PIN, RST_PIN); 

void setup() {
  Serial.begin(9600);
  SPI.begin();
  
  // Initial MFRC RFID Reader Module 
  rfid.PCD_Init();
  rfid.PCD_SetAntennaGain(rfid.RxGain_max);

}

void loop() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    for (byte i=0; i<4; i++) {
      uid[i] = rfid.uid.uidByte[i];
    }
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
      
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}

void printHex(byte *buffer, byte bufferSize) {
  cardID = "";
  Serial.print("Card found.. \n");
  
  for (byte i = 0; i < bufferSize; i++) 
  {    
    cardID += String(buffer[i] < 0x10 ? "0" : "");
    cardID += String(buffer[i], HEX);
    cardID.toUpperCase();
  } 
  Serial.print(cardID);
}

