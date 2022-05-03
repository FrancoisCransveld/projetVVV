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
#define MAX_NOM 32
//#include ""


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
        //printf("sortie interface\n"); 
        glMatrixMode(GL_PROJECTION);
        //printf("matrixModeDisplay\n");
	glLoadIdentity();
	//printf("LoadIdentity\n");
	if(MENU){
		//printf("MENU true glutOrtho\n");
		gluOrtho2D(0, width, heigth, 0);
	}
	else{
		//printf("MENU false glutOrtho\n");
		gluOrtho2D(TILE_SIZE*(camera.x)-(width/4+(TILE_SIZE*3)), TILE_SIZE*(camera.x)+(width/4+(TILE_SIZE*3)), TILE_SIZE*(camera.y)+heigth/4, TILE_SIZE*(camera.y)-heigth/4);
	}
	printf("gluOrtho %d,%d\n",width,heigth);
	glFlush();
	//printf("fin display\n");
	
}
int main (int argc,char* argv[]){
	
	//int t_map_X=0;
	//int t_map_Y=0;
	selectionMenu=0;
	
	MENU=true;
	printf("MENU=true\n");
	srand(time(NULL));
	
	//loadMaps(&t_map_X, &t_map_Y);
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
			/*if(!MENU&&selectionMenu==1){
				liste = creer_liste();
				afficher_liste(liste);
				loadMaps(&t_map_X, &t_map_Y);
				j=loadJoueur(0);
				glutTimerFunc(25, upDateKeyboard, 0);
				glutTimerFunc(25, upDateTirs,1);
				glutTimerFunc(75, upDateEnnemi,2);
			}*/
		}
		glutTimerFunc(50, upDatemenu, 3);
	}
	/*else if(!MENU&&selectionMenu==1){
		glutTimerFunc(25, upDateKeyboard, 0);
		glutTimerFunc(25, upDateTirs,1);
		glutTimerFunc(75, upDateEnnemi,2);
	}*/
	glutMainLoop();
	return 0;
}
