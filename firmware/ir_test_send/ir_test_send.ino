/*
 * ir_test_send.ino
 *
 * Simple IR send demo.
 *
 * Author: Sean Caulfield <sean@yak.net>
 * License: GPL v2.0
 *
 */

#include <Arduino.h>
#include <IRremote.h>

#define SEND_DATA (0xa90)
#define SEND_BITS (12)

IRsend ir_send = IRsend(); // Can only be on pin 3 I think, for ATMega328

void setup() {
}

void loop() {
  ir_send.sendNEC(SEND_DATA, SEND_BITS);
  delay(40);
  ir_send.sendNEC(SEND_DATA, SEND_BITS);
  delay(40);
  ir_send.sendNEC(SEND_DATA, SEND_BITS);
  delay(5000);
}
