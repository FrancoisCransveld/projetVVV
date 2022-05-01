#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "LoadMaps.h"
#include "interface.h"
#include "jeu.h"
#include "menu.h"
#include "joueur.h"
#include "imageloader.h"

//
//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	
	if(image->RGBA){
		glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGBA,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGBA, //GL_RGB, because pixels are stored in RGBA format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	}
	else{
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	}
	return textureId; //Returns the id of the texture
}
void vBitmapOutput(int x, int y, char *string, void *font)
{
	int len,i; // len donne la longueur de la chaîne de caractères
	
	glLoadIdentity();
	glRasterPos2f(x,y); // Positionne le premier caractère de la chaîne
	len = (int) strlen(string); // Calcule la longueur de la chaîne
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font,string[i]); // Affiche chaque caractère de la chaîne
	} 
}

void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font)
{
	char *p;

	glPushMatrix();	// glPushMatrix et glPopMatrix sont utilisées pour sauvegarder 
	glLoadIdentity();		// et restaurer les systèmes de coordonnées non translatés
	glTranslatef(x, y, 0); // Positionne le premier caractère de la chaîne
	
	for (p = string; *p; p++){
		glutStrokeCharacter(font, *p); // Affiche chaque caractère de la chaîne
	}
	glPopMatrix();
}

