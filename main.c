#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "LoadMaps.h"
#include "interface.h"
#include "jeu.h"
#include "joueur.h"
#include "ennemi.h"
#include "menu.h"
#include "keyboard.h"
#include "score.h"
#define MAX_NOM 32



void initRendering()
{
	glEnable(GL_DEPTH_TEST);
}

void handleResize(int width,int heigth)
{
	glViewport(0, 0, width, heigth);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(TILE_SIZE*(camera.x)-width/2, TILE_SIZE*(camera.x)+width/2, TILE_SIZE*(camera.y)+heigth/2, TILE_SIZE*(camera.y)-heigth/2);
}

void Display()
{
	
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        interface(1);
        glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(MENU||MenuTabScore){
		gluOrtho2D(0, width, heigth, 0);
	}
	else{
		gluOrtho2D(TILE_SIZE*(camera.x)-(width/4), TILE_SIZE*(camera.x)+(width/4), TILE_SIZE*(camera.y)+heigth/4, TILE_SIZE*(camera.y)-heigth/4);
	}
	glFlush();
	
}
int main (int argc,char* argv[]){
	
	//if(selectionMenu!=1){
		selectionMenu=0;
	//}
	
	MENU=true;
	UP = false;
	LEFT = false;
	RIGHT = false;
	DOWN = false;
	ESCAPE = false;
	SPACE = false;
	lettre='\0';
	srand(time(NULL));
	listeAffichage=creer_liste_score();
	
	width=64*TILE_SIZE;
	heigth=64*TILE_SIZE;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA );
	glutInitWindowSize(64*TILE_SIZE, 64*TILE_SIZE);
	glutCreateWindow("VeloVsVoiture");
	initRendering();
	glutReshapeFunc(handleResize);
	glutDisplayFunc(Display);
	if(MENU){
		menu();
		if(selectionMenu>0){
			MENU=false;
			printf("MENU=false\n");
			if(!MENU){
				printf("MENU false\n");
			}
		}
		glutTimerFunc(50, upDatemenu, 3);
	}
	glutTimerFunc(25,upDateKeyboard,0);
	glutTimerFunc(25,upDateTirs,1);
	glutTimerFunc(100,upDateEnnemi,2);
	glutTimerFunc(500, upDatemenu, 3);
	glutMainLoop();
	return 0;
}
