const int step_delay = 10;
const int base_pins[8] = {2, 3, 4, 5, 6, 7, 8, 9};

const int control_pin = 10;

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(base_pins[i], OUTPUT);
  }

  pinMode(control_pin, INPUT);

  moveOneStep();
}

void loop() {
  if (digitalRead(control_pin) == HIGH) {
    moveOneStep();
    delay(step_delay);
  }
}

void moveOneStep() {
  static int step_sequence_index = 0;
  int step_sequence[][8] = {
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 1}
  };

  for (int i = 0; i < 8; i++) {
    digitalWrite(base_pins[i], step_sequence[step_sequence_index][i]);
  }

  step_sequence_index++;
  if (step_sequence_index >= 8) {
    step_sequence_index = 0;
  }
}
