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
	gluOrtho2D(0, width, heigth, 0);
}

void Display()
{
	
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        interface(1);
	glFlush();
	
}
int main (int argc,char* argv[]){
	
	int t_map_X=0;
	int t_map_Y=0;
	loadMaps(&t_map_X, &t_map_Y);
	j=loadJoueur(0);
	srand(time(NULL));
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA );
	glutInitWindowSize(t_map_X*TILE_SIZE, t_map_Y*TILE_SIZE);
	glutCreateWindow("VeloVsVoiture");
	initRendering();
	glutReshapeFunc(handleResize);
	/*glMatrixMode( GL_MODELVIEW );
    	glPopMatrix();
    	glLoadIdentity(); 
    	glTranslatef( 0.0f, tailleNext.y*TILE_SIZE, 0.f );
    	glPushMatrix();*/
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}
