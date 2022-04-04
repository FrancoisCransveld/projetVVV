#ifndef _JEU_H_
#define _JEU_H_

struct coordonnee{
	int x;
	int y;
};
typedef struct coordonnee Coordonnee;

void KeyboardSpecial(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void jeu( Joueur j);
#endif
