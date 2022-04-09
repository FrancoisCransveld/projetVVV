#ifndef _ENNEMI_H_
#define _ENNEMI_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jeu.h"
#define MAX_NOM 32
enum typeEnnemi{voiture,moto,camion,SUV,vide};
typedef enum typeEnnemi TypeEnnemi;

struct ennemi{
  Coordonnee pos;
  char* nom;
  int vie;
  TypeEnnemi type;
  bool attente;
};
typedef struct ennemi Ennemi;

typedef struct elementEnnemi ElementEnnemi;
struct elementEnnemi{
  Ennemi e;
  ElementEnnemi* suivant;
  ElementEnnemi* precedent;
};

typedef struct listeEnnemi ListeEnnemi;
struct listeEnnemi{
  int nombre;
  ElementEnnemi* premier;
  ElementEnnemi* dernier;
};

ListeEnnemi* liste;

ListeEnnemi* creer_liste(void);  
void nouvel_ennemi(ListeEnnemi* liste, char nom[], int vie, Coordonnee pos, TypeEnnemi t);
void modifier_ennemi(ListeEnnemi* liste, int numero, char nom[], int vie, Coordonnee pos, TypeEnnemi t,bool a);
void supprimer_ennemi_numero(ListeEnnemi* liste, int numero);
void retirer_vie_numero(ListeEnnemi* liste, int numero, int degat);
void modifier_pos_ennemi(ListeEnnemi* liste, int numero, Coordonnee pos);
void modifier_pos_ennemis(ListeEnnemi* liste, Coordonnee variation);
void supprimer_ennemi_hors_portee(ListeEnnemi* liste);
void afficher_liste(ListeEnnemi* liste);
#endif
