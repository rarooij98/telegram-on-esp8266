#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>
#include "Adafruit_NeoPixel.h"
 
// Replace with your network credentials
const char* ssid = "Spothot";
const char* password = "12345678";
 
// Initialize Telegram BOT
#define BOTtoken "5407707540:AAGRMdZeTAwBwGo9hEtj99o-H_W-6oVsSsM"  // your Bot Token (Get from Botfather)
 
// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "5378189364"

// Ledstrip
#define PIN          D5
#define NUM_PIXELS   14
Adafruit_NeoPixel pixels(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
 
#ifdef ESP8266
  X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif
 
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
 
// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

//const int ledPin = 2;
const int ledPin = PIN;
bool ledState = LOW;
 
// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));
 
  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
     
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);
 
    String from_name = bot.messages[i].from_name;
 
    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control your outputs.\n\n";
      welcome += "/led_on to turn GPIO ON \n";
      welcome += "/led_off to turn GPIO OFF \n";
      welcome += "/state to request current GPIO state \n";
      bot.sendMessage(chat_id, welcome, "");
    }
 
    if (text == "/led_on") {
      bot.sendMessage(chat_id, "LED state set to ON", "");

      for(int i=0; i<NUM_PIXELS; i++) { // For each pixel...
        pixels.setPixelColor(i, pixels.Color(0, 150, 0));
        pixels.show();   // Send the updated pixel colors to the hardware.
        delay(DELAYVAL); // Pause before next pass through loop
      }
    }
     
    if (text == "/led_off") {
      bot.sendMessage(chat_id, "LED state set to OFF", "");

      for(int i=0; i<NUM_PIXELS; i++) { // For each pixel...
        pixels.setPixelColor(i, pixels.Color(0, 0, 0)); //turn to black to "turn off"
        pixels.show();   // Send the updated pixel colors to the hardware.
      }
    }
     
    if (text == "/state") {
      if (pixels.getPixelColor(i) == (0, 0, 0)){
        bot.sendMessage(chat_id, "LED is OFF", "");
      }
      else{
        bot.sendMessage(chat_id, "LED is ON", "");
      }
    }
  }
}
 
void setup() {
  Serial.begin(115200);
 
  #ifdef ESP8266
    configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
    client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  #endif
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
   
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}
 
void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
 
    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
