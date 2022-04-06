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
	int minX=0;
	int minY=0;
	int maxX=nextMap.taille.x;
	int maxY=nextMap.taille.y;
	
	//Décalage de la hauteur (y)
	//Dans tous les cas
	if(nextMap.previous){		//si next map est une map suivant bien la map current dans l'ordre du tableau niveauA (comprendre que du coups on vient de currentMap ou nextLRMap)
		if(niveauA.Nmap[niveauA.next-1].Next==0){	//si la sortie de la map qui se trouve juste avant est vers le haut
			minY-=nextMap.taille.y;			//on dessine nextmap au coordonnée y=-hauteur nextMap jusque 0 
			maxY=0;
		}
		if(niveauA.Nmap[niveauA.next-1].Next==2){	//si la sortie de current est vers le bas
			minY+=currentMap.taille.y;		//on dessine nextmap au coordonnée y=hauteur currentMap jusque hauteur de currentMap+nextMap 
			maxY=currentMap.taille.y;
		}
	}
	else{	//(comprendre que du coups on va vers currentMap ou nextLRMap)
		if(niveauA.Nmap[niveauA.next].Next==0){	//si la sortie de next est vers le haut
			minY+=currentMap.taille.y;		//on dessine nextmap au coordonnée y=hauteur currentMap jusque hauteur de currentMap+nextMap 
			maxY=currentMap.taille.y;
		}
		if(niveauA.Nmap[niveauA.next].Next==2){	//si la sortie de next est vers le bas
			minY-=nextMap.taille.y;			//on dessine nextmap au coordonnée y=-hauteur nextMap jusque 0 
			maxY=0;
		}
	}
	//Décalage sur la largeur (x)
	// seulement si soit nextMap se trouve après nextLRMap alors que celle-ci est après current, soit nextMap est avant nextLRMap et currentMap
	
	if(niveauA.next>niveauA.nextLR&&niveauA.next>niveauA.current){		//si next map est une map suivant bien la map current dans l'ordre du tableau niveauA (comprendre que du coups on vient de currentMap)
		if(niveauA.Nmap[niveauA.current].Next==1){	//si la sortie de current est vers la droite
			minX+=currentMap.taille.x;		//on dessine nextmap au coordonnée x=largeur currentMap jusque largeur de currentMap+nextMap 
			maxX=currentMap.taille.x;
		}
		if(niveauA.Nmap[niveauA.current].Next==3){	//si la sortie de current est vers la gauche
			minX-=nextLRMap.taille.x;		//on dessine nextmap au coordonnée x=-largeur de nextLRMap jusque 0
			maxX=0;
		}
	}
	else if(niveauA.next<niveauA.nextLR&&niveauA.next<niveauA.current){	//(comprendre que du coups on va vers currentMap)
		if(niveauA.Nmap[niveauA.nextLR].Next==1){	//si la sortie de nextLR est vers la droite
			minX-=nextLRMap.taille.x;		//on dessine nextmap au coordonnée x=-largeur nextMap jusque 0 
			maxX=0;
		}
		if(niveauA.Nmap[niveauA.nextLR].Next==3){	//si la sortie de next est vers la gauche
			minX+=currentMap.taille.x;		//on dessine nextmap au coordonnée x=largeur currentMap jusque largeur de currentMap+nextMap 
			maxX=currentMap.taille.x;
		}
	}
	
	char** pDrawnMap=nextMap.c;
	char carActuel;
	for(y=minY;y<maxY;y++){
		for(x=minX;x<maxX;x++){
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
	
	drawCurrent();
	drawNext();
	
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


