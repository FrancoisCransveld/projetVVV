#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "jeu.h"
#include "LoadMaps.h"
#include "joueur.h"
#include "ennemi.h"

#define TILE_SIZE 16.0
int width;
int heigth;

Coordonnee camera;

void interface(int nb);
void drawMap(void);
void drawJoueur(void);
void drawEnnemis(void);
#endif
