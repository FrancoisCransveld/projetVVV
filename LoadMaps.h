#ifndef _LOADMAP_H_
#define _LOADMAP_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jeu.h"
#include "tirs.h"

//attention ces deux #define son a modifié dés que le nombre de fichier texte auquel ils font référence changent
#define MAPS 14	//nombre de carte différente de jeu dans les fichiers texte
#define MAPS_BOSS 2	//nombre de carte de boss différente dans les fichiers texte

//structure contenant des information sur les différente maps du jeu, elle garde le numéro de cette carte dans la liste de correspondance avec les fichier texte, le booleen loadStatus si cette carte est dans une des variables globales Map current, previous ou next, le booleen ennemi s'il faut charger les ennemis, les Directions Next et previous sont des enum pour faire correspondre, dans l'algorithme de selection aléatoire des cartes du niveau, les entrees et sorties de chaque carte.   
struct selectionMap{
	int s;
	bool loadStatus;
	bool ennemi;//est-ce que les ennemis doivent être chargé
	Direction Next;
	Direction previous;
};
typedef struct selectionMap SelectionMap;

//Structure qui gardera la sélection des cartes du niveau dans l'ordre du tableau Nmap, garde aussi le nombre de carte qui compose le Niveau et le numero dans le tableau Nmap des cartes de CurrentMap, nextMap et previousMap 
struct tabNiveau{
	SelectionMap* Nmap;
	int nombreMap;
	int current;//le numéro dans le tableau de la map qui est chargée dans currentMap
	int next;  //le numéro dans le tableau de la map qui est chargée dans nextMap
	int previous;//le numéro dans le tableau de la map qui est chargée dans previousMap
};
typedef struct tabNiveau TabNiveau;

//Structure des cartes du jeu, dans cette version elle font toujours 64x64 caractères qui sont enregistré dans le double pointeur de char (char**) c. La structure garde aussi la taille en x et y de la map dans une structure Coordonnee taille. le booleen previous indique si la carte en enregistré dans previousMap
struct map{
	char** c;
	Coordonnee taille;
	bool previous; //si previous true sinon false
};
typedef struct map Map;

//variable globale currentMap, next Map et previousMap qui garde en mémoire la Map centrale ou se situe le jeu, la prochaine map (nextMap) et la précédente (previousMap) du niveau. seul trois carte maximum sont gardé en mémoire à la fois parmis les cartes du niveau.
Map currentMap;

Map nextMap;

Map previousMap;

//niveauA est la variable globale dans laquel on garde la selection du niveau en cours, qui a été créé aléatoirement au lancement de la partie. elle garde la succession des cartes, le nombres, et le numero dans le tableau de SelectionMap de la progression (current, next et previous)
TabNiveau niveauA; // tableau des niveaux aléatoirement choisis

/*PRE:cette fonction prend en argument un nombre entier
  POST:cette fonction renvoie un pointeur de char qui correspond à la chaîne de caractère représentant l'entier rentrer en argument, cette fonction utilise une allocation de mémoire dynamique pour créer la chaîne de caractère il faut donc libérer la chaîne de caractère qui en provient après son utilisation */
char* int_vers_char(int nombre);
/*PRE:cette fonction prend en argument un entier select qui correspond au numero du fichier que l'on veut charger et un pointeur de char* qui est une chaîne de caractère que l'on veut récupérer après le traitement de la fonction, en entrée la chaîne sera toujours vide {"\0"}; 
  POST:cette fonction va former le nom du fichier qui doit être charger selon le format qui est utilisé par le programme (map#.txt,mapPreBoss#.txt,mapBoss#.txt)*/
void map_select(int select,char* nom);
/*PRE:cette fonction prend en entree le numero de la carte qui doit être chargé (int select), et dans les pointeurs Direction entreeN  et sortieN on renverra le résultat de la fonction (cette enumeration est utilisé pour faire correspondre la sortie et l'entree de chaque carte) on utilise l'enum Direction, car dans les entree sortie on a défini 5 type d'ouverture (0 correspond à l'ouverture centrale normale, 1 à l'ouverture normale à droite, 3 ouverture normale à gauche, type 2 ouverture encore non-utilisé pourrait-être plus large ou plus étroit, 4 pas d'ouverture)
  POST:cette fonction va donc aller charger le header (1er ligne du fichier .txt) de la map correspondante à select et chercher les type d'ouverture représenté par une valeur d'enum Direction de la sortie et de l'entree de la carte*/
