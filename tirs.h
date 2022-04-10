#ifndef _TIRS_H_
#define _TIRS_H_
#include <stdlib.h>
#include <stdio.h>
//#include <stdbool.h>
#include "jeu.h"
enum typeTirs{pistolet,riffle,bazooka,rien};
typedef enum typeTirs TypeTirs;

struct tirs{
  Coordonnee pos;
  TypeTirs t;
  int distanceMax;
  Direction dir;
};
typedef struct tirs Tirs;

typedef struct elementTirs ElementTirs;
struct elementTirs{
  Tirs t;
  ElementTirs* suivant;
  ElementTirs* precedent;
};

typedef struct listeTirs ListeTirs;
struct listeTirs{
  int nombre;
  ElementTirs* premier;
  ElementTirs* dernier;
};

//ListeTirs* liste;

ListeTirs* creer_liste_tirs(void);  
void tirs(ListeTirs* listeT, Coordonnee pos, TypeTirs t, Direction dir);
void modifier_tirs(ListeTirs* listeT, int numero, Coordonnee pos, TypeTirs t,Direction dir);
void supprimer_tirs_numero(ListeTirs* listeT, int numero);
void supprimer_tirs_hors_portee(ListeTirs* listeT);
void modifier_pos_tirs(ListeTirs* listeT, Coordonnee variation);
void deplacement_tirs(ListeTirs* listeT);
Coordonnee pos_tirs(ListeTirs* listeT,int numero);
void afficher_liste_tirs(ListeTirs* listeT);
#endif
