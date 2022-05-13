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

Coordonnee camera;// variable camera qui garde la position x et y de la camera dans le jeu exprimé en case.
//fonction qui affiche la carte qui lui est donnée en entrée au coordonnée comprise entre minX, minY et maxX et maxY
void drawMap(int y,int x,int minX,int minY,int maxX,int maxY,char** pDrawnMap);
void drawNext(void);
void drawPrevious(void);
void drawCurrent(void);
void interface(int nb);
void drawMapCall(void);
void drawJoueur(void);
void drawEnnemis(void);
void interface_entree_nom(char* nom);
void interface_tableau_score(void);
void hub_info_jeu(void);
void interface_menu(void);
#endif
