#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include "jeu.h"
#include "LoadMaps.h"
#include "interface.h"
#include "joueur.h"
bool UP = false;
bool LEFT = false;
bool RIGHT = false;
bool DOWN = false;
bool ESCAPE = false;

void Keyboard(unsigned char key, int x, int y)  // fonction allant gérer les input
{
	printf("Keyboard \n");
	switch(key)
	{
		case 27:
			exit(0);
		case'z':
			UP = true;
			break;
		case'q':
			LEFT = true;
			break;
		case'd':
			RIGHT = true;
			break;
		case's':
			DOWN = true;
			break;
	}	
};
void KeyboardSpecial(int key, int x, int y)  // fonction allant gérer les input
{
	printf("KeyboardSpecial \n");
	switch(key)
	{
		case GLUT_KEY_UP:
			UP = true;
			break;
		case GLUT_KEY_LEFT:
			LEFT = true;
			break;
		case GLUT_KEY_RIGHT:
			RIGHT = true;
			break;
		case GLUT_KEY_DOWN:
			DOWN = true;
			break;
	}	
};
//glutTimerFunc(500, InputLoop, 1);
void upDateKeyboard(int i){
	jeu();
	glutTimerFunc(50, upDateKeyboard, 0);
};
void jeu()
{
	glutKeyboardFunc(Keyboard);		//fonction de glut gérant le clavier
	glutSpecialFunc(KeyboardSpecial);
	if (LEFT == true)
	{
		
		moveLeft(j);		//va se déplacer vers la gauche si on appuie sur q
		LEFT = false;
		printf("LEFT ");
	}
	if (RIGHT == true)
	{
		printf("RIGHT ");
		moveRight(j);		//va se déplacer vers la droite si on apppuie sur d
		RIGHT = false;
	}
	if (UP == true)
	{
		printf("UP ");
		moveUp(j);
		UP = false;
	}
	
	if (DOWN == true)
	{
		printf("DOWN ");
                moveDown(j);
		DOWN = false;
	}
	glutPostRedisplay();
};
