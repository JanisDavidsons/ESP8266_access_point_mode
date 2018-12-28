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
  server.on("/login", HTTP_POST, handleLogin);			// Call the 'handleLED' function when a POST request is made to URI "/LED"
  server.onNotFound(handleNotFound);
  server.begin();									// Actually start the server
  Serial.println("HTML server started!");
}

void loop() {
	server.handleClient();							// Listen for HTTP requests from clients
}


void handleRoot() {                          // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", "<form action=\"/login\" method=\"POST\">		<input type=\"text\" name=\"username\" placeholder=\"Username\"></br>		<input type=\"password\" name=\"password\" placeholder=\"Password\"></br>		<input type=\"submit\" value=\"Login\"></form><p>Welcome to Janis Davidsons microcontroller server! Please log in.</p>");
}

void handleLogin(){									// If a POST request is made to URI /login
	if( ! server.hasArg("username") || ! server.hasArg("password") || server.arg("username") == NULL || server.arg("password") == NULL){		// If the POST request doesn't have username and password data
		server.send(400, "text/plain", "404: Invalid request");		// The request is invalid, so send HTTP status 400
		return;
	}
	if(server.arg("username") == "Janis Davidsons" && server.arg("password") == "zzvzvh6m"){
		server.send(200, "text/html", "<h1>Welcome, " + server.arg("username") + "!</h1><p>Login successful</p>");
	}else {
		server.send(401, "text/plain", "401 Unauthorised");			//Username and password don't match
	}

}

void handleNotFound(){
	server.send(404, "text/plain", "404: Not found");	// Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}


