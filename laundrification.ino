/*

laundrification.ino
by David Andrs, 2016

A simple code that monitors an analog pinout 0 and if the value gets above 512
then a notification is send via IFTTT channel called maker.

*/

#include <SPI.h>
#include <WiFi101.h>
#include "config.h"

int status = WL_IDLE_STATUS;

char server[] = "maker.ifttt.com";
char WASHING_MACHINE_DONE[] = "washing_machine_done";

const unsigned int PHOTOCELL_PIN = 0;

int washing_machine_status = 0;
int send_notification = 0;

WiFiClient client;

void setup() {
  Serial.begin(9600);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true)
      ;
  }

  Serial.println("Starting laundrification...");

  connect_to_wifi();
}

void connect_to_wifi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.print(WLAN_SSID);
    Serial.print("... ");

    WiFi.begin(WLAN_SSID, WLAN_PASS);
    while (WiFi.status() != WL_CONNECTED) {
      delay(3000);
    }

    Serial.println("done");
  }
}

bool triggerMakerEvent(const char * event) {
  Serial.print("Connecting to maker.ifttt.com... ");

  client.stop();
  if (client.connect(server, 80)) {
    Serial.println("done");
    // Make a HTTP request:
    client.print("POST ");
    client.print("/trigger/");
    client.print(event);
    client.print("/with/key/");
    client.print(IFTTT_MAKER_KEY);
    client.println(" HTTP/1.1");
    client.println("Host: maker.ifttt.com");
    client.println("Connection: close");
    client.println();

    Serial.println("Notification sent.");

    return true;
  }
  else {
    Serial.println("failed");

    return false;
  }
}

void loop() {
  int photocellReading = analogRead(PHOTOCELL_PIN);
  if (photocellReading > 512 && washing_machine_status == 0) {
    // washing machine LED turned on
    washing_machine_status = 1;
    send_notification = 1;
  }

  if (send_notification == 2 && photocellReading <= 512 && washing_machine_status == 1) {
    // washing machine LED turned off
    washing_machine_status = 0;
    send_notification = 0;
  }

  if (send_notification == 1) {
    connect_to_wifi();
    if (triggerMakerEvent(WASHING_MACHINE_DONE))
      send_notification = 2;
  }

  delay(1000);
}
