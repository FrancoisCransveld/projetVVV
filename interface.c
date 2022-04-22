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
//Post:Fonction qui dessine la map nextMap; c'est dans cette fonction qu'on détermine ou dessinner NextMap par rapport à current
void drawNext(){
	
	//printf("drawNext \n");
	//printf("etat Map :%d %d",nextMap.taille.x, nextMap.taille.y);
	//printf("etat niveauA : \n  -niveauA.next: %d\n  -niveauA.current: %d\n  -niveauA.nextLR: %d",niveauA.next,niveauA.current,niveauA.nextLR);
	int y=0;
	int x=0;
	int minX=0;
	int minY=0-nextMap.taille.y;//next map est toujours affichée au dessus
	int maxX=nextMap.taille.x;
	int maxY=0;
	char** pDrawnMap=nextMap.c;
	char carActuel;
	//printf("taille x, y: %d, %d et MaxX ,Y : %d %d\n",minX,minY,maxX,maxY);
	for(y=minY;y<maxY;y++){
		for(x=minX;x<maxX;x++){
			carActuel=*(*(pDrawnMap+y-minY)+x-minX);
			
			switch (carActuel){	//switch sur la valeur du char à l'emplacement [x].[y] dans nextMap
				case '#':	//cas des bords de la carte
					glColor3f(1.0f,1.0f,1.0f); //couleurs blanche
					glMatrixMode(GL_MODELVIEW);
					glLoadIdentity();	//on remplace la matrice modelview par la matrice identité
					glTranslatef(x*TILE_SIZE,y*TILE_SIZE,0.0f);//positionnement vers la case [x].[y] ou on dessinne l'élément en cours
					
					glBegin(GL_QUADS);
					
					glVertex2f(0.0,0.0);
					glVertex2f(TILE_SIZE,0.0f);
					glVertex2f(TILE_SIZE,TILE_SIZE);
					glVertex2f(0.0f,TILE_SIZE);
					
					glEnd();
					break;
				case ' ' :	//cas du sol classique
					glColor3f(0.25f,0.25f,0.25f); //couleurs verte
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
				default :	//cas du sol classique
					glColor3f(0.25f,0.25f,0.25f); //couleurs verte
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
//Pre: reçoit en argument nextLRMap et niveauA
//Post:Fonction qui dessine la map nextLRMap; c'est dans cette fonction qu'on détermine ou dessinner NextLRMap par rapport à current et next
void drawPrevious(){
	
	int y=0;
	int x=0;
	int minX=0;
	int minY=currentMap.taille.y; // previous map est toujours affichée en dessous
	int maxX=previousMap.taille.x;
	int maxY=previousMap.taille.y+currentMap.taille.y;
	char** pDrawnMap=previousMap.c;
	char carActuel;
	//printf("taille x, y: %d, %d et MaxX ,Y : %d %d\n",minX,minY,maxX,maxY);
	for(y=minY;y<maxY;y++){
		for(x=minX;x<maxX;x++){
			carActuel=*(*(pDrawnMap+y-minY)+x-minX);
			switch (carActuel){	//switch sur la valeur du char à l'emplacement [x].[y] dans nextLRMap
				case '#':	//cas des bords de la carte
					glColor3f(1.0f,1.0f,1.0f); //couleurs blanche
					glMatrixMode(GL_MODELVIEW);
					glLoadIdentity();	//on remplace la matrice modelview par la matrice identité
					glTranslatef(x*TILE_SIZE,y*TILE_SIZE,0.0f);//positionnement vers la case [x].[y] ou on dessinne l'élément en cours
					
					glBegin(GL_QUADS);
					
					glVertex2f(0.0,0.0);
					glVertex2f(TILE_SIZE,0.0f);
					glVertex2f(TILE_SIZE,TILE_SIZE);
					glVertex2f(0.0f,TILE_SIZE);
					
					glEnd();
					break;
				case ' ' :	//cas du sol classique
					glColor3f(0.25f,0.25f,0.25f); //couleurs verte
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
				default :	//cas du sol classique
					glColor3f(0.25f,0.25f,0.25f); //couleurs verte
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

	//printf("drawCurrent\n");
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
					glColor3f(0.25f,0.25f,0.25f);
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
				case 'j' :	//cas du sol classique
					glColor3f(0.25f,0.25f,0.25f); //couleurs verte
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
				default :	//cas du sol classique
					glColor3f(0.25f,0.25f,0.25f); //gris
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
	
	//printf("drawMap\n");
	drawCurrent();
	if(nextMap.c!=NULL){
		drawNext();
	}
	//printf("drawMap\n");
	if(previousMap.c!=NULL){
		drawPrevious();
	}
	//printf("drawMap\n");
}

void drawEnnemis(){
	
	printf("drawEnnemi\n");
	ElementEnnemi* actuel=liste->premier;
	
	for(int i=0;i<liste->nombre;i++){
		
		switch (actuel->e.type){
				case voiture:
					glColor3f(1.0f,1.0f,0.0f);
					glMatrixMode(GL_MODELVIEW);
					glLoadIdentity();
					glTranslatef(actuel->e.pos.x*TILE_SIZE,actuel->e.pos.y*TILE_SIZE,0.0f);
					
					glBegin(GL_QUADS);
					
					glVertex2f(0.0,0.0);
					glVertex2f(TILE_SIZE,0.0f);
					glVertex2f(TILE_SIZE,TILE_SIZE);
					glVertex2f(0.0f,TILE_SIZE);
					
					glEnd();
					break;
				case moto :
					glColor3f(0.5f,0.5f,0.0f);
					glMatrixMode(GL_MODELVIEW);
					glLoadIdentity();
					glTranslatef(actuel->e.pos.x*TILE_SIZE,actuel->e.pos.y*TILE_SIZE,0.0f);
					
					glBegin(GL_QUADS);
					
					glVertex2f(0.0,0.0);
					glVertex2f(TILE_SIZE,0.0f);
					glVertex2f(TILE_SIZE,TILE_SIZE);
					glVertex2f(0.0f,TILE_SIZE);
	
					glEnd();
					break;
				case camion :	//cas du sol classique
					glColor3f(0.5f,0.0f,1.0f); //couleurs verte
					glMatrixMode(GL_MODELVIEW);
					glLoadIdentity();
					glTranslatef(actuel->e.pos.x*TILE_SIZE,actuel->e.pos.y*TILE_SIZE,0.0f);
					
					glBegin(GL_QUADS);
					
					glVertex2f(0.0,0.0);
					glVertex2f(TILE_SIZE,0.0f);
					glVertex2f(TILE_SIZE,TILE_SIZE);
					glVertex2f(0.0f,TILE_SIZE);
	
					glEnd();
					break;
				case SUV :	//cas du sol classique
					glColor3f(0.2f,1.0f,0.2f); //couleurs verte
					glMatrixMode(GL_MODELVIEW);
					glLoadIdentity();
					glTranslatef(actuel->e.pos.x*TILE_SIZE,actuel->e.pos.y*TILE_SIZE,0.0f);
					
					glBegin(GL_QUADS);
					
					glVertex2f(0.0,0.0);
					glVertex2f(TILE_SIZE,0.0f);
					glVertex2f(TILE_SIZE,TILE_SIZE);
					glVertex2f(0.0f,TILE_SIZE);
	
					glEnd();
					break;
				case vide :
					break;
			}

		if(actuel->suivant!=NULL){
			actuel=actuel->suivant;
		}
	}
};

void drawJoueur(){
	
	//printf("drawJoueur\n");
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

};
void drawTirs(){
	printf("drawTirs debut\n");
	for(int i=0;i<j.tirs->nombre;i++){
		Coordonnee posT=pos_tirs(j.tirs,i);
		glColor3f(0.7f,0.7f,1.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(posT.x*TILE_SIZE,posT.y*TILE_SIZE,0.0f);
		
		glBegin(GL_QUADS);
		
		glVertex2f(0.0,0.0);
		glVertex2f(TILE_SIZE/2,0.0f);
		glVertex2f(TILE_SIZE/2,TILE_SIZE/2);
		glVertex2f(0.0f,TILE_SIZE/2);
		
		glEnd();
	}
	printf("drawTirs fin \n");
}
void interface(int nb){
	
	//printf("Interface\n");
	drawMap();
	drawEnnemis();
	drawJoueur();
	drawTirs();
};


