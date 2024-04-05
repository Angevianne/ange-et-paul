//*************************BONJOUR MONSIEUR ROBERT, VOICI LE MAGNIFIQUE CODE POUR FAIRE TOURNER LA BASE.************************************************************************
//*************************LE PROBLEME N'ETAIT PAS DANS LES PINS, MAIS DANS LE DEUXIEME "STEP_SEQUENCE"*************************************************************************
const int step_delay = 10; 
const int base_pins[8] = {2, 3, 4, 5, 6, 7, 8, 9}; 

const int D6=8;

int sens_step_sequence[8] = {1, 0, 0, 0, 0, 0, 0, 0};
int sens_step_sequence_reverse[8] = {0, 1, 1, 1, 1, 1, 1, 1};
int step_sequence_1[8] = {0, 1, 0, 0, 0, 0, 0, 0};
int step_sequence_2[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  // Configuration des broches
  for (int i = 0; i < 8; i++) {
    pinMode(base_pins[i], OUTPUT);
  }

  // Définition de la séquence de rotation initiale
  for (int i = 0; i < 8; i++) {
    digitalWrite(base_pins[i], sens_step_sequence[i]);
  }
  delay(50);

  // Définition des séquences de rotation 1 et 2
  for (int j = 0; j < 8; j++) {
    digitalWrite(base_pins[j], step_sequence_1[j]);
  }
  for (int j = 0; j < 8; j++) {
    digitalWrite(base_pins[j], step_sequence_2[j]);
  }
}

void loop() {
  int nbPas;
  Serial.begin(9600);
  Serial.println("Entrez le nombre de pas à effectuer (positif pour tourner dans un sens, négatif pour tourner dans l'autre sens) :");
  while(!Serial.available());
  nbPas = Serial.parseInt();
  Serial.print("Voici le nombre de pas à effectuer : ");
  Serial.println(nbPas);
  
  // Exécution des pas dans le sens approprié
  if (nbPas >= 0) {
    for(int i=0; i<abs(nbPas); i++) {
      moveOneStep(sens_step_sequence); 
      delay(step_delay); 
    }
  } else {
    for(int i=0; i<abs(nbPas); i++) {
      moveOneStep(sens_step_sequence_reverse); 
      delay(step_delay); 
    }
  }
}

void moveOneStep(int sequence[]) {
  // Envoyer la séquence de rotation aux broches du moteur
  for (int i = 0; i < 8; i++) {
    digitalWrite(base_pins[i], sequence[i]);
  }
  delay(10);
  for (int i = 0; i < 8; i++) {
    digitalWrite(base_pins[i], step_sequence_1[i]);
  }
  delay(10);
}