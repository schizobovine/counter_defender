/*
 * counter_defender.ino
 *
 * Keep my goddamn cats off the goddamn countertops.
 *
 * Author: Sean Caulfield <sean@yak.net>
 * License: GPL v2.0
 *
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>

/*
 * Include file intentionally excluded from source control (via .gitignore in
 * my case) that defines the wireless network configuration. This is so I can
 * be lazy and just hard code it into the firmware--since I don't change my
 * wireless password very often and the alternatives are way too much
 * complexity for what amounts to a fancy software switch with buzzer. :P
 *
 * The following defines should be created in the included file:
 *
 * MY_WIFI_SSID - network name
 * MY_WIFI_PASS - network password
 *
 * These are passed to the ESP Wifi subsystem and then magic happens.
 */
#include "my_wireless_config.h"

#define PIN_DRIVER 4
#define PIN_MOTION 5

#define DEBUG_SERIAL 1
#define DEBUG_BAUD 115200

#if DEBUG_SERIAL
#define DPRINT(...) Serial.print(__VA_ARGS__)
#define DPRINTLN(...) Serial.println(__VA_ARGS__)
#else
#define DPRINT(...)
#define DPRINTLN(...)
#endif

void setup() {

  pinMode(PIN_MOTION, INPUT);
  pinMode(PIN_DRIVER, OUTPUT);
  digitalWrite(PIN_DRIVER, LOW);

#if DEBUG_SERIAL
  Serial.begin(DEBUG_BAUD);
#endif

  DPRINT("Connecting to ");
  DPRINT(MY_WIFI_SSID);
  WiFi.begin(MY_WIFI_SSID, MY_WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    DPRINT(".");
  }
  DPRINTLN();
  DPRINT("Connected, IP address: ");
  DPRINTLN(WiFi.localIP());

}

void loop() {
}
