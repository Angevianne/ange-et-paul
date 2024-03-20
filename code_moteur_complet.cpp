 /*
  Programme de base pour tester un robot Youpi.
  Le 27/01/2018
  Voir http://calvix.org
  Voir aussi : http://youpi.forler.ch/
 */
 
// déclaration des n° de sorties utilisées
#define MOT1 4
#define MOT2 5
#define MOT3 6
#define MOT4 7
#define MOT5 8
#define MOT6 9
#define BITCDEPAS 10
#define BITCDESENS 11
// definition des masks
#define MASKPAS 0b01000000
#define MASKSENS 0b10000000
#define BIT0 0b00000001  //decalage bit
#define BIT1 0b00000010
#define BIT2 0b00000100
#define BIT3 0b00001000
#define BIT4 0b00010000
#define BIT5 0b00100000
#define BIT6 0b01000000
#define BIT7 0b10000000

#define C1 A0
#define C2 A1
#define C3 A2
#define C4 A3
#define C5 A4
#define C6 A5


//definition du sens de rotation des moteurs
byte sensRotBase=0;
byte sensEpaule=0;
byte sensCoude=0;
byte sensPoignet=0;
byte sensPoignetRotation=0;
byte sensPince=0;

byte capteursAlinit = 0;


void setup() {
  pinMode(MOT1, OUTPUT);
  pinMode(MOT2, OUTPUT);
  pinMode(MOT3, OUTPUT);
  pinMode(MOT4, OUTPUT);
  pinMode(MOT5, OUTPUT);
  pinMode(MOT6, OUTPUT);
  pinMode(BITCDESENS, OUTPUT);
  pinMode(BITCDEPAS, OUTPUT);
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  
  
  digitalWrite(MOT1, LOW);
  digitalWrite(MOT2, LOW);
  digitalWrite(MOT3, LOW);
  digitalWrite(MOT4, LOW);
  digitalWrite(MOT5, LOW);
  digitalWrite(MOT6, LOW);
  digitalWrite(BITCDESENS, LOW);
  digitalWrite(BITCDEPAS, LOW);
  Serial.begin(9600);
  //Initialisation carte
  ecrireOctet(0x47);
  ecrireOctet(0x00);
  
  
  

  Serial.println("Initialisation carte faite");
  Serial.println("Bonjour, Commande ROBOT YOUPI");
  Serial.println("Entrer une commande du style : Numéro Moteur,Sens,Nombre de pas");
 
	for (int i=0; i<6; i++){
		capteursAlinit = capteursAlinit + digitalRead(i+14)*pow(2,i);
	} 
	Serial.print("capteur init = "); Serial.println(capteursAlinit,BIN);

}
void ecrireOctet(byte octet){
	// Serial.print("octet = ");Serial.println( octet, BIN);
	if (octet & BIT0){
		digitalWrite(MOT1, 1);
	} else {
		digitalWrite(MOT1, 0);
	}
	// digitalWrite( MOT1, (octet & BIT0?1:0) );
	if (octet & BIT1){
		digitalWrite(MOT2, 1);
	} else {
		digitalWrite(MOT2, 0);
	}
	if (octet & BIT2){
		digitalWrite(MOT3, 1);
	} else {
		digitalWrite(MOT3, 0);
	}
	if (octet & BIT3){
		digitalWrite(MOT4, 1);
	} else {
		digitalWrite(MOT4, 0);
	}
	if (octet & BIT4){
		digitalWrite(MOT5, 1);
	} else {
		digitalWrite(MOT5, 0);
	}
	if (octet & BIT5){
		digitalWrite(MOT6, 1);
	} else {
		digitalWrite(MOT6, 0);
	}
	if (octet & BIT6){
		digitalWrite(BITCDEPAS, 1);
	} else {
		digitalWrite(BITCDEPAS, 0);
	}
	if (octet & BIT7){
		digitalWrite(BITCDESENS, 1);
	} else {
		digitalWrite(BITCDESENS, 0);
	}
	delay(1);
	// Serial.print("Ecriture d'un ");Serial.print(digitalRead(MOT1));Serial.print(" sur la pin ");Serial.println( MOT1);
	// Serial.print("Ecriture d'un ");Serial.print(digitalRead(MOT2));Serial.print(" sur la pin ");Serial.println( MOT2);
	// Serial.print("Ecriture d'un ");Serial.print(digitalRead(MOT3));Serial.print(" sur la pin ");Serial.println( MOT3);
	// Serial.print("Ecriture d'un ");Serial.print(digitalRead(MOT4));Serial.print(" sur la pin ");Serial.println( MOT4);
	// Serial.print("Ecriture d'un ");Serial.print(digitalRead(MOT5));Serial.print(" sur la pin ");Serial.println( MOT5);
	// Serial.print("Ecriture d'un ");Serial.print(digitalRead(MOT6));Serial.print(" sur la pin ");Serial.println( MOT6);
	// Serial.print("Ecriture d'un ");Serial.print(digitalRead(BITCDEPAS));Serial.print(" sur la pin ");Serial.println( BITCDEPAS);
	// Serial.print("Ecriture d'un ");Serial.print(digitalRead(BITCDESENS));Serial.print(" sur la pin ");Serial.println( BITCDESENS);
	
}


