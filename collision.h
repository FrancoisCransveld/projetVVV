#ifndef _COLLISION_H_
#define _COLLISION_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jeu.h"
#include "ennemi.h"
#include "joueur.h"
#include "tirs.h"

//PRE:prend en argument le type de l'ennemi, la direction dans laquel il est tourné, la coordonnee de celui-ci en x et y.
/*POST:Cette fonction renvoie la position du coin opposé de la hit box de l'ennemi dans la structure Coordonnee et dans le pointeur bool en entrée si cette coordonnée dépassait en x
 ou y la taille de la carte (le tableau de caractère char** ) sur laquel on devrait faire le test de collision. Remarque si ce booleen est actif on ne doit pas tester, dans la carte
  sélectionné précédement, le caractère à la limite inférieur, car y sera plus grand que la taille max du tableau et on sortira de la mémoire alloué du programme. La Coordonnee
   limiteBD, comme elle sera appelé dans cette fonction, représentera le coin inférieur droit de l'ennemi ce coin dépend de l'orientation dans laquel l'ennemi est tourné et de la
   taille de celui-ci dépendant de son type */
Coordonnee  HitBoxEnnemi_collision_decors(TypeEnnemi type,Direction dir,Coordonnee limiteHG,bool* DIFFERENTMAP);
/*PRE:prend en argument la coordonnee (des cases) du coin supérieur gauche limiteHG et coin inférieur droit limiteBD des cases occupé par l'ennemi, la direction dans laquel l'ennemi
	est tourné et la map (char** MapCol) dans laquel on retrouve les caractères avec lesquel on effecture le test de collision */
/*POST:Cette fonction renvoie un booleen qui indique si  le déplacement est possible , en fonction de la direction de l'ennemi de ses limites et de la position dans laquel
	 l'ennemi désire se rendre. */ 
bool collision_ennemi_decor(Coordonnee limiteHG, Coordonnee limiteBD, Direction dir, char** MapCol);
/*PRE:prend en argument la coordonnee (des cases) du coin supérieur gauche limiteHG et coin inférieur droit limiteBD des cases occupé par l'ennemi, la direction dans laquel l'ennemi
	est tourné et la map (char** MapCol) dans laquel on retrouve les caractères avec lesquel on effecture le test de collision pour limiteHG, enfin on retrouve l'autre carte
	(char** Maplimite) dans laquel on effectue aussi des tests de collisions,mais pour limiteBD.y (case du coin inférieur droit) de l'ennemi*/
/*POST:Cette fonction renvoie un booleen qui indique si  le déplacement est possible , en fonction de la direction de l'ennemi de ses limites et de la position dans laquel
	 l'ennemi désire se rendre. Remarque cette fonction est très similaire à collision_ennemi_decor elle est utilisé pour gérer les cas limites ou l'ennemi se trouve sur 
	 plusieur Map différente entre currentMap, previousMap et nextMap les test pours la collision ne se font pas dans la même map, qu'on utilise la Coordonnee de la case
	  représenté pas limiteHG.y ou limiteBD.y */ 
bool collision_ennemi_decor_limiteMap(Coordonnee limiteHG, Coordonnee limiteBD, Direction dir, char** MapCol,char** Maplimite);
/*PRE:prend en argument le numero de l'ennemi dans la ListeEnnemi liste (variable globale) à tester, et le numero du tirs dans la liste de tirs du joueur (ListeTirs j.tirs)
  POST:Vérifie que les positions de l'ennemi et du tirs correspondent ou non et renvoie le résultat dans un booleen (true=collision, false=les deux objets ne se touche pas)*/
bool collision_tirs_ennemi(int ennemi,int tirs);
/*PRE:prend en argument le numero de l'ennemi dans la ListeEnnemi liste (variable globale) à tester, la position du joueur se trouve dans j.pos (la variable Joueur j est 
	une variable globale)
  POST:Cette fonction renvoie un booleen true si on a bien une collision entre le joueur et l'ennemi précisé en argument*/
bool collision_joueur_ennemi(int ennemi);
/*PRE:Cette fonction utilise les variable globale ListeEnnemi liste (variable globale) pour la position de chaque ennemi et la position du joueur qui se trouve dans j.pos 
	(la variable Joueur j est une variable globale)
  POST:Cette fonction renvoie un booleen true si on a bien une collision entre le joueur et un ennemi de la liste. Pour cela on fera appel à la fonction collision_joueur_ennemi 
  	dans une boucle for pour tester toute la liste des ennemis. Remarque cette fonction est similaire à la suivante la différence réside dans les effets que la fonction à sur les
  	variables de Joueur j. De plus celle-ci est appellé dans le tours des ennemis après leurs déplacement et effectue la modification de j->hp ainsi que le l'invulnerabilite
  	de j en plus d'éjecter joueur à l'oposer de la direction de joueur*/
bool collisionEnnemiJoueur();
/*PRE:Cette fonction utilise les variable globale ListeEnnemi liste (variable globale) pour la position de chaque ennemi et la position du joueur qui se trouve dans j.pos 
	(la variable Joueur j est une variable globale)
  POST:Cette fonction renvoie un booleen true si on a bien une collision entre le joueur et un ennemi de la liste. Pour cela on fera appel à la fonction collision_joueur_ennemi 
  	dans une boucle for pour tester toute la liste des ennemis. Remarque cette fonction est similaire à la précédente la différence réside dans les effets que la fonction à 
  	sur les variables de Joueur j. Les modifications des variables de j ne sont pas effectué dans cette fonction, mais dans la fonction appelante moveLeft, moveRight, moveUp,
  	 ou moveDown*/
bool collisionJoueurEnnemi();
/*PRE:Prend en argument le numero de deux ennemis(ennemi et ennemi2) de la ListeEnnemi liste
  POST:Cette fonction renvoie un booleen indiquant à true s'il y a bien une collision entre les deux ennemis*/
bool collision_ennemi_ennemi(int ennemi, int ennemi2);
/*PRE:Prend en argument le numero d'un ennemi (int ennemi) et un pointeur de Coordonnee (EnnemiActuel) qui permettra de récupérer la position de l'ennemi 
  POST:Cette fonction renvoie la valeur de la coordonnee l'ennemi demandé en argument dans le pointeur de coordonnee EnnemiActuel, ce qui représentera les limites gauche et haute de la hitBox (ou le coin haut gauche du rectangle dans lequel se trouve l'ennemi) et renvoie par return la coordonnee de la limite inférieur droite de la hitBox (ou le coin inférieur droit). Remarque dans ces fonctions on passe par la coordonnee en return la valeur en demi case (TILE_SIZE) elle est donc doublée par rapport à la coordonnee renvoyée par pointeur (par case) */
Coordonnee HitBoxEnnemi(int ennemi,Coordonnee* EnnemiActuel);
/*PRE:Prend en argument la direction du joueur
  POST:Cette fonction renvoie via le pointeur coordonnee hitBoxHG, ce qui représentera les limites gauche et haute de la hitBox (ou le coin haut gauche du rectangle dans lequel se trouve le joueur) et renvoie par return la coordonnee de la limite inférieur droite de la hitBox (ou le coin inférieur droit). Remarque dans cette fonction on passe par la coordonnee en return et par le pointeur de Coordonnee la valeur en demi case (TILE_SIZE) elle est donc doublée par rapport à la coordonnee renvoyée par pointeur (par case) */
Coordonnee hit_box_joueur(Direction dir,Coordonnee* hitBoxHG);
#endif
