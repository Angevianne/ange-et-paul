#define MOT1 4
#define MOT2 5
#define MOT3 6
#define MOT4 7
#define MOT5 8
#define MOT6 9
#define BITCDEPAS 10
#define BITCDESENS 11

#define MASKPAS 0b01000000
#define MASKSENS 0b10000000
#define BIT0 0b00000001
#define BIT1 0b00000010
#define BIT2 0b00000100
#define BIT3 0b00001000
#define BIT4 0b00010000
#define BIT5 0b00100000
#define BIT6 0b01000000
#define BIT7 0b10000000

void setup() {
  pinMode(MOT1, OUTPUT);
  pinMode(MOT2, OUTPUT);
  pinMode(MOT3, OUTPUT);
  pinMode(MOT4, OUTPUT);
  pinMode(MOT5, OUTPUT);
  pinMode(MOT6, OUTPUT);
  pinMode(BITCDESENS, OUTPUT);
  pinMode(BITCDEPAS, OUTPUT);

  digitalWrite(MOT1, LOW);
  digitalWrite(MOT2, LOW);
  digitalWrite(MOT3, LOW);
  digitalWrite(MOT4, LOW);
  digitalWrite(MOT5, LOW);
  digitalWrite(MOT6, LOW);
  digitalWrite(BITCDESENS, LOW);
  digitalWrite(BITCDEPAS, LOW);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() >= 3) {
    byte numMoteur = Serial.parseInt();
    byte sens = Serial.parseInt();
    unsigned int nbrpas = Serial.parseInt();

    fixeSensRot(numMoteur, sens);
    for (unsigned int i = 0; i < nbrpas; i++) {
      pasMot(numMoteur);
      delay(1); // délai pour permettre à l'Arduino de traiter la commande
    }
  }
}

void ecrireOctet(byte octet) {
  digitalWrite(MOT1, octet & BIT0);
  digitalWrite(MOT2, octet & BIT1);
  digitalWrite(MOT3, octet & BIT2);
  digitalWrite(MOT4, octet & BIT3);
  digitalWrite(MOT5, octet & BIT4);
  digitalWrite(MOT6, octet & BIT5);
  digitalWrite(BITCDEPAS, octet & BIT6);
  digitalWrite(BITCDESENS, octet & BIT7);
}

void pasMot(byte numMot) {
  numMot = numMot - 1;
  if (numMot > 5) return;
  ecrireOctet(numMot | MASKPAS);
  ecrireOctet(numMot);
}

void fixeSensRot(byte numMoteur, byte sens) {
  // Vous devez implémenter votre propre logique pour définir le sens de rotation
}
