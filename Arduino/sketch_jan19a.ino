// Import required libraries
#ifdef ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>
#else
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <FS.h>
#endif
#include <Wire.h>


const byte numBytes = 64;
byte receivedBytes[numBytes];
byte numReceived = 0;
double c;
boolean newData = false;

// Replace with your network credentials
const char* ssid = "IoTmeteo";
const char* password = "iotmeteo";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);


String readSentTemperature() {
  recvBytesWithStartEndMarkers();
  byte receivedNumber=receivedBytes[0];
  return String(receivedNumber);
}

String readSentHumidity() {
  byte receivedNumber=receivedBytes[1];
  return String(receivedNumber);
}

String readSentPressure() {
  int receivedNumber=receivedBytes[2]+1000;
  showNewData();
  return String(receivedNumber);
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  
  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
  delay(100);
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readSentTemperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readSentHumidity().c_str());
  });
  server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readSentPressure().c_str());
  });

  showNewData();

  // Start server
  server.begin();
}
 
void loop(){
  
}

void recvBytesWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  byte startMarker = 0xFE;
  byte endMarker = 0xFF;
  byte rb;


  while (Serial.available() > 0 && newData == false) {
    rb = Serial.read();

    if (recvInProgress == true) {
      if (rb != endMarker) {
        receivedBytes[ndx] = rb;
        ndx++;
        if (ndx >= numBytes) {
          ndx = numBytes - 1;
        }
      }
      else {
        receivedBytes[ndx] = '\0';
        recvInProgress = false;
        numReceived = ndx;
        ndx = 0;
        newData = true;
      }
    }

    else if (rb == startMarker) {
      recvInProgress = true;
    }
  }
}

void showNewData() {
  if (newData == true) {
    Serial.print("Received: ");
    for (byte n = 0; n < numReceived; n++) {
      Serial.print(receivedBytes[n], HEX);
      Serial.print(' ');
    }
    Serial.println();
    Serial.println(String(receivedBytes[0]));
    newData = false;
  }
}
