// MIDI_Relay Copyright (C) 2014 Ichi Kanaya
// For Pineapple Mini 2014 / Arduino Micro

//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

// Door opener is activated: A0 = 5V
// Door opener is not activated: A0 = 0V

#define TH  256

#define LED         13
#define BLINK_DELAY 50
#define A_HIGH      255
#define A_LOW       0
#define A_SNZ       32

#define C4          60
#define C5          72

int the_status = 0;  // OFF

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
  midiNoteOn(C5, 127);
}

void loop() {
  static int count = 0;
  static int dir = 1;
  int a0 = analogRead(A0);
  int a1 = analogRead(A1);
  
  if (the_status >= TH) {
    // ON --> ON
    //   do nothing
    // ON --> OFF
    //   do nothing
  }
  else {
    if (a0 >= TH || a1 >= TH) {
      // OFF --> ON
      midiNoteOn(C4, 127);
    }
    // OFF --> OFF
    //   do nothing
  }
  the_status = (a1 > a0) ? a1 : a0;
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


