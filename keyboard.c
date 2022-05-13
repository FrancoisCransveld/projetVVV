#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jeu.h"
#include "LoadMaps.h"
#include "interface.h"
#include "joueur.h"
#include "menu.h"
#include "collision.h"
#include "keyboard.h"

void KeyboardJeu(unsigned char key, int x, int y)  // fonction allant gérer les input
{
	printf("Keyboard \n");
	switch(key)
	{
		case 27:
			ESCAPE=true;
			if(MENU&&ESCAPE&&selectionMenu==0){
				exit(0);
				ESCAPE=false;
			}
			else if(!MENU){
				MENU=true;
				if(MenuTabScore){
					MenuTabScore=false;
				}
				selectionMenu=0;
			}
		case'z':
			INPUT=true;
			UP = true;
			LEFT=false;
			RIGHT=false;
			DOWN=false;
			ENTER=false;
			break;
		case'q':
			INPUT=true;
			UP=false;
			LEFT=true;
			RIGHT=false;
			DOWN=false;
			ENTER=false;
			break;
		case'd':
			INPUT=true;
			UP=false;
			LEFT=false;
			RIGHT=true;
			DOWN=false;
			ENTER=false;
			break;
		case's':
			INPUT=true;
			UP=false;
			LEFT=false;
			RIGHT=false;
			DOWN=true;
			ENTER=false;
			break;
		case' ':
			INPUT=true;
			SPACE = true;
			UP=false;
			LEFT=false;
			RIGHT=false;
			DOWN=false;
			ENTER=false;
			break;
		case'\r':
			INPUT=true;
			SPACE = false;
			UP=false;
			LEFT=false;
			RIGHT=false;
			DOWN=false;
			ENTER=true;
			break;
		default:
			UP=false;
			LEFT=false;
			RIGHT=false;
			DOWN=false;
			SPACE=false;
			break;
	}	
};
void KeyboardSpecialJeu(int key, int x, int y)  // fonction allant gérer les input
{
	//printf("KeyboardSpecial \n");

	switch(key)
	{
		case GLUT_KEY_UP:
			INPUT=true;
			UP = true;
			LEFT=false;
			RIGHT=false;
			DOWN=false;
			printf("UP\n");
			break;
		case GLUT_KEY_LEFT:
			INPUT=true;
			UP=false;
			LEFT=true;
			RIGHT=false;
			DOWN=false;
			break;
		case GLUT_KEY_RIGHT:
			INPUT=true;
			UP=false;
			LEFT=false;
			RIGHT=true;
			DOWN=false;
			break;
		case GLUT_KEY_DOWN:
			INPUT=true;
			UP=false;
			LEFT=false;
			RIGHT=false;
			DOWN=true;
			break;
		default:
			INPUT=true;
			break;
	}	
};
void mouse_pos(int button, int etat, int x, int y){
	
	if(button==GLUT_LEFT_BUTTON&&MENU){
		if(etat==GLUT_UP){
		
			coordonneeSouris.x=x;//coordonnee en pixel par rapport à (0;0) coin supérieur gauche
			coordonneeSouris.y=y;
			MOUSECLICK=true;
			printf(" CoordonneeSouris: (%d,%d)\n",coordonneeSouris.x,coordonneeSouris.y);
		}
	}
};
void Keyboard(unsigned char key, int x, int y)  // fonction allant gérer les input
{
	switch(key)
	{
		case'z':
			lettre='z';
			break;
		case'q':
			lettre='q';
			break;
		case'd':
			lettre='d';
			break;
		case's':
			lettre='s';
			break;
		case' ':
			lettre=' ';
			break;
		case'a':
			lettre='a';
			break;
		case'e':
			lettre='e';
			break;
		case'r':
			lettre='r';
			break;
		case't':
			lettre='t';
			break;
		case'y':
			lettre='y';
			break;
		case'u':
			lettre='u';
			break;
		case'i':
			lettre='i';
			break;
		case'o':
			lettre='o';
			break;
		case'p':
			lettre='p';
			break;
		case'f':
			lettre='f';
			break;
		case'g':
			lettre='g';
			break;
		case'h':
			lettre='h';
			break;
		case'j':
			lettre='j';
			break;
		case'k':
			lettre='k';
			break;
		case'l':
			lettre='l';
			break;
		case'm':
			lettre='m';
			break;
		case'w':
			lettre='w';
			break;
		case'x':
			lettre='x';
			break;
		case'c':
			lettre='c';
			break;
		case'v':
			lettre='v';
			break;
		case'b':
			lettre='b';
			break;
		case'n':
			lettre='n';
			break;
		case'1':
			lettre='1';
			break;
		case'2':
			lettre='2';
			break;
		case'3':
			lettre='3';
			break;
		case'4':
			lettre='4';
			break;
		case'5':
			lettre='5';
			break;
		case'6':
			lettre='6';
			break;
		case'7':
			lettre='7';
			break;
		case'8':
			lettre='8';
			break;
		case'9':
			lettre='9';
			break;
		case'0':
			lettre='0';
			break;
		case '\b':
			lettre='\b';
			break;
		case '\r':
			lettre='\r';
			break;
		default:
			lettre='\0';
			break;
	}
};
void KeyboardSpecial(int key, int x, int y)  // fonction allant gérer les input
{
	//printf("KeyboardSpecial \n");
	switch(key)
	{
		case GLUT_KEY_UP:
			UP = true;
			printf("UP\n");
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

