#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jeu.h"
#include "LoadMaps.h"
#include "joueur.h"
#include "ennemi.h"
#include "tirs.h"
#include "collision.h"

Coordonnee  HitBoxEnnemi_collision_decors(TypeEnnemi type,Direction dir,Coordonnee limiteHG,bool* DIFFERENTMAP){
	
	int longueur;	//variable entière qui récupérera la longueur du type d'ennemi
	int largeur;	//variable entière qui récupérera la largeur du type d'ennemi
	Coordonnee Cadre;//Coordonnee qui permettra d'agencer la longueur et la largeur selon la direction de l'ennemi
	*DIFFERENTMAP=false;	//On initialise le booleeb à false, a priori on se trouve sur une seul carte, les cas limites sont plus rare
	switch (type){	//switch pour faire correspondre la longueur et la largeur avec le type d'ennemi
		case voiture:
				longueur=2;
				largeur=1;
				break;
		case moto:
				longueur=1;
				largeur=0;
				break;
		case camion:
				longueur=4;
				largeur=2;
				break;
		case SUV:
				longueur=3;
				largeur=2;
				break;
		case vide:
				longueur=0;
				largeur=0;
				break;
		default:
				longueur=0;
				largeur=0;
				break;
	}
	switch (dir){	//switch pour que la longueur et la largeur soient cohérente par rapport à la direction de l'ennemi dans cadre on considère que la composante y de cette
			// struct coordonnee représente le montant vertical du cadre et x l'horizontale du cadre
		case Up:
			Cadre.x=largeur;
			Cadre.y=longueur;
			break;
		case Right:
			Cadre.y=largeur;
			Cadre.x=longueur;
			break;
		case Down:
			Cadre.x=largeur;
			Cadre.y=longueur;
			break;
		case Left:
			Cadre.y=largeur;
			Cadre.x=longueur;
			break;
		case fin:
			Cadre.x=largeur;
			Cadre.y=longueur;
			break;
		default:
			Cadre.x=largeur;
			Cadre.y=longueur;
			break;
	}
	Coordonnee LimiteEnnemi;	//La coordonnee limiteEnnemi correspondra au limite de la hitBox inférieure et droite
	LimiteEnnemi.x=((limiteHG.x)+Cadre.x);	//initialisation de la variable LimiteEnnemi qui est à la position initiale en x de l'ennemi + le montant horizontale du cadre 
							//de la hitBox	
	LimiteEnnemi.y=((limiteHG.y)+Cadre.y);	//initialisation de la variable LimiteEnnemi qui est à la position initiale en y de l'ennemi + le montant vertical du cadre 
							//de la hitBox	
	if(LimiteEnnemi.x>63){
		LimiteEnnemi.x=63;
	}
	else if(LimiteEnnemi.x<0){
		LimiteEnnemi.x=0;
	}
	if(LimiteEnnemi.y<0){
		LimiteEnnemi.y+=64;		//Remarque ici on vérifie que ces limites du cadre ne dépasse pas la taille des tableaux de char** car on devra allez chercher 
						//le caractère à la position de cette coordonnee dans le tableau. si cette valeur est trop grande on fera un segmentation fault
		*DIFFERENTMAP=true;		//On remanie cette valeur pour qu'elle soie comprise dans les limites de ce tableau et on change le booleen DIFFERENTMAP pour
						// signifier qu'il faudra faire la recherche de collision sur une autre map que la map utilisé pour le coin supérieur gauche 
						//de la hitBox
	}
	else if(LimiteEnnemi.y>63){
		LimiteEnnemi.y-=64;
		*DIFFERENTMAP=true;
	}
	return (LimiteEnnemi);
}
Coordonnee HitBoxEnnemi(int ennemi,Coordonnee* EnnemiActuel){
	
	printf("PreCoordonneeEnnemi %d\n", ennemi);
	*EnnemiActuel=pos_Ennemi(liste,ennemi);	//EnnemiActuel récupère la coordonnee de base de l'ennemi de numero (int ennemi) de la liste
	Direction ennemiDir;				//On declare une variable enumeration Direction
	TypeEnnemi ennemiType;				//On declare une variable enumeration TypeEnnemi
	if(liste->premier!=NULL){
		int i=0;
		int decalage=ennemi;
		bool SensCroissant=true;
		ElementEnnemi* actuel=NULL;
		if(ennemi<liste->nombre){
			if(ennemi<liste->nombre/2){
				actuel=liste->premier;
			}
			else{
				actuel=liste->dernier;			//Recherche de l'ennemi actuel grâce à son numero contenu dans (int ennemi)
				SensCroissant=false;
				decalage=liste->nombre-ennemi-1;
			}

			while(i<decalage){
				if(SensCroissant){
					actuel=actuel->suivant;
				}
				else{
					actuel=actuel->precedent;
				}
				i++;
			}
		}
		ennemiType=actuel->e.type;	//récupération du type de l'ennemi actuel
		ennemiDir=actuel->e.dir;	//récupération de la direction de l'ennemi actuel
	}
	int longueur;	//variable entière qui récupérera la longueur du type d'ennemi
	int largeur;	//variable entière qui récupérera la largeur du type d'ennemi
	Coordonnee Cadre;//Coordonnee qui permettra d'agencer la longueur et la largeur selon la direction de l'ennemi
	switch (ennemiType){	//switch pour faire correspondre la longueur et la largeur avec le type d'ennemi
		case voiture:
				longueur=5;
				largeur=3;
				break;
		case moto:
				longueur=3;
				largeur=1;
				break;
		case camion:
				longueur=9;
				largeur=4;
				break;
		case SUV:
				longueur=6;
				largeur=4;
				break;
		case vide:
				longueur=0;
				largeur=0;
				break;
		default:
				longueur=0;
				largeur=0;
				break;
	}
	switch (ennemiDir){//switch pour que la longueur et la largeur soient cohérente par rapport à la direction de l'ennemi dans cadre on considère que la composante y de cette
			// struct coordonnee représente le montant vertical du cadre et x l'horizontale du cadre
		case Up:
			Cadre.x=largeur;
			Cadre.y=longueur;
			break;
		case Right:
			Cadre.y=largeur;
			Cadre.x=longueur;
			break;
		case Down:
			Cadre.x=largeur;
			Cadre.y=longueur;
			break;
		case Left:
			Cadre.y=largeur;
			Cadre.x=longueur;
			break;
		case fin:
			Cadre.x=largeur;
			Cadre.y=longueur;
			break;
		default:
			Cadre.x=largeur;
			Cadre.y=longueur;
			break;
	}
	Coordonnee LimiteEnnemi;	//La coordonnee limiteEnnemi correspondra au limite de la hitBox inférieure et droite
	LimiteEnnemi.x=((EnnemiActuel->x*2)+Cadre.x);	//initialisation de la variable LimiteEnnemi qui est à la position initiale en x de l'ennemi actuel + le montant 
							//horizontale du cadre de la hitBox	
	LimiteEnnemi.y=((EnnemiActuel->y*2)+Cadre.y);	//initialisation de la variable LimiteEnnemi qui est à la position initiale en y de l'ennemi actuel + le montant 
							//vertical du cadre de la hitBox
							
							//Dans cette fonction la valeur de la limite inférieure droite est calculer en demi-case (donc de valeur doublée), 
							//mais pas la coordonnee d'EnnemiActuel
	return (LimiteEnnemi);
}

