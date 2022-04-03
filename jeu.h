#ifndef _JEU_H_
#define _JEU_H_

struct coordonnee{
	int x;
	int y;
};
typedef struct coordonnee Coordonnee;
struct joueur{
	Coordonnee pos;
	int vie;
	//other
};
typedef struct joueur Joueur;
void KeyboardSpecial(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
#endif
