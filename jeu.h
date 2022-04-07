#ifndef _JEU_H_
#define _JEU_H_
//#include "joueur.h"

struct coordonnee{
	int x;
	int y;
};
typedef struct coordonnee Coordonnee;

enum direction{Up, Right, Down, Left, fin};
typedef enum direction Direction;

void KeyboardSpecial(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void jeu( void );
void upDateKeyboard(int i);
#endif