Coordonnee hit_box_joueur(Direction dir,Coordonnee* hitBoxHG){
	*hitBoxHG=j.pos;	//limite supérieur gauche de la hitBox de joueur (hitBoxHG) est égale à la position de joueur	
	hitBoxHG->x*=2;	// les valeurs sont exprimées en demi-case donc *2
	hitBoxHG->y*=2;
	Coordonnee hitBoxBD=j.pos;	//limite inférieure droite de la hitBox de joueur (hitBoxBD) est initialisé à la position de joueur
	hitBoxBD.x*=2;			//les valeurs sont exprimées en demi-case donc *2
	hitBoxBD.y*=2;
	switch(dir){
		case Up:
			hitBoxBD.x+=1;
			hitBoxBD.y+=3;
			break;
		case Right:
			hitBoxBD.x+=1;
			hitBoxBD.y+=1;
			hitBoxHG->x=hitBoxBD.x-3;
			break;
		case Down:
			hitBoxBD.y+=1;		//Valeur de hitBoxBD modifiée en fonction de la direction de j, de plus, contrairement au ennemi la position du 
						//joueur ,retenue dans j.pos, ne correspond pas toujours à la limite supérieur gauche de la hitBox selon la direction 
						//regardé par le joueur. vers la droite elle se situe à x-3(demi-case) et vers le bas à y-3(demi-case)
			hitBoxBD.x+=1;
			hitBoxHG->y=hitBoxBD.y-3;
			break;
		case Left:
			hitBoxBD.x+=3;
			hitBoxBD.y+=1;
			break;
		case fin:
			hitBoxBD.x=300;
			hitBoxBD.y=300;
			break;
		default:
			hitBoxBD.x=300;
			hitBoxBD.y=300;
			break;
	}

	return hitBoxBD;
	
}
bool collision_ennemi_ennemi(int ennemi, int ennemi2){
	
	bool COLLISION=false;		//boolleen qui vaudra true s'il y a bien une collision entre les ennemis (ennemi et ennemi2) 
	Coordonnee EnnemiActuel;	//Coordonnee représentant la limite supérieur gauche de la hitBox de "ennemi"
	Coordonnee LimiteEnnemi=HitBoxEnnemi(ennemi,&EnnemiActuel);	//Coordonnee représentant la limite inférieure droite de la hitBox de "ennemi"
	Coordonnee Ennemi2Actuel;	//Coordonnee représentant la limite supérieur gauche de la hitBox de "ennemi2"
	Coordonnee LimiteEnnemi2=HitBoxEnnemi(ennemi2,&Ennemi2Actuel);//Coordonnee représentant la limite inférieure droite de la hitBox de "ennemi2"
	printf("coordonnee ennemi coin supérieur: (%d;%d) coin inférieur: (%d,%d),coordonnee ennemi2 coin supérieur: (%d;%d) coin inférieur: (%d,%d))\n",EnnemiActuel.x,EnnemiActuel.y,LimiteEnnemi.x,LimiteEnnemi.y,Ennemi2Actuel.x,Ennemi2Actuel.y,LimiteEnnemi2.x,LimiteEnnemi2.y);
	
	if((LimiteEnnemi2.y>=EnnemiActuel.y*2)&&(Ennemi2Actuel.y*2)<=(LimiteEnnemi.y)){ 
		
		if((Ennemi2Actuel.x*2<=(LimiteEnnemi.x))&&(LimiteEnnemi2.x>=(EnnemiActuel.x*2))){	//condition vérifiant que les limites des hitBox des deux ennemis se recoupent
		
			COLLISION=true;	//si les hitBox se recoupent COLLISION vaut true, on a bien une collision de ces ennemis
		}
	}
	
	return COLLISION;
}
bool collision_joueur_ennemi(int ennemi){
	
	bool COLLISION=false;		//boolleen qui vaudra true s'il y a bien une collision entre l'ennemi (ennemi) et le joueur(j) 
	Coordonnee EnnemiActuel;	//Coordonnee représentant la limite supérieur gauche de la hitBox de "ennemi"
	Coordonnee LimiteEnnemi=HitBoxEnnemi(ennemi,&EnnemiActuel);	//Coordonnee représentant la limite inférieure droite de la hitBox de "ennemi"
	Coordonnee HitBoxJoueurHG;	//Coordonnee représentant la limite supérieur gauche de la hitBox du joueur
	Coordonnee HitBoxJoueurBD=hit_box_joueur(j.dir,&HitBoxJoueurHG);	//Coordonnee représentant la limite inférieure droite de la hitBox du joueur
	printf("coordonnee ennemi coin supérieur: (%d;%d) coin inférieur: (%d,%d),j:(%d,%d)\n",EnnemiActuel.x,EnnemiActuel.y,LimiteEnnemi.x,LimiteEnnemi.y,j.pos.x,j.pos.y);
	
	if((HitBoxJoueurBD.y>=EnnemiActuel.y*2)&&(HitBoxJoueurHG.y)<=(LimiteEnnemi.y)){ 
													//condition vérifiant que les limites des hitBox des deux se recoupent
		if((HitBoxJoueurHG.x<=(LimiteEnnemi.x))&&(HitBoxJoueurBD.x>=(EnnemiActuel.x*2))){	
		
			COLLISION=true;	//si les hitBox se recoupent COLLISION vaut true, on a bien une collision avec l'ennemi (int ennemi)
		}
	}
	
	return COLLISION;
}
bool collision_ennemi_decor_limiteMap(Coordonnee limiteHG, Coordonnee limiteBD, Direction dir, char** MapCol,char** Maplimite){
	
	bool DEPLACEMENT=false;	//booleen qui vérifie si on doit bien effectuer le déplacement de l'ennemi
	switch (dir){			//vérification qui se fait en fonction de la direction de l'ennemi
		case 0:
			if(*(*(MapCol+limiteHG.y)+limiteHG.x)!='#'&&*(*(MapCol+limiteHG.y)+limiteBD.x)!='#'){	//les conditions vérifient que le caractère se trouvant dans la 
															//carte correspondante à la position de limite ne sont pas des 
															//bloqueur ('#' ou '!')

				DEPLACEMENT=true;		//sinon ça signifie que l'ennemi peut se déplacer vers cette direction
			}
			break;
		case 1:
			if(*(*(Maplimite+limiteBD.y)+limiteBD.x)!='#'&&*(*(MapCol+limiteHG.y)+limiteBD.x)!='#'){
				DEPLACEMENT=true;
			}
			break;
		case 2:
			if(*(*(Maplimite+limiteBD.y)+limiteBD.x)!='#'&&*(*(Maplimite+limiteBD.y)+limiteHG.x)!='#'){
				DEPLACEMENT=true;
			}
			break;
		case 3:
			if(*(*(MapCol+limiteHG.y)+limiteHG.x)!='#'&&*(*(Maplimite+limiteBD.y)+limiteHG.x)!='#'){
				DEPLACEMENT=true;
			}
			break;
		case 4:
			break;
	}
	return DEPLACEMENT;
}
bool collision_ennemi_decor(Coordonnee limiteHG, Coordonnee limiteBD, Direction dir, char** MapCol){
	
	bool DEPLACEMENT=false;	//booleen qui vérifie si on doit bien effectuer le déplacement de l'ennemi
	switch (dir){			//vérification qui se fait en fonction de la direction de l'ennemi
		case 0:
			if(*(*(MapCol+limiteHG.y)+limiteHG.x)!='#'&&*(*(MapCol+limiteHG.y)+limiteBD.x)!='#'){	//les conditions vérifient que le caractère se trouvant dans la 
															//carte correspondante à la position de limite ne sont pas des 
															//bloqueur ('#' ou '!'), ici plus simple car on sait que toute
															//les limites se trouvent dans la même carte
				DEPLACEMENT=true;
			}
			break;
		case 1:
			if(*(*(MapCol+limiteBD.y)+limiteBD.x)!='#'&&*(*(MapCol+limiteHG.y)+limiteBD.x)!='#'){
				DEPLACEMENT=true;
			}
			break;
		case 2:
			if(*(*(MapCol+limiteBD.y)+limiteBD.x)!='#'&&*(*(MapCol+limiteBD.y)+limiteHG.x)!='#'){
				DEPLACEMENT=true;
			}
			break;
		case 3:
			if(*(*(MapCol+limiteHG.y)+limiteHG.x)!='#'&&*(*(MapCol+limiteBD.y)+limiteHG.x)!='#'){
				DEPLACEMENT=true;
			}
			break;
		case 4:
			break;
	}
	return DEPLACEMENT;
}