void Entree_sortie_Map( int select, Direction* entreeN, Direction* sortieN);
/*PRE:cette fonction prend en entree un entier (nombreMap)correspondant au nombre de map que doit contenir le niveau. Remarque: le niveau doit au moins faire 3 carte donc nombreMap>2
  POST:cette fonction va initialiser les Map variable globale currentMap, nextMap et previousMap à zero faire l'allocation dynamique de la taille du niveau avec l'entier nombreMap, lancer le choix de map aléatoire, remettre le score à zero et le niveau current à zero pour que ce soit bien le début du niveau*/
void preparation_niveau(int nombreMap);
/*PRE:cette fonction ne prend aucun argument en entree, car elle fonctionne uniquement avec des variables globales 
  POST:cette fonction va effectué une initialisation de la partie en chargeant les première cartes du jeu que la fonction retrouve dans niveauA.Nmap (le tableau de SelectionMap des cartes du niveau), initialise la variable booléene ennemi de toutes les cartes, charge les ennemis ce ces deux cartes, initialise la camera du jeu (variable globale camera)*/
void loadMaps(void);
/*PRE:cette fonction prend en argument les entiers tMapX et tMapY qui corresponde à la taille en X et Y de la carte qui aura été préalablement calculée, l'argument niveauA qui contient toute les cartes du niveau, et l'int select correspond au numero dans le tableau SelectionMap de la carte qui doit être chargé (le numero de la carte sera donc dans niveauA->Nmap[select].s)
  POST:cette fonction charge dans nextMap, previousMap, ou currentMap la carte (niveauA->Nmap[select].s)*/
void loadMap(int tMapX, int tMapy,TabNiveau* niveauA, int select);
/*PRE:cette fonction prend en argument le numero dans le tableau SelectionMap de la carte qui doit être chargé dans l'int select
  POST:cette fonction prépare le chargement de la prochaine carte avec les ennemis elle fera appele aux fonction loadMap, loadEnnemi et tailleMap*/
void loadNext(int select);
/*PRE:cette fonction prend en argument des pointeur d'int tMapY et tMapX qui seront utilisés pour le retour de la valeur de la taille en y et en x de la carte, niveauA est la structure du niveau, int est le numero de la carte à chargé dans le tableau niveauA.Nmap
  POST:cette fonction va renvoyer la taille de la ma dans les pointeur tMapX et tMapY mais aussi le contenu du header pour l'entree et la sortie dans niveauA.Nmap[select].previous ou niveauA.Nmap[select].Next*/
void tailleMap(int* tMapX,int* tMapY,TabNiveau niveauA, int select);
/*PRE:cette fonction ne prend rien en argument les informations sont inscritent dans niveauA (la variable globale)
  POST:cette fonction va donc chercher aléatoirement des cartes et vérifier la correspondance de l'ouverture de la carte, à potentiellement ajouter au niveau, à la précédente. si le test est bon le numero est ajouté à niveauA la variable globale, sinon on retest une au carte aléatoire. le format du niveau aura quand même des parties fixe la carte initiale sera toujours map0.txt, après on aura une sélection de carte aléatoire jusqu'à l'avant dernière carte du niveau qui fera correspondre la sortie de l'antepenultième carte avec la carte boss choisie aléatoirement. Remarque la carte boss aura toujours un type d'entree de valeur 0
  Le tout sera enregistré dans la variable globale niveauA*/
void choix_map_aleatoire(void);
#include "joueur.h"
#include "ennemi.h"
/*PRE:cette fonction cette fonction prend en argument le numero de la carte dans le tableau de carte du niveau niveauA.Nmap
  POST:cette fonction va allez charger la position (x;y) initial du joueur et initialiser les variables de la structure du joueur*/
Joueur loadJoueur(int select);
/*PRE:cette fonction cette fonction prend en argument le numero de la carte dans le tableau de carte du niveau niveauA.Nmap
  POST:cette fonction va juste allez charger la position (x;y) initial du joueur*/
Coordonnee load_respawn_Joueur(int select);
/*PRE:cette fonction prend en argument l'entier select qui correspond au numero de la carte dans le tableau de carte du niveau niveauA.Nmap, et la liste chainee des ennemis
  POST:cette fonction va allez charger dans la liste chainee des ennemi liste (variable globale déclaré dans ennemi.h) les ennemis présent dans la carte*/
void loadEnnemi(ListeEnnemi* liste, int select);
/*PRE:cette fonction prend en argument une structure Map en pointeur
  POST:cette fonction initialise les valeurs de la structure (char** c=NULL, Coordonnee taille.x et taille.y =0 et bool previous=false)*/
void initialisation_Map(Map* initMap);
#endif
