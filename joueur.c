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
	/*
	if(x>=0&&x<currentMap.taille.x){	   //position horizontale entre 0 et taille currentMap
		if(y<0||y>=currentMap.taille.y){  //position verticale en dehors 0 et taille currentMap
			map->c=nextMap.c;       //j est juste au dessus ou en dessous de currentMap, donc dans nextMap
			mjX=x;				//x ne change pas
			if(y<0){			//si au dessus, alors la position dans nextMap est à la fin, donc à la taille de next+y (y est négatif)
				
				mjY=y+nextMap.taille.y;
			}		
			else{			//si en dessous, alors la position dans nextMap est au début, donc à y-la hauteur de current	
				
				mjY=y-currentMap.taille.y;
			}
		}
		else{				//j est entre les limites de currentMap
			map->c=currentMap.c;
			mjX=x;
			mjY=y;
			//printf("vous etes ici 3");
		}
	}
	else{					    //position horizontale en dehors de 0 et taille currentMap
		if((y<0||y>=currentMap.taille.y)){  //position verticale en dehors 0 et taille currentMap
							//j est à la fois en dehors horizontalement et verticalement des limites de currentMap
			if(niveauA.next==niveauA.current+1||niveauA.next==niveauA.current-1){// si la première map après current est nextMap
				map->c=nextLRMap.c;
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
				map->c=nextMap.c;
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
			map->c=nextLRMap.c;
			mjY=y;				//y ne change pas
			if(x<0){
				
				mjX=x+nextLRMap.taille.x;//si a gauche, alors la position dans nextLRMap est à la fin, donc à la taille de nextLR+x (x est négatif)
			}
			else{
				
				mjX=x-currentMap.taille.x;//si a droite, alors la position dans nextMap est au début, donc à x-la largeur de current
			}
		}
	}*/
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

	//recherche position par rapport à current 
	/*  */
	if (*(*(MapJ.c + MapJ.taille.y) + MapJ.taille.x)!='#')
	{
		j.dir=3;
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
	//printf("moveRight\n");
	if (*(*(MapJ.c + MapJ.taille.y) + MapJ.taille.x)!='#')
	{
		j.dir=1;
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
	
	 //variable pour le placement du joueur dans la carte sur lequel il se trouve (next, nextLR ou current).
	replacement_joueur(x,y,&MapJ);
	//printf("moveUp\n");
	if (*(*(MapJ.c + MapJ.taille.y) + MapJ.taille.x)!='#'){//attention a changer
		j.dir=0;
		j.pos.y = y;
		if(autorisation_scroll( x, y,MapJ,j.dir)){
			camera.y--;
		}
		//mapLoader(MapJ,j.dir);
		switchMap();
		supprimer_ennemi_hors_portee(liste);
		activer_ennemi_a_portee(liste);
		/*if(y>=20||(*(*(currentMap.c + 0)+20)=='#')){
			//j->pos.y = y;
			printf("\npos y: %d\n",y+1);
		}
		else{
			printf("\npos y: %d\n",y+1);
			//loadMap();
		}*/
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
   if (*(*(MapJ.c + MapJ.taille.y) + MapJ.taille.x)!='#'){   
		j.dir=2;
		j.pos.y = y;
		if(autorisation_scroll( x, y,MapJ,j.dir)){
			camera.y++;
		}
		
		//mapLoader(MapJ,j.dir);
		switchMap();
		supprimer_ennemi_hors_portee(liste);
		activer_ennemi_a_portee( liste);
		/*if(y<currentMap.taille.y-22){
			//j->pos.y = y;
			printf("\npos y: %d\n",y+1);
		}
		else{
			printf("\npos y: %d\n",y+1);
			//loadMap();
		}*/
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
			if((*(*(MapJ.c + yLock) + xLock)=='#')&&(MapJ.taille.y<9)){
				SCROLL_LOCK=false;
			}
			if((camera.y-y)>7){
				SCROLL_J=true;
			}
			break;
		case 1:
			xLock=currentMap.taille.x-1;
			if((*(*(MapJ.c + yLock) + xLock)=='#')&&(MapJ.taille.x>54)){
				SCROLL_LOCK=false;
			}
			if((x-camera.x)>6){
				SCROLL_J=true;
			}
			break;
		case 2:
			yLock=currentMap.taille.y-1;
			if((*(*(MapJ.c + yLock) + xLock)=='#')&&(MapJ.taille.y>54)){
				SCROLL_LOCK=false;
			}
			if((y-camera.y)>6){
				SCROLL_J=true;
			}
			break;
		case 3:
			xLock=0;
			if((*(*(MapJ.c + yLock) + xLock)=='#')&&(MapJ.taille.x<9)){
				SCROLL_LOCK=false;
			}
			if((camera.x-x)>7){
				SCROLL_J=true;
			}
			break;
		case 4:
			SCROLL_J=false;
			break;
	}
	return(SCROLL_J&&SCROLL_LOCK);
};
/*
void mapLoader(Map MapJ,Direction jDir){
	
	printf("mapLoader\n");
	int nextLoad=-1;
	switch(jDir){
		case 0:
			if(MapJ.taille.y<26){
			printf("up: jdirP%d next dir%d current%d previous dir%d next%d nextLR %d \n",jDir,niveauA.Nmap[niveauA.current].Next,niveauA.current,niveauA.Nmap[niveauA.current].previous,niveauA.next,niveauA.nextLR);
				int i=0;
				while(niveauA.Nmap[niveauA.current+i].Next!=5&&i<2){
					if(jDir==niveauA.Nmap[niveauA.current+i].Next){
						nextLoad=niveauA.current+1+i;
						break;
					}
					i++;
				}
				i=0;
				while(niveauA.Nmap[niveauA.current-i].previous!=5&&i<2){
					if(jDir==niveauA.Nmap[niveauA.current-i].previous){
						nextLoad=niveauA.current-1-i;
						break;
					}
					i++;
				}	
				}
			break;
		case 1:
			if(MapJ.taille.x>38){
			printf("right: jdirP%d next dir%d current%d previous dir%d next%d \n",jDir,niveauA.Nmap[niveauA.current].Next,niveauA.current,niveauA.Nmap[niveauA.current].previous,niveauA.next);
				int i=0;
				while(niveauA.Nmap[niveauA.current+i].Next!=5&&i<2){
					if(jDir==niveauA.Nmap[niveauA.current+i].Next){
						nextLoad=niveauA.current+1+i;
						break;
					}
					i++;
				}
				i=0;
				while(niveauA.Nmap[niveauA.current-i].previous!=5&&i<2){
					if(jDir==niveauA.Nmap[niveauA.current-i].previous){
						nextLoad=niveauA.current-1-i;
						break;
					}
					i++;
				}	
			}
			
			break;
		case 2:
			if(MapJ.taille.y>38){
				printf("down: jdirP%d next dir%d current%d previous dir%d next%d \n",jDir,niveauA.Nmap[niveauA.current].Next,niveauA.current,niveauA.Nmap[niveauA.current].previous,niveauA.next);
				int i=0;
				while(niveauA.Nmap[niveauA.current+i].Next!=5&&i<2){
					if(jDir==niveauA.Nmap[niveauA.current+i].Next){
						nextLoad=niveauA.current+1+i;
						break;
					}
					i++;
				}
				i=0;
				while(niveauA.Nmap[niveauA.current-i].previous!=5&&i<2){
					if(jDir==niveauA.Nmap[niveauA.current-i].previous){
						nextLoad=niveauA.current-1-i;
						break;
					}
					i++;
				}	
			}
			break;
		case 3:
			if(MapJ.taille.x<26){
			printf("left: jdirP%d next dir%d current%d previous dir%d next%d \n",jDir,niveauA.Nmap[niveauA.current].Next,niveauA.current,niveauA.Nmap[niveauA.current].previous,niveauA.next);
				int i=0;
				while(niveauA.Nmap[niveauA.current+i].Next!=5&&i<2){
					if(jDir==niveauA.Nmap[niveauA.current+i].Next){
						nextLoad=niveauA.current+1+i;
						break;
					}
					i++;
				}
				i=0;
				while(niveauA.Nmap[niveauA.current-i].previous!=5&&i<2){
					if(jDir==niveauA.Nmap[niveauA.current-i].previous){
						nextLoad=niveauA.current-1-i;
						break;
					}
					i++;
				}	
			}
			break;
		case 4:
			break;
	}
	if(nextLoad>=0){
		if(!niveauA.Nmap[nextLoad].loadStatus){
			printf("nextLoad pre %d\n",nextLoad);
			loadNext(nextLoad);
			printf("nextLoad %d\n",nextLoad);
		}
	}
	else{
		printf("nothing\n");
	}
}
*/



















//void movePlayer(
