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
#include "score.h"

//
//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	
	if(image->RGBA){//modification de la fonction initiale qui permet d'utiliser une texture en.bmp pour accepter le format 32bits RGBA
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
	else{		//code de la fonction initiale sans changement pour la gestion des formats .bmp 24bits RGB
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
	
	glPushMatrix();
	glLoadIdentity();
	printf("glraster\n");
	glRasterPos2f(x,y); // Positionne le premier caractère de la chaîne
	len = (int) strlen(string); // Calcule la longueur de la chaîne
	for (i = 0; i < len; i++) {
		printf("%c",string[i]);
		glutBitmapCharacter(font,string[i]); // Affiche chaque caractère de la chaîne
	}
	printf("\n",string[i]);
	glPopMatrix();
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
void drawMap(int y,int x,int minX,int minY,int maxX,int maxY,char** pDrawnMap){
	
	//printf("DrawMap\n");
	char carActuel;
	int nbrRandom=0;
	Image* image=NULL;
	
	//printf("herbe\n");
	image = loadBMP("herbe1.bmp");
	_textureId = loadTexture(image);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);						
	for(y=minY;y<maxY;y++){
		for(x=minX;x<maxX;x++){
			if((x>=camera.x-(width/(2*TILE_SIZE))-1)&&(x<=(camera.x+(width/(2*TILE_SIZE))+1))&&(y<=(camera.y+(width/(2*TILE_SIZE))+1))&&(y>=(camera.y-(width/(2*TILE_SIZE))-1))){
		carActuel=*(*(pDrawnMap+y-minY)+x-minX);
				if(carActuel=='h'){
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
					glTranslatef(x*TILE_SIZE,y*TILE_SIZE,0.0f);
					
					glBegin(GL_QUADS);

					glTexCoord2f(0.0f, 0.0f);
					glVertex2f(TILE_SIZE,TILE_SIZE);
					glTexCoord2f(1.0f, 0.0f);
					glVertex2f(0.0f,TILE_SIZE);
					glTexCoord2f(1.0f,1.0f);
					glVertex2f(0.0,0.0);
					glTexCoord2f(0.0f, 1.0f);
					glVertex2f(TILE_SIZE,0.0f);
					glEnd();
					
				}
			}
		}
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
	//printf("route\n");
	image = loadBMP("route1.bmp");
	_textureId = loadTexture(image);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);						
	for(y=minY;y<maxY;y++){
		for(x=minX;x<maxX;x++){
			if((x>=camera.x-(width/(2*TILE_SIZE))-1)&&(x<=(camera.x+(width/(2*TILE_SIZE))+1))&&(y<=(camera.y+(width/(2*TILE_SIZE))+1))&&(y>=(camera.y-(width/(2*TILE_SIZE))-1))){
			
				
				carActuel=*(*(pDrawnMap+y-minY)+x-minX);
				if(carActuel==' '||carActuel=='c'||carActuel=='v'||carActuel=='j'||carActuel=='m'){
					
					
					nbrRandom=((x-minX+y-minY)%4);
					
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
					glTranslatef(x*TILE_SIZE,y*TILE_SIZE,0.0f);
					
					glBegin(GL_QUADS);
					switch (nbrRandom){
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
						default:
							glTexCoord2f(0.0f, 0.0f);
							glVertex2f(TILE_SIZE,TILE_SIZE);
							glTexCoord2f(1.0f, 0.0f);
							glVertex2f(0.0f,TILE_SIZE);
							glTexCoord2f(1.0f,1.0f);
							glVertex2f(0.0,0.0);
							glTexCoord2f(0.0f, 1.0f);
							glVertex2f(TILE_SIZE,0.0f);
							break;	
					}
					nbrRandom++;
					glEnd();
					
				}
			}
		}
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	//printf("trotoir\n");
	image = loadBMP("trotoir.bmp");
	_textureId = loadTexture(image);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);						
	for(y=minY;y<maxY;y++){
		for(x=minX;x<maxX;x++){
			if((x>=camera.x-(width/(2*TILE_SIZE))-1)&&(x<=(camera.x+(width/(2*TILE_SIZE))+1))&&(y<=(camera.y+(width/(2*TILE_SIZE))+1))&&(y>=(camera.y-(width/(2*TILE_SIZE))-1))){
				//printf("pos c %d,%d\n",x,y);
				carActuel=*(*(pDrawnMap+y-minY)+x-minX);
				if(carActuel=='b'){
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
					glTranslatef(x*TILE_SIZE,y*TILE_SIZE,0.0f);
					
					glBegin(GL_QUADS);

					glTexCoord2f(0.0f, 0.0f);
					glVertex2f(TILE_SIZE,TILE_SIZE);
					glTexCoord2f(1.0f, 0.0f);
					glVertex2f(0.0f,TILE_SIZE);
					glTexCoord2f(1.0f,1.0f);
					glVertex2f(0.0,0.0);
					glTexCoord2f(0.0f, 1.0f);
					glVertex2f(TILE_SIZE,0.0f);
					glEnd();
					
				}
			}
		}
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	//printf("ligne\n");
	image = loadBMP("ligne.bmp");
	_textureId = loadTexture(image);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);						
	for(y=minY;y<maxY;y++){
		for(x=minX;x<maxX;x++){
			if((x>=camera.x-(width/(2*TILE_SIZE))-1)&&(x<=(camera.x+(width/(2*TILE_SIZE))+1))&&(y<=(camera.y+(width/(2*TILE_SIZE))+1))&&(y>=(camera.y-(width/(2*TILE_SIZE))-1))){
		carActuel=*(*(pDrawnMap+y-minY)+x-minX);
				if(carActuel=='l'||carActuel=='H'){
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
					glTranslatef(x*TILE_SIZE,y*TILE_SIZE,0.0f);
					
					glBegin(GL_QUADS);
					if(carActuel=='l'){
						glTexCoord2f(0.0f, 0.0f);
						glVertex2f(TILE_SIZE,TILE_SIZE);
						glTexCoord2f(1.0f, 0.0f);
						glVertex2f(0.0f,TILE_SIZE);
						glTexCoord2f(1.0f,1.0f);
						glVertex2f(0.0,0.0);
						glTexCoord2f(0.0f, 1.0f);
						glVertex2f(TILE_SIZE,0.0f);
					}
					else{
						glTexCoord2f(0.0f, 0.0f);
						glVertex2f(0.0f,TILE_SIZE);
						glTexCoord2f(1.0f, 0.0f);
						glVertex2f(0.0,0.0);
						glTexCoord2f(1.0f,1.0f);
						glVertex2f(TILE_SIZE,0.0f);
						glTexCoord2f(0.0f, 1.0f);
						glVertex2f(TILE_SIZE,TILE_SIZE);
						
						
					}
					glEnd();
					
				}
			}
		}
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
	image = loadBMP("ligneDiagonale.bmp");
	_textureId = loadTexture(image);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);						
	for(y=minY;y<maxY;y++){
		for(x=minX;x<maxX;x++){
			if((x>=camera.x-(width/(2*TILE_SIZE))-1)&&(x<=(camera.x+(width/(2*TILE_SIZE))+1))&&(y<=(camera.y+(width/(2*TILE_SIZE))+1))&&(y>=(camera.y-(width/(2*TILE_SIZE))-1))){
		carActuel=*(*(pDrawnMap+y-minY)+x-minX);
				if(carActuel=='d'||carActuel=='D'||carActuel=='O'||carActuel=='o'){
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
					glTranslatef(x*TILE_SIZE,y*TILE_SIZE,0.0f);
					
					glBegin(GL_QUADS);
					if(carActuel=='d'){
						glTexCoord2f(0.0f, 0.0f);
						glVertex2f(TILE_SIZE,TILE_SIZE);
						glTexCoord2f(1.0f, 0.0f);
						glVertex2f(0.0f,TILE_SIZE);
						glTexCoord2f(1.0f,1.0f);
						glVertex2f(0.0,0.0);
						glTexCoord2f(0.0f, 1.0f);
						glVertex2f(TILE_SIZE,0.0f);
					}
					else if(carActuel=='D'){
						glTexCoord2f(0.0f, 0.0f);
						glVertex2f(0.0,0.0);
						glTexCoord2f(1.0f, 0.0f);
						glVertex2f(TILE_SIZE,0.0f);
						glTexCoord2f(1.0f,1.0f);
						glVertex2f(TILE_SIZE,TILE_SIZE);
						glTexCoord2f(0.0f, 1.0f);
						glVertex2f(0.0f,TILE_SIZE);
					}
					else if(carActuel=='O'){
						glTexCoord2f(0.0f, 0.0f);
						glVertex2f(0.0f,TILE_SIZE);
						glTexCoord2f(1.0f, 0.0f);
						glVertex2f(0.0,0.0);
						glTexCoord2f(1.0f,1.0f);
						glVertex2f(TILE_SIZE,0.0f);
						glTexCoord2f(0.0f, 1.0f);
						glVertex2f(TILE_SIZE,TILE_SIZE);
					}
					else if(carActuel=='o'){
						glTexCoord2f(0.0f, 0.0f);
						glVertex2f(TILE_SIZE,0.0f);
						glTexCoord2f(1.0f, 0.0f);
						glVertex2f(TILE_SIZE,TILE_SIZE);
						glTexCoord2f(1.0f,1.0f);
						glVertex2f(0.0f,TILE_SIZE);
						glTexCoord2f(0.0f, 1.0f);
						glVertex2f(0.0,0.0);
					}
					glEnd();
					
				}
			}
		}
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	//printf("barrière\n");
	image = loadBMP("barrière.bmp");
	_textureId = loadTexture(image);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);						
	char carSuivant;
	for(y=minY;y<maxY;y++){
		for(x=minX;x<maxX;x++){
			if((x>=camera.x-(width/(2*TILE_SIZE))-1)&&(x<=(camera.x+(width/(2*TILE_SIZE))+1))&&(y<=(camera.y+(width/(2*TILE_SIZE))+1))&&(y>=(camera.y-(width/(2*TILE_SIZE))-1))){
			
				
				carActuel=*(*(pDrawnMap+y-minY)+x-minX);
				if(carActuel=='#'){
					if(x-minX<63){
						carSuivant=*(*(pDrawnMap+(y-minY))+(x-minX+1));
					}
					if(carSuivant=='b'){
						//printf("%d\n",nbrRandom);
						nbrRandom=2;
						
					}
					if(x-minX>0){
						carSuivant=*(*(pDrawnMap+(y-minY))+(x-minX-1));
					}
					if(carSuivant=='b'){
						//printf("%d\n",nbrRandom);
						nbrRandom=0;	
					}
					if(y-minY>0){
						carSuivant=*(*(pDrawnMap+(y-minY-1))+(x-minX));
					}
					if(carSuivant=='b'||carSuivant==' '){
						//printf("%d\n",nbrRandom);
						nbrRandom=3;
						
					}
					if(y-minY<63){
						carSuivant=*(*(pDrawnMap+(y-minY+1))+(x-minX));
					}
					if(carSuivant=='b'||carSuivant==' '){
						//printf("%d\n",nbrRandom);
						nbrRandom=1;
					}
					
						
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
					glTranslatef(x*TILE_SIZE,y*TILE_SIZE,0.0f);
					
					glBegin(GL_QUADS);
					switch (nbrRandom){
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
						default:
							glTexCoord2f(0.0f, 0.0f);
							glVertex2f(TILE_SIZE,TILE_SIZE);
							glTexCoord2f(1.0f, 0.0f);
							glVertex2f(0.0f,TILE_SIZE);
							glTexCoord2f(1.0f,1.0f);
							glVertex2f(0.0,0.0);
							glTexCoord2f(0.0f, 1.0f);
							glVertex2f(TILE_SIZE,0.0f);
							break;
					}
					glEnd();
				}
					
			}
		}
	}
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
	//printf("blocage\n");
	image = loadBMP("blocage.bmp");
	_textureId = loadTexture(image);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);						
	for(y=minY;y<maxY;y++){
		for(x=minX;x<maxX;x++){
			if((x>=camera.x-(width/(2*TILE_SIZE))-1)&&(x<=(camera.x+(width/(2*TILE_SIZE))+1))&&(y<=(camera.y+(width/(2*TILE_SIZE))+1))&&(y>=(camera.y-(width/(2*TILE_SIZE))-1))){
		carActuel=*(*(pDrawnMap+y-minY)+x-minX);
				if(carActuel=='t'){
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
					glTranslatef(x*TILE_SIZE,y*TILE_SIZE,0.0f);
					
					glBegin(GL_QUADS);

					glTexCoord2f(0.0f, 0.0f);
					glVertex2f(TILE_SIZE,TILE_SIZE);
					glTexCoord2f(1.0f, 0.0f);
					glVertex2f(0.0f,TILE_SIZE);
					glTexCoord2f(1.0f,1.0f);
					glVertex2f(0.0,0.0);
					glTexCoord2f(0.0f, 1.0f);
					glVertex2f(TILE_SIZE,0.0f);
					glEnd();
					
				}
			}
		}
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
	//printf("limite\n");
	image = loadBMP("limite.bmp");
	_textureId = loadTexture(image);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);						
	for(y=minY;y<maxY;y++){
		for(x=minX;x<maxX;x++){
			if((x>=camera.x-(width/(2*TILE_SIZE))-1)&&(x<=(camera.x+(width/(2*TILE_SIZE))+1))&&(y<=(camera.y+(width/(2*TILE_SIZE))+1))&&(y>=(camera.y-(width/(2*TILE_SIZE))-1))){
			
				
				carActuel=*(*(pDrawnMap+y-minY)+x-minX);
				if(carActuel=='!'){
					if(x-minX==63){
						nbrRandom=1;
					}
					if(x-minX==0){
						nbrRandom=3;	
					}
					if(y-minY==0){
						nbrRandom=0;	
					}
					if(y-minY==63){
						nbrRandom=2;
					}
					
						
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
					glTranslatef(x*TILE_SIZE,y*TILE_SIZE,0.0f);
					
					glBegin(GL_QUADS);
					switch (nbrRandom){
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
						default:
							glTexCoord2f(0.0f, 0.0f);
							glVertex2f(TILE_SIZE,TILE_SIZE);
							glTexCoord2f(1.0f, 0.0f);
							glVertex2f(0.0f,TILE_SIZE);
							glTexCoord2f(1.0f,1.0f);
							glVertex2f(0.0,0.0);
							glTexCoord2f(0.0f, 1.0f);
							glVertex2f(TILE_SIZE,0.0f);
							break;
					}
					glEnd();
				}
					
			}
		}
	}
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	free(image);
	//printf("sortie DrawMap\n");
}
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
	
	drawMap(y,x,minX,minY,maxX,maxY,pDrawnMap);
	
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
	
	drawMap(y,x,minX,minY,maxX,maxY,pDrawnMap);
	
}
void drawCurrent(){

	//printf("drawCurrent\n");
	int y=0;
	int x=0;
	char** pDrawnMap=currentMap.c;
	
	drawMap(y,x,0,0,currentMap.taille.x,currentMap.taille.y,pDrawnMap);
	
}
void drawMapCall(){
	
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
	
	Image* image=NULL;
	for(int i=0;i<liste->nombre;i++){
		
		switch (actuel->e.type){
				case voiture:
						image = loadBMP("voiture2.bmp");
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
						glTranslatef(actuel->e.pos.x*TILE_SIZE,actuel->e.pos.y*TILE_SIZE,0.0f);
						
						glBegin(GL_QUADS);
						switch (actuel->e.dir){
							case 0:
								glTexCoord2f(0.0f, 0.0f);
								glVertex2f(2*TILE_SIZE,3*TILE_SIZE);
								glTexCoord2f(1.0f, 0.0f);
								glVertex2f(0*TILE_SIZE,3*TILE_SIZE);
								glTexCoord2f(1.0f,1.0f);
								glVertex2f(0*TILE_SIZE,0*TILE_SIZE);
								glTexCoord2f(0.0f, 1.0f);
								glVertex2f(2*TILE_SIZE,0*TILE_SIZE);

								
								break;
							case 1:
								glTexCoord2f(0.0f, 0.0f);
								glVertex2f(0*TILE_SIZE,0*TILE_SIZE);
								glTexCoord2f(1.0f, 0.0f);
								glVertex2f(0*TILE_SIZE,2*TILE_SIZE);
								glTexCoord2f(1.0f,1.0f);
								glVertex2f(3*TILE_SIZE,2*TILE_SIZE);
								glTexCoord2f(0.0f, 1.0f);
								glVertex2f(3*TILE_SIZE,0*TILE_SIZE);

								
								break;
							case 2:
								glTexCoord2f(0.0f, 0.0f);
								glVertex2f(0*TILE_SIZE,0*TILE_SIZE);
								glTexCoord2f(1.0f, 0.0f);
								glVertex2f(2*TILE_SIZE,0*TILE_SIZE);
								glTexCoord2f(1.0f,1.0f);
								glVertex2f(2*TILE_SIZE,3*TILE_SIZE);
								glTexCoord2f(0.0f, 1.0f);
								glVertex2f(0*TILE_SIZE,3*TILE_SIZE);

								
								break;
							case 3:
								glTexCoord2f(0.0f, 0.0f);
								glVertex2f(3*TILE_SIZE,2*TILE_SIZE);
								glTexCoord2f(1.0f, 0.0f);
								glVertex2f(3*TILE_SIZE,0*TILE_SIZE);
								glTexCoord2f(1.0f,1.0f);
								glVertex2f(0*TILE_SIZE,0*TILE_SIZE);
								glTexCoord2f(0.0f, 1.0f);
								glVertex2f(0*TILE_SIZE,2*TILE_SIZE);
								
								
								break;
							case 4:
								glTexCoord2f(0.0f, 0.0f);
								glVertex2f(2*TILE_SIZE,3*TILE_SIZE);
								glTexCoord2f(1.0f, 0.0f);
								glVertex2f(0.0f,3*TILE_SIZE);
								glTexCoord2f(1.0f,1.0f);
								glVertex2f(0.0,0.0);
								glTexCoord2f(0.0f, 1.0f);
								glVertex2f(2*TILE_SIZE,0.0f);

								
								break;
						}
						glEnd();
						glDisable(GL_TEXTURE_2D);
						glDisable(GL_BLEND);
					
					break;
				case moto :
					image = loadBMP("moto1.bmp");
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
						glTranslatef(actuel->e.pos.x*TILE_SIZE,actuel->e.pos.y*TILE_SIZE,0.0f);
						
						glBegin(GL_QUADS);
						switch (actuel->e.dir){
							case 0:
								glTexCoord2f(0.0f, 0.0f);
								glVertex2f(1*TILE_SIZE,2*TILE_SIZE);
								glTexCoord2f(1.0f, 0.0f);
								glVertex2f(0*TILE_SIZE,2*TILE_SIZE);
								glTexCoord2f(1.0f,1.0f);
								glVertex2f(0*TILE_SIZE,0*TILE_SIZE);
								glTexCoord2f(0.0f, 1.0f);
								glVertex2f(1*TILE_SIZE,0*TILE_SIZE);

								
								break;
							case 1:
								glTexCoord2f(0.0f, 0.0f);
								glVertex2f(0*TILE_SIZE,0*TILE_SIZE);
								glTexCoord2f(1.0f, 0.0f);
								glVertex2f(0*TILE_SIZE,1*TILE_SIZE);
								glTexCoord2f(1.0f,1.0f);
								glVertex2f(2*TILE_SIZE,1*TILE_SIZE);
								glTexCoord2f(0.0f, 1.0f);
								glVertex2f(2*TILE_SIZE,0*TILE_SIZE);

								
								break;
							case 2:
								glTexCoord2f(0.0f, 0.0f);
								glVertex2f(0*TILE_SIZE,0*TILE_SIZE);
								glTexCoord2f(1.0f, 0.0f);
								glVertex2f(1*TILE_SIZE,0*TILE_SIZE);
								glTexCoord2f(1.0f,1.0f);
								glVertex2f(1*TILE_SIZE,2*TILE_SIZE);
								glTexCoord2f(0.0f, 1.0f);
								glVertex2f(0*TILE_SIZE,2*TILE_SIZE);

								
								break;
							case 3:
								glTexCoord2f(0.0f, 0.0f);
								glVertex2f(2*TILE_SIZE,1*TILE_SIZE);
								glTexCoord2f(1.0f, 0.0f);
								glVertex2f(2*TILE_SIZE,0*TILE_SIZE);
								glTexCoord2f(1.0f,1.0f);
								glVertex2f(0*TILE_SIZE,0*TILE_SIZE);
								glTexCoord2f(0.0f, 1.0f);
								glVertex2f(0*TILE_SIZE,1*TILE_SIZE);
								
								
								break;
							case 4:
								glTexCoord2f(0.0f, 0.0f);
								glVertex2f(1*TILE_SIZE,2*TILE_SIZE);
								glTexCoord2f(1.0f, 0.0f);
								glVertex2f(0.0f,2*TILE_SIZE);
								glTexCoord2f(1.0f,1.0f);
								glVertex2f(0.0,0.0);
								glTexCoord2f(0.0f, 1.0f);
								glVertex2f(1*TILE_SIZE,0.0f);

								
								break;
						}
						glEnd();
						glDisable(GL_TEXTURE_2D);
						glDisable(GL_BLEND);
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
	free(image);
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
	free(image);

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
	
	printf("interface_menu\n");
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
	}
	glColor3d(0,0,0); // Texte en noir
	
	vBitmapOutput(15*TILE_SIZE,18*TILE_SIZE+8,"New Game",GLUT_BITMAP_TIMES_ROMAN_24);
	vBitmapOutput(12*TILE_SIZE,26*TILE_SIZE+8,"Tableaux des Scores",GLUT_BITMAP_TIMES_ROMAN_24);
	vBitmapOutput(15*TILE_SIZE,34*TILE_SIZE+8,"Commandes",GLUT_BITMAP_TIMES_ROMAN_24);
	vBitmapOutput(15*TILE_SIZE,42*TILE_SIZE+8,"Exit Game",GLUT_BITMAP_TIMES_ROMAN_24);
	
	glFlush(); 
}
void interface_tableau_score(void){

	int x;
	int debutCadre=8;
	
	int nombreScore=listeAffichage->nombre;
	ElementScore* actuel=listeAffichage->premier;
	
	glColor3f(0.9f,0.8f,0.3f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,0.0f);
	
	glBegin(GL_QUADS);
	
	glVertex2f(0.0,0.0);
	glVertex2f(64*TILE_SIZE,0.0f);
	glVertex2f(64*TILE_SIZE,64*TILE_SIZE);
	glVertex2f(0.0f,64*TILE_SIZE);

	glEnd();
	for(x=0;x<nombreScore;x++){
		
		glColor3f(0.9f,0.6f,0.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(8*TILE_SIZE,debutCadre*TILE_SIZE,0.0f);
		
		glBegin(GL_QUADS);
		
		glVertex2f(0.0,0.0);
		glVertex2f(38*TILE_SIZE,0.0f);
		glVertex2f(38*TILE_SIZE,3*TILE_SIZE);
		glVertex2f(0.0f,3*TILE_SIZE);
		
		glEnd();
		debutCadre+=4;
	}
	debutCadre=8;
	printf("nombreScore %d\n",nombreScore);
	for(x=0;x<nombreScore;x++){
		char* valeurPlace=NULL;
		valeurPlace=int_vers_char(actuel->element.place);
		char String[MAX_NOM]={" ->"};
		char tamponString[MAX_NOM*2]={"\0"};
		strcpy(tamponString,valeurPlace);
		strcat(tamponString,String);
		strcat(tamponString,actuel->element.nom);
		
		glColor3d(1,0.1,0.1);
		printf("premier vBitmap %d\n",x);
		vBitmapOutput(10*TILE_SIZE,((debutCadre+2)*TILE_SIZE)+8,tamponString,GLUT_BITMAP_TIMES_ROMAN_24);
		
		free(valeurPlace);
		
		char* valeurScore=NULL;
		//char nomp[MAX_NOM]={"test"};
		valeurScore=int_vers_char(actuel->element.sco);
		
		printf("deuxieme vBitmap\n");
		vBitmapOutput(30*TILE_SIZE,((debutCadre+2)*TILE_SIZE)+8,valeurScore,GLUT_BITMAP_TIMES_ROMAN_24);
		
		debutCadre+=4;
		actuel=actuel->suivant;
		free(valeurScore);
	}
	glFlush(); 

}
void hub_info_jeu(){


	glColor3d(0.9,0.9,0.9); // Texte en blanc

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
void interface_entree_nom(char* nom){

	int y=camera.y-2;
	int x=camera.x-10;
	
		glColor3f(0.1f,0.1f,0.6f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(x*TILE_SIZE,y*TILE_SIZE,0.0f);
		
		glBegin(GL_QUADS);
		
		glVertex2f(0.0,0.0);
		glVertex2f(TILE_SIZE*24,0.0f);
		glVertex2f(TILE_SIZE*24,TILE_SIZE*4);
		glVertex2f(0.0f,TILE_SIZE*4);
		
		glEnd();
	
	glColor3d(0.9,0.9,0.9); // Texte en blanc
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	char string[MAX_NOM+12]={"Votre nom: "};
	strcat(string,nom);
	printf("%s\n",string);
	vBitmapOutput((x+3)*TILE_SIZE,(y+2)*TILE_SIZE+(TILE_SIZE/2),string,GLUT_BITMAP_TIMES_ROMAN_24);
	 
}
void interface(int nb){
	
	
	printf("Interface\n");
	if(MENU||MenuTabScore){
		
		switch (selectionMenu){
			case 0:
				interface_menu();
				break;
			case 1:
				
				break;
			case 2:
				interface_tableau_score();
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				break;

		}
			
	}
	else if(!MENU){
		drawMapCall();
		drawEnnemis();
		drawJoueur();
		drawTirs();
		hub_info_jeu();
		if(selectionMenu==5||selectionMenu==6){
			interface_entree_nom(nomEncode);
		}
	}
};


