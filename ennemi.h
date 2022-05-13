#ifndef _ENNEMI_H_
#define _ENNEMI_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jeu.h"

#define MAX_NOM 32
enum typeEnnemi{voiture,moto,camion,SUV,vide};	//déclaration d'un type enumeration typeEnnemi avec 5 valeurs  
typedef enum typeEnnemi TypeEnnemi;

struct ennemi{		//Structure ennemi 
  Coordonnee pos;		//Coordonnee de l'ennemi calculée en case 
  char* nom;			//Nom de l'ennemi (qui correspond juste au nom de son type pour le moment)
  int vie;			//entier qui contient le nombre de point de vie restant à l'ennemi (cette variable à une valeur de base liée au type de l'ennemi)
  TypeEnnemi type;		//Le type de l'ennemi {voiture, moto, camion, SUV, vide}
  bool attente;		//Booleen indique si l'ennemi doit effectuer des actions ou non (attente=true, l'ennemi ne fait rien il est en attente, attente=false,
  				// l'ennemi effectue ses action). Ce booleen change en fonction de la distance qui le sépare du joueur s'il est trop loin 
  				//l'ennemi passe en mode attente, mais si le joueur est à une certaine distance l'ennemi est activé
  Direction dir;		//L'énumération Direction dir correspond à la direction dans laquel est tourné l'ennemi.
};
typedef struct ennemi Ennemi;

typedef struct elementEnnemi ElementEnnemi;	//Les ennemis seront gardé dans une liste doublement chaînée avec un pointeur vers l'élément suivant et précédent pour chaque
						// élément de la liste
struct elementEnnemi{
  Ennemi e;			//Structure ennemi contenant les variables de cette ElementEnnemi
  ElementEnnemi* suivant;	//pointeur vers l'élément suivant de la liste 
  ElementEnnemi* precedent;	//pointeur vers l'élément précédent de la liste
};

typedef struct listeEnnemi ListeEnnemi;
struct listeEnnemi{				//ListeEnnemi conserve les informations sur la liste chaînée à proprement parlée
  int nombre;						//le nombre d'élément qui la compose dans (int nombre)
  ElementEnnemi* premier;				//le pointeur vers le premier élément de cette liste
  ElementEnnemi* dernier;				//le pointeur vers le dernier élément de cette liste
};

ListeEnnemi* liste;		//Les ennemis sont gardés dans une variable globale liste (structure ListeEnnemi)

/*PRE:la fonction ne prend rien en argument elle se contente de faire une allocation de mémoire pour une liste d'ennemi et un élément fictif de cette liste 
  POST:Cette fonction renvoie le pointeur vers la ListeEnnemi initialisé, dont on a fait la demande d'allocation de mémoire dans la fonction. l'initialisation 
  	des variable de la liste (nombre=0;premier et dernier pointe sur le premier élément dont ont a fait l'allocation de mémoire dans la fonction et dont les variables sont 
  	initialisé aux valeurs de base*/
ListeEnnemi* creer_liste(void);  
/*PRE:prend en entrée la liste chainée à laquel on donne un nouvelle élément, le nom de cette élément, sa vie, sa coordonnee, son type
  POST:ne renvoie rien, mais ajoute un ennemi en fin de la liste chainée liste(variable globale), qui aura toute les caractéristiques données en argument. L'élément est ajouté à la fin de la liste à ElementEnnemi* dernier, et l'ancien dernier élément aura son pointeur suivant modifié à l'adresse de ce nouvelle élément */
void nouvel_ennemi(ListeEnnemi* liste, char nom[], int vie, Coordonnee pos, TypeEnnemi t);
//PRE:prend en entrée la liste chainée à laquel on donne un nouvelle élément, le nom de cette élément, sa vie, sa coordonnee, son type
//POST:on modifie un élément de la liste donnée, cette élement se retrouve avec numero il correspond à la place dans la liste chainée commençant par 0 jusqu'à (liste->nombre-1)
void modifier_ennemi(ListeEnnemi* liste, int numero, char nom[], int vie, Coordonnee pos, TypeEnnemi t,bool a);
//PRE:On prend la liste dans laquel on veut supprimer et le numéro de l'élément (int numero) la numérotation des éléments commence par 0 jusqu'à (liste->nombre-1)
//POST:Supprime l'element numero et refait les liens entre les suivants et précédent
void supprimer_ennemi_numero(ListeEnnemi* liste, int numero);
/*PRE: prend juste en argument la liste chaînée liste
  POST: Cette fonction ne renvoie rien mais modifie la liste chaînée pour en éliminer tous les éléments, et initialiser ses pointeur vers le premier et le dernier à NULL, mais ne 	libère par l'espace mémoire de cette liste pour pouvoir être réutilisé dans une autre partie*/
