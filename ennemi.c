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
#include "ennemi.h"
#include "LoadMaps.h"
#include "interface.h"
//PRE:aucun argument d'entree
//POST:crée la liste chainée et initialise le premier element de cette liste chainee avec la vie de l'ennemi à 1, la position à(0;0) le type à 0 et le nom à Bot1
ListeEnnemi* creer_liste(void){
  	char nom[MAX_NOM]={"Bot1"};
  
	ListeEnnemi* liste=malloc(sizeof(ListeEnnemi));
	
	ElementEnnemi* ennemi=malloc(sizeof(ElementEnnemi));
	
	if(liste==NULL||ennemi==NULL){
		exit(EXIT_FAILURE);
	}
		
	ennemi->e.vie=0;
	ennemi->e.pos.x=0;
	ennemi->e.pos.y=0;
	ennemi->e.type=vide;
	ennemi->suivant=NULL;
  	ennemi->precedent=NULL;
  	ennemi->e.attente=true;
  	ennemi->e.nom=malloc(sizeof(char*)*MAX_NOM);
	strcpy(ennemi->e.nom,nom);
	liste->premier=ennemi;
  	liste->dernier=ennemi;
	liste->nombre=1;
	
	return (liste);
};

//PRE:prend en entrée la liste chainée à laquel on donne un nouvelle élément, le nom de cette élément, sa vie, sa coordonnee, son type
//POST:ajoute un ennemi en fin de la liste chainée, qui aura toute les caractéristiques donnée en entrée
void nouvel_ennemi(ListeEnnemi* liste, char* nom, int vie, Coordonnee pos, TypeEnnemi t){
	
	ElementEnnemi* actuel=liste->dernier;
	if(actuel->e.type!=vide){
		ElementEnnemi* nouveau=malloc(sizeof(ElementEnnemi));

		nouveau->e.vie=vie;
		nouveau->e.pos=pos;
		nouveau->e.type=t;
		nouveau->e.attente=true;
		nouveau->suivant=NULL;
		actuel->suivant=nouveau;
		nouveau->precedent=actuel;
		
		nouveau->e.nom=malloc(sizeof(char*)*MAX_NOM);
		
		strcpy(nouveau->e.nom,nom);

		liste->nombre++;
		liste->dernier=nouveau;
	}
	else{
		modifier_ennemi(liste, 0, nom, vie, pos, t,true);
	}
	
};
//PRE:prend en entrée la liste chainée à laquel on donne un nouvelle élément, le nom de cette élément, sa vie, sa coordonnee, son type
//POST:on modifie un élément de la liste donnée, cette élement se retrouve avec numero il correspon à la place dans la liste chainée commençant par 0 jusque nombre-1
void modifier_ennemi(ListeEnnemi* liste, int numero, char nom[], int vie, Coordonnee pos, TypeEnnemi t,bool a){
	int i=0;
	int decalage=numero;
	bool SensCroissant=true;
	ElementEnnemi* actuel=NULL;
	if(numero<liste->nombre){
		if(liste->nombre/2<numero){
			actuel=liste->premier;
		}
		else{
			actuel=liste->dernier;
			SensCroissant=false;
			decalage=liste->nombre-numero-1;
		}

			while(i<decalage){
				if(SensCroissant){
					actuel=actuel->suivant;
				}
				else{
					actuel=actuel->precedent;
				}
				i++;
			}
		actuel->e.vie=vie;
		actuel->e.pos=pos;
		actuel->e.type=t;
		actuel->e.attente=a;
		actuel->e.nom=malloc(sizeof(char*)*MAX_NOM);
		strcpy(actuel->e.nom,nom);
	}
};
//PRE:On prend la liste dans laquel on veut supprimer et le numéro de l'élément (int numero) on commence par 0
//POST:Supprime l'element numero et refait les liens entre les suivants et précédent
void supprimer_ennemi_numero(ListeEnnemi* liste, int numero){
	int i=0;
	int decalage=numero;
	bool SensCroissant=true;
	ElementEnnemi* actuel=NULL;
	ElementEnnemi* precedent=NULL;
	ElementEnnemi* suivant=NULL;
	if(numero<liste->nombre){
		if(liste->nombre/2<numero){
			actuel=liste->premier;
		}
		else{
			actuel=liste->dernier;
			SensCroissant=false;
			decalage=liste->nombre-numero-1;
		}

			while(i<decalage){
				if(SensCroissant){
					actuel=actuel->suivant;
				}
				else{
					actuel=actuel->precedent;
				}
				i++;
			}
		precedent=actuel->precedent;
		suivant=actuel->suivant;
		if(!actuel->e.attente){
			if(precedent==NULL&&suivant==NULL){
				char nom[5]={"vide"};
				actuel->e.vie=0;
				strcpy(actuel->e.nom,nom);
				actuel->e.pos.x=-64;
				actuel->e.pos.y=-64;
				actuel->e.type=vide;
			}
			else {
				if(precedent==NULL){
					suivant->precedent=NULL;
					liste->premier=actuel->suivant;
				}
				else if(suivant==NULL){
					precedent->suivant=NULL;
					liste->dernier=actuel->precedent;
				}
				else{
					precedent->suivant=actuel->suivant;
					suivant->precedent=actuel->precedent;
				}
				free(actuel);
				liste->nombre--;
			}
		}
	}
};
//PRE: argument d'entrée nécessaire la structure liste de la chaine, le numéro de l'ennemi et les dégats infligé
//POST:Retire un nombre de vie égale à (int degat) à l'ennemi numéro (int numero) de la liste chainée d'ennemi (ListeEnnemi liste)
void retirer_vie_numero(ListeEnnemi* liste, int numero, int degat){
	int i=0;
	int decalage=numero;
	bool SensCroissant=true;
	ElementEnnemi* actuel=NULL;
	if(numero<liste->nombre){
		if(liste->nombre/2<numero){
			actuel=liste->premier;
		}
		else{
			actuel=liste->dernier;
			SensCroissant=false;
			decalage=liste->nombre-numero-1;
		}

			while(i<decalage){
				if(SensCroissant){
					actuel=actuel->suivant;
				}
				else{
					actuel=actuel->precedent;
				}
				i++;
			}
		actuel->e.vie-=degat;
		if(actuel->e.vie<1){
			supprimer_ennemi_numero(liste, numero);
		}
		
	}
};
//PRE:En argument on prend le numero de l'ennemi dans la liste à modifier, la liste en question, et la Coordonnee pos
//POST:modifie uniquement la position (ElementEnnemi e->pos) de l'ennemi numéro (numero) de la liste chainée (liste) 
void modifier_pos_ennemi(ListeEnnemi* liste, int numero, Coordonnee pos){
	int i=0;
	int decalage=numero;
	bool SensCroissant=true;
	ElementEnnemi* actuel=NULL;
	if(numero<liste->nombre){
		if(liste->nombre/2<numero){
			actuel=liste->premier;
		}
		else{
			actuel=liste->dernier;
			SensCroissant=false;
			decalage=liste->nombre-numero-1;
		}

			while(i<decalage){
				if(SensCroissant){
					actuel=actuel->suivant;
				}
				else{
					actuel=actuel->precedent;
				}
				i++;
			}
		actuel->e.pos=pos;
	}
};
//PRE:En argument la liste à modifier, la variation de Coordonnee pos
//POST:On déplace tous les ennemis de la variation
void modifier_pos_ennemis(ListeEnnemi* liste, Coordonnee variation){
	int i=0;
	
	ElementEnnemi* actuel=liste->premier;
	for(i=0;i<liste->nombre;i++){
		actuel->e.pos.x+=variation.x;
		actuel->e.pos.y+=variation.y;
		if(actuel->e.pos.y>camera.y+(CAM_RANGE*2)||actuel->e.pos.y<camera.y-(CAM_RANGE*2)||actuel->e.pos.x>camera.x+(CAM_RANGE*2)||actuel->e.pos.x<camera.x-(CAM_RANGE*2)){
			printf("suprimer\n");
			actuel->e.attente=false;
			supprimer_ennemi_numero(liste, i);
		}
		actuel=actuel->suivant;
	}
	afficher_liste(liste);
};

//suprime les ennemis hors de portées 
void supprimer_ennemi_hors_portee(ListeEnnemi* liste){
	ElementEnnemi* actuel=liste->premier;
	for(int i=0;i<liste->nombre;i++){
		if(actuel->e.pos.y>camera.y+(CAM_RANGE*2)||actuel->e.pos.y<camera.y-(CAM_RANGE*2)||actuel->e.pos.x>camera.x+(CAM_RANGE*2)||actuel->e.pos.x<camera.x-(CAM_RANGE*2)){
			printf("suprimer\n");
			actuel->e.attente=false;
			supprimer_ennemi_numero(liste, i);
		}
		actuel=actuel->suivant;
	}
	afficher_liste(liste);
};

//PRE: prend en argument la liste
//post:affiche cette liste dans la console
void afficher_liste(ListeEnnemi* liste){
	int i=0;
	printf("---Liste ennemi : ---\n");
	ElementEnnemi* actuel=liste->premier;
	while(i<liste->nombre){
	printf(" nom ennemi :%s vie : %d pos : (x=%d;y=%d) type :%d\n",actuel->e.nom,actuel->e.vie,actuel->e.pos.x,actuel->e.pos.y,actuel->e.type);
	actuel=actuel->suivant;
	i++;
	}
};			
