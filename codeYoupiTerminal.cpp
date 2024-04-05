//*************************BONJOUR MONSIEUR ROBERT, VOICI LE MAGNIFIQUE CODE POUR FAIRE TOURNER LA BASE.************************************************************************
//*************************LE PROBLEME N'ETAIT PAS DANS LES PINS, MAIS DANS LE DEUXIEME "STEP_SEQUENCE"*************************************************************************
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
  // pour définir le numéro du moteur
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
  int nbPas;
  Serial.begin(9600);
  Serial.println("Entrez le nombre de pas à effectuer :");
  while(!Serial.available());
  nbPas = Serial.parseInt();
  Serial.print("Nombre de pas à effectuer : ");
  Serial.println(nbPas);
  
  for(int i=0; i<nbPas; i++) {
    moveOneStep(); 
    delay(step_delay); 
  }
}

void moveOneStep() {

    digitalWrite(D6,LOW);
    delay(10);
    digitalWrite(D6,HIGH);
    delay(10);
      
  }