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
void replacement_joueur(int x, int y, Map* map){
	
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
	//printf("j pos x: %d j pos y: %d et mjX: %d mjY: %d\n",j.pos.x,j.pos.y, mjX,mjY);
	//printf("niveau.current %d %dniveau.Next %d %dniveau.LR %d %d\n",niveauA.current,niveauA.Nmap[niveauA.current].s,niveauA.next,niveauA.Nmap[niveauA.next].s,niveauA.previous,niveauA.Nmap[niveauA.previous].s);
	return ;

};
void moveLeft(){		//la fonction va vérifier si on peut se déplacer vers la gauche et le faire le cas échéant

	int x = 0, y = 0;

	x = j.pos.x-1;
	y = j.pos.y;
	Map MapJ;
	
	 //variable pour le placement du joueur dans la carte sur lequel il se trouve (next, nextLR ou current).
	replacement_joueur(x,y,&MapJ);
	//printf("moveLeft\n");
	j.dir=3;
	//recherche position par rapport à current 
	/*  */
	if (*(*(MapJ.c + MapJ.taille.y) + MapJ.taille.x)!='#')
	{
		
		j.pos.x = x;
		if(autorisation_scroll( x, y,MapJ,j.dir)){
			camera.x--;//position initiale de la camera affichant une map complète au centre. 
		}
		//mapLoader(MapJ,j.dir);
		switchMap();
		supprimer_ennemi_hors_portee(liste);
		activer_ennemi_a_portee(liste);
	}
	//printf("moveLeft\n");
	//printf("j pos x: %d j pos y: %d",j.pos.x,j.pos.y);

};
void moveRight()		//la fonction va vérifier si on peut se déplacer vers la droite et le faire le cas échéant
{
	int x = 0, y = 0;


	x = j.pos.x+1;
	y = j.pos.y;
	
	Map MapJ;
	
	 //variable pour le placement du joueur dans la carte sur lequel il se trouve (next, nextLR ou current).
	replacement_joueur(x,y,&MapJ);
	j.dir=1;
	//printf("moveRight\n");
	if (*(*(MapJ.c + MapJ.taille.y) + (MapJ.taille.x))!='#')
	{

		j.pos.x = x;
		if(autorisation_scroll( x, y,MapJ,j.dir)){
			camera.x++;
		}
		//mapLoader(MapJ,j.dir);
		switchMap();
		supprimer_ennemi_hors_portee(liste);
		activer_ennemi_a_portee(liste);
	}
	//printf("j pos x: %d j pos y: %d",j.pos.x,j.pos.y);

};
void moveUp()
{
 int  x = 0, y = 0;
      
	x = j.pos.x;
	y = j.pos.y-1;
	
	Map MapJ;
	j.dir=0;
	 //variable pour le placement du joueur dans la carte sur lequel il se trouve (next, nextLR ou current).
	replacement_joueur(x,y,&MapJ);
	//printf("moveUp\n");
	if (*(*(MapJ.c + MapJ.taille.y) + MapJ.taille.x)!='#'&&*(*(MapJ.c + MapJ.taille.y) + MapJ.taille.x)!='!'){//attention a changer
		
		j.pos.y = y;
		if(autorisation_scroll( x, y,MapJ,j.dir)){
			camera.y--;
		}
		//mapLoader(MapJ,j.dir);
		switchMap();
		supprimer_ennemi_hors_portee(liste);
		activer_ennemi_a_portee(liste);
		
	}
	//printf("j pos x: %d j pos y: %d",j.pos.x,j.pos.y);     
	
};
void moveDown()
{
 int  x = 0, y = 0;
 
   x = j.pos.x;
   y = j.pos.y+1;
   
   Map MapJ;
	//printf("moveDown\n");
	 //variable pour le placement du joueur dans la carte sur lequel il se trouve (next, nextLR ou current).
	replacement_joueur(x,y,&MapJ);	//dans MapJ la structure taille correspond au futur coordonée du joueur dans le plateau logique qui lui correspond
	j.dir=2;
   if (*(*(MapJ.c + (MapJ.taille.y)) + MapJ.taille.x)!='#'&&*(*(MapJ.c + (MapJ.taille.y)) + MapJ.taille.x)!='!'){   
		
		j.pos.y = y;
		if(autorisation_scroll( x, y,MapJ,j.dir)){
			camera.y++;
		}
		
		//mapLoader(MapJ,j.dir);
		switchMap();
		supprimer_ennemi_hors_portee(liste);
		activer_ennemi_a_portee( liste);
		
      }
      //printf("j pos x: %d j pos y: %d",j.pos.x,j.pos.y);
};
//PRE: les argument sont la postion du joueur après le déplacement et la carte sur laquel il évolue.
//POST: fonction qui va testé si oui ou non la caméra doit scroller
bool autorisation_scroll(int x,int y,Map MapJ,Direction jDir){
	bool SCROLL_LOCK=true;//booleen vérifiant si on a un verrou de scrolling dans la direction que prend le joueur 
	bool SCROLL_J=false;	//booleen vérifiant que la position du joueur par rapport à la caméra selon sa direction est suffisament éloignée
	int xLock=32;	//position x du verrou du srcolling pour la direction
	int yLock=32;	//position y du verrou du srcolling pour la direction
	//printf("Srcrolllock\n");
	switch(jDir){
		case 0:
			yLock=0;
			if((*(*(MapJ.c + yLock) + xLock)=='!')&&(MapJ.taille.y<12)){
				SCROLL_LOCK=false;
			}
			if((camera.y-y)>4){
				SCROLL_J=true;
			}
			break;
		case 1:
			xLock=currentMap.taille.x-1;
			if((*(*(MapJ.c + yLock) + xLock)=='#')&&(MapJ.taille.x>51)){
				SCROLL_LOCK=false;
			}
			if((x-camera.x)>3){
				SCROLL_J=true;
			}
			break;
		case 2:
			yLock=currentMap.taille.y-1;
			if((*(*(MapJ.c + yLock) + xLock)=='!')&&(MapJ.taille.y>51)){
				SCROLL_LOCK=false;
			}
			if((y-camera.y)>3){
				SCROLL_J=true;
			}
			break;
		case 3:
			xLock=0;
			if((*(*(MapJ.c + yLock) + xLock)=='#')&&(MapJ.taille.x<12)){
				SCROLL_LOCK=false;
			}
			if((camera.x-x)>4){
				SCROLL_J=true;
			}
			break;
		case 4:
			SCROLL_J=false;
			break;
	}
	return(SCROLL_J&&SCROLL_LOCK);
};

bool collisionEnnemiJoueur(){
	bool collision=false;
	for(int i=0;i<liste->nombre;i++){
				Coordonnee EnnemiActuel=pos_Ennemi(liste,i);
				if(EnnemiActuel.x==j.pos.x){
					if((EnnemiActuel.y==j.pos.y)||((EnnemiActuel.y-1==j.pos.y)&&j.dir==2)||((EnnemiActuel.y+1==j.pos.y)&&j.dir==0)){
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
						collision=true;
						return collision;
					}
				}
				if(EnnemiActuel.y==j.pos.y){
					if((EnnemiActuel.x==j.pos.x)||((EnnemiActuel.x+1==j.pos.y)&&j.dir==3)||((EnnemiActuel.x-1==j.pos.y)&&j.dir==1)){
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
						collision=true;
						return collision;
					}
				}
	
	}
	return collision;
}

