#include "Arduino.h"
#include <ESP8266WiFi.h>       		 // Include the Wi-Fi library
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server (80);		// Create a webserver object that listens for HTTP request on port 80

const int led = 2;

void handleRoot();					// function prototypes for HTTP handlers
void handleNotFound();				// function prototypes for HTTP handlers
void handleLED();


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP("ESP8266", "asdfqwerty") ? "Ready" : "Failed!");
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());

  server.on("/",HTTP_GET, handleRoot);				// Call the 'handleRoot' function when a client requests URI "/"
  server.on("/LED", HTTP_POST, handleLED);			// Call the 'handleLED' function when a POST request is made to URI "/LED"
  server.onNotFound(handleNotFound);
  server.begin();									// Actually start the server
  Serial.println("HTML server started!");
}

void loop() {
	server.handleClient();							// Listen for HTTP requests from clients
}

void handleRoot(){
	server.send(200, "text/html", "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");		// When URI / is requested, send a web page with a button to toggle the LED
}

void handleLED(){									// If a POST request is made to URI /LED
	digitalWrite(led, !digitalRead(led));		 	// Change the state of the LED
	server.sendHeader("Location", "/");				// Add a header to respond with a new location for the browser to go to the home page again
	server.send(303);								// Send it back to the browser with an HTTP status 303 (See Other) to redirect
	Serial.println("LED is now: ");
	Serial.print("\t");
	Serial.print(digitalRead(led));
}

void handleNotFound(){
	server.send(404, "text/plain", "404: Not found");	// Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}


