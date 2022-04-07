#ifndef _JOUEUR_H_
#define _JOUEUR_H_
#include "jeu.h"
#include "LoadMaps.h"

struct joueur{
	Coordonnee pos;
	int vie;
	Direction dir;
	//other
};
typedef struct joueur Joueur;
Joueur j;

void replacement_joueur(int x, int y, int* mjX, int* mjY, char** map);
void moveLeft(Joueur j);
void moveRight(Joueur j);
void moveUp(Joueur j);
void moveDown(Joueur j);

#endif