bool collisionEnnemiJoueur(){
	bool collis=false;		//booleen qui gardera en méroire si dans le test en boucle de toutes les collisions entre ennemi et joueur il y a biens une collision
	for(int i=0;i<liste->nombre;i++){//boucle for qui parcours toute la liste des ennemis 
				
		if(collision_joueur_ennemi(i)){	//appel du test de collision ennemi (i) avec le joueur
			if(!j.invulnerable){		//si on a une collision et que le joueur n'est pas en invulnerabilité 
				j.hp--;		//j perd un hp
				j.invulnerable=true;	//et devient invulnerable pour un cycle (2 secondes)
				j.debutInvulnerabilite=true;
			}
				switch(dir_ennemi(liste,i)){
					case 0:		//le joueur est également repousé par l'ennemi de deux case dans la direction que regarde l'ennemi
						moveDown();
						moveDown();
						break;
					case 1:
						moveLeft();
						moveLeft();
						break;
					case 2:
						moveUp();
						moveUp();
						break;
					case 3:
						moveRight();
						moveRight();
						break;
					case 4:
						break;
				}
			collis=true;
			return collis;	//on retourne collision pour confirmer qu'on a bien eu une collision à la fonction appelante qui se trouve dans jeu et bloquera les ennemis
		}
	}
	return collis;
}
bool collisionJoueurEnnemi(){

	//même fonction que précédement mais sans les changement de variable de j
	bool collis=false;
	for(int i=0;i<liste->nombre;i++){
				
		if(collision_joueur_ennemi(i)){
			collis=true;
			return collis;
		}
	}
	return collis;
}



