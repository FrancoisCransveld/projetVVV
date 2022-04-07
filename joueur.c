#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
//#include "jeu.h"
//#include "LoadMaps.h"
#include "interface.h"
#include "joueur.h"

void moveLeft(Joueur j){		//la fonction va vérifier si on peut se déplacer vers la gauche et le faire le cas échéant

	int x = 0, y = 0;

	x = j.pos.x-1;
	y = j.pos.y;
	
	char** MapJoueur;
	int mjX, mjY; //variable pour le placement du joueur dans la carte sur lequel il se trouve (next, nextLR ou current).
	//recherche position par rapport à current 
	if((x>=0||x<currentMap.taille.y){	   //position horizontale entre 0 et taille currentMap
		if((y<0||y>=currentMap.taille.y){  //position verticale en dehors 0 et taille currentMap
			MapJoueur=nextMap.c;       //j est juste au dessus ou en dessous de currentMap, donc dans nextMap
			mjX=x;				//x ne change pas
			if(y<0){			//si au dessus, alors la position dans nextMap est à la fin, donc à la taille de next+y (y est négatif)
				mjY=y+nextMap.taille.y;
			}		
			else{			//si en dessous, alors la position dans nextMap est au début, donc à y-la hauteur de current	
				mjY=y-currentMap.taille.y;
			}
		}
		else{				//j est entre les limites de currentMap
			MapJoueur=currentMap.c;
			mjX=x;
			mjY=y;
		}
	}
	else{					    //position horizontale en dehors de 0 et taille currentMap
		if((y<0||y>=currentMap.taille.y)){  //position verticale en dehors 0 et taille currentMap
							//j est à la fois en dehors horizontalement et verticalement des limites de currentMap
			if(niveauA.next==niveau.current+1||niveauA.next==niveau.current-1){// si la première map après current est nextMap
				MapJoueur=nextLRMap.c;
				if(x<0){
					mjX=x+nextLRMap.taille.x;//si a gauche, alors la position dans nextLRMap est à la fin, donc à la taille de nextLR+x (x est négatif)
				}
				else{
					mjX=x-currentMap.taille.x;//si a droite, alors la position dans nextMap est au début, donc à x-la largeur de current
				}
				if(y<0){			//si au dessus, alors la position dans nextMap est à la fin, donc à la taille de next+y (y est négatif)
					mjY=y+nextLRMap.taille.y;
				}		
				else{			//si en dessous, alors la position dans nextMap est au début, donc à y-la hauteur de current	
					mjY=y-currentMap.taille.y;
				}
			}
			else{
				MapJoueur=nextMap.c;
				if(x<0){
					mjX=x+nextMap.taille.x;//si a gauche, alors la position dans nextLRMap est à la fin, donc à la taille de nextLR+x (x est négatif)
				}
				else{
					mjX=x-currentMap.taille.x;//si a droite, alors la position dans nextMap est au début, donc à x-la largeur de current
				}
				if(y<0){			//si au dessus, alors la position dans nextMap est à la fin, donc à la taille de next+y (y est négatif)
					mjY=y+nextMap.taille.y;
				}		
				else{			//si en dessous, alors la position dans nextMap est au début, donc à y-la hauteur de current	
					mjY=y-currentMap.taille.y;
				}
			}
		}
		else{					//j est juste à gauche ou droite de currentMap, donc dans nextLRMap
			MapJoueur=nextLRMap.c;
			mjY=y;				//y ne change pas
			if(x<0){
				mjX=x+nextLRMap.taille.x;//si a gauche, alors la position dans nextLRMap est à la fin, donc à la taille de nextLR+x (x est négatif)
			}
			else{
				mjX=x-currentMap.taille.x;//si a droite, alors la position dans nextMap est au début, donc à x-la largeur de current
			}
		}
	}
	if (*(*(MapJoueur + MJY) + MJX)!='#')
	{
		j.dir=3;
		j.pos.x = x;
	}

}
void moveRight(Joueur j)		//la fonction va vérifier si on peut se déplacer vers la droite et le faire le cas échéant
{
	int x = 0, y = 0;


	x = j.pos.x+1;
	y = j.pos.y;
	
	if (*(*(currentMap.c + y) + (x+1))!='#')
	{
		j.dir=1;
		j.pos.x = x;
	}

}
void moveUp(Joueur j)
{
 int  x = 0, y = 0;
      
	x = j.pos.x;
	y = j.pos.y-1;

	if (*(*(currentMap.c + y) + x)!='#'){//attention a changer
		j.dir=0;
		j.pos.y = y;
		if(y>=20||(*(*(currentMap.c + 0)+20)=='#')){
			//j->pos.y = y;
			printf("\npos y: %d\n",y+1);
		}
		else{
			printf("\npos y: %d\n",y+1);
			//loadMap();
		}
	}     
	
}
void moveDown(Joueur j)
{
 int  x = 0, y = 0;
 
   x = j.pos.x;
   y = j.pos.y+1;
   
   if (*(*(currentMap.c + (y+1)) + x) !='#'){
		j.dir=2;
		j.pos.y = y;
		if(y<currentMap.taille.y-22){
			//j->pos.y = y;
			printf("\npos y: %d\n",y+1);
		}
		else{
			printf("\npos y: %d\n",y+1);
			//loadMap();
		}
      }
}
//void movePlayer(
