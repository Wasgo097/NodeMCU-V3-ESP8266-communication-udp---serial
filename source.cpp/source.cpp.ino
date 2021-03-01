#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#define Debug
const char* ssid = "ssid";
const char* password = "password";
WiFiUDP Udp;
const unsigned int localUdpPort = 4210;
const int buffer_size=255;
char Buffer[buffer_size]; 
void setup(){
  Serial.begin(115200);
#ifdef Debug
  Serial.printf("Connecting to %s ", ssid);
#endif
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
#ifdef Debug
    Serial.print(".");
#endif
  }
#ifdef Debug
  Serial.println(" connected");
#endif
  Udp.begin(localUdpPort);
#ifdef Debug
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
#endif
}
void FromWiFiToSerial(){
  int packetSize = Udp.parsePacket();
  if (packetSize){
#ifdef Debug
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
#endif
    int len = Udp.read(Buffer, buffer_size);
    if (len > 0)
      Buffer[len] = 0;
#ifdef Debug
    Serial.printf("UDP packet contents: %s\n", Buffer);
#endif
#ifdef Debug
    Serial.write(Buffer);
#else
    Serial.println(Buffer);
#endif
    Serial.flush();
  }
}
void FromSerialToWifi(){
    if(Serial.available()>0){
    int len=Serial.readBytesUntil('\n', Buffer, buffer_size);
    if(len>0)
      Buffer[len]='\0';
#ifdef Debug
    Serial.println(Buffer);
#endif
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(Buffer);
    Udp.endPacket();
    }
}
void loop(){
  FromWiFiToSerial();
  FromSerialToWifi();
}
