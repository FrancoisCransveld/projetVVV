#ifndef _LOADMAP_H_
#define _LOADMAP_H_
#include <stdlib.h>
#include <stdio.h>
#include "jeu.h"

//#define Nombre_de_carte 1
char** currentMap;
Coordonnee tailleCurrent;
char** nextMap;
Coordonnee tailleNext;
char** previousMap;
Coordonnee taillePrevious;
Joueur j;
int* selectionAleatoire;

void loadMaps(int* tMapX, int* tMapy);
void loadMap(int tMapX, int tMapy,int selectedMap);
void tailleMap(int* tMapX,int* tMapY,int selectedMap);
Joueur loadJoueur(int select);
#endif
