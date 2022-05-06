#ifndef _JEU_H_
#define _JEU_H_
//#include "joueur.h"
#include <stdbool.h>
int score;
bool MENU;

struct coordonnee{
	int x;
	int y;
};
typedef struct coordonnee Coordonnee;

enum direction{Up, Right, Down, Left, fin};
typedef enum direction Direction;

Coordonnee coordonneeSouris;
void KeyboardSpecial(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void mouse_pos(int button, int etat, int x, int y);
void jeu( void );
void upDateTirs(int num);
void upDateEnnemi(int num);
void upDateKeyboard(int i);
void switchMap(void);
void mort();
void game_over();
#endif
