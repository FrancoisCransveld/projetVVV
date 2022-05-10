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
#include "keyboard.h"
#include "score.h"

//PRE:prend en argument la référence vers stucture mode et la référence vers l'int nombreJoueur correspondant au nombre de joueur de la partie précédente, sinon 2
//POST:permet de modifier les paramètres de la partie (mode de jeu en cours et nombre de joueur), puis de lancer la partie soit avec les modification de mode,
//     soit en version classique et le nombre de joueur défini, 2 au premier lancement.
int menu(void){
    
	//bool commencer=false;
	int choix=selectionMenu;
	if(MENU){    	
		printf("\n-----------Menu----------\n\n");
		glutMouseFunc(mouse_pos);
		glutKeyboardFunc(KeyboardJeu);		//fonction de glut gérant le clavier
		glutSpecialFunc(KeyboardSpecialJeu);
		printf(" CoordonneeSouris: (%d,%d)\n",coordonneeSouris.x,coordonneeSouris.y);	
		if(MOUSECLICK){
			MOUSECLICK=false;
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
		}
	}
	coordonneeSouris.x=0;
	coordonneeSouris.y=0;
	return choix;
	
};
void upDatemenu(int num){
	printf("updateMenu \n");
	if(MENU||MenuTabScore){
		selectionMenu=menu();
		if(selectionMenu!=2){
			printf("suprimer listeA\n");
			if(listeAffichage->premier!=NULL){
				printf("premier!=NULL\n");
				if(listeAffichage->nombre>0){
					printf("nombre>0\n");
					afficher_listeSc(listeAffichage);
					suprimer_liste_elementScore(listeAffichage);
				}
			}
		}
		if(selectionMenu>0){
			
			int nombreMap=8;
			if(selectionMenu==1){
				MENU=false;
				MenuTabScore=false;
				printf("MENU=false\n");
				liste = creer_liste();
				afficher_liste(liste);
				preparation_niveau(nombreMap);
				loadMaps();
				j=loadJoueur(0);

			}
			else if(selectionMenu==2){
				printf("selection 2 interface\n");
				if(listeAffichage->nombre<=1){
					printf("recuperation Tab\n");
					recuperer_tableau_score(listeAffichage);
					afficher_listeSc(listeAffichage);
				}
				interface(1);
				glutKeyboardFunc(KeyboardJeu);
				MENU=false;
				MenuTabScore=true;
			}
			else if(selectionMenu==3){
				
			}
			else if(selectionMenu==4){
			
			}
			
		}
		else{
			//glutTimerFunc(50, upDatemenu, 3);
		}
	}
	glutTimerFunc(50, upDatemenu, 3);
	
	glutPostRedisplay();
};

