#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LoadMaps.h"
#include "interface.h"
#include "jeu.h"

void drawMap(){

	int y;
	int mapY=0;
	int x;
	int mapX=0;
	//int maxY=tailleCurrent.y;
	int maxX=tailleNext.x;
	bool NEXT=false;
	char** pDrawnMap=nextMap;
	char carActuel;
	for(y=0;y<tailleCurrent.y+tailleNext.y;y++){
		for(x=0;x<maxX;x++){
			carActuel=*(*(pDrawnMap+mapY)+mapX);
			
			switch (carActuel){
				case '#':
					glColor3f(1.0f,1.0f,1.0f);
					glMatrixMode(GL_MODELVIEW);
					glLoadIdentity();
					glTranslatef(x*TILE_SIZE,y*TILE_SIZE,0.0f);
					
					glBegin(GL_QUADS);
					
					glVertex2f(0.0,0.0);
					glVertex2f(TILE_SIZE,0.0f);
					glVertex2f(TILE_SIZE,TILE_SIZE);
					glVertex2f(0.0f,TILE_SIZE);
					
					glEnd();
					break;
				case ' ' :
					glColor3f(0.0f,1.0f,0.0f);
					glMatrixMode(GL_MODELVIEW);
					glLoadIdentity();
					glTranslatef(x*TILE_SIZE,y*TILE_SIZE,0.0f);
					
					glBegin(GL_QUADS);
					
					glVertex2f(0.0,0.0);
					glVertex2f(TILE_SIZE,0.0f);
					glVertex2f(TILE_SIZE,TILE_SIZE);
					glVertex2f(0.0f,TILE_SIZE);
	
					glEnd();
					break;
			}
			mapX++;
		}
		
		mapX=0;
		if(y<tailleNext.y-1||NEXT){
			mapY++;
		}
		else{
			
			pDrawnMap=currentMap;
			mapY=0;
			maxX=tailleCurrent.x;
			NEXT=true;
		}
		
	}
	
}

void drawJoueur(){
	
	glColor3f(1.0f,0.2f,0.8f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(j.pos.x*TILE_SIZE,j.pos.y*TILE_SIZE,0.0f);
	
	glBegin(GL_QUADS);
	
	glVertex2f(0.0,0.0);
	glVertex2f(TILE_SIZE,0.0f);
	glVertex2f(TILE_SIZE,TILE_SIZE);
	glVertex2f(0.0f,TILE_SIZE);
	
	glEnd();

}
void interface(int nb){
	
	drawMap();
	drawJoueur();
}


