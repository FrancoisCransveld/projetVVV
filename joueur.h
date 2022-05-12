#ifndef _JOUEUR_H_
#define _JOUEUR_H_
#include "jeu.h"
#include "LoadMaps.h"
#include "tirs.h"

//Structure joueur contient toute les variables concernant le joueur elle est pour le moment uniquement utilisé pour 1 joueur dans la variable globale j.
struct joueur{
	Coordonnee pos;	//coordonnée en x et y contenue dans la variable position. Coordonnée est une structure contenue dans LoadsMaps.h et qui contient 2 int (x et y).
			//ces coordonnées sont grossière et corresponde à des cases de 16/16 pixels 
	int vie;	//vie est un entier contenant le nombre de vie du joueur, qui correspond au nombre de fois qu'il peut repartir avec son score 
			//après avoir perdu tous se hp
	int hp;		//hp est l'entier correspondant au nombre de fois que le joueur peut être touché avant de perdre une vie
	Direction dir;	//dir est une variable d'énumeration Direction qui contient les sens vers lequel le joueur se tourne (haut, droite, bas, gauche, rien).
	ListeTirs* tirs;//tirs contient le pointeur vers les premiers et derniers éléments de la liste de structure tirs, ainsi que le nombre d'élément de la lise.
			//Tous les éléments de cette liste sont des tirs du joueur. 
	int maxTirs;	//maxTirs correspond au maximum de d'élément tirs qui peuvent-être présent en même temps dans la liste tirs, et donc à l'écran. 
			//cette variable dépend du type d'arme.
};
typedef struct joueur Joueur; //redéfinition de la structure struct joueur en Joueur.
Joueur j;		//déclaration de la variable globale j 

//PRE:cette fonction prend en entrée la position absolue du joueur en x et y deux entiers et un pointeur variable struct map Map qui contiendra les valeurs de retour de x et y dans sa 
//	variable Coordonnee (MapJ.taille.x ou MapJ.taille.y) ainsi que la map char** dans sa variable c (MapJ.c)
//POST:cette fonction recalcule la position sur un grid de 64x64 (de 0 inclu à 63 inclu) de la position du joueur et sélectionne la map parmis 
//	currentMap,nextMap et previousMap (variable globale de LoadMap.h) quelle pointeur de tableau de char (char** ) doit être utilisé pour faire les tests de collision avec le décors
//	et les tests pour le blocage éventuelle du scrolling de la caméra
void replacement_joueur(int x, int y, Map* map);
//PRE:cette fonction prend en entrée la position effective du joueur après un déplacement dans les entiers int x et y, ainsi que la carte MapJ et  la Direction du joueur jDir
//POST:cette fonction renvoie un booleen qui si il est égale à true autorise la camera à suivre le déplacement du joueur sinon à false bloquera la camera sur place 
//	en bloquant la mise à jour de la variable Coordonnee de la camera.
bool autorisation_scroll(int x,int y,Map MapJ,Direction jDir);
//Les quatres fonctions qui suivent effectue les appels des deux fonctions précédentes pour vérifier les variations à effectuer sur les variables de j et camera 
//PRE: elle ne prenne rien en entrée car elle utilise la variable globale Joueur j, Coordonnee camera et les Map currentMap, nextMap et  previousMap
//POST:en sortie elle auront modifié la position du joueur vers la direction correspondante au nom si rien ne l'empéchait sur la carte, pareil pour la camera si on se trouve entre 
//	les limites du niveau (des cartes) et modifie la variable Direction dir de j quand elles sont appelé peu importe le résultat sur les autres variables. 
void moveLeft();
void moveRight();
void moveUp();
void moveDown();

#endif