void supprimer_liste_ennemi(ListeEnnemi* liste);
/*PRE: argument d'entrée nécessaire la structure liste de la chaine, le numéro de l'ennemi et les dégats infligés à l'ennemi
  POST:Retire un nombre de vie égale à (int degat) à l'ennemi numéro (int numero) de la liste chainée d'ennemi (ListeEnnemi liste)*/
void retirer_vie_numero(ListeEnnemi* liste, int numero, int degat);
//PRE:En argument on prend le numero de l'ennemi dans la liste à modifier, la liste en question, et la Coordonnee pos
//POST:modifie uniquement la position (ElementEnnemi e->pos) de l'ennemi numéro (numero) de la liste chainée (liste) 
void modifier_pos_ennemi(ListeEnnemi* liste, int numero, Coordonnee pos);
/*PRE:On prend la liste dans laquel se trouve l'ennemi dont on veut la Direction dans laquel l'ennemi est tourné et le numéro de l'élément (int numero) 
	la numérotation des éléments commence par 0 jusqu'à (liste->nombre-1)
  POST: Renvoie la valeur de type énumération Direction de l'ennemi (int numero) de la liste chaînée liste*/
Direction dir_ennemi(ListeEnnemi* liste, int numero);
/*PRE:Prend en argument la liste chaînée des ennemis liste et la variation de position à appliquer à tous les ennemis de la liste
  POST:La fonction ne renvoie rien, mais modifie la position (Coordonnee e.pos) de tous les éléments de la liste par la variation en entrée.
       surtout utiliser pour switch map (deplacement vertical), ou les valeurs de position absolue sont toutes modifiées autant pour le
       joueur, que la camera, que pour les ennemis et les tirs, en même temps que les cartes sont échangés pour donné l'impression que rien n'a bougé tout en permettant de 
      libérer des élément duquel on est fort éloigné*/
void modifier_pos_ennemis(ListeEnnemi* liste, Coordonnee variation);
/*PRE:Prend en argument la liste chaînée des ennemis liste 
  POST:ne renvoie rien, mais vérifie s'il faut modifier la valeur du booleen attente des éléments ElementEnnemi de la liste. La vérification se fait selon la distance par rapport à
  	la camera. remarque la fonction active ou désactive les ennemis contrairement à ce que peut faire penser le nom de la fonction*/
void activer_ennemi_a_portee(ListeEnnemi* liste);
/*PRE:On prend la liste dans laquel se trouve l'ennemi dont on veut la position et le numéro de l'élément (int numero) la numérotation des éléments commence
	 par 0 jusqu'à (liste->nombre-1)
  POST:renvoie la structure Coordonnee pos de l'ennemi (int numero) de la liste chaînée*/
Coordonnee pos_Ennemi(ListeEnnemi* liste,int numero);
/*PRE:prend en argument la liste chainée des ennemis liste;
  POST:La fonction ne renvoie rien mais supprime les ennemis qui se trouve trop loin de l'action, ditance calculée par rapport à la position de la camera*/
void supprimer_ennemi_hors_portee(ListeEnnemi* liste);
//PRE:cette fontion reçoit un pointeur de map, une coordonnee x et une coordonnee y de l'ennemi ou il veut se déplacer
//POST:la fonction renvoie la coordonnee de l'ennemi sur la map qui le concerne next, current ou previous dans la structure coordonnee du pointeur de map donné en entrée ce qui premettra de vérifier la correspondance avec les murs sur les cartes.
#include "LoadMaps.h"
void replacement_ennemi(int x, int y, Map* map);
/*PRE:on prend un élément ennemi de la liste chainée et le numero de celui-ci (int numero) la numérotation des éléments commence par 0 jusqu'à (liste->nombre-1)
  POST: la fontion va effectuer l'algorithme qui détermine vers ou l'ennemi veut se déplacer ou l'action qu'il veut effectuer et test après cela s'il peut effectuer ce déplacement dans deux test de collision, un avec les autres ennemis et l'autre avec les éléments bloquant du décors*/
void action_voiture(Ennemi* voiture, int numero);
/*PRE:on prend un élément ennemi de la liste chainée et le numero de celui-ci (int numero) la numérotation des éléments commence par 0 jusqu'à (liste->nombre-1)
  POST: la fontion va effectuer l'algorithme qui détermine vers ou l'ennemi veut se déplacer ou l'action qu'il veut effectuer et test après cela s'il peut effectuer ce déplacement dans deux test de collision, un avec les autres ennemis et l'autre avec les éléments bloquant du décors*/
void action_moto(Ennemi* moto, int numero);
/*PRE:prend en argument la liste des ennemis liste, car la fonction va appelé tous les ennemis à effectuer leur action
  POST:La fonction ca appelé dans une boucle tous les ennemis un par un pour effectuer une action*/
void action_ennemi(ListeEnnemi* liste);
/*PRE:prend la liste des ennemis
  POST:affiche la liste des ennemis en consoles*/
void afficher_liste(ListeEnnemi* liste);
#endif
