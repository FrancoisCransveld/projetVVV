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
#include <math.h>
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
	if(liste->nombre>0){
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
	else if(liste->nombre==0){
		ElementEnnemi* nouveau=malloc(sizeof(ElementEnnemi));

		nouveau->e.vie=vie;
		nouveau->e.pos=pos;
		nouveau->e.type=t;
		nouveau->e.attente=true;
		nouveau->suivant=NULL;
		nouveau->precedent=NULL;
		
		nouveau->e.nom=malloc(sizeof(char*)*MAX_NOM);
		
		strcpy(nouveau->e.nom,nom);

		liste->nombre++;
		liste->dernier=nouveau;
		liste->premier=nouveau;
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
		if(numero<liste->nombre/2){
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
	
	if(liste==NULL){
		exit(EXIT_FAILURE);
	}
	int i=0;
	int decalage=numero;
	bool SensCroissant=true;
	if(liste->premier!=NULL){
		//afficher_liste(liste);
		ElementEnnemi* actuel=NULL;
		ElementEnnemi* precedent=NULL;
		ElementEnnemi* suivant=NULL;
		if(numero<liste->nombre){
			if(numero<liste->nombre/2){
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
					liste->premier=NULL;
					liste->dernier=NULL;
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
					
				}
				free(actuel);
				liste->nombre--;
				afficher_liste(liste);
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
		if(numero<liste->nombre/2){
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
		actuel->e.vie-=(degat+1);
		actuel->e.attente=false;
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
		if(numero<liste->nombre/2){
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
	int nombreMax=liste->nombre;
	for(i=0;i<nombreMax;i++){
		printf("avant ennemi %d->x:%d y:%d\n",i,actuel->e.pos.x,actuel->e.pos.y);
		actuel->e.pos.x+=variation.x;
		actuel->e.pos.y+=variation.y;
		printf("apres ennemi %d->x:%d y:%d\n",i,actuel->e.pos.x,actuel->e.pos.y);
		actuel=actuel->suivant;
	}
	supprimer_ennemi_hors_portee(liste);
	//afficher_liste(liste);
};

//suprime les ennemis hors de portées 
void supprimer_ennemi_hors_portee(ListeEnnemi* liste){
	ElementEnnemi* actuel=liste->premier;
	int nombreMax=liste->nombre;
	for(int i=0;i<nombreMax;i++){
		if(actuel->e.pos.y>camera.y+(CAM_RANGE*8)||actuel->e.pos.y<camera.y-(CAM_RANGE*8)){
			//printf("suprimer %d adresse %hx\n",i,actuel);
			actuel->e.attente=false;
			supprimer_ennemi_numero(liste, i);
		}
		else{
			actuel=actuel->suivant;
		}
	}
	//	afficher_liste(liste);
};
//PRE:
//POST:active et désactive les ennemis: e.attente=true en attente e.attente=false ennemi actif
void activer_ennemi_a_portee(ListeEnnemi* liste){
	ElementEnnemi* actuel=liste->premier;
	int nombreMax=liste->nombre;
	for(int i=0;i<nombreMax;i++){
		if(actuel->e.pos.y<camera.y+(CAM_RANGE+4)&&actuel->e.pos.y>camera.y-(CAM_RANGE+4)){
			//printf("activer %d adresse %hx\n",i,actuel);
			actuel->e.attente=false;
		}
		else{	
			actuel->e.attente=true;
		}
		actuel=actuel->suivant;
	}
	//	afficher_liste(liste);
};
//PRE:
//POST:Renvoie la coordonnee de l'ennemi, numero (les ennemis sont numeroté de 0 à liste.nombre-1)
Coordonnee pos_Ennemi(ListeEnnemi* liste,int numero){
	Coordonnee ennemiPos;
	ennemiPos.x=128;
	ennemiPos.y=128;
	if(liste->premier!=NULL){
	int i=0;
	int decalage=numero;
	bool SensCroissant=true;
	ElementEnnemi* actuel=NULL;
	if(numero<liste->nombre){
		if(numero<liste->nombre/2){
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
	}
	ennemiPos=actuel->e.pos;

	}
	return(ennemiPos);
}
//PRE:cette fontion reçoit un pointeur de map, une coordonnee x et une coordonnee y de l'ennemi ou il veut se déplacer
//POST:la fonction renvoie la coordonnee de l'ennemi sur la map qui le concerne next, current ou previous dans la structure coordonnee du pointeur de map donné en entrée ce qui premettra de vérifier la correspondance avec les murs sur les cartes.
void replacement_ennemi(int x, int y, Map* map){
	
	//printf("replacementJoueur\n");
	int mjX, mjY;
 	//variable pour le placement du joueur dans la carte sur lequel il se trouve (next, nextLR ou current).
	//recherche position par rapport à current 
	if(y<0||y>=currentMap.taille.y){  //position verticale en dehors 0 et taille currentMap
			
			mjX=x;				//x ne change pas
			if(y<0){			//si au dessus, alors la position dans nextMap est à la fin, donc à la taille de next+y (y est négatif)
				map->c=nextMap.c;       //j est juste au dessus de currentMap, donc dans nextMap
				mjY=y+nextMap.taille.y;
			}		
			else{			//si en dessous, alors la position dans previousMap est au début, donc à y-la hauteur de current	
				map->c=previousMap.c;       //j est juste au dessus de currentMap, donc dans nextMap
				mjY=y-currentMap.taille.y;
			}
	}
	else{
		map->c=currentMap.c;
		mjX=x;
		mjY=y;
	}
	//printf("car %c\n",map->c[0][0]);
	map->taille.x=mjX;	//Coordonnée de j dans la carte logique/le plateau qui le concerne contenu dans map->taille
	map->taille.y=mjY;
	return ;

};
//
//POST: fonction qui va appeler les ennemis pour effectuer leurs actions
void action_ennemi(ListeEnnemi* liste){
	ElementEnnemi* actuel=liste->premier;
	for(int i=0;i<liste->nombre;i++){
		if(!actuel->e.attente){
			switch(actuel->e.type){
				case voiture:
					action_voiture(&(actuel->e));
					break;
				case moto:
					action_moto(&(actuel->e));
					break;
				case camion:
					
					break;
				case SUV:
					
					break;
				case vide:
					break;
				
			}
		}
		actuel=actuel->suivant;
	}
};
//PRE:on envoie le pointeur de l'ennemi voiture dont le traitement est en cours dans action_ennemi
//POST:fonction ou l'on retrouve les actions automatique d'un ennemi type voiture appelé par action_ennemi
void action_voiture(Ennemi* voiture){
	int x=voiture->pos.x;
	int y=voiture->pos.y;
	if(voiture->pos.x-j.pos.x<0){
		x++;
	}
	else if(voiture->pos.x-j.pos.x>0){
		x--;
	}
	else{
		if(voiture->pos.y-j.pos.y<0){
			y++;
		}
		else if(voiture->pos.y-j.pos.y>0){
			y--;
		}
	}
	Map Emap;
	replacement_ennemi(x,y,&Emap);
	if(*(*(Emap.c+Emap.taille.y)+Emap.taille.x)!='#'){
		voiture->pos.x=x;
		voiture->pos.y=y;
	}
	else{
		
	}
};
//PRE:on envoie le pointeur de l'ennemi moto dont le traitement est en cours dans action_ennemi
//POST:fonction ou l'on retrouve les actions automatique d'un ennemi type moto appelé par action_ennemi
void action_moto(Ennemi* moto){
	int x=moto->pos.x;
	int y=moto->pos.y;
	if((moto->pos.x-moto->pos.y)%2==0){
		if(moto->pos.x-j.pos.x<0){
			x++;
		}
		else if(moto->pos.x-j.pos.x>0){
			x--;
		}
	}
	else{
		if(moto->pos.y-j.pos.y<0){
			y++;
		}
		else if(moto->pos.y-j.pos.y>0){
			y--;
		}
	}
	Map Emap;
	replacement_ennemi(x,y,&Emap);
	if(*(*(Emap.c+Emap.taille.y)+Emap.taille.x)!='#'){
		moto->pos.x=x;
		moto->pos.y=y;
	}
};
//PRE: prend en argument la liste
//post:affiche cette liste dans la console
void afficher_liste(ListeEnnemi* liste){
	int i=0;
	printf("---Liste ennemi %d: ---\n",liste->nombre);
	ElementEnnemi* actuel=liste->premier;
	while(i<liste->nombre){
	printf(" nom ennemi :%s vie : %d pos : (x=%d;y=%d) type :%d\n",actuel->e.nom,actuel->e.vie,actuel->e.pos.x,actuel->e.pos.y,actuel->e.type);
	actuel=actuel->suivant;
	i++;
	}
	printf("-----------fin liste----------\n");
};			
