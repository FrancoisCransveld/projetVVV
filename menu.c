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
#include "menu.h"
#include "interface.h"

//PRE:prend en argument la référence vers stucture mode et la référence vers l'int nombreJoueur correspondant au nombre de joueur de la partie précédente, sinon 2
//POST:permet de modifier les paramètres de la partie (mode de jeu en cours et nombre de joueur), puis de lancer la partie soit avec les modification de mode,
//     soit en version classique et le nombre de joueur défini, 2 au premier lancement.
int menu(void){
    
	//bool commencer=false;
	int choix=0;
    	
	printf("\n-----------Menu----------\n\n");
	glutMouseFunc(mouse_pos);
	glutKeyboardFunc(Keyboard);		//fonction de glut gérant le clavier
	glutSpecialFunc(KeyboardSpecial);
	printf(" CoordonneeSouris: (%d,%d)\n",coordonneeSouris.x,coordonneeSouris.y);	
	if(((coordonneeSouris.x>=8*TILE_SIZE)&&(coordonneeSouris.x<30*TILE_SIZE))&&((coordonneeSouris.y>=16*TILE_SIZE)&&(coordonneeSouris.y<20*TILE_SIZE))){
        	choix=1;
        	printf("choix %d\n",choix);
	}
	else if(((coordonneeSouris.x>=8*TILE_SIZE)&&(coordonneeSouris.x<30*TILE_SIZE))&&((coordonneeSouris.y>=24*TILE_SIZE)&&(coordonneeSouris.y<28*TILE_SIZE))){
		choix=2;
        	printf("choix %d\n",choix);		
	}
	else if(((coordonneeSouris.x>=8*TILE_SIZE)&&(coordonneeSouris.x<30*TILE_SIZE))&&((coordonneeSouris.y>=32*TILE_SIZE)&&(coordonneeSouris.y<36*TILE_SIZE))){
		choix=3;
        	printf("choix %d\n",choix);
	}
	else if(((coordonneeSouris.x>=8*TILE_SIZE)&&(coordonneeSouris.x<30*TILE_SIZE))&&((coordonneeSouris.y>=40*TILE_SIZE)&&(coordonneeSouris.y<44*TILE_SIZE))){
		choix=4;
        	printf("choix %d\n",choix);
	}
	coordonneeSouris.x=0;
	coordonneeSouris.y=0;
	return choix;
	
};
void upDatemenu(int num){
	printf("updateMenu \n");
	if(MENU){
		selectionMenu=menu();
		if(selectionMenu>0){
			MENU=false;
			printf("MENU=false\n");
			int nombreMap=8;
			if(!MENU&&selectionMenu==1){
				
				liste = creer_liste();
				afficher_liste(liste);
				preparation_niveau(nombreMap);
				loadMaps();
				j=loadJoueur(0);
				upDateKeyboard(0);
				upDateTirs(1);
				upDateEnnemi(2);
			}
			else if(!MENU&&selectionMenu==2){
				liste = creer_liste();
				afficher_liste(liste);
				preparation_niveau(nombreMap);
				loadMaps();
				j=loadJoueur(0);
				upDateKeyboard( 0);
				upDateTirs(1);
				upDateEnnemi(2);
			}
			else if(!MENU&&selectionMenu==3){
				
			}
			else if(!MENU&&selectionMenu==4){
			
			}
			selectionMenu=0;
		}
		else{
			//glutTimerFunc(50, upDatemenu, 3);
		}
	}
	glutTimerFunc(500, upDatemenu, 3);
	glutPostRedisplay();
};

