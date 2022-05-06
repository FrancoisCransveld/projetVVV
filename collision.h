#ifndef _ENNEMI_H_
#define _ENNEMI_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jeu.h"
#include "ennemi.h"
#include "joueur.h"
#include "tirs.h"

bool collision_tirs_ennemi(int ennemi,int tirs);
bool collision_joueur_ennemi(int ennemi);
bool collisionEnnemiJoueur();
Coordonnee HitBoxEnnemi(int ennemi,Coordonnee* EnnemiActuel);
Coordonnee hit_box_joueur(Direction dir);
#endif
