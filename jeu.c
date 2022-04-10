#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include "jeu.h"
#include "LoadMaps.h"
#include "interface.h"
#include "joueur.h"
bool UP = false;
bool LEFT = false;
bool RIGHT = false;
bool DOWN = false;
bool ESCAPE = false;
bool SPACE = false;
void Keyboard(unsigned char key, int x, int y)  // fonction allant gérer les input
{
	//printf("Keyboard \n");
	switch(key)
	{
		case 27:
			exit(0);
		case'z':
			UP = true;
			break;
		case'q':
			LEFT = true;
			break;
		case'd':
			RIGHT = true;
			break;
		case's':
			DOWN = true;
			break;
		case' ':
			SPACE = true;
			break;
	}	
};
void KeyboardSpecial(int key, int x, int y)  // fonction allant gérer les input
{
	//printf("KeyboardSpecial \n");
	switch(key)
	{
		case GLUT_KEY_UP:
			UP = true;
			break;
		case GLUT_KEY_LEFT:
			LEFT = true;
			break;
		case GLUT_KEY_RIGHT:
			RIGHT = true;
			break;
		case GLUT_KEY_DOWN:
			DOWN = true;
			break;
	}	
};
//glutTimerFunc(500, InputLoop, 1);
void upDateKeyboard(int i){
	jeu();
	if(j.tirs->nombre>0){
		deplacement_tirs(j.tirs);
	}
	glutTimerFunc(25, upDateKeyboard, 0);
};
void switchMap(){
	printf("switchMap\n");
	printf("x%d y%d\nmap %d %d",camera.x,camera.y,nextMap.taille.x,nextMap.taille.y);
	//bool switchEffectue=false;
	bool switchPrevious=false;
	bool switchNext=false;
	//bool switchLREffectue=false;
	int tamponCam=0;
	int tamponJ=0;
	int nextLoad;
	Coordonnee variationE;//variable qui sera envoyer à modifier_pos_ennemis(ListeEnnemi* liste, Coordonnee variation) pour déplacer les ennemis
	variationE.x=0;
	variationE.y=0;
	if(camera.y<=-nextMap.taille.y/2){
		tamponCam=camera.y+nextMap.taille.y;
		tamponJ=j.pos.y+nextMap.taille.y;
		variationE.y+=nextMap.taille.y;
		switchNext=true;
	}
	if(camera.y>=((previousMap.taille.y/2)+currentMap.taille.y)){
		if(nextMap.taille.y!=0){
			tamponCam=camera.y-nextMap.taille.y;
			tamponJ=j.pos.y-nextMap.taille.y;
			variationE.y-=nextMap.taille.y;
			switchPrevious=true;
		}
		else{
			tamponCam=camera.y-currentMap.taille.y;
			tamponJ=j.pos.y-currentMap.taille.y;
			variationE.y-=currentMap.taille.y;
			switchPrevious=true;
		}
	}
	/* On oublie pour le moment, trop compliqué
	
	if(camera.x>=currentMap.taille.x+nextLRMap.taille.x/2){
		tamponCam=camera.x-nextMap.taille.x;
		tamponJ=j.pos.x-nextMap.taille.x;
		variationE.x-=nextMap.taille.x;
		//currentMap=nextLRMap;
		switchLREffectue=true;
	}
	if(camera.x<=-nextLRMap.taille.x/2){
		tamponCam=camera.x+nextMap.taille.x;
		tamponJ=j.pos.x+nextMap.taille.x;
		variationE.x+=nextMap.taille.x;
		//currentMap=nextLRMap;
		switchLREffectue=true;
	}*/
	if(switchNext||switchPrevious){
		modifier_pos_ennemis(liste,variationE);
		camera.y=tamponCam;
		j.pos.y=tamponJ;

		/*
		if(switchLREffectue){
			camera.x=tamponCam;
			j.pos.x=tamponJ;
		}*/
	}
	if(switchNext){	//si on a un switch vers next lié à la position de la caméra à la moitié de nextMap.
	//On passe currentMap à previousMap et nextMap à currentMap et on va recharger l'éventuelle nextMap
		printf("ici 1");
		previousMap=currentMap;
		currentMap=nextMap;
		nextMap.c=NULL;
		nextMap.taille.y=0;
		nextMap.taille.x=0;
		niveauA.Nmap[niveauA.previous].loadStatus=false;//on change le status de previous avant de modifié sa position dans le tableau
		niveauA.previous=niveauA.current;
		niveauA.current=niveauA.next;
		nextLoad=niveauA.next+1;
		/*	trop compliqué on oublie pour le moment
		if(!nextMap.previous){ //si la map n'est pas avant current dans le niveau
			if(niveauA.current>niveauA.nextLR){//la map current est plus loin dans le niveau que la map nextLR on peu la libérer
				niveauA.Nmap[niveauA.nextLR].loadStatus=false;
				nextLRMap.c=NULL;
				nextLoad=niveauA.current+1;
			}
			else{	//loadStatus est true
				nextLoad=niveauA.current+2;
			}
		}
		else{	//la map next est avant currentMap
			if(niveauA.current<niveauA.nextLR){
				niveauA.Nmap[niveauA.nextLR].loadStatus=false;
				nextLRMap.c=NULL;
				nextLoad=niveauA.current-1;
			}
			else{
				nextLoad=niveauA.current-2;
			}
		}
		//printf("nextload %d\n",nextLoad);
		loadNext(nextLoad);
	}*/
	}
	if(switchPrevious){
		nextMap=currentMap;
		currentMap=previousMap;
		previousMap.c=NULL;
		previousMap.taille.y=0;
		previousMap.taille.x=0;
		niveauA.Nmap[niveauA.next].loadStatus=false;//on change le status de previous avant de modifié sa position dans le tableau
		niveauA.next=niveauA.current;
		niveauA.current=niveauA.previous;
		nextLoad=niveauA.previous-1;
		/*currentMap.c=NULL;
		currentMap=nextLRMap;
		niveauA.Nmap[niveauA.current].loadStatus=false;
		niveauA.current=niveauA.nextLR;

		if(!nextMap.previous){ //si la map next n'est pas avant current dans le niveau
			if(niveauA.current>niveauA.next){//la map current est plus loin dans le niveau que la map next on peu la libérer
				niveauA.Nmap[niveauA.nextLR].loadStatus=false;
				nextLRMap.c=NULL;
				nextLoad=niveauA.current+1;
			}
			else{	//loadStatus est true
				nextLoad=niveauA.current+2;
			}
		}
		else{	//la map nextLR est avant currentMap
			if(niveauA.current<niveauA.next){
				niveauA.Nmap[niveauA.next].loadStatus=false;
				nextMap.c=NULL;
				nextLoad=niveauA.current-1;
			}
			else{
				nextLoad=niveauA.current-2;
			}
		}*/
		
	}
	if(nextLoad<niveauA.nombreMap&&nextLoad>=0){
		printf("prochaine Map loade :%d nextMap %d previousMap %d currentmap %d",nextLoad,niveauA.next,niveauA.previous,niveauA.current);
		printf("cam x%d y%d\n",camera.x,camera.y);
		loadNext(nextLoad);
	}
	else{
		printf("limite du niveau\n");
	}
};
void jeu()
{
	glutKeyboardFunc(Keyboard);		//fonction de glut gérant le clavier
	glutSpecialFunc(KeyboardSpecial);
	if (LEFT == true)
	{
		
		moveLeft(j);		//va se déplacer vers la gauche si on appuie sur q
		LEFT = false;
		//printf("LEFT ");
	}
	if (RIGHT == true)
	{
		//printf("RIGHT ");
		moveRight(j);		//va se déplacer vers la droite si on apppuie sur d
		RIGHT = false;
	}
	if (UP == true)
	{
		//printf("UP ");
		moveUp(j);
		UP = false;
	}
	
	if (DOWN == true)
	{
		//printf("DOWN ");
                moveDown(j);
		DOWN = false;
	}
	if (SPACE == true){
	
		if(j.tirs->nombre<j.maxTirs){
			tirs(j.tirs,j.pos,pistolet,j.dir);
		}
		SPACE=false;
	}
	
	glutPostRedisplay();
};
