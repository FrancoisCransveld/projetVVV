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
	
	//printf("drawNext ");
	//printf("etat Map :%d %d",nextMap.taille.x, nextMap.taille.y);
	if(nextMap.previous){
		//printf(" previous: true");
	}
	else{
		//printf(" previous: false");
	}
	//printf("etat niveauA : \n  -niveauA.next: %d\n  -niveauA.current: %d\n  -niveauA.nextLR: %d",niveauA.next,niveauA.current,niveauA.nextLR);
	int y=0;
	int x=0;
	int minX=0;
	int minY=0;
	int maxX=nextMap.taille.x;
	int maxY=nextMap.taille.y;
	
	//Décalage de la hauteur (y)
	//Dans tous les cas
	if(!nextMap.previous){		//si next map est une map suivant bien la map current dans l'ordre du tableau niveauA (comprendre que du coups on vient de currentMap ou nextLRMap)
		if(niveauA.Nmap[niveauA.next-1].Next==0){	//si la sortie de la map qui se trouve juste avant est vers le haut
			minY-=nextMap.taille.y;			//on dessine nextmap au coordonnée y=-hauteur nextMap jusque 0 
			maxY=0;
		}
		if(niveauA.Nmap[niveauA.next-1].Next==2){	//si la sortie de current est vers le bas
			minY+=currentMap.taille.y;		//on dessine nextmap au coordonnée y=hauteur currentMap jusque hauteur de currentMap+nextMap 
			maxY+=currentMap.taille.y;
		}
	}
	else{	//(comprendre que du coups on va vers currentMap ou nextLRMap)
		if(niveauA.Nmap[niveauA.next].Next==0){	//si la sortie de next est vers le haut
			minY+=currentMap.taille.y;		//on dessine nextmap au coordonnée y=hauteur currentMap jusque hauteur de currentMap+nextMap 
			maxY+=currentMap.taille.y;
		}
		if(niveauA.Nmap[niveauA.next].Next==2){	//si la sortie de next est vers le bas
			minY-=nextMap.taille.y;			//on dessine nextmap au coordonnée y=-hauteur nextMap jusque 0 
			maxY=0;
		}
	}
	//Décalage sur la largeur (x)
	// seulement si soit nextMap se trouve après nextLRMap alors que celle-ci est après current, soit nextMap est avant nextLRMap et currentMap
	
	if(niveauA.next>niveauA.nextLR&&niveauA.nextLR>niveauA.current){		//si next map est une map suivant bien la map current dans l'ordre du tableau niveauA (comprendre que du coups on vient de currentMap)
		if(niveauA.Nmap[niveauA.current].Next==1){	//si la sortie de current est vers la droite
			minX+=currentMap.taille.x;		//on dessine nextmap au coordonnée x=largeur currentMap jusque largeur de currentMap+nextMap 
			maxX+=currentMap.taille.x;
		}
		if(niveauA.Nmap[niveauA.current].Next==3){	//si la sortie de current est vers la gauche
			minX-=nextLRMap.taille.x;		//on dessine nextmap au coordonnée x=-largeur de nextLRMap jusque 0
			maxX=0;
		}
	}
	else if(niveauA.next<niveauA.nextLR&&niveauA.nextLR<niveauA.current){	//(comprendre que du coups on va vers currentMap)
		if(niveauA.Nmap[niveauA.nextLR].Next==1){	//si la sortie de nextLR est vers la droite
			minX-=nextLRMap.taille.x;		//on dessine nextmap au coordonnée x=-largeur nextMap jusque 0 
			maxX=0;
		}
		if(niveauA.Nmap[niveauA.nextLR].Next==3){	//si la sortie de next est vers la gauche
			minX+=currentMap.taille.x;		//on dessine nextmap au coordonnée x=largeur currentMap jusque largeur de currentMap+nextMap 
			maxX+=currentMap.taille.x;
		}
	}
	//ok jusque là, à priori
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
void drawNextLR(){
	
	//printf("drawNextLR ");
	//printf("etat Map :%d %d",nextLRMap.taille.x, nextLRMap.taille.y);
	if(nextLRMap.previous){
		//printf(" previous: true");
	}
	else{
		//printf(" previous: false");
	}
	//printf("etat niveauA : \n  -niveauA.next: %d\n  -niveauA.current: %d\n  -niveauA.nextLR: %d",niveauA.next,niveauA.current,niveauA.nextLR);
	int y=0;
	int x=0;
	int minX=0;
	int minY=0;
	int maxX=nextLRMap.taille.x;
	int maxY=nextLRMap.taille.y;
	
	//Décalage de la largeur (x)
	//Dans tous les cas
	if(!nextLRMap.previous){		//si nextLR map est une map suivant bien la map current dans l'ordre du tableau niveauA (comprendre que du coups on vient de currentMap ou nextLRMap)
		if(niveauA.Nmap[niveauA.nextLR-1].Next==1){	//si la sortie de la map qui se trouve juste avant est vers la droite
			minX+=currentMap.taille.x;		//on dessine nextmap au coordonnée x=largeur currentMap jusque largeur currentMap+nextLRMap 
			maxX+=currentMap.taille.x;
		}
		if(niveauA.Nmap[niveauA.nextLR-1].Next==3){	//si la sortie de current est vers la gauche
			minX-=nextLRMap.taille.x;		//on dessine nextmap au coordonnée x=-largeur nextLRMap jusque 0
			maxX-=nextLRMap.taille.x;
		}
	}
	else{	//(comprendre que du coups on va vers currentMap ou nextMap)
		if(niveauA.Nmap[niveauA.nextLR].Next==1){	//si la sortie de nextLR est vers la droite
			minX-=nextLRMap.taille.x;		//on dessine nextmap au coordonnée x=-largeur nextLRMap jusque 0
			maxX-=nextLRMap.taille.x;
		}
		if(niveauA.Nmap[niveauA.nextLR].Next==3){	//si la sortie de nextLR est vers la gauche
			minX+=currentMap.taille.x;		//on dessine nextmap au coordonnée x=largeur currentMap jusque largeur currentMap+nextLRMap 
			maxX+=currentMap.taille.x;
		}
	}
	//Décalage sur la hauteur (y)
	// seulement si soit nextLRMap se trouve après nextMap alors que celle-ci est après current, soit nextLRMap est avant nextMap et cette deuxième est avant currentMap
	
	if(niveauA.nextLR>niveauA.next&&niveauA.next>niveauA.current){		//si next map est une map suivant bien la map current dans l'ordre du tableau niveauA (comprendre que du coups on vient de currentMap)
		if(niveauA.Nmap[niveauA.current].Next==0){	//si la sortie de current est vers le haut
			minY-=nextLRMap.taille.y;		//on dessine nextmap au coordonnée y=-hauteur nextLRMap jusque 0 
			maxY-=currentMap.taille.y;
		}
		if(niveauA.Nmap[niveauA.current].Next==2){	//si la sortie de current est vers le bas
			minY+=currentMap.taille.y;		//on dessine nextmap au coordonnée y=hauteur de currentMap jusque hauteur de currentMap+nextLRMap
			maxY+=currentMap.taille.y;
		}
	}
	else if(niveauA.nextLR<niveauA.next&&niveauA.next<niveauA.current){	//(comprendre que du coups on va vers currentMap)
		if(niveauA.Nmap[niveauA.next].Next==0){	//si la sortie de nextLR est vers le haut
			minY+=currentMap.taille.y;		//on dessine nextmap au coordonnée y=hauteur de currentMap jusque hauteur de currentMap+nextLRMap
			maxY+=currentMap.taille.y;
		}
		if(niveauA.Nmap[niveauA.next].Next==2){	//si la sortie de next est vers le bas
			minY-=nextLRMap.taille.y;		//on dessine nextmap au coordonnée y=-hauteur nextLRMap jusque 0 
			maxY-=currentMap.taille.y;
		}
	}
	
	char** pDrawnMap=nextLRMap.c;
	char carActuel;
	printf("taille x, y: %d, %d et MaxX ,Y : %d %d\n",minX,minY,maxX,maxY);
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
	if(nextLRMap.c!=NULL){
		drawNextLR();
	}
	//printf("drawMap\n");
}

void drawEnnemis(){
	
	//printf("drawEnnemi\n");
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
void interface(int nb){
	
	//printf("Interface\n");
	drawMap();
	drawEnnemis();
	drawJoueur();
};


