#ifndef _LOADMAP_H_
#define _LOADMAP_H_
#include <stdlib.h>
#include <stdio.h>
#include "jeu.h"
#include "joueur.h"

//structure destinée à soit renseigner la direction dans laquel se dirige le joueur,soit renseigner où se trouve la prochaine map.
enum direction{Up, Right, Down, Left, fin};
typedef enum direction Direction;

struct selection{
	int s;
	Direction Next;
};
typedef struct selection Selection;

struct map{
	char** c;
	Selection Num; //numero actuelle dans la liste du niveau
};
typedef struct map Map;
//#define Nombre_de_carte 1
Map currentMap;
Coordonnee tailleCurrent;
Map nextMap;
Coordonnee tailleNext;
Map nextLRMap;
Coordonnee tailleLRNext;
//Map previousMap; Peut-être pas utile
//Coordonnee taillePrevious;
Selection* niveauA;//niveau aléatoirement choisi

void loadMaps(int* tMapX, int* tMapy);
void loadMap(int tMapX, int tMapy,Selection niveauA);
void LoadNext();
void tailleMap(int* tMapX,int* tMapY,int selectedMap);
Joueur loadJoueur(int select);
#endif
