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
#include "joueur.h"

//
//Pre: reçoit en argument nextMap et niveauA
//Post:Fonction qui dessine la map nextMap; c'est dans cette fonction qu'on détermine ou dessinné NextMap par rapport à current
void drawNext(){
	
	int y=0;
	int x=0;
	int maxX=0;
	int maxY=0;
	
	//Décalage de la hauteur (y)
	if(!niveauA.Nmap[niveauA.next].previous){		//si next map est une map suivant bien la map current dans l'ordre du tableau niveauA (comprendre que du coups on vient de currentMap ou nextLRMap)
		if(niveauA.Nmap[niveauA.next-1].dir==0){	//si la sortie de la map qui se trouve juste avant est vers le haut
			y-=nextMap.taille.y;			//on dessine nextmap au coordonnée y=-hauteur nextMap jusque 0 
			maxY=0;
		}
		if(niveauA.Nmap[niveauA.next-1].dir==2){	//si la sortie de current est vers le bas
			y+=currentMap.taille.y;		//on dessine nextmap au coordonnée y=hauteur currentMap jusque hauteur de currentMap+nextMap 
			maxY=currentMap.taille.y+nextMap.taille.y;
		}
	}
	else{	//(comprendre que du coups on va vers currentMap ou nextLRMap)
		if(niveauA.Nmap[niveauA.next].dir==0){	//si la sortie de next est vers le haut
			y+=currentMap.taille.y;		//on dessine nextmap au coordonnée y=hauteur currentMap jusque hauteur de currentMap+nextMap 
			maxY=currentMap.taille.y+nextMap.taille.y;
		}
		if(niveauA.Nmap[niveauA.next].dir==2){	//si la sortie de next est vers le bas
			y-=nextMap.taille.y;			//on dessine nextmap au coordonnée y=-hauteur nextMap jusque 0 
			maxY=0;
		}
	}
	//Décalage sur la largeur (x)
	// soit nextMap se trouve après nextLRMap alors que celle-ci est après current, soit nextMap est avant nextLRMap et currentMap
	if((niveauA.next>niveauA.nextLR&&!(niveauA.Nmap[niveauA.nextLR].previous))||(niveauA.next<niveauA.nextLR&&niveauA.Nmap[niveauA.nextLR].previous)){ 
		if(!niveauA.Nmap[niveauA.next].previous){		//si next map est une map suivant bien la map current dans l'ordre du tableau niveauA (comprendre que du coups on vient de currentMap)
			if(niveauA.Nmap[niveauA.current].dir==0){	//si la sortie de current est vers le haut
				x-=nextMap.taille.y;			//on dessine nextmap au coordonnée y=-hauteur nextMap jusque 0 
				maxY=0;
			}
			if(niveauA.Nmap[niveauA.current].dir==2){	//si la sortie de current est vers le bas
				y+=currentMap.taille.y;		//on dessine nextmap au coordonnée y=hauteur currentMap jusque hauteur de currentMap+nextMap 
				maxY=currentMap.taille.y+nextMap.taille.y;
			}
		}
		else{	//(comprendre que du coups on va vers currentMap)
			if(niveauA.Nmap[niveauA.next].dir==0){	//si la sortie de next est vers le haut
				y+=currentMap.taille.y;		//on dessine nextmap au coordonnée y=hauteur currentMap jusque hauteur de currentMap+nextMap 
				maxY=currentMap.taille.y+nextMap.taille.y;
			}
			if(niveauA.Nmap[niveauA.next].dir==2){	//si la sortie de next est vers le bas
				y-=nextMap.taille.y;			//on dessine nextmap au coordonnée y=-hauteur nextMap jusque 0 
				maxY=0;
			}
		}
	}
	char** pDrawnMap=currentMap.c;
	char carActuel;
	for(y;y<maxY;y++){
		for(x=;x<currentMap.taille.x;x++){
			carActuel=*(*(pDrawnMap+y)+x);
			
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
		}
		
	}
	
}
void drawCurrent(){
	int y;
	int x;
	int maxX=currentMap.taille.x;
	char** pDrawnMap=currentMap.c;
	char carActuel;
	for(y=0;y<currentMap.taille.y;y++){
		for(x=0;x<currentMap.taille.x;x++){
			carActuel=*(*(pDrawnMap+y)+x);
			
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
		}
		
	}
	
}
void drawMap(){

	int y;
	int mapY=0;
	int x;
	int mapX=0;
	//int maxY=tailleCurrent.y;
	int maxX=nextMap.taille.x;
	bool NEXT=false;
	char** pDrawnMap=nextMap.c;
	char carActuel;
	for(y=0;y<currentMap.taille.y+nextMap.taille.y;y++){
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
		if(y<nextMap.taille.y-1||NEXT){
			mapY++;
		}
		else{
			
			pDrawnMap=currentMap.c;
			mapY=0;
			maxX=currentMap.taille.x;
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


