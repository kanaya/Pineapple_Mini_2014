// MIDI_Relay
// Pineapple Mini 2014 / Arduino Micro
// Written by Ichi Kanaya
// Copyright (C) 2014, All rights reserved.

// Door opener is activated: A0 = 5V
// Door opener is not activated: A0 = 0V

#define TH  256

#define LED         13
#define BLINK_DELAY 50
#define A_HIGH      255
#define A_LOW       0
#define A_SNZ       32

int a0status = 0;

void doubleBlink() {
  analogWrite(LED, A_HIGH);
  delay(BLINK_DELAY);
  analogWrite(LED, A_LOW);
  delay(BLINK_DELAY);
  analogWrite(LED, A_HIGH);
  delay(BLINK_DELAY);
  analogWrite(LED, A_LOW);
}

void midiNoteOn(int pitch, int velocity) {
  Serial1.write(0x90);
  Serial1.write(pitch);
  Serial1.write(velocity);
  doubleBlink();
  delay(BLINK_DELAY);
}

void setup() {
  pinMode(LED, OUTPUT);
  Serial1.begin(31250);
}

void loop() {
  static int count = 0;
  static int dir = 1;
  int a0 = analogRead(A0);
  if (a0status >= TH) {
    if (a0 >= TH) {
      // ON --> ON
      // do nothing
    }
    else {
      // ON --> OFF
      // do nothing
    }
  }
  else {
    if (a0 >= TH) {
      // OFF --> ON
      midiNoteOn(60, 127);
    }
    else {
      // OFF --> OFF
      // do nothing
    }
  }
  a0status = a0;
  analogWrite(LED, count);
  if (dir == 1) {
    ++count;
  }
  else {
    --count;
  }
  if (count > A_SNZ) {
    count = A_SNZ;
    dir = 0;
  }
  else if (count < 0) {
    count = 0;
    dir = 1;
  } 
  delay(100);
}


