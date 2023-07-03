//*******************************libraries********************************
//RFID-----------------------------
#include <SPI.h>
#include <MFRC522.h>
//NodeMCU--------------------------
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
//************************************************************************
#define SS_PIN D4
#define RST_PIN D2
//************************************************************************
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
//************************************************************************

// wifi settings
const char *ssid = "";
const char *password = "";

//additional info
String API_URL = "https://backend-websocket-production.up.railway.app/api/idcard";  //computer IP or the server domain

const char fingerprint[] PROGMEM = "9F 61 8C 4C 90 C0 CC E0 65 B3 87 86 DF 43 21 B9 3E D6 A9 B3";

void setup() {
  delay(1000);
  Serial.begin(115200);
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card
  //---------------------------------------------
  connectToWiFi();
}

void loop() {
  //check if there's a connection to Wi-Fi or not
  if (!WiFi.isConnected()) {
    connectToWiFi();  //Retry to connect to Wi-Fi
  }
  String cardID = "";
  //read the idcard
  if (mfrc522.PICC_IsNewCardPresent()) {
    //select a card
    if (mfrc522.PICC_ReadCardSerial()) {
      // construct the idcard
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        cardID += mfrc522.uid.uidByte[i];
      }
      mfrc522.PICC_HaltA();
      sendCardID(cardID);
    }
  }
  delay(1);
}


//************send the Card UID to the server*************
void sendCardID(String cardID) {
  Serial.println("Sending the Card ID");
  if (WiFi.isConnected()) {
    WiFiClientSecure httpsClient;
    HTTPClient http;  
    
    //print fingerprint
    Serial.printf("Using fingerprint '%s'\n", fingerprint);
    httpsClient.setFingerprint(fingerprint);

    //initiate HTTP request
    http.begin(httpsClient, API_URL);  

    http.addHeader("Content-Type", "application/json");
    String payload = "{\"idCard\":\"" + String(cardID) + "\"}";

    Serial.println(cardID);
    Serial.println(payload);

    // POST method
    int httpResponseCode = http.POST(payload);

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    // Free resources
    http.end();
  }
}

//********************connect to the WiFi******************
void connectToWiFi() {
  WiFi.mode(WIFI_OFF);  //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  delay(1000);
}