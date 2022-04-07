#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ennemi.h"

ListeEnnemi* creer_liste(){
  char nom[MAX_NOM]={"Bot1"};
	ListeEnnemi* liste=malloc(sizeof(ListeEnnemi));
	ElementEnnemi* ennemi=malloc(sizeof(ElementEnnemi));
	if(liste==NULL||ennemi==NULL){
		exit(EXIT_FAILURE);
	}
	
	ennemi->hp=1;
	ennemi->suivant=NULL;
  ennemi->suivant=NULL;
	strcpy(ennemi->nom,nom);
	liste->premier=ennemi;
  liste->dernier=ennemi;
	liste->nombre=1;
	
	return(liste);
};
