#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include "interface.h"
#include "joueur.h"
#include "collision.h"
void replacement_joueur(int x, int y, Map* map){
	
	
	int mjX, mjY;
 	//variable pour le placement du joueur dans la carte sur lequel il se trouve (next, nextLR ou current).
	//recherche position par rapport à current 
	if(y<0||y>=currentMap.taille.y){  //position verticale en dehors 0 et taille currentMap
			
			mjX=x;				//x ne change pas
			if(y<0){			//si au dessus, alors la position dans nextMap est à la fin, donc à la taille de next+y (y est négatif)
				map->c=nextMap.c;       //j est juste au dessus de currentMap, donc dans nextMap
				mjY=y+nextMap.taille.y;	//on adapte la position de j désirée suite à la demande de déplacement contenue dans y, et on l'enregistre dans la variable mjY
			}		
			else{			//si en dessous, alors la position dans previousMap est au début, donc à y-la hauteur de current	
				map->c=previousMap.c;       //j est juste au dessus de currentMap, donc dans nextMap
				mjY=y-currentMap.taille.y;	//on adapte la position de j désirée suite à la demande de déplacement contenue dans y, et on l'enregistre dans la variable mjY
			}
	}
	else{
		map->c=currentMap.c;	//on se trouve sur currentMap, on fera donc les tests avec le tableau de pointeur de char contenu dans current pour les collisions avec le décors, map donné en argument prend dans sa variable c le tableau contenu dans la variable globale currentMap.c
		mjX=x;	//La position de x et y, position désirée de j après déplacement sont correctes donc les variables mjX et mjY prennent ces valeurs 
		mjY=y;
	}
	map->taille.x=mjX;	//Coordonnée de j dans la carte logique/le plateau qui le concerne contenu dans map->taille
	map->taille.y=mjY;	
	return ;

};
void moveLeft(){		//la fonction va vérifier si on peut se déplacer vers la gauche et le faire le cas échéant

	int x = 0, y = 0;	//variable qui vont contenir la position désirée en x pour x et en y pour y  

	x = j.pos.x-1;		//la variable x est donc initialisé à la position j en x (j.pos.x) décalé à gauche (donc -1, une case à gauche pour openGL)
	y = j.pos.y;		//la variable y est donc initialisé à la position j en y (j.pos.y), comme c'est le décalage à gauche on a pas de variation pour la position y de j
	Map MapJ;		//structure Map qui contiendra la carte sur laquel j se trouve (parmis currentMap, nextMap et previousMap) et avec laquel on effectuera les test de collision avec le décors
	replacement_joueur(x,y,&MapJ);//fonction qui repassera les valeurs correcte de x et y pour le tableau de char** dans Map.taille.x/y et aussi la bonne carte sur laquel se trouve la joueur dans MapJ.c
	j.dir=3;	//on modifie j.dir avec la valeur qui correspond à gauche 3 dans l'enum Direction
	
	if (*(*(MapJ.c + MapJ.taille.y) + MapJ.taille.x)!='#')	//On vérifie que l'objet du décord à la position désirée autorise ce déplacement
	{
		
		j.pos.x = x;		//on enregistre ce déplacement si oui dans la variable j.pos
		if(autorisation_scroll( x, y,MapJ,j.dir)){	//condition vérifie si la camera doit suivre le déplacement du joueur (cette condition est vérifiée dans la fonction)
			camera.x--;	//adaptation de la position de la camera
		}
		switchMap();		//fonction qui va vérifier si on ne doit pas au regard de cette nouvelle position de j si on doit charger une nouvelle carte et passer currentMap à nextMap ou previousMap
		supprimer_ennemi_hors_portee(liste);	//on supprime les ennemis qui sont trop loin du joueur
		activer_ennemi_a_portee(liste);	//les ennemis qui sont suffisament proche de j sont activés et effectueront leurs actions
	}


};

