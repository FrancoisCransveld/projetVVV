#ifndef _JEU_H_
#define _JEU_H_

#include <stdbool.h>
int score;//variable globale qui contiendra le score pendant une partie
bool MENU;//Variable globale qui indique qu'on est sur le MENU initiale du jeu

struct coordonnee{	//structure coordonnee qui contient deux int x et y pour avoir la position sur un plan en deux dimensions des éléments du jeu dans une même structure
	int x;
	int y;
};
typedef struct coordonnee Coordonnee;

enum direction{Up, Right, Down, Left, fin};	//variable énumération Direction qui sera utilisé pour garder et indiquer la direction des différents objets du jeu (joueur,ennemis,tirs)
typedef enum direction Direction;

Coordonnee coordonneeSouris;
void KeyboardSpecialJeu(int key, int x, int y);
void KeyboardJeu(unsigned char key, int x, int y);
void mouse_pos(int button, int etat, int x, int y);
void jeu( void );
void upDateTirs(int num);
void upDateEnnemi(int num);
void upDateKeyboard(int i);
void upDateInvulnerabilite(int num);
void switchMap(void);
void mort();
void game_over();
#endif
