#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include "jeu.h"
#include "loadMaps.h"
#include "interface.h"
#include "joueur.h"
bool UP = false;
bool LEFT = false;
bool RIGHT = false;
bool DOWN = false;
bool ESCAPE = false;

void Keyboard(unsigned char key, int x, int y)  // fonction allant gérer les input
{
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
}
void KeyboardSpecial(int key, int x, int y)  // fonction allant gérer les input
{
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
}
void jeu( Joueur j)
{

	
	//drawWall(mX, mY);			//afficher la carte
	//drawPlayer(p);
	glutKeyboardFunc(Keyboard);		//fonction de glut gérant le clavier
	glutSpecialFunc(KeyboardSpecial);
	//glutTimerFunc(500, InputLoop, 1);
	if (LEFT == true)
	{
		
		moveLeft(p);		//va se déplacer vers la gauche si on appuie sur q
		LEFT = false;
		
	}
	if (RIGHT == true)
	{
		moveRight(p);		//va se déplacer vers la droite si on apppuie sur d
		RIGHT = false;
	}
	if (UP == true)
	{
		moveUp(p);
		UP = false;
	}
	
	if (DOWN == true)
	{
		
                moveDown(p);
		DOWN = false;
	}
	//glutTimerFunc(500, InputLoop, 1);
	glutPostRedisplay();
	
}
