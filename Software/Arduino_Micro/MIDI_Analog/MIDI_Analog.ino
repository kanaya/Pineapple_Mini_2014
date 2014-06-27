#define LED         13
#define BLINK_DELAY 50
#define A_HIGH      255
#define A_LOW       0

int sensor0 = 0;
int sensor1 = 0;

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
  // doubleBlink();
  // delay(BLINK_DELAY);
}

void midiNoteOff(int pitch) {
  Serial1.write(0x80);
  Serial1.write(pitch);
  Serial1.write(0);
}

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(13, OUTPUT);
  // Serial.begin(9600);
  Serial1.begin(31250);
}

void loop() {
  // read the value from the sensor:
  sensor0 = analogRead(A0);
  // sensor1 = analogRead(A1);
  sensor0 >>= 2;
  analogWrite(13, sensor0);
  // Serial.println(sensor0);
  midiNoteOn(sensor0, 127);
  delay(120);
  midiNoteOff(sensor0);
  
}
