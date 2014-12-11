/*
 * counter_defender - Keep my goddamn cats off my goddamn countertop.
 */

#include "usec.h"

// Pin constants

const int BUZZER = 2;
const int SWITCH = 3;
const int LED_G = 6;
const int LED_R = 7;
const int LED_Y = 8;
const int PIR_A = 9;
const int PIR_B = 10;
const int RELAY_A = 11;
const int RELAY_B = 12;

void setup() {

  pinMode(SWITCH, INPUT_PULLUP);

  pinMode(PIR_A, INPUT);
  pinMode(PIR_B, INPUT);

  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RELAY_A, OUTPUT);
  pinMode(RELAY_B, OUTPUT);

  // I have no idea why I just didn't wire this up but here we are.
  digitalWrite(LED_G, HIGH);
}

// Alert only once per this many usec
unsigned long MAX_ALERT_FREQ = 1000000; // 1s

// Each alert MUST last this many usec
unsigned long MIN_ALERT_TIME = 500000; // 0.5s

// Time of last alert in usec since last rollover
unsigned long last_alert = 0;

// Keep track of alert state
bool alerting = false;

// Check for motion and issue new/recall old alerts.
bool isIntruderAlert() {

  // Read-once, motherfuckers
  bool isMotionA = digitalRead(PIR_A);
  bool isMotionB = digitalRead(PIR_B);
  usec now = micros();
  usec diff = USEC_DIFF(now, last_alert);

  // If we're not alerting and there's an alert from either sensor, issue alert
  // and record state-tracking info for next check cycle, but only if this
  // alert is outside the frequency window from the last alert.
  if (!alerting && (isMotionA || isMotionB) && (diff > MAX_ALERT_FREQ)) {
    last_alert = now;
    alerting = true;

  // Otherwise, if we're already alerting and there isn't any motion going on,
  // check for duration/frequency and if applicable, recall alert and update
  // state.
  } else if (alerting && !isMotionA && !isMotionB && (diff > MIN_ALERT_TIME)) {

    alerting = false;

    // NB: Updating last_alert state so that the max frequency check above will
    // key off when the alert ENDED, not when it began (raising the possibility
    // that, if MIN_ALERT_TIME < MAX_ALERT_FREQ, back-to-back alerts could
    // still happen, even though that's what the max frequency is trying to
    // prevent).
    last_alert = now;

  }


  // Conveniently gives us the correct value to return to caller, though all
  // the above checks are necessary since they detect/handle state changes.
  return alerting;
}

void loop() {

  // Switch is connected to the internal pull-ups, so will read low when the
  // contacts are closed. Since this is a maintained pushbutton, we can just
  // keep checking it each loop rather than dicking around with debouncing or
  // other momentary button bullshit.
  if (digitalRead(SWITCH) == LOW) {

    // Light up yellow LED to signal we're armed. This is actually integrated
    // into the pushbutton because I'm awesome like that. (Well, either that or
    // stupid obsessed with pushbuttons.)
    digitalWrite(LED_Y, HIGH);

    // LOUD NOISES
    if (isIntruderAlert()) {
      digitalWrite(LED_R, HIGH);
      digitalWrite(RELAY_A, LOW);
      digitalWrite(RELAY_B, LOW);
      tone(BUZZER, 4000);

    // NO MORE LOUD NOISES
    } else {
      digitalWrite(LED_R, LOW);
      digitalWrite(RELAY_A, HIGH);
      digitalWrite(RELAY_B, HIGH);
      noTone(BUZZER); 
    }

  // Not armed, deactivate anything that's activated
  } else {
    digitalWrite(LED_Y, LOW);
    digitalWrite(LED_R, LOW);
    digitalWrite(RELAY_A, HIGH);
    digitalWrite(RELAY_B, HIGH);
    noTone(BUZZER);
  }

}

// vim: syntax=cpp