void moveRight()		//la fonction va vérifier si on peut se déplacer vers la droite et le faire le cas échéant
{
	int x = 0, y = 0;	//variable qui vont contenir la position désirée en x pour x et en y pour y  


	x = j.pos.x+1;	//la variable x est donc initialisé à la position j en x (j.pos.x) décalé à droite (donc +1, une case à droite pour openGL)
	y = j.pos.y;	//la variable y est donc initialisé à la position j en y (j.pos.y), comme c'est le décalage à droite on a pas de variation pour la position y de j
	Map MapJ;	//structure Map qui contiendra la carte sur laquel j se trouve (parmis currentMap, nextMap et previousMap) et avec laquel on effectuera les test de collision avec le décors
	
	 //variable pour le placement du joueur dans la carte sur lequel il se trouve (next, nextLR ou current).
	replacement_joueur(x,y,&MapJ);//fonction qui repassera les valeurs correcte de x et y pour le tableau de char** dans Map.taille.x/y et aussi la bonne carte sur laquel se trouve la joueur dans MapJ.c
	j.dir=1;	//on modifie j.dir avec la valeur qui correspond à gauche 3 dans l'enum Direction
	
	if (*(*(MapJ.c + MapJ.taille.y) + (MapJ.taille.x))!='#')	//On vérifie que l'objet du décord à la position désirée autorise ce déplacement
	{

		j.pos.x = x;		//on enregistre ce déplacement si oui dans la variable j.pos
		if(autorisation_scroll( x, y,MapJ,j.dir)){	//condition vérifie si la camera doit suivre le déplacement du joueur (cette condition est vérifiée dans la fonction)
			camera.x++;	//adaptation de la position de la camera
		}
		switchMap();		//fonction qui va vérifier si on ne doit pas au regard de cette nouvelle position de j si on doit charger une nouvelle carte et passer currentMap à nextMap ou previousMap
		supprimer_ennemi_hors_portee(liste);	//on supprime les ennemis qui sont trop loin du joueur
		activer_ennemi_a_portee(liste);	//les ennemis qui sont suffisament proche de j sont activés et effectueront leurs actions
	}

};
void moveUp()
{
 int  x = 0, y = 0;
      
	x = j.pos.x;	//la variable x est donc initialisé à la position j en x (j.pos.x), comme c'est le décalage vers le haut on a pas de variation pour la position x de j
	y = j.pos.y-1;	//la variable y est donc initialisé à la position j en y (j.pos.y) décalé vers le haut (donc -1, une case vers le haut pour openGL)
	
	Map MapJ;	//fonction qui repassera les valeurs correcte de x et y pour le tableau de char** dans Map.taille.x/y et aussi la bonne carte sur laquel se trouve la joueur dans MapJ.c
	j.dir=0;	//on modifie j.dir avec la valeur qui correspond à haut 0 dans l'enum Direction
	 //variable pour le placement du joueur dans la carte sur lequel il se trouve (next, nextLR ou current).
	replacement_joueur(x,y,&MapJ);	//fonction qui repassera les valeurs correcte de x et y pour le tableau de char** dans Map.taille.x/y et aussi la bonne carte sur laquel se trouve la joueur dans MapJ.c
	if (*(*(MapJ.c + MapJ.taille.y) + MapJ.taille.x)!='#'&&*(*(MapJ.c + MapJ.taille.y) + MapJ.taille.x)!='!'){//On vérifie que l'objet du décord à la position désirée autorise ce déplacement
		
		j.pos.y = y;		//on enregistre ce déplacement si oui dans la variable j.pos
		if(autorisation_scroll( x, y,MapJ,j.dir)){	//condition vérifie si la camera doit suivre le déplacement du joueur (cette condition est vérifiée dans la fonction)
			camera.y--;	//adaptation de la position de la camera
		}
		switchMap();		//fonction qui va vérifier si on ne doit pas au regard de cette nouvelle position de j si on doit charger une nouvelle carte et passer currentMap à nextMap ou previousMap
		supprimer_ennemi_hors_portee(liste);	//on supprime les ennemis qui sont trop loin du joueur
		activer_ennemi_a_portee(liste);	//les ennemis qui sont suffisament proche de j sont activés et effectueront leurs actions
		
	} 
	
};
void moveDown()
{
 int  x = 0, y = 0;
 
   x = j.pos.x;	//la variable x est donc initialisé à la position j en x (j.pos.x), comme c'est le décalage vers le bas on a pas de variation pour la position x de j
   y = j.pos.y+1;	//la variable y est donc initialisé à la position j en y (j.pos.y) décalé vers le bas (donc +1, une case vers le bas pour openGL)
   
   Map MapJ;		//fonction qui repassera les valeurs correcte de x et y pour le tableau de char** dans Map.taille.x/y et aussi la bonne carte sur laquel se trouve la joueur dans MapJ.c
	 //variable pour le placement du joueur dans la carte sur lequel il se trouve (next, nextLR ou current).
	replacement_joueur(x,y,&MapJ);	//fonction qui repassera les valeurs correcte de x et y pour le tableau de char** dans Map.taille.x/y et aussi la bonne carte sur laquel se trouve la joueur dans MapJ.c
	j.dir=2;	//on modifie j.dir avec la valeur qui correspond à bas 2 dans l'enum Direction
   if (*(*(MapJ.c + (MapJ.taille.y)) + MapJ.taille.x)!='#'&&*(*(MapJ.c + (MapJ.taille.y)) + MapJ.taille.x)!='!'){   
		
		j.pos.y = y;		//on enregistre ce déplacement si oui dans la variable j.pos	
		if(autorisation_scroll( x, y,MapJ,j.dir)){	//condition vérifie si la camera doit suivre le déplacement du joueur (cette condition est vérifiée dans la fonction)
			camera.y++;	//adaptation de la position de la camera
		}
		switchMap();		//fonction qui va vérifier si on ne doit pas au regard de cette nouvelle position de j si on doit charger une nouvelle carte et passer currentMap à nextMap ou previousMap
		supprimer_ennemi_hors_portee(liste);	//on supprime les ennemis qui sont trop loin du joueur
		activer_ennemi_a_portee( liste);	//les ennemis qui sont suffisament proche de j sont activés et effectueront leurs actions
		
      }
};
//PRE: les argument sont la postion du joueur après le déplacement et la carte sur laquel il évolue.
//POST: fonction qui va testé si oui ou non la caméra doit scroller
bool autorisation_scroll(int x,int y,Map MapJ,Direction jDir){
	bool SCROLL_LOCK=true;//booleen vérifiant si on a un verrou de scrolling dans la direction que prend le joueur 
	bool SCROLL_J=false;	//booleen vérifiant que la position du joueur par rapport à la caméra selon sa direction est suffisament éloignée
	int xLock=32;	//position x du verrou du srcolling pour la direction
	int yLock=32;	//position y du verrou du srcolling pour la direction
	switch(jDir){	//switch case sur la direction du joueur passé en argument
		case 0:
			yLock=0;			//le verrou sera en position y=0 dans le tableau de char* MapJ
			if((*(*(MapJ.c + yLock) + xLock)=='!')&&(MapJ.taille.y<11)){	//double condition de vérification pour le blocage du scrolling, le caractère à la position yLock et xLock dans le tableau MapJ.c doit être différent de '!' caractère signalant la limite supérieur et inférieur de la carte et MapJ.taille.y (la position du joueur après déplacement) doit être >=11. ce qui signifie que si le joueur est trop près du bord de la map le scrolling ne suivera pas le déplacement du joueur vers la limite de la map
				SCROLL_LOCK=false; //SCROLL_LOCK a false bloque le scrolling
			}
			if((camera.y-y)>3){	//si la camera n'est pas à plus de 4 case de la position du joueur alors on ne rentre pas dans la condition
				SCROLL_J=true;	//SCROLL_J à true autorise le scrolling 
			}
			break;
		case 1:
			xLock=currentMap.taille.x-1;	//le verrou sera en position x=currentMap.taille.x-1 dans le tableau de char* MapJ
			if(((*(*(MapJ.c + yLock) + xLock))=='#'||(*(*(MapJ.c + yLock) + xLock)=='!'))&&(MapJ.taille.x>48)){//double condition de vérification pour le blocage du scrolling, le caractère à la position yLock et xLock dans le tableau MapJ.c doit être différent de '#' caractère signalant la limite latérale gauche et droite de la carte et MapJ.taille.x (la position du joueur après déplacement) doit être <=50. ce qui signifie que si le joueur est trop près du bord de la map le scrolling ne suivera pas le déplacement du joueur vers la limite de la map
				SCROLL_LOCK=false;
			}
			if((x-camera.x)>2){//si la camera n'est pas à plus de 2 case de la position du joueur alors on ne rentre pas dans la condition. Remarque il y a une différence de position par rapport à j de la camera demandée à gauche et a droite pour déplacer la caméra. Cela est du au nombre pair de case sur lequel peut être positionné la caméra faisant qu'il n'existe pas de case centrale absolue, le centre est le point entre la case (31;32)(32;32)(31;31)et(32;31) Mais on a choisi de déterminé que le centre serait (32;32) donc il y a un décalage initiale de la caméra d'une case vers la droite et le bas
				SCROLL_J=true;
			}
			break;
		case 2:
			yLock=currentMap.taille.y-1;	//le verrou sera en position y=currentMap.taille.y-1 dans le tableau de char* MapJ
			if((*(*(MapJ.c + yLock) + xLock)=='!')&&(MapJ.taille.y>50)){//double condition de vérification pour le blocage du scrolling, le caractère à la position yLock et xLock dans le tableau MapJ.c doit être différent de '!' caractère signalant la limite supérieur et inférieur de la carte et MapJ.taille.y (la position du joueur après déplacement) doit être <=50. ce qui signifie que si le joueur est trop près du bord de la map le scrolling ne suivera pas le déplacement du joueur vers la limite de la map
				SCROLL_LOCK=false;
			}
			if((y-camera.y)>2){	//si la camera n'est pas à plus de 2 case de la position du joueur alors on ne rentre pas dans la condition. Remarque il y a une différence de position par rapport à j de la camera demandée à gauche et a droite pour déplacer la caméra. Cela est du au nombre pair de case sur lequel peut être positionné la caméra faisant qu'il n'existe pas de case centrale absolue, le centre est le point entre la case (31;32)(32;32)(31;31)et(32;31) Mais on a choisi de déterminé que le centre serait (32;32) donc il y a un décalage initiale de la caméra d'une case vers la droite et le bas
				SCROLL_J=true;
			}
			break;
		case 3:
			xLock=0;			//le verrou sera en position x=0 dans le tableau de char* MapJ
			if(((*(*(MapJ.c + yLock) + xLock)=='#')||*(*(MapJ.c + yLock) + xLock)=='!')&&(MapJ.taille.x<15)){//double condition de vérification pour le blocage du scrolling, le caractère à la position yLock et xLock dans le tableau MapJ.c doit être différent de '#' caractère signalant la limite latérale gauche et droite de la carte et MapJ.taille.x (la position du joueur après déplacement) doit être >=11. ce qui signifie que si le joueur est trop près du bord de la map le scrolling ne suivera pas le déplacement du joueur vers la limite de la map
				SCROLL_LOCK=false;
			}
			if((camera.x-x)>3){
				SCROLL_J=true;
			}
			break;
		case 4:			//condition du switch si le joueur n'a pas de direction, à priori impossible, mais dans le doute on bloque le déplacement de la camera
			SCROLL_J=false;		
			break;
	}
	return(SCROLL_J&&SCROLL_LOCK);	//C'est une double autorisation pour le scrolling qui est renvoyé, les deux doivent être respectée sinon la camera ne suivra pas le joueur
};
