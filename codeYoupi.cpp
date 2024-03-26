const int step_delay = 100; // Définition de la constante pour le délai entre chaque pas
const int base_pins[8] = {2, 3, 4, 5, 6, 7, 8, 9}; // Broches utilisées pour contrôler le moteur

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(base_pins[i], OUTPUT); // Définition des broches de sortie
  }
}

void loop() {
  moveOneStep(); // Appel de la fonction pour effectuer un pas
  delay(step_delay); // Attente avant le prochain pas
}

void moveOneStep() {
  // Définition des séquences de pas
  int step_sequence_1[8] = {0, 1, 0, 0, 0, 0, 0, 0};
  int step_sequence_2[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  // Boucle pour effectuer un pas
  for (int i = 0; i < 100; i++) { // Répéter le mouvement 100 fois
    for (int j = 0; j < 8; j++) {
      // Envoyer les signaux de la séquence de pas aux broches correspondantes
      digitalWrite(base_pins[j], step_sequence_1[j]);
      delay(10); // Délai entre chaque étape du pas
    }
    delay(step_delay); // Délai entre chaque répétition de pas
  }
}
