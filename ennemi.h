#ifndef _ENNEMI_H_
#define _ENNEMI_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jeu.h"

enum typeEnnemi={voiture,moto,camion,SUV};
typedef enum typeEnnemi TypeEnnemi;
struct ennemi{
  Coordonnee pos;
  char* nom;
  int vie;
  TypeEnnemi type;
};
typedef struct ennemi Ennemi;

typedef struct elementEnnemi ElementEnnemi;
struct elementEnnemi{
  Ennemi e;
  ElementEnnemi* suivant;
  ElementEnnemi* precedent;
};

typedef struct listeEnnemi ListeEnnemi;
struct elementEnnemi{
  int nombre;
  ElementEnnemi* premierListe;
  ElementEnnemi* dernierListe;
};

#endif