bool collision_tirs_ennemi(int ennemi,int tirs){
	
	bool COLLISION=false;	//booleen qui indique si on a une collision entre le tirs (int tirs) et l'ennemi (int ennemi)
	printf("PreCoordonneeEnnemi %d\n", ennemi);
	Coordonnee EnnemiActuel;	//Coordonnee représentant la limite supérieur gauche de la hitBox de "ennemi"
	printf("PreCoordonneeTirs %d\n", tirs);
	Coordonnee tirsActuel=pos_tirs(j.tirs,tirs);	//Coordonnee de tirs le tirs fait une demi-case de largeur et longueur donc sa hitBox correspondra à une seul Coordonnee
							// et adapter la hitBox de l'ennemi pour qu'elle soit exprimée en demi-case également (*2 les x et les y et +1 case en 
							//x et y pour la limite inférieur droite) . remarque ces calculs sont effectué par la fonction HitBoxEnnemi pour limiteEnnemi
							//mais pas pour EnnemiActuel
	
	Coordonnee LimiteEnnemi=HitBoxEnnemi(ennemi,&EnnemiActuel);
	
	printf("coordonnee ennemi coin supérieur: (%d;%d) coin inférieur: (%d,%d), tirs  (%d,%d)j:(%d,%d)\n",EnnemiActuel.x,EnnemiActuel.y,LimiteEnnemi.x,LimiteEnnemi.y,tirsActuel.x,tirsActuel.y,j.pos.x,j.pos.y);// condition vérifiant que la position du tirs se
														//trouve bien entre les limites de la hitBox de l'ennemi
	if(((EnnemiActuel.y*2)<=tirsActuel.y)&&((LimiteEnnemi.y)>=tirsActuel.y)){ 
		printf("condition y ok\n");
		if(((EnnemiActuel.x*2)<=tirsActuel.x)&&((LimiteEnnemi.x)>=tirsActuel.x)){
			printf("condition x ok\n");
			COLLISION=true;	//on a bien une collision alors COLLISION=true
		}
	}
	
	return COLLISION;
}
