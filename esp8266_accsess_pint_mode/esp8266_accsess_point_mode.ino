#include "Arduino.h"
#include <ESP8266WiFi.h>       		 // Include the Wi-Fi library
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server (80);		// Create a webserver object that listens for HTTP request on port 80

void handleRoot();					// function prototypes for HTTP handlers
void handleNotFound();				// function prototypes for HTTP handlers


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP("ESP8266", "asdfqwerty") ? "Ready" : "Failed!");
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);				// Call the 'handleRoot' function when a client requests URI "/"
  server.onNotFound(handleNotFound);
  server.begin();							// Actually start the server
  Serial.println("HTML server started!");

}

void loop() {
	server.handleClient();					// Listen for HTTP requests from clients

}

void handleRoot(){
	server.send(200, "text/plain", "Hello World");		// Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleNotFound(){
	server.send(404, "text/plain", "404: Not found");	// Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