void pasMot(byte numMot){ // numero de moteur de 1 à 6
	numMot=numMot-1;
	if (numMot>5) return;
	ecrireOctet(numMot|MASKPAS);
	ecrireOctet(numMot);
}

// travail avec les variables globales de sens
void fixeSensRot(){
	byte valeur=0;
	valeur=sensRotBase;
	valeur=valeur|(sensEpaule*2);
	valeur=valeur|(sensCoude*4);
	valeur=valeur|(sensPoignet*8);
	valeur=valeur|(sensPoignetRotation*16);
	valeur=valeur|(sensPince*32);

	ecrireOctet(valeur|MASKSENS);
	ecrireOctet(valeur);
}



void loop() {
	byte numMoteur, sens ;
	unsigned int nbrpas;
	byte capteurs = 0;
	
	// Serial.print("numéro du capteur = "); Serial.println(capteurs,BIN);
	while (Serial.available()){
		numMoteur=Serial.parseInt();
		sens=Serial.parseInt();
		nbrpas=Serial.parseInt();
		
		if(numMoteur==1) sensRotBase=sens;
		if(numMoteur==2) sensEpaule=sens;
		if(numMoteur==3) sensCoude=sens;
		if(numMoteur==4) sensPoignet=sens;
		if(numMoteur==5) sensPoignetRotation=sens;
		if(numMoteur==6) sensPince=sens;
		// Serial.print("Moteur = ");Serial.println(numMoteur);
		// Serial.print("sens = ");Serial.println(sens);
		// Serial.print("Pas = ");Serial.println(nbrpas);
		fixeSensRot();
		unsigned int i=0;
		for (i=0; i<nbrpas; i++) { //On ne peut commander à la carte de controle que 1 pas à la fois
			pasMot( numMoteur );
			for (int j=0; j<6; j++){
				capteurs = capteurs + digitalRead(j+14)*pow(2,j);
			}
	// Serial.print("capteur init = "); Serial.println(capteursAlinit,BIN);
	// Serial.print("capteur = "); Serial.println(capteurs,BIN);	
			if(capteurs != capteursAlinit) break;
			capteurs = 0;
		}
		
		
		Serial.println("Terminé :  (Nombre de pas à la bascule du capteur)= "); Serial.println(i);
		// Serial.print("Capteur 1 = "); Serial.println(digitalRead(A0));
		// Serial.print("Capteur 2 = "); Serial.println(digitalRead(A1));
		// Serial.print("Capteur 3 = "); Serial.println(digitalRead(A2));
		// Serial.print("Capteur 4 = "); Serial.println(digitalRead(A3));
		// Serial.print("Capteur 5 = "); Serial.println(digitalRead(A4));
		// Serial.print("Capteur 6 = "); Serial.println(digitalRead(A5));

	}
	capteursAlinit=0;
	for (int i=0; i<6; i++){
		capteursAlinit = capteursAlinit + digitalRead(i+14)*pow(2,i);
	}
	Serial.print("numéro du capteursAlinit fin = "); Serial.println(capteursAlinit,BIN);
	delay(50);
}
