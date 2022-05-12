#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jeu.h"
#include "LoadMaps.h"
#include "interface.h"
#include "joueur.h"
#include "menu.h"
#include "collision.h"
#include "score.h"
#include "keyboard.h"



void upDateKeyboard(int num){
	printf("updateKeyboard %d \n",selectionMenu);
	if(selectionMenu==1){
		jeu();
	}
	if(INPUT){
		INPUT=false;
	}
	else{
		UP=false;
		LEFT=false;
		RIGHT=false;
		DOWN=false;
		SPACE=false;
	}
	glutTimerFunc(50, upDateKeyboard, 0);
};
//PRE:
//POST:
void upDateTirs(int num){
	printf("upDateTirs\n");
	if(selectionMenu==1){
		if (SPACE == true){
			if(j.tirs->nombre<j.maxTirs){
				tirs(j.tirs,j.pos,pistolet,j.dir);
			}
			SPACE=false;
		}
		if(j.tirs->nombre>0){
			//printf("preDeplacement\n");
			deplacement_tirs(j.tirs);
			for(int i=0;i<liste->nombre;i++){
				
				for(int tirs=0;tirs<j.tirs->nombre;tirs++){
					if(i<liste->nombre){
						/*//printf("PreCoordonneeEnnemi %d\n", i);
						Coordonnee EnnemiActuel=pos_Ennemi(liste,i);
						//printf("PreCoordonneeTirs %d\n", tirs);
						Coordonnee tirsActuel=pos_tirs(j.tirs,tirs);*/
						if(collision_tirs_ennemi(i,tirs)){ 
							retirer_vie_numero(liste, i,degat_tirs(j.tirs, tirs));
							supprimer_tirs_numero(j.tirs,tirs);
							printf("sortie de suppresion tirs \n");
						}
					}
					//printf("sortie for 2\n");
				}
				//printf("sortie for 1\n");
			}
		}
		//printf("fin UpdateTirs\n");
	}
	glutTimerFunc(25, upDateTirs,1);
};

//PRE:
//POST:
void upDateEnnemi(int num){
	printf("upDateEnnemi\n");
	bool colli=true;
	if(selectionMenu==1){
		action_ennemi(liste);
		colli=collisionEnnemiJoueur();
	}

	if(colli){
		glutTimerFunc(1000, upDateEnnemi,2);
	}
	else{
		glutTimerFunc(120, upDateEnnemi,2); 
	}
};
//PRE:
//POST:Cette fonction va échanger la carte current avec la carte sur laquel le joueur se trouve (previous ou next) et décale la position sur l'axe vertical de tout les objets (joueur, tirs, ennemis)
void switchMap(){
	//printf("switchMap\n");
	//printf("x%d y%d\nmap %d %d",camera.x,camera.y,nextMap.taille.x,nextMap.taille.y);
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
	
	if(switchNext||switchPrevious){
		printf("switchMap\n");
		modifier_pos_ennemis(liste,variationE);
		camera.y=tamponCam;
		j.pos.y=tamponJ;
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
		niveauA.Nmap[niveauA.previous].ennemi=true;
		niveauA.previous=niveauA.current;
		niveauA.current=niveauA.next;
		nextLoad=niveauA.next+1;
		
	}
	if(switchPrevious){
		nextMap=currentMap;
		currentMap=previousMap;
		previousMap.c=NULL;
		previousMap.taille.y=0;
		previousMap.taille.x=0;
		niveauA.Nmap[niveauA.next].loadStatus=false;//on change le status de previous avant de modifié sa position dans le tableau
		niveauA.Nmap[niveauA.next].ennemi=true;
		niveauA.next=niveauA.current;
		niveauA.current=niveauA.previous;
		nextLoad=niveauA.previous-1;
		
		
	}
	if(nextLoad<niveauA.nombreMap&&nextLoad>=0){
		printf("prochaine Map loade :%d nextMap %d previousMap %d currentmap %d",nextLoad,niveauA.next,niveauA.previous,niveauA.current);
		printf("cam x%d y%d\n",camera.x,camera.y);
		loadNext(nextLoad);
	}
	else{
		//printf("limite du niveau\n");
	}
};
void mort(){
	j.vie--;
	j.hp=5;
	supprimer_liste_ennemi(liste);
	if(j.vie<=0){
		game_over();
	}
	else{
		liste = creer_liste();
		niveauA.current=0;
		niveauA.next=1;
		loadMaps();
		j.pos=load_respawn_Joueur(niveauA.current);
		
	}
};
void game_over(){
	
	selectionMenu=5;
	inscription_score();
	
};
void jeu()
{
	printf("jeu \n");
	glutKeyboardFunc(KeyboardJeu);		//fonction de glut gérant le clavier
	glutSpecialFunc(KeyboardSpecialJeu);
	if (LEFT == true)
	{
		moveLeft(j);		//va se déplacer vers la gauche si on appuie sur q
		//LEFT = false;
		printf("LEFT ");
	}
	if (RIGHT == true)
	{
		printf("RIGHT ");
		moveRight(j);		//va se déplacer vers la droite si on apppuie sur d
		//RIGHT = false;
	}
	if (UP == true)
	{
		printf("UP ");
		moveUp(j);
		//UP = false;
	}
	
	if (DOWN == true)
	{
		printf("DOWN ");
        	moveDown(j);
		//DOWN = false;
	}
	if (j.hp<=0){
		printf("mort\n");
		mort();
	}
	glutPostRedisplay();
};
