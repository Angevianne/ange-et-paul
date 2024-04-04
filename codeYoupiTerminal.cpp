const int step_delay = 10; 
const int base_pins[8] = {2, 3, 4, 5, 6, 7, 8, 9}; 

const int D6=8;

void setup() {
  int sens_step_sequence[8] = {1, 0, 0, 0, 0, 0, 0, 0};
  int step_sequence_1[8] = {0, 1, 0, 0, 0, 0, 0, 0};
  int step_sequence_2[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  for (int i = 0; i < 8; i++) {
    pinMode(base_pins[i], OUTPUT);
  }

  for (int i = 0; i < 8; i++) {
    digitalWrite(base_pins[i],sens_step_sequence[i]);
  }
  delay(50);
  for (int j = 0; j < 8; j++) 
  {
    digitalWrite(base_pins[j], step_sequence_1[j]);
  }
  for (int j = 0; j < 8; j++) 
  {
    digitalWrite(base_pins[j], step_sequence_2[j]);
  }
}

void loop() {
  if (Serial.available() > 0) {
    int bits = Serial.parseInt();
    if (bits >= 0 && bits < 256) {
      setOutputBits(bits);
    }
  }
}

void setOutputBits(int bits) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(base_pins[i], bitRead(bits, i));
  }
  delay(step_delay);
}