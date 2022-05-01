#ifndef _LOADMAP_H_
#define _LOADMAP_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jeu.h"
#include "tirs.h"
#define MAPS 14
#define MAPS_BOSS 2
//structure destinée à soit renseigner la direction dans laquel se dirige le joueur,soit renseigner où se trouve la prochaine map.
struct selectionMap{
	int s;
	bool loadStatus;
	bool ennemi;//est-ce que les ennemis doivent être chargé
	Direction Next;
	Direction previous;
};
typedef struct selectionMap SelectionMap;

struct tabNiveau{
	SelectionMap* Nmap;
	int nombreMap;
	int current;//le numéro dans le tableau de la map qui est chargée dans currentMap
	int next;  //le numéro dans le tableau de la map qui est chargée dans nextMap
	int previous;//le numéro dans le tableau de la map qui est chargée dans nextLRMap
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

Map previousMap;

TabNiveau niveauA; // tableau des niveaux aléatoirement choisis
char* int_vers_char(int nombre);
void map_select(int select,char* nom);
void Entree_sortie_Map( int select, Direction* entreeN, Direction* sortieN);
void loadMaps( int nombreMap);
void loadMap(int tMapX, int tMapy,TabNiveau* niveauA, int select);
void loadNext(int select);
void tailleMap(int* tMapX,int* tMapY,TabNiveau niveauA, int selectedMap);
void choix_map_aleatoire(void);
#include "joueur.h"
#include "ennemi.h"
Joueur loadJoueur(int select);
void loadEnnemi(ListeEnnemi* liste, int select);
void initialisation_Map(Map* initMap);
#endif
