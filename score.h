#ifndef _SCORE_H_
#define _SCORE_H_

#include "jeu.h"
#include "ennemi.h"

struct scoreJ{
	char nom[MAX_NOM];
	int sco;
	int place;
};
typedef struct scoreJ ScoreJ;

typedef struct elementScore ElementScore;
struct elementScore{
	ScoreJ element;
	ElementScore* suivant;
};

typedef struct listeScore ListeScore;
struct listeScore{
	ElementScore* premier;
	int nombre;
};

ListeScore* listeAffichage;
char nomEncode[MAX_NOM];
int nombreLettre;

void inscription_score();
ListeScore* creer_liste_score(void);
void nouvel_elementScore(ListeScore* listeSc, char nom[], int EntreeScore,int place);
void suprimer_liste_elementScore(ListeScore* listeSc);
void suprimer_elementScore_n(ListeScore* listeSc,int numero);
void modifier_elementScore(ListeScore* listeSc,int numero,int EntreeScore,int place,char* nom);
int transcr_char_int(char valeur);
bool encodage_nom(char* nom,int* nombreLettre);
int recuperer_tableau_score(ListeScore* listeSc);
int inserer_nouveau_score_selon_classement(ListeScore* listeSc,ScoreJ* Nouveau);
void inscrire_tableau_score(ListeScore* listeSc);
void afficher_listeSc(ListeScore* listeSc);

#endif



