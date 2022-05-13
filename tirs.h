#ifndef _TIRS_H_
#define _TIRS_H_
#include <stdlib.h>
#include <stdio.h>
#include "jeu.h"

enum typeTirs{pistolet,riffle,bazooka,rien};	//déclaration d'un type enumeration typeTirs 
typedef enum typeTirs TypeTirs;		//redéclaration du nom enum typeTirs en TypeTirs
						//remarque: cette enumeration n'est pas encore exploité dans le jeu
struct tirs{			//structure tirs  
  Coordonnee pos;		//Variable coordonnee qui correspond à la position du tirs (cette position dans la structure en calculée en demi-case (TILE_SIZE/2) )
  TypeTirs t;			//le type du tirs dans t
  int distanceMax;		//entier qui contiendra le nombre de demi-case que le tirs peux se déplacer (ce nombre sera initialisé à la création du tirs selon son type)
  Direction dir;		//la direction du tirs qui utilise normalement l'enum Direction, le déplacement du tirs dépend de cette direction (Up,Right,Down,Left,rien)	
};
typedef struct tirs Tirs;

typedef struct elementTirs ElementTirs;
struct elementTirs{		//Les tirs seront utilisé dans des listes doublement chaînées avec 
  Tirs t;			//Tirs la structure tirs dans lequel on retrouve les valeurs du tirs
  ElementTirs* suivant;	//Le pointeur vers le prochaine élément de la liste chainée. Ce pointeur vaut NULL au dernier élément 
  ElementTirs* precedent;	//le pointeur vers l'élément précédent de la liste chainée. Ce pointeur vaut NULL au premier élément
};

typedef struct listeTirs ListeTirs;
struct listeTirs{		//La listeTirs permet de retrouver le début ou la fin de la liste de tirs
  int nombre;			//le nombre d'élément de la liste de tirs
  ElementTirs* premier;	//pointeur vers le premier élément de la liste
  ElementTirs* dernier;	//pointeur vers le dernier élément de la liste
};

/*PRE:la fonction ne prend rien en argument elle se contente de faire une allocation de mémoire pour une liste de tirs et un élément fictif de cette liste 
  POST:Cette fonction renvoie le pointeur vers la ListeTirs initialisé, dont on a fait la demande d'allocation de mémoire dans la fonction. l'initialisation 
  	des variable de la liste (nombre=0;premier et dernier pointe sur le premier élément dont ont a fait l'allocation de mémoire dans la fonction et dont les variables sont 
  	initialisé aux valeurs suivante[suivant=NULL;precedent=NULL;coordonnee(0;0);TypeTirs=rien;dir=4;distanceMax=0]) */
ListeTirs* creer_liste_tirs(void);
/*PRE:prend en entrée la liste chainée à laquel on donne un nouvelle élément, le nom de cette élément, sa vie, sa coordonnee, son type
  POST:ajoute un tirs en fin de la liste chainée, qui aura toute les caractéristiques donnée en entrée. L'élément est ajouté à la fin de la liste à ElementTirs* dernier, et l'ancien dernier élément aura son pointeur suivant modifié à l'adresse de ce nouvelle élément */  
void tirs(ListeTirs* listeT, Coordonnee pos, TypeTirs t, Direction dir);
/*PRE:prend en entrée la liste chainée à laquel on donne un nouvelle élément, le nom de cette élément, sa vie, sa coordonnee, son type
  POST:on modifie un élément de la liste donnée, cette élement se retrouve avec numero il correspond à sa place dans la liste chainée. La numérotation commence par 0 jusque 
  listT->nombre-1*/
void modifier_tirs(ListeTirs* listeT, int numero, Coordonnee pos, TypeTirs t,Direction dir);
/*PRE:On prend la liste dans laquel on veut supprimer et le numéro de l'élément (int numero). La numérotation commence par 0 jusque 
  listT->nombre-1
  POST:Supprime l'element numero et refait les liens entre les éléments via leurs pointeurs suivants et précédent, et dans les cas limites redéfini les pointeur
   des premier et dernier élément de la liste*/
void supprimer_tirs_numero(ListeTirs* listeT, int numero);
/*PRE:En argument la liste à modifier
  POST:La fonction ne renvoie rien mais supprime les éléments de tirs qui sont trop éloigné */
void supprimer_tirs_hors_portee(ListeTirs* listeT);
/*PRE:En argument la liste à modifier, la variation de Coordonnee pos
  POST:On déplace tous les tirs de la variation surtout utiliser pour switch map (deplacement vertical), ou les valeurs de position absolue sont toutes modifiées autant pour le
  	 joueur, que la camera, que pour les ennemis et les tirs, en même temps que les cartes sont échangés pour donné l'impression que rien n'a bougé tout en permettant de 
  	 libérer des élément duquel on est fort éloigné*/
void modifier_pos_tirs(ListeTirs* listeT, Coordonnee variation);
/*PRE:Prend en argument la liste Chaînée de tirs
  POST:La fonction ne renvoie rien, mais s'occupe de modifier la position de chaque élément de la liste selon sa direction d'une demi-case. De plus si l'élément à atteint 
  	sa distance maximale (lorsque sa valeurs distanceMax sera égale à 0) l'élément sera suprimer de la liste après avoir effectuer tous les déplacements des éléments de la liste*/
void deplacement_tirs(ListeTirs* listeT);
/*PRE:On prend la liste dans laquel on veut récupérer la position d'un élément tirs et le numéro de cette élément (int numero). La numérotation commence par 0 jusque listT->nombre-1
  POST: La fonction renvoie la position de l'élément demandé en argument dans la liste passé en argument, dans une structure Coordonnee. Remarque les valeurs x et y de cette
  	 coordonnee sont exprimée en demi-case (ce qui fait des valeurs doublée par rapport à d'autre coordonnée par case, comme pour la position du joueur ou les positions
  	 des ennemis)*/
Coordonnee pos_tirs(ListeTirs* listeT,int numero);
/*PRE:On prend la liste dans laquel on récupérer la valeur du type du tirs pour l'élément (int numero). La numérotation commence par 0 jusque listT->nombre-1
  POST:Renvoie la valeur de type Enumération TypeTirs*/
TypeTirs degat_tirs(ListeTirs* listeT, int numero);
/*PRE:On prend en argument le liste chaînée de tirs à afficher
  POST:La fonction se contente d'afficher dans la console tous les éléments de la liste chaînée et ce qu'ils se trouvent dans les variables de chaque élément tirs */
void afficher_liste_tirs(ListeTirs* listeT);
#endif
