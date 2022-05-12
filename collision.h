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
	 plusieur Map différente entre currentMap, previousMap et nextMap les test pours la collision ne se font pas dans la même map, qu'on utilise la Coordonnee de la case représenté pas limiteHG.y ou limiteBD.y */ 
bool collision_ennemi_decor_limiteMap(Coordonnee limiteHG, Coordonnee limiteBD, Direction dir, char** MapCol,char** Maplimite);
/*PRE:prend en argument le numero de l'ennemi dans la ListeEnnemi liste (variable globale) à tester, et le numero du tirs dans la liste de tirs du joueur (ListeTirs j.tirs)
  POST:Vérifie que les positions de l'ennemi et du tirs correspondent ou non et renvoie le résultat dans un booleen (true=collision, false=les deux objets ne se touche pas)*/
bool collision_tirs_ennemi(int ennemi,int tirs);
/*PRE:prend en argument le numero de l'ennemi dans la ListeEnnemi liste (variable globale) à tester, la position du joueur se trouve dans j.pos (la variable Joueur j est une variable globale)
  POST:*/
bool collision_joueur_ennemi(int ennemi);
//PRE:
//POST:
bool collisionEnnemiJoueur();
//PRE:
//POST:
Coordonnee HitBoxEnnemi(int ennemi,Coordonnee* EnnemiActuel);
//PRE:
//POST:
Coordonnee hit_box_joueur(Direction dir);
#endif
