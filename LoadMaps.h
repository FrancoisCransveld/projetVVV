#ifndef _LOADMAP_H_
#define _LOADMAP_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jeu.h"

//structure destinée à soit renseigner la direction dans laquel se dirige le joueur,soit renseigner où se trouve la prochaine map.
//enum direction{Up, Right, Down, Left, fin};
//typedef enum direction Direction;

struct selectionMap{
	int s;
	bool loadStatus;
	bool ennemi;
	Direction Next;
	Direction previous;
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
	bool previous; //si previous true sinon false
};
typedef struct map Map;
//#define Nombre_de_carte 1
Map currentMap;

Map nextMap;

Map nextLRMap;

TabNiveau niveauA; // tableau des niveaux aléatoirement choisis

void loadMaps(int* tMapX, int* tMapy);
void loadMap(int tMapX, int tMapy,TabNiveau* niveauA, int select);
void loadNext(int select);
void tailleMap(int* tMapX,int* tMapY,TabNiveau niveauA, int selectedMap);
#include "joueur.h"
#include "ennemi.h"
Joueur loadJoueur(int select);
void loadEnnemi(ListeEnnemi* liste, int select);
void initialisation_Map(Map* initMap);
#endif
