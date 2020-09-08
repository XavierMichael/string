#include "shox96_0_2.h"
#include <SD.h>
#include "SPI.h"
#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#define SD_ENABLED      1
#define SHOX_ENABLED    1
#define ESP_ENABLED     1

#if SD_ENABLED
    #define CS_PIN     7
    File myFile;
#endif// SD_ENABLED

#if ESP_ENABLED
/*TO DO: Write function and parameters to use to send data to webserver*/
#endif// ESP_ENABLED
void setup() {
    Serial.begin(115200);
    // put your setup code here, to run once:
    #if SD_ENABLED
        if (!SD.begin(CS_PIN)) {
        Serial.println("initialization failed!");
        return;
        }
        Serial.println("initialization done.");
    #endif// SD_ENABLED
}

void loop() {
  // put your main code here, to run repeatedly:
  #if SHOX_ENABLED
      char str[2048];
      char cbuf[2100];
  #endif
  /*Read txt file and store in str variable.*/
  #if SD_ENABED
  // open the file for reading:
  myFile = SD.open("2048.txt", FILE_READ);
  if (myFile) {
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      for(int i = 0; i<2048; i++)
      {
        str[i] = myFile.read();
      }
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening 2048.txt");
  }
  #endif// SD_ENABLED

  #if SHOX_ENABLED
      memset(cbuf, 0, sizeof(cbuf));
      shox96_0_2_compress(str, 2048, cbuf, NULL);
  #endif// SHOX_ENABLED

  #if SD_ENABLED
      myFile = SD.open("2048_c.txt", FILE_WRITE);
      if (myFile) {
        // read from the file until there's nothing else in it:
          for(int i = 0; i<2048; i++)
          {
            myFile.print(str[i]);
          }
        // close the file:
        myFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening 2048_c.txt");
      } 
  #endif// SD_ENABLED 
  #if ESP_ENABLED
    postFileContent("/2048.txt"); // Read file data_log.txt in Root directory
    postFileContent("/2048_c.txt"); // Read file data_log.txt in Root directory
  #endif// ESP_ENABLED
}

#if ESP_ENABLED
void postFileContent(const char * path)
{
    /*TODO: Code to send file data to webserver*/
}
#endif// ESP-ENABLED
