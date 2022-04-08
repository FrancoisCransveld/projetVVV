#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ennemi.h"

//PRE:aucun argument d'entree
//POST:crée la liste chainée et initialise le premier element de cette liste chainee avec la vie de l'ennemi à 1, la position à(0;0) le type à 0 et le nom à Bot1
ListeEnnemi* creer_liste(){
  char nom[MAX_NOM]={"Bot1"};
	ListeEnnemi* liste=malloc(sizeof(ListeEnnemi));
	ElementEnnemi* ennemi=malloc(sizeof(ElementEnnemi));
	if(liste==NULL||ennemi==NULL){
		exit(EXIT_FAILURE);
	}
	
	ennemi->e->vie=1;
	ennemi->e->pos->x=0;
	ennemi->e->pos->y=0;
	ennemi->e->TypeEnnemi=0;
	ennemi->suivant=NULL;
  	ennemi->suivant=NULL;
	strcpy(ennemi->e->nom,nom);
	liste->premier=ennemi;
  	liste->dernier=ennemi;
	liste->nombre=1;
	
	return(liste);
};

//PRE:prend en entrée la liste chainée à laquel on donne un nouvelle élément, le nom de cette élément, sa vie, sa coordonnee, son type
//POST:ajoute un ennemi en fin de la liste chainée, qui aura toute les caractéristiques donnée en entrée
void nouvel_ennemi(ListeEnnemi* liste, char nom[], int vie, Coordonnee pos, TypeEnnemi t){
	
	ElementEnnemi* actuel=liste->dernier;
	ElementEnnemi* nouveau=malloc(sizeof(ElementEnnemi));
	nouveau->e->vie=vie;
	nouveau->e->pos=pos;
	nouveau->e->type=t;
	nouveau->suivant=NULL;
	actuel->suivant=nouveau;
	nouveau->precedent=actuel;
	strcpy(nouveau->e->nom,nom);
	liste->nombre++;
	liste->dernier=nouveau;
};
//PRE:prend en entrée la liste chainée à laquel on donne un nouvelle élément, le nom de cette élément, sa vie, sa coordonnee, son type
//POST:on modifie un élément de la liste donnée, cette élement se retrouve avec numero il correspon à la place dans la liste chainée commençant par 0 jusque nombre-1
void modifier_ennemi(ListeEnnemi* liste, int numero, char nom[], int vie, Coordonnee pos, TypeEnnemi t){
	int i=0;
	int declageE=numero;
	bool SensCroissant=true;
	ElementEnnemi* actuel=NULL;
	if(numero<liste->nombre){
		if(liste->nombre/2<numero){
			actuel=liste->premier;
		}
		else{
			actuel=liste->dernier;
			SensCroissant=false;
			decalageE=liste->nombre-numero-1;
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
		actuel->e->vie=vie;
		actuel->e->pos=pos;
		actuel->e->type=t;
		strcpy(actuel->e->nom,nom);
	}
};
//PRE:On prend la liste dans laquel on veut supprimer et le numéro de l'élément (int numero) on commence par 0
//POST:Supprime l'element numero et refait les liens entre les suivants et précédent
void supprimer_ennemi_numero(ListeEnnemi* liste, int numero){
	int i=0;
	int declageE=numero;
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
			decalageE=liste->nombre-numero-1;
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
		//pas sur que ça marche
		//actuel->precedent->suivant=actuel->suivant;
		//actuel->suivant->precedent=actuel->precedent;
		precedent=actuel->precedent;
		suivant=actuel->suivant;
		if(precedent==NULL){
			suivant->precedent=NULL;
		}
		else if(suivant==NULL){
			precedent->suivant==NULL;
		}
		else{
			precedent->suivant==actuel->suivant;
			suivant->precedent=actuel->precedent;
		}
		free(actuel);
		liste->nombre--;
	}
};
//PRE: argument d'entrée nécessaire la structure liste de la chaine, le numéro de l'ennemi et les dégats infligé
//POST:Retire un nombre de vie égale à (int degat) à l'ennemi numéro (int numero) de la liste chainée d'ennemi (ListeEnnemi liste)
void retirer_vie_numero(ListeEnnemi* liste, int numero, int degat){
	int i=0;
	int declageE=numero;
	bool SensCroissant=true;
	ElementEnnemi* actuel=NULL;
	if(numero<liste->nombre){
		if(liste->nombre/2<numero){
			actuel=liste->premier;
		}
		else{
			actuel=liste->dernier;
			SensCroissant=false;
			decalageE=liste->nombre-numero-1;
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
		actuel->e->vie-=degat;
		if(actuel->e->vie<1){
			supprimer_ennemi_numero(ListeEnnemi* liste, int numero);
		}
	}
};
//PRE:En argument on prend le numero de l'ennemi dans la liste à modifier, la liste en question, et la Coordonnee pos
//POST:modifie uniquement la position (ElementEnnemi e->pos) de l'ennemi numéro (numero) de la liste chainée (liste) 
void modifier_pos_ennemi(ListeEnnemi* liste, int numero, Coordonnee pos){
	int i=0;
	int declageE=numero;
	bool SensCroissant=true;
	ElementEnnemi* actuel=NULL;
	if(numero<liste->nombre){
		if(liste->nombre/2<numero){
			actuel=liste->premier;
		}
		else{
			actuel=liste->dernier;
			SensCroissant=false;
			decalageE=liste->nombre-numero-1;
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
		actuel->e->pos=pos;
	}
};
		
		
		
