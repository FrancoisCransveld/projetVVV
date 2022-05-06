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
#include "joueur.h"
#include "ennemi.h"
#include "tirs.h"

Coordonnee HitBoxEnnemi(int ennemi,Coordonnee* EnnemiActuel){
	
	printf("PreCoordonneeEnnemi %d\n", ennemi);
	*EnnemiActuel=pos_Ennemi(liste,ennemi);
	Direction ennemiDir;
	TypeEnnemi ennemiType;
	if(liste->premier!=NULL){
		int i=0;
		int decalage=ennemi;
		bool SensCroissant=true;
		ElementEnnemi* actuel=NULL;
		if(ennemi<liste->nombre){
			if(ennemi<liste->nombre/2){
				actuel=liste->premier;
			}
			else{
				actuel=liste->dernier;
				SensCroissant=false;
				decalage=liste->nombre-ennemi-1;
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
		ennemiType=actuel->e.type;
		ennemiDir=actuel->e.dir;
	}
	int longueur;
	int largeur;
	Coordonnee Cadre;
	switch (ennemiType){
		case voiture:
				longueur=5;
				largeur=3;
				break;
		case moto:
				longueur=3;
				largeur=1;
				break;
		case camion:
				longueur=9;
				largeur=4;
				break;
		case SUV:
				longueur=6;
				largeur=4;
				break;
		case vide:
				longueur=0;
				largeur=0;
				break;
		default:
				longueur=0;
				largeur=0;
				break;
	}
	switch (ennemiDir){
		case Up:
			Cadre.x=largeur;
			Cadre.y=longueur;
			break;
		case Right:
			Cadre.y=largeur;
			Cadre.x=longueur;
			break;
		case Down:
			Cadre.x=largeur;
			Cadre.y=longueur;
			break;
		case Left:
			Cadre.y=largeur;
			Cadre.x=longueur;
			break;
		case fin:
			Cadre.x=largeur;
			Cadre.y=longueur;
			break;
		default:
			Cadre.x=largeur;
			Cadre.y=longueur;
			break;
	}
	Coordonnee LimiteEnnemi;
	LimiteEnnemi.x=((EnnemiActuel->x*2)+Cadre.x);
	LimiteEnnemi.y=((EnnemiActuel->y*2)+Cadre.y);
	return (LimiteEnnemi);
}

Coordonnee hit_box_joueur(Direction dir,Coordonnee* hitBoxHG){
	*hitBoxHG=j.pos;
	hitBoxHG->x*=2;
	hitBoxHG->y*=2;
	Coordonnee hitBoxBD=j.pos;
	hitBoxBD.x*=2;
	hitBoxBD.y*=2;
	switch(dir){
		case Up:
			hitBoxBD.x+=1;
			hitBoxBD.y+=3;
			break;
		case Right:
			hitBoxBD.x+=1;
			hitBoxBD.y+=1;
			hitBoxHG->x=hitBoxBD.x-3;
			break;
		case Down:
			hitBoxBD.y+=1;
			hitBoxBD.x+=1;
			hitBoxHG->y=hitBoxBD.y-3;
			break;
		case Left:
			hitBoxBD.x+=3;
			hitBoxBD.y+=1;
			break;
		case fin:
			hitBoxBD.x=300;
			hitBoxBD.y=300;
			break;
		default:
			hitBoxBD.x=300;
			hitBoxBD.y=300;
			break;
	}

	return hitBoxBD;
	
}
bool collision_joueur_ennemi(int ennemi){
	
	bool COLLISION=false;
	Coordonnee EnnemiActuel;
	Coordonnee LimiteEnnemi=HitBoxEnnemi(ennemi,&EnnemiActuel);
	Coordonnee HitBoxJoueurHG;
	Coordonnee HitBoxJoueurBD=hit_box_joueur(j.dir,&HitBoxJoueurHG);
	printf("coordonnee ennemi coin supérieur: (%d;%d) coin inférieur: (%d,%d),j:(%d,%d)\n",EnnemiActuel.x,EnnemiActuel.y,LimiteEnnemi.x,LimiteEnnemi.y,j.pos.x,j.pos.y);
	
	if((HitBoxJoueurBD.y>=EnnemiActuel.y*2)&&(HitBoxJoueurHG.y)<=(LimiteEnnemi.y)){ 
		
		if((HitBoxJoueurHG.x<=(LimiteEnnemi.x))&&(HitBoxJoueurBD.x>=(EnnemiActuel.x*2))){
		
			COLLISION=true;
		}
	}
	
	return COLLISION;
}

bool collisionEnnemiJoueur(){
	bool collis=false;
	for(int i=0;i<liste->nombre;i++){
				
		if(collision_joueur_ennemi(i)){
			j.hp--;
				switch(j.dir){
					case 0:
						moveDown();
						moveDown();
						break;
					case 1:
						moveLeft();
						moveLeft();
						break;
					case 2:
						moveUp();
						moveUp();
						break;
					case 3:
						moveRight();
						moveRight();
						break;
					case 4:
						moveDown();
						moveDown();
						break;
				}
			collis=true;
			return collis;
		}
	}
	return collis;
}



bool collision_tirs_ennemi(int ennemi,int tirs){
	
	bool COLLISION=false;
	printf("PreCoordonneeEnnemi %d\n", ennemi);
	Coordonnee EnnemiActuel;
	printf("PreCoordonneeTirs %d\n", tirs);
	Coordonnee tirsActuel=pos_tirs(j.tirs,tirs);
	
	Coordonnee LimiteEnnemi=HitBoxEnnemi(ennemi,&EnnemiActuel);
	
	printf("coordonnee ennemi coin supérieur: (%d;%d) coin inférieur: (%d,%d), tirs  (%d,%d)j:(%d,%d)\n",EnnemiActuel.x,EnnemiActuel.y,LimiteEnnemi.x,LimiteEnnemi.y,tirsActuel.x,tirsActuel.y,j.pos.x,j.pos.y);
	if(((EnnemiActuel.y*2)<=tirsActuel.y)&&((LimiteEnnemi.y)>=tirsActuel.y)){ 
		printf("condition y ok\n");
		if(((EnnemiActuel.x*2)<=tirsActuel.x)&&((LimiteEnnemi.x)>=tirsActuel.x)){
			printf("condition x ok\n");
			COLLISION=true;
		}
	}
	
	return COLLISION;
}
