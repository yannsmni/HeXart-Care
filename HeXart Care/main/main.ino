#include "cardio.h"
#include "coeur.h"
#include "param.h"

typedef struct Pouls {              //Définition d'une struct pour les bpm par rapport au temps
  int bpm;
  unsigned long int mil;
} Pouls;

Pouls pouls;


int a = 0, b = 0, c = 0 ;                   // a:
const int SEUILMAX = 424, SEUILMIN = 350;   // On définit le seuil pour lequel un battement est reconnu et ne pas prendre en compte le "contrepouls"

void battement() {
  switch (parametre) {
    case 1:
      all_on();
      break;
    case 2:
      one_on_x_on(parametre2);
      break;
    case 3:
      one_on(parametre2);
      break;
    case 4:
      chenille();
      break;
    case 5:
      loading();
      break;
    case 6:
      tourn();
      break;
    case 7:
      load();
  }
}

void setup() {
  Serial.begin(9600);
  pinMode("A0", INPUT);
  for (int i=2;i<=11;i++) {
    pinMode(i,OUTPUT);
  }
}


void loop() {
  c = 0;
  a = 0;
  b = 0;


  do {                                            //Tant que c=0 on continue la boucle quipermet de recupérer c qui est le delta entre 2 battements.
    c = 0;
    if (b == 0 && analogRead(0) < SEUILMAX && analogRead(0) > SEUILMIN) {
      a = millis();
      battement();
    }
    else if (a != 0 && analogRead(0) < SEUILMAX && analogRead(0) > SEUILMIN) {
      b = millis();
      c = b - a;            //Temps écoulé entre deux battements
      battement();
    }
    else {
      c = 0;
    }
  } while (c < 200);





  pouls.bpm = mstobpm(c);
  pouls.mil = millis();

  Serial.print(pouls.mil);          //On imprimme
  Serial.print(";");
  Serial.println(pouls.bpm);


  //Serial.println(analogRead(0));
  //delay(50);
}
