#ifndef _JOUEUR_H_
#define _JOUEUR_H_
#include "jeu.h"
#include "LoadMaps.h"
#include "tirs.h"
struct joueur{
	Coordonnee pos;
	int vie;
	Direction dir;
	ListeTirs* tirs;
	int maxTirs;
};
typedef struct joueur Joueur;
Joueur j;

void replacement_joueur(int x, int y, Map* map);
bool autorisation_scroll(int x,int y,Map MapJ,Direction jDir);
//void mapLoader(Map MapJ,Direction jDir);
void moveLeft();
void moveRight();
void moveUp();
void moveDown();


#endif
