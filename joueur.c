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
	
	if (*(*(currentMap.c + y) + x)!='#')
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
