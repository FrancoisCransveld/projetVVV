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
void nouvel_ennemi(ListeEnnemi* liste, char nom[], int vie, Coordonnee pos, TypeEnnemi t);
void modifier_ennemi(ListeEnnemi* liste, int numero, char nom[], int vie, Coordonnee pos, TypeEnnemi t,bool a);
void supprimer_ennemi_numero(ListeEnnemi* liste, int numero);
void supprimer_liste_ennemi(ListeEnnemi* liste);
void retirer_vie_numero(ListeEnnemi* liste, int numero, int degat);
void modifier_pos_ennemi(ListeEnnemi* liste, int numero, Coordonnee pos);
Direction dir_ennemi(ListeEnnemi* liste, int numero);
void modifier_pos_ennemis(ListeEnnemi* liste, Coordonnee variation);
void activer_ennemi_a_portee(ListeEnnemi* liste);
Coordonnee pos_Ennemi(ListeEnnemi* liste,int numero);
void supprimer_ennemi_hors_portee(ListeEnnemi* liste);
void action_voiture(Ennemi* voiture, int numero);
void action_moto(Ennemi* moto, int numero);
void action_ennemi(ListeEnnemi* liste);
void afficher_liste(ListeEnnemi* liste);
#endif
