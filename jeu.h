#ifndef _JEU_H_
#define _JEU_H_

#include <stdbool.h>
int score;//variable globale qui contiendra le score pendant une partie
bool MENU;//Variable globale qui indique qu'on est sur le MENU initiale du jeu

struct coordonnee{	//structure coordonnee qui contient deux int x et y pour avoir la position sur un plan en deux dimensions des éléments du jeu dans une même structure
	int x;
	int y;
};
typedef struct coordonnee Coordonnee;

enum direction{Up, Right, Down, Left, fin};	//variable énumération Direction qui sera utilisé pour garder et indiquer la direction des différents objets du jeu (joueur,ennemis,tirs)
typedef enum direction Direction;
/*PRE:cette fonction ne prend rien en argument elle va juste appeler les différentes fonction liée au action du joueur, et qui dépende des entrées clavier, mais aussi des point 
      de vie du joueur ou une collision avec un ennemi
  POST:elle ne renvoie rien, mais elle modifie des variables vie des fonctions qu'elle appelle, pour la position du joueur notament*/
void jeu( void );
/*Cette fonction va faire les appels des différentes fonction concerant les tirs. dont l'appel du déplacement des tirs, la vérification de la collision avec n ennemi et 
	la création de nouveau tirs, cette fonction est liée à un glutTimerFunc qui va rappelé cette fonction pendant le fonctionnement du jeu toutes les 25ms */
void upDateTirs(int num);
/*Cette fonction fait l'appel des fonction pour les actions ennemies et si après celle-ci il y a une collision avec le joueur avec au moins un ennemi, la fonction
 a deux glutTimerFunc différent qui ne sont pas appelé dans les même circonstances. Ces timer rappelle cette fonction,mais s'il y a collision le timer prendra 800ms 
 avant le prochain rappel, sinon 120 milliseconde. ce qui aura pour effet de bloquer les ennemis un petit temps après une collision avec le joueur*/
void upDateEnnemi(int num);
/*cette Fonction va être celle qui appelle la fonction jeu toute les 30 ms grace à sont glutTimerFunc sur lui même, mais la fonction jeu ne sera appelé que si la partie a été lancée
	elle réinitialise aussi les booleens Globales liée au touche clavier pour le jeu a false si aucune touhce n'a été pressée*/
void upDateKeyboard(int i);
/*cette fonction va lancé un timer de 2secondes qui va rappeler la fonction upDateInvulnerabilite lorsque le booleen dans j.debutInvulnerabilite est a true.
 Puis à ce deuxième appel, comme dans le premier appel j.debutInvulnerabilité aura été mis a false, la fonction rentre dans une autre condition et change j.invulnerable en false,
  finissant l'invincibilité du joueur et ne relançant pas de timer. 
  Remarque cette fonction est lancé à la base depuis jeu lorsque j.invulnerable et j.debutInvulnerabilité sont vrai tous les deux*/
void upDateInvulnerabilite(int num);
/*fonction qui va permettre d'effectuer la rotation des cartes sur lequel les ennemis, le joueur et les tirs évolue et de chargée les nouvelles cartes.
 Ces changements on lieu Lorsque la camera atteint un certain point dans les cartes previousMap ou nextMap. Cette fonction va échanger la carte current avec la carte sur laquel le joueur se trouve (previous ou next) et décale la position sur l'axe vertical de tout les objets (joueur, tirs, ennemis)*/
void switchMap(void);
/*cette fonction réinitialise la position du joueur au début du niveau, recharge les ennemis et les cartes du début du niveau, rend 5 hp au joueur, et retire une vie. Si la vie du joueur atteint 0 le fonction appel game_over*/
void mort();
/*Cette fonction change l'int de selectionMenu à 5 ce qui fait sortir le jeu de sa phase de jeu et lance la fonction inscription_score()*/
void game_over();
#endif
