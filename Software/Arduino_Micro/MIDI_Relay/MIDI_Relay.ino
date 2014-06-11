// MIDI_Relay
// Pineapple Mini 2014 / Arduino Micro
// Written by Ichi Kanaya
// Copyright (C) 2014, All rights reserved.

// Door opener is activated: A0 = 5V
// Door opener is not activated: A0 = 0V

#define TH  256
#define LED 13

int a0status = 0;

void midiNoteOn(int pitch, int velocity) {
  digitalWrite(LED, HIGH);
  Serial1.write(0x90);
  Serial1.write(pitch);
  Serial1.write(velocity);
  delay(100);
  digitalWrite(LED, LOW);
}

void setup() {
  pinMode(LED, OUTPUT);
  Serial1.begin(31250);
}

void loop() {
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
  delay(100);
}


