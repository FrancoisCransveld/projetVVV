#ifndef _LOADMAP_H_
#define _LOADMAP_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jeu.h"
#include "joueur.h"

//structure destinée à soit renseigner la direction dans laquel se dirige le joueur,soit renseigner où se trouve la prochaine map.
enum direction{Up, Right, Down, Left, fin};
typedef enum direction Direction;

struct selectionMap{
	int s;
	bool loadStatus;
	Direction Next;
};
typedef struct selectionMap SelectionMap;

struct tabNiveau{
	SelectionMap* map;
	int Current;
}
typedef struct tabNiveau TabNiveau;

struct map{
	char** c;
	Coordonnee taille; 
};
typedef struct map Map;
//#define Nombre_de_carte 1
Map currentMap;
//Coordonnee tailleCurrent;
Map nextMap;
//Coordonnee tailleNext;
Map nextLRMap;
//Coordonnee tailleLRNext;
//Map previousMap; Peut-être pas utile
//Coordonnee taillePrevious;
TabNiveau niveauA; // tableau des niveaux aléatoirement choisis

void loadMaps(int* tMapX, int* tMapy);
void loadMap(int tMapX, int tMapy,TabNiveau niveauA);
void LoadNext();
void tailleMap(int* tMapX,int* tMapY,int selectedMap);
Joueur loadJoueur(int select);
#endif
