#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
#include<stdbool.h>
#include "jeu.h"
bool INPUT;
bool UP;
bool LEFT;
bool RIGHT;
bool DOWN ;
bool ESCAPE ;
bool SPACE ;
char lettre;

void KeyboardJeu(unsigned char key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardSpecialJeu(int key, int x, int y);
void KeyboardSpecial(int key, int x, int y);
void mouse_pos(int button, int etat, int x, int y);

#endif
