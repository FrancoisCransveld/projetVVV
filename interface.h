#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "jeu.h"
#include "LoadMaps.h"
#include "joueur.h"
#include "ennemi.h"
#define CAM_RANGE 16
#define TILE_SIZE 16.0
int width;
int heigth;

Coordonnee camera;
void drawMap(int y,int x,int minX,int minY,int maxX,int maxY,char** pDrawnMap);
void drawNext(void);
void drawPrevious(void);
void drawCurrent(void);
void interface(int nb);
void drawMapCall(void);
void drawJoueur(void);
void drawEnnemis(void);
void interface_menu(void);
#endif
