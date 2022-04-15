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
#include "tirs.h"
#include "LoadMaps.h"
#include "interface.h"
//#include
//PRE:aucun argument d'entree
//POST:crée la liste chainée et initialise le premier element de cette liste chainee avec la vie de l'ennemi à 1, la position à(0;0) le type à 0 et le nom à Bot1
ListeTirs* creer_liste_tirs(void){
  
	ListeTirs* listeT=malloc(sizeof(ListeTirs));
	
	ElementTirs* tirs=malloc(sizeof(ElementTirs));
	
	if(listeT==NULL||tirs==NULL){
		exit(EXIT_FAILURE);
	}
		
	tirs->t.dir=4;
	tirs->t.pos.x=0;
	tirs->t.pos.y=0;
	tirs->t.t=rien;
	tirs->suivant=NULL;
  	tirs->precedent=NULL;
  	tirs->t.distanceMax=0;
	listeT->premier=tirs;
  	listeT->dernier=tirs;
	listeT->nombre=0;
	
	return (listeT);
};

//PRE:prend en entrée la liste chainée à laquel on donne un nouvelle élément, le nom de cette élément, sa vie, sa coordonnee, son type
//POST:ajoute un tirs en fin de la liste chainée, qui aura toute les caractéristiques donnée en entrée
void tirs(ListeTirs* listeT, Coordonnee pos, TypeTirs t, Direction dir){
	
	ElementTirs* actuel=listeT->dernier;
	if(listeT->nombre>0){
		ElementTirs* nouveau=malloc(sizeof(ElementTirs));
		nouveau->t.pos=pos;
		nouveau->t.t=t;
		switch (nouveau->t.t){
			case 0:
				nouveau->t.distanceMax=20;
				break;
			case 1:
				nouveau->t.distanceMax=15;
				break;
			case 2:
				nouveau->t.distanceMax=10;
				break;
			case 3:
				nouveau->t.distanceMax=0;
				break;
		}
		nouveau->t.dir=dir;
		nouveau->suivant=NULL;
		actuel->suivant=nouveau;
		nouveau->precedent=actuel;
		listeT->nombre++;
		listeT->dernier=nouveau;
	}
	else if(listeT->nombre==0){
		modifier_tirs(listeT,0, pos, t, dir);
	}
	else{
		printf("ce n'est pas un tirs\n");
	}
	
};
//PRE:prend en entrée la liste chainée à laquel on donne un nouvelle élément, le nom de cette élément, sa vie, sa coordonnee, son type
//POST:on modifie un élément de la liste donnée, cette élement se retrouve avec numero il correspon à la place dans la liste chainée commençant par 0 jusque nombre-1
void modifier_tirs(ListeTirs* listeT, int numero, Coordonnee pos, TypeTirs t,Direction dir){
	int i=0;
	int decalage=numero;
	bool SensCroissant=true;
	ElementTirs* actuel=NULL;
	if(numero<listeT->nombre){
		if(listeT->nombre/2<numero){
			actuel=listeT->premier;
		}
		else{
			actuel=listeT->dernier;
			SensCroissant=false;
			decalage=listeT->nombre-numero-1;
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
		actuel->t.t=t;
		actuel->t.pos=pos;
		actuel->t.dir=dir;
		switch (actuel->t.t){
			case 0:
				actuel->t.distanceMax=20;
				break;
			case 1:
				actuel->t.distanceMax=15;
				break;
			case 2:
				actuel->t.distanceMax=10;
				break;
			case 3:
				actuel->t.distanceMax=0;
				break;
		}
	}
	if(listeT->nombre==0){
		listeT->nombre=1;
	}
};
//PRE:On prend la liste dans laquel on veut supprimer et le numéro de l'élément (int numero) on commence par 0
//POST:Supprime l'element numero et refait les liens entre les suivants et précédent
void supprimer_tirs_numero(ListeTirs* listeT, int numero){
	
	if(listeT==NULL){
		exit(EXIT_FAILURE);
	}
	int i=0;
	int decalage=numero;
	bool SensCroissant=true;
	ElementTirs* actuel=NULL;
	ElementTirs* precedent=NULL;
	ElementTirs* suivant=NULL;
	if(listeT->premier!=NULL){
		if(numero<listeT->nombre){
			if(listeT->nombre/2<numero){
				actuel=listeT->premier;
			}
			else{
				actuel=listeT->dernier;
				SensCroissant=false;
				decalage=listeT->nombre-numero-1;
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
			printf("suprimer tirs %d adresse %hx nombre%d\n",numero,actuel,listeT->nombre);
			if(precedent==NULL&&suivant==NULL){
				actuel->t.dir=4;
				actuel->t.pos.x=0;
				actuel->t.pos.y=0;
				actuel->t.t=rien;
			}
			else {
				if(precedent==NULL){
					suivant->precedent=NULL;
					listeT->premier=actuel->suivant;
				}
				else if(suivant==NULL){
					precedent->suivant=NULL;
					listeT->dernier=actuel->precedent;
				}
				else{
					precedent->suivant=actuel->suivant;
					suivant->precedent=actuel->precedent;
				}
				//free(actuel);
				listeT->nombre--;
			}
		}
	}
};
TypeTirs degat_tirs(ListeTirs* listeT, int numero){
	int i=0;
	int decalage=numero;
	bool SensCroissant=true;
	ElementTirs* actuel=NULL;
	if(numero<listeT->nombre){
		if(listeT->nombre/2<numero){
			actuel=listeT->premier;
		}
		else{
			actuel=listeT->dernier;
			SensCroissant=false;
			decalage=listeT->nombre-numero-1;
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
	return (actuel->t.t);
};
//PRE:En argument la liste à modifier, la variation de Coordonnee pos
//POST:On déplace tous les tirs de la variation surtout utiliser pour switch map (deplacement vertical)
void modifier_pos_tirs(ListeTirs* listeT, Coordonnee variation){
	int i=0;
	
	ElementTirs* actuel=listeT->premier;
	int nombreMax=listeT->nombre;
	for(i=0;i<nombreMax;i++){
		//actuel->t.pos.x+=variation.x;
		actuel->t.pos.y+=variation.y;
		actuel=actuel->suivant;
	}
	supprimer_tirs_hors_portee(listeT);
	//afficher_liste(liste);
};

//suprime les tirs hors de portées plus pertinent pour le jeu en cours
void supprimer_tirs_hors_portee(ListeTirs* listeT){
	ElementTirs* actuel=listeT->premier;
	int nombreMax=listeT->nombre;
	for(int i=0;i<nombreMax;i++){
		if(actuel->t.pos.y>camera.y+(CAM_RANGE*4)||actuel->t.pos.y<camera.y-(CAM_RANGE*4)){
			
			supprimer_tirs_numero(listeT, i);
		}
		else{
		actuel=actuel->suivant;
		}
	}
	//	afficher_liste(liste);
};
//
//POST: fonction qui va appeler les ennemis pour effectuer leurs actions
void deplacement_tirs(ListeTirs* listeT){
	ElementTirs* actuel=listeT->premier;
	for(int i=0;i<listeT->nombre;i++){
		if(actuel->t.distanceMax>0){
			switch(actuel->t.dir){
				case Up:
					actuel->t.pos.y--;
					break;
				case Right:
					actuel->t.pos.x++;
					break;
				case Down:
					actuel->t.pos.y++;
					break;
				case Left:
					actuel->t.pos.x--;
					break;
				case fin:
					break;
			}
			actuel->t.distanceMax--;
			actuel=actuel->suivant;
			
		}
		else{
			supprimer_tirs_numero(listeT, i);
		}
		
	}
};
//PRE:
//POST:Renvoie la coordonnee du tirs numero (les tirs sont numeroté de 0 à listeT.nombre-1)
Coordonnee pos_tirs(ListeTirs* listeT,int numero){
	int i=0;
	int decalage=numero;
	bool SensCroissant=true;
	ElementTirs* actuel=NULL;
	if(numero<listeT->nombre){
		if(listeT->nombre/2<numero){
			actuel=listeT->premier;
		}
		else{
			actuel=listeT->dernier;
			SensCroissant=false;
			decalage=listeT->nombre-numero-1;
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
	return(actuel->t.pos);
}
//PRE: prend en argument la liste
//post:affiche cette liste dans la console
void afficher_liste_tirs(ListeTirs* listeT){
	int i=0;
	printf("---Liste ennemi : ---\n");
	ElementTirs* actuel=listeT->premier;
	while(i<listeT->nombre){
	printf(" tirs type : %d pos : (x=%d;y=%d) dir:%d portee: %d\n",actuel->t.t,actuel->t.pos.x,actuel->t.pos.y,actuel->t.dir,actuel->t.distanceMax);
	actuel=actuel->suivant;
	i++;
	}
};			
