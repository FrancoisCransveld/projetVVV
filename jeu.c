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
	glutTimerFunc(50, upDateKeyboard, 0);
};
void switchMap(){
	printf("switchMap\n");
	printf("x%d y%d\nmap %d %d",camera.x,camera.y,nextMap.taille.x,nextMap.taille.y);
	bool switchEffectue=false;
	bool switchLREffectue=false;
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
		switchEffectue=true;
	}
	if(camera.y>=nextMap.taille.y/2+currentMap.taille.y){
		tamponCam=camera.y-nextMap.taille.y;
		tamponJ=j.pos.y-nextMap.taille.y;
		variationE.y-=nextMap.taille.y;
		//currentMap=nextMap;
		switchEffectue=true;
	}
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
	}
	if(switchEffectue||switchLREffectue){
		modifier_pos_ennemis(liste,variationE);
		if(switchEffectue){
			camera.y=tamponCam;
			j.pos.y=tamponJ;
		}
		if(switchLREffectue){
			camera.x=tamponCam;
			j.pos.x=tamponJ;
		}
	}
	if(switchEffectue){
		printf("ici 1");
		currentMap.c=NULL;//peut-être ça va déconner!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		currentMap=nextMap;
		niveauA.Nmap[niveauA.current].loadStatus=false;
		niveauA.current=niveauA.next;

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
		printf("nextload %d\n",nextLoad);
		loadNext(nextLoad);
	}
	if(switchLREffectue){
		printf("ici 2");
		currentMap.c=NULL;//peut-être ça va déconner!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
		}
		loadNext(nextLoad);
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
	switchMap();
	glutPostRedisplay();
};
