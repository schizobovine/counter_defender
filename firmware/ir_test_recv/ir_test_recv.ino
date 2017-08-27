/*
 * ir_test_recv.ino
 *
 * Simple IR receive demo.
 *
 * Author: Sean Caulfield <sean@yak.net>
 * License: GPL v2.0
 *
 */

#include <Arduino.h>
#include <IRremote.h>

#define PIN_RECV    11

IRrecv ir_recv(PIN_RECV);
decode_results ir_data;

void setup() {
  Serial.begin(115200);
  Serial.println(F("IR Demo Start"));
  ir_recv.enableIRIn();
}

void loop() {
  size_t i;

  // Check if data is available for reading
  Serial.println(F("Receiving..."));
  if (ir_recv.decode(&ir_data)) {
    Serial.print(F("val = ")); Serial.println(ir_data.value, HEX);
    Serial.print(F("len = ")); Serial.println(ir_data.rawlen);
    for (i=0; i<ir_data.rawlen; i++) {
      Serial.print(ir_data.rawbuf[i] * USECPERTICK, HEX);
      Serial.print(F(" "));
    }
    Serial.println();
    ir_recv.resume();
  }

  delay(5000);

}
