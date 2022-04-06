#ifndef _LOADMAP_H_
#define _LOADMAP_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jeu.h"
#include "joueur.h"

//structure destinée à soit renseigner la direction dans laquel se dirige le joueur,soit renseigner où se trouve la prochaine map.
//enum direction{Up, Right, Down, Left, fin};
//typedef enum direction Direction;

struct selectionMap{
	int s;
	bool loadStatus;
	Direction Next;
};
typedef struct selectionMap SelectionMap;

struct tabNiveau{
	SelectionMap* Nmap;
	int current;//le numéro dans le tableau de la map qui est chargée dans currentMap
	int next;  //le numéro dans le tableau de la map qui est chargée dans nextMap
	int nextLR;//le numéro dans le tableau de la map qui est chargée dans nextLRMap
};
typedef struct tabNiveau TabNiveau;

struct map{
	char** c;
	Coordonnee taille;
	bool previous; 
};
typedef struct map Map;
//#define Nombre_de_carte 1
Map currentMap;

Map nextMap;

Map nextLRMap;

TabNiveau niveauA; // tableau des niveaux aléatoirement choisis

void loadMaps(int* tMapX, int* tMapy);
void loadMap(int tMapX, int tMapy,TabNiveau niveauA, int select);
void LoadNext();
void tailleMap(int* tMapX,int* tMapY,int selectedMap);
Joueur loadJoueur(int select);
#endif
