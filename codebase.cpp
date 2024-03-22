int step_delay = 100;

void setup() {

  for (int i = 0; i < 8; i++) {
    pinMode(base_pins[i], OUTPUT);
  }
}

void loop() {
  moveOneStep();
  delay(step_delay);
}

void moveOneStep() {

  int step_sequence_1[8] = {0, 1, 0, 0, 0, 0, 0, 0};
  int step_sequence_2[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    for (int j = 0; j < 8; j++) 



  // pilotage de la rotation du moteur
  for (int i=0 ; i<100)
  {
    for (int j = 0; j < 8; j++) {
    digitalWrite(2+j, step_sequence[j]);
    delay(10);



  }

  }
}int step_delay = 100;

void setup() {

  for (int i = 0; i < 8; i++) {
    pinMode(base_pins[i], OUTPUT);
  }
}

void loop() {
  moveOneStep();
  delay(step_delay);
}

void moveOneStep() {

  int step_sequence_1[8] = {0, 1, 0, 0, 0, 0, 0, 0};
  int step_sequence_2[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    for (int j = 0; j < 8; j++) 



  // pilotage de la rotation du moteur
  for (int i=0 ; i<100)
  {
    for (int j = 0; j < 8; j++) {
    digitalWrite(2+j, step_sequence[j]);
    delay(10);



  }

  }
}