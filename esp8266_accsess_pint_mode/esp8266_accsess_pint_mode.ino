#include "Arduino.h"
//The setup function is called once at startup of the sketch
#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266mDNS.h>

//
//IPAddress local_IP(192,168,4,22);
//IPAddress gateway(192,168,4,9);
//IPAddress subnet(255,255,255,0);

void setup()
{
  Serial.begin(115200);
  Serial.println();

//  Serial.print("Setting soft-AP configuration ... ");
//  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP("ESP8266", "asdfqwerty") ? "Ready" : "Failed!");

  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
}

void loop() {}