GLuint _textureId; //The id of the texture
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
				case '!':
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
				case '!':
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
				case '!':
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
					glVertex2f(2*TILE_SIZE,0.0f);
					glVertex2f(2*TILE_SIZE,3*TILE_SIZE);
					glVertex2f(0.0f,3*TILE_SIZE);
					
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

	Image* image = loadBMP("velo1.bmp");
	_textureId = loadTexture(image);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	if(image->RGBA){
		glColor4f(1.0f,1.0f,1.0f,1.0f);
	}
	else{
		glColor3f(1.0f,1.0f,1.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(j.pos.x*TILE_SIZE,j.pos.y*TILE_SIZE,0.0f);
	
	glBegin(GL_QUADS);
	switch (j.dir){
		case 0:
			
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(TILE_SIZE,TILE_SIZE);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(0.0f,TILE_SIZE);
			glTexCoord2f(1.0f,1.0f);
			glVertex2f(0.0,0.0);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(TILE_SIZE,0.0f);

			
			break;
		case 1:
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(0.0,0.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(0.0f,TILE_SIZE);
			glTexCoord2f(1.0f,1.0f);
			glVertex2f(TILE_SIZE,TILE_SIZE);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(TILE_SIZE,0.0f);

			
			break;
		case 2:
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(0.0,0.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(TILE_SIZE,0.0f);
			glTexCoord2f(1.0f,1.0f);
			glVertex2f(TILE_SIZE,TILE_SIZE);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(0.0f,TILE_SIZE);

			
			break;
		case 3:
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(TILE_SIZE,TILE_SIZE);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(TILE_SIZE,0.0f);
			glTexCoord2f(1.0f,1.0f);
			glVertex2f(0.0,0.0);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(0.0f,TILE_SIZE);
			
			
			break;
		case 4:
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(0.0,0.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(TILE_SIZE,0.0f);
			glTexCoord2f(1.0f,1.0f);
			glVertex2f(TILE_SIZE,TILE_SIZE);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(0.0f,TILE_SIZE);

			
			break;
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
	image = loadBMP("velo2.bmp");
	_textureId = loadTexture(image);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	if(image->RGBA){
		glColor4f(1.0f,1.0f,1.0f,1.0f);
	}
	else{
		glColor3f(1.0f,1.0f,1.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	
	
	switch (j.dir){
		case 0:
			glTranslatef(j.pos.x*TILE_SIZE,(j.pos.y+1)*TILE_SIZE,0.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(TILE_SIZE,TILE_SIZE);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(0.0f,TILE_SIZE);
			glTexCoord2f(1.0f,1.0f);
			glVertex2f(0.0,0.0);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(TILE_SIZE,0.0f);

			
			break;
		case 1:
			glTranslatef((j.pos.x-1)*TILE_SIZE,j.pos.y*TILE_SIZE,0.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(0.0,0.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(0.0f,TILE_SIZE);
			glTexCoord2f(1.0f,1.0f);
			glVertex2f(TILE_SIZE,TILE_SIZE);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(TILE_SIZE,0.0f);

			
			break;
		case 2:
			glTranslatef(j.pos.x*TILE_SIZE,(j.pos.y-1)*TILE_SIZE,0.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(0.0,0.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(TILE_SIZE,0.0f);
			glTexCoord2f(1.0f,1.0f);
			glVertex2f(TILE_SIZE,TILE_SIZE);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(0.0f,TILE_SIZE);

			
			break;
		case 3:
			glTranslatef((j.pos.x+1)*TILE_SIZE,j.pos.y*TILE_SIZE,0.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(TILE_SIZE,TILE_SIZE);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(TILE_SIZE,0.0f);
			glTexCoord2f(1.0f,1.0f);
			glVertex2f(0.0,0.0);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(0.0f,TILE_SIZE);
			
			
			break;
		case 4:
			glTranslatef(j.pos.x*TILE_SIZE,(j.pos.y-1)*TILE_SIZE,0.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(0.0,0.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(TILE_SIZE,0.0f);
			glTexCoord2f(1.0f,1.0f);
			glVertex2f(TILE_SIZE,TILE_SIZE);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(0.0f,TILE_SIZE);

			
			break;
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	//glutSwapBuffers();

};
void drawTirs(){
	//printf("drawTirs debut\n");

	for(int i=0;i<j.tirs->nombre;i++){
		Coordonnee posT=pos_tirs(j.tirs,i);
		glColor3f(0.7f,0.7f,1.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(posT.x*(TILE_SIZE/2),posT.y*(TILE_SIZE/2),0.0f);
		
		glBegin(GL_QUADS);
		
		glVertex2f(0.0,0.0);
		glVertex2f(TILE_SIZE/2,0.0f);
		glVertex2f(TILE_SIZE/2,TILE_SIZE/2);
		glVertex2f(0.0f,TILE_SIZE/2);
		
		glEnd();
	}
	//printf("drawTirs fin \n");
};
void interface_menu(){
	int y;
	int x;

	for(y=0;y<64;y++){
		for(x=0;x<64;x++){
			//printf("(x:%d y%d) ",x,y);
			if((x>=8&&x<30)&&(y>=16&&y<20)){
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
			}
			else if((x>=8&&x<30)&&(y>=24&&y<28)){
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
			}
			else if((x>=8&&x<30)&&(y>=32&&y<36)){
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
			}
			else if((x>=8&&x<30)&&(y>=40&&y<44)){
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
			}
			else{
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
			}
			
			
		}
		//printf("\n",x,y);
		
	}
};
void hub_info_jeu(){


	glColor3d(0.9,0.9,0.9); // Texte en blanc
	vBitmapOutput(0,0,"Blanc HELVETICA",GLUT_BITMAP_HELVETICA_18);
	char* valeur=NULL;
	valeur=int_vers_char(score);
	char scoreString[MAX_NOM]={"score:"};
	strcat(scoreString,valeur);
	
	vBitmapOutput(camera.x*TILE_SIZE,camera.y*TILE_SIZE+(15*TILE_SIZE),scoreString,GLUT_BITMAP_TIMES_ROMAN_24);
	
	valeur=int_vers_char(j.vie);
	char vieString[MAX_NOM]={"vie:"};
	strcat(vieString,valeur);
	
	vBitmapOutput((camera.x-10)*TILE_SIZE,camera.y*TILE_SIZE+(15*TILE_SIZE),vieString,GLUT_BITMAP_TIMES_ROMAN_24);
	
	valeur=int_vers_char(j.hp);
	char hpString[MAX_NOM]={"HP:"};
	strcat(hpString,valeur);
	
	vBitmapOutput((camera.x+10)*TILE_SIZE,camera.y*TILE_SIZE+(15*TILE_SIZE),hpString,GLUT_BITMAP_TIMES_ROMAN_24);
   	free(valeur);
   
	glFlush(); 
}
void interface(int nb){
	
	
	//printf("Interface\n");
	if(MENU){
		printf("interface_menu\n");
		interface_menu();
	}
	else if(!MENU){
		drawMap();
		drawEnnemis();
		drawJoueur();
		drawTirs();
		hub_info_jeu();
	}
};


