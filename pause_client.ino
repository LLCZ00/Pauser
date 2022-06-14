
/*
 sends udp message to server on specified ip, which pauses/fast forwards/rewinds videos
*/


#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>

int status = WL_IDLE_STATUS;
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;        
char pass[] = SECRET_PASS;    

char backReply[] = "a";       
char pauseReply[] = "s";
char forwardReply[] = "d";

int forward = 8;
int pause = 7;
int back = 6;

IPAddress ip(192, 168, 1, 29); // Destination IP
unsigned int port = 9516; // Destination Port

unsigned int localPort = 2390; // Local port (unused, but it's required)
WiFiUDP Udp;

void setup() {
  pinMode(forward, INPUT);
  pinMode(pause, INPUT);
  pinMode(back, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);
  
  while (!Serial) {
    ; 
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    
    status = WiFi.begin(ssid, pass);

    // wait 8 seconds for connection:
    delay(8000);
  }
  Serial.println("Connected to wifi");
  digitalWrite(LED_BUILTIN, HIGH); // Activates Arduino built-in LED upon successful wifi connection
  Udp.begin(localPort);
}

void loop() {
  if (digitalRead(back) == 1) {
    Udp.beginPacket(ip, port);
    Udp.write(backReply);
    Udp.endPacket();
    delay(500);
  }
  else if(digitalRead(pause) == 1){
    Udp.beginPacket(ip, port);
    Udp.write(pauseReply);
    Udp.endPacket();
    delay(500);
  }
  else{
    if(digitalRead(forward) == 1){
      Udp.beginPacket(ip, port);
      Udp.write(forwardReply);
      Udp.endPacket();
      delay(500);
    }
  }

}
