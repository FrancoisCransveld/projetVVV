#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "tirs.h"
#include "LoadMaps.h"
#include "interface.h"

ListeTirs* creer_liste_tirs(void){
  
	printf("creer liste tirs\n");
	ListeTirs* listeT=malloc(sizeof(ListeTirs));	//allocation dynamique de la liste chaînée de tirs
	
	ElementTirs* tirs=malloc(sizeof(ElementTirs));//allocation dynamique d'un élément tirs de la liste
	
	if(listeT==NULL||tirs==NULL){	//si une des allocations a échouées, une des pointeurs est égale à NULL et on sort du programme avec exit 
		exit(EXIT_FAILURE);
	}
		
	tirs->t.dir=4;
	tirs->t.pos.x=0;
	tirs->t.pos.y=0;		
	tirs->t.t=rien;
	tirs->suivant=NULL;		//initialisation des variables et des pointeurs de la liste chaînée et du premier élément 
  	tirs->precedent=NULL;		//Remarque on considère qu'il n'y a néanmoins pas d'élément dans la liste, en effet on indique quand même que listeT->nombre=0
  	tirs->t.distanceMax=0;
	listeT->premier=tirs;
  	listeT->dernier=tirs;
	listeT->nombre=0;
	
	return (listeT);	//on renvoie l'adresse de cette liste allouée dynamiquement
};


void tirs(ListeTirs* listeT, Coordonnee pos, TypeTirs t, Direction dir){
	
	ElementTirs* actuel=listeT->dernier;	//On récupère le dernier élément de la liste car c'est à lui que l'on va lié notre nouvelle élément
	if(listeT->nombre>0){			//il existe deux cas de figure soit on a déjà des éléments, donc listeT->nombre>0
		ElementTirs* nouveau=malloc(sizeof(ElementTirs));//on fait l'allocation de mémoire du nouvelle élément à ajouter à la liste
		nouveau->t.pos=pos;
		nouveau->t.pos.x*=2;		
		nouveau->t.pos.y*=2;		//On donne au nouvelle élément les valeurs qui sont passé en argument de la fonction
		nouveau->t.t=t;
		switch (nouveau->t.t){		//La distance max est initialisé en fonction du type de tirs de l'élément passé en argument
			case 0:
				nouveau->t.distanceMax=40;
				break;
			case 1:
				nouveau->t.distanceMax=30;
				break;
			case 2:
				nouveau->t.distanceMax=20;
				break;
			case 3:
				nouveau->t.distanceMax=0;
				break;
		}
		nouveau->t.dir=dir;		
		nouveau->suivant=NULL;		//le pointeur du nouveau tirs vers suivant est égale à NULL vu que c'est lui le dernier élément
		actuel->suivant=nouveau;	//le pointeur d'actuel vers l'élément suivant, pointe sur le pointeur nouveau
		nouveau->precedent=actuel;	//le pointeur du nouveau tirs vers le precedent, pointe sur l'ancien dernier élément qui se trouve dans le pointeur actuel
		listeT->nombre++;		//on incrémente le nombre d'élément de cette liste
		listeT->dernier=nouveau;	//on détermine que le dernier élément de cette liste est à l'adresse du nouvelle élément
	}
	else if(listeT->nombre==0){		//soit il n'existe pas encore d'élément dans la liste chaînée, donc listeT->nombre est égale à 0
		ElementTirs* nouveau=malloc(sizeof(ElementTirs));//on fait l'allocation de mémoire du nouvelle élément à ajouter à la liste
		nouveau->t.pos=pos;
		nouveau->t.pos.x*=2;
		nouveau->t.pos.y*=2;		//On donne au nouvelle élément les valeurs qui sont passé en argument de la fonction
		nouveau->t.t=t;
		switch (nouveau->t.t){		//La distance max est initialisé en fonction du type de tirs de l'élément passé en argument
			case 0:
				nouveau->t.distanceMax=40;
				break;
			case 1:
				nouveau->t.distanceMax=30;
				break;
			case 2:
				nouveau->t.distanceMax=20;
				break;
			case 3:
				nouveau->t.distanceMax=0;
				break;
		}
		nouveau->t.dir=dir;		
		nouveau->suivant=NULL;		//le pointeur du nouveau tirs vers suivant est égale à NULL vu que c'est lui le dernier élément
		nouveau->precedent=NULL;	//le pointeur du nouveau tirs vers precedent est égale à NULL vu que c'est le seul élément
		listeT->nombre++;		//on incrémente le nombre d'élément de cette liste
		listeT->dernier=nouveau;	//on détermine que le dernier élément de cette liste est à l'adresse du nouvelle élément
		listeT->premier=nouveau;	//on détermine que le premier élément de cette liste est également à l'adresse du nouvelle élément vu que c'est le seul
	}
	else{
		printf("ce n'est pas un tirs\n");
	}
	
};

void modifier_tirs(ListeTirs* listeT, int numero, Coordonnee pos, TypeTirs t,Direction dir){

	int i=0;				//compteur pour se retrouver dans le parcours de la liste
	int decalage=numero;			//decalage sera le nombre de fois que devra être effectué le saut d'un élément vers son suivant ou précédent selon ce qui sera calculé
	bool SensCroissant=true;		//booleen qui détermine le sens dans lequel on parcours la liste (en passant par actuel->suivant SensCroissant=true, 
						//en passante par actuel->precedent SensCroissant=false)
	ElementTirs* actuel=NULL;		//On déclare le pointeur de l'élément actuel, mais on attend de vérifier par quelle coté de la 
						//liste chaînée on commence (premier ou dernier)
	if(numero<listeT->nombre){		//on vérifie que le numero de l'élément dans la liste est bien compris dans les limites de celle-ci
		if(numero<listeT->nombre/2){	//si numero est plus petit que la moitié entière de liste->nombre
			actuel=listeT->premier;	//on commence par le premier et SensCroissant rest à true
		}
		else{				//sinon 
			actuel=listeT->dernier;
			SensCroissant=false;		//on commence par le dernier élément de la liste et le booleen SensCroissant passe à false
			decalage=listeT->nombre-numero-1;// decalage est adapté pour que l'on tombe bien sur l'élément depuis le dernier en autant de saut precedent depuis actuel
							  // que nécessaire 
		}

			while(i<decalage){	//boucle tant que i est plus petit que decalage
				if(SensCroissant){
					actuel=actuel->suivant;		
				}					//on parcours la liste chaînée via les pointeur d'élément suivant ou précédent, decalage nombre de fois.
				else{					
					actuel=actuel->precedent;
				}
				i++;		//i tiens le compte du nombre de saut vers precedent ou suivant (autrement dis le décalage par rapport au premier ou au dernier) 
			}
		actuel->t.t=t;
		actuel->t.pos=pos;
		actuel->t.pos.x=actuel->t.pos.x*2;	//ici on donne à l'élément trouvé les valeurs passée en argument de la fonction
		actuel->t.pos.y=actuel->t.pos.y*2;
		actuel->t.dir=dir;
		switch (actuel->t.t){
			case 0:
				actuel->t.distanceMax=40;
				break;
			case 1:
				actuel->t.distanceMax=30;
				break;
			case 2:
				actuel->t.distanceMax=20;
				break;
			case 3:
				actuel->t.distanceMax=0;
				break;
		}
	}
	if(listeT->nombre==0){		//condition pour gérer la modification du premier élément de la liste suite à tirs créer dans créer liste sans pour autant incrémenter le nombre d'élément de la liste
		listeT->nombre=1;
	}
};

void supprimer_tirs_numero(ListeTirs* listeT, int numero){
	
	if(listeT==NULL){		//si la liste est vide et que l'on tente de supprimer un élément on sort de la fonction
		exit(EXIT_FAILURE);
	}
	
	ElementTirs* precedent=NULL;		//pointeur d'ElementTirs vers precedent tampon pour la suite du programme et raccomoder la chaîne	
	ElementTirs* suivant=NULL;		//pointeur d'ElementTirs vers suivant tampon pour la suite du programme et raccomoder la chaîne	
	
	int i=0;				//
	int decalage=numero;			//
	bool SensCroissant=true;		//
	ElementTirs* actuel=NULL;		//On retrouve le même algorithme de parcours de la liste chaînée pour retrouver l'élément demandé en argument (int numero) que pour la
						//fonction précédente modifier tirs
	if(listeT->premier!=NULL){
		if(numero<listeT->nombre){
			
			if(numero<listeT->nombre/2){
			
				actuel=listeT->premier;
			}
			else{
			
				actuel=listeT->dernier;
				SensCroissant=false;
				decalage=listeT->nombre-numero-1;
			}

				while(i<decalage){
				
					if(SensCroissant){
						actuel=actuel->suivant;
					}
					else{
						actuel=actuel->precedent;
					}
					i++;
				}			//fin de l'algorithme de recherche de l'élément (int numero) de la liste
				
			precedent=actuel->precedent;	//on récupère l'adresse du précédent élément de actuel dans precedent
			suivant=actuel->suivant;	//on récupère l'adresse du suivant élément de actuel dans suivant
			
			if(precedent==NULL&&suivant==NULL){	//s'il sont tous les deux NULL, c'est qu'on a qu'un seul élément
				
				listeT->premier=NULL;		//la liste ne pointera plus vers aucun premier élément, la liste sera vide en sortie de la fonction
				listeT->dernier=NULL;		//la liste ne pointera plus vers aucun dernier élément, la liste sera vide en sortie de la fonction
			}
			else {
				if(precedent==NULL){		//si seulement precedent est NULL, on est sur le premier élément de la liste 
					suivant->precedent=NULL;	//le pointeur de l'élément suivant precedent sera vide
					listeT->premier=actuel->suivant;//et suivant ou actuel->suivant devient le premier élément de la liste
				}
				else if(suivant==NULL){	//si seulement suivant est NULL, on est sur le dernier élément de la liste 
					precedent->suivant=NULL;		//le pointeur de l'élément precedent suivant sera vide
					listeT->dernier=actuel->precedent;	//et precedent ou actuel->precedent devient le dernier élément de la liste
				}
				else{				//sinon on se trouve au millieu de la liste chaînée
					precedent->suivant=actuel->suivant;	//on rechaîne l'élément suivant de precedent avec l'element suivant ou actuel->suivant
					suivant->precedent=actuel->precedent;	//on rechaîne l'élément precedant de suivant avec l'élément précédent ou actuel->precedent
				}
				
				
				
			}
			printf("suprimer tirs %d adresse %hx nombre%d\n",numero,actuel,listeT->nombre);
			free(actuel);		//on libère l'élément actuel qui n'est plus liée a personne 
			listeT->nombre--;	// on décrémente le nombre d'élément de la liste chainée
			
		}
	}
};

TypeTirs degat_tirs(ListeTirs* listeT, int numero){

	int i=0;				//On retrouve le même algorithme de parcours de la liste chaînée pour retrouver l'élément demandé en argument (int numero) que pour la
						//fonction précédente modifier tirs
	int decalage=numero;
	bool SensCroissant=true;
	ElementTirs* actuel=NULL;
	if(numero<listeT->nombre){
		if(numero<listeT->nombre/2){
			actuel=listeT->premier;
		}
		else{
			actuel=listeT->dernier;
			SensCroissant=false;
			decalage=listeT->nombre-numero-1;
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
	}				//fin de l'algorithme de positionnement dans la liste
	return (actuel->t.t);		//on renvoie la valeur de l'enumeration TypeTirs de l'element actuel
};

void modifier_pos_tirs(ListeTirs* listeT, Coordonnee variation){
	int i=0;		//compteur qui va parcourir la liste
	
	ElementTirs* actuel=listeT->premier;	//déclaration d'un pointeur actuel vers le premier élément de la liste chainée
	int nombreMax=listeT->nombre;		//déclaration d'un entier nombreMax qui est initialisé au nombre d'élément de la liste chainée
	for(i=0;i<nombreMax;i++){		//on parcours toute la liste dans la boucle for
	
		actuel->t.pos.y+=variation.y;	//on modifie la position de tous les tirs de la variation donnée en argument d'entré
		actuel=actuel->suivant;	//on passe à l'élément suivant
	}
	supprimer_tirs_hors_portee(listeT);	// on supprime les éléments qui après cette manipulation se trouve trop loin
};


void supprimer_tirs_hors_portee(ListeTirs* listeT){
	ElementTirs* actuel=listeT->premier;	//déclaration d'un pointeur actuel vers le premier élément de la liste chainée
	int nombreMax=listeT->nombre;		//déclaration d'un entier nombreMax qui est initialisé au nombre d'élément de la liste chainée
	for(int i=0;i<nombreMax;i++){		//on parcours toute la liste dans la boucle for, et on déclare dans la boucle l'entier i qui sert de compteur des itérations de la boucle
		if(actuel->t.pos.y>camera.y+(CAM_RANGE*4)||actuel->t.pos.y<camera.y-(CAM_RANGE*4)){	//condition qui compare la position du tirs par rapport à la position de la camera
		
			supprimer_tirs_numero(listeT, i);	//si la condition est remplie c'est que le tirs est trop loin donc on le supprime
		}
		else{
		actuel=actuel->suivant;			//sinon on passe à l'élément suivant
		}
	}

};

void deplacement_tirs(ListeTirs* listeT){
	
	if(listeT->premier!=NULL){		//vérification que la liste possède bien un élément
		ElementTirs* actuel=listeT->premier;	//déclaration d'un pointeur vers un ElementTirs qui est initialisé à l'adresse du premier élément
		int* registre=NULL;			// déclaration d'un tableau d'int qui sera géré dynamiquement et qui contiendra tours les éléments 
							//qui devront être éliminé après les modifications apporté au variable de chaque élément
		int nombreRegistre=0;			//déclaration du compteur des éléments de ce registre initialement égale à 0 
		for(int i=0;i<listeT->nombre;i++){	//parcours de toute la liste dans la boucle for, et on déclare dans la boucle l'entier i qui sert de compteur des itérations de la boucle
			if(actuel->t.distanceMax>0){	//vérifiaction que l'élément n'est pas arrivé en bout de course
				switch(actuel->t.dir){	//switch sur l'enum Direction du tirs ne train d'être traité pour savoir dans quelle sens il faut le déplacer
					case Up:
						actuel->t.pos.y--;
						break;
					case Right:
						actuel->t.pos.x++;
						break;
					case Down:
						actuel->t.pos.y++;
						break;
					case Left:
						actuel->t.pos.x--;
						break;
					case fin:
						break;
				}
				actuel->t.distanceMax--;	//on décrémente la distance maximale
				actuel=actuel->suivant;	//on passe au suivant
			}
			else{		// ici l'élément en train d'être traité est arrivé à sa distance maximale on va donc l'enregistré dans le registre des éléments à éliminé après
				if(registre==NULL){
					registre=malloc(sizeof(int*));

				}
				else{
					registre=realloc(registre, sizeof(int*)*nombreRegistre+1);
	
				}
				*(registre+nombreRegistre)=i;
				nombreRegistre++;	
				actuel->t.distanceMax--;
				actuel=actuel->suivant;
				
			}
		
		}
		for(int n=0;n<nombreRegistre;n++){	
			printf("%d ",*(registre+n));
		}
		for(int n=nombreRegistre;n>0;n--){	//On effectue la suppresion des éléments du registre, on parcours les éléments a supprimer dans le sens inverse car les éléments lorqu'ils sont supprimés modifie la position de tous les éléments qui les suits ce qui fait supprimer les mauvais éléments par le registre dans le sens croissant après la première suppression, mais pas dans l'autre sens les éléments supérieur supprimé ne changeant pas la position des éléments les précédents dans l'ordre de la liste
			afficher_liste_tirs(listeT);
			supprimer_tirs_numero(listeT,*(registre+(n-1)));
			afficher_liste_tirs(listeT);
		}
		free(registre);	//on libère le registre
	}
};

Coordonnee pos_tirs(ListeTirs* listeT,int numero){

	Coordonnee position;		//déclaration de la Coordonnee position qui sera renvoyé en fin de fonction
	position.x=-200;		//initialisation de position x et y hors de toute carte
	position.y=-200;
	if(listeT->premier!=NULL){	//on vérifie que la liste possède un élément
					
					//On retrouve le même algorithme de parcours de la liste chaînée pour retrouver l'élément demandé en argument (int numero) que pour la
					//fonction précédente modifier tirs
	int i=0;
	int decalage=numero;
	bool SensCroissant=true;
	ElementTirs* actuel=NULL;
	if(numero<listeT->nombre){
		if(numero<listeT->nombre/2){
			actuel=listeT->premier;
		}
		else{
			actuel=listeT->dernier;
			SensCroissant=false;
			decalage=listeT->nombre-numero-1;
		}

		while(i<decalage){
			if(SensCroissant){
				actuel=actuel->suivant;
			}
			else{
				actuel=actuel->precedent;
			}
			i++;
		}		//fin de la recherche de l'element souhaité
		position=actuel->t.pos;	//on récupère sa Coordonnee dans position
	}
	
	
	}
	return(position);	//on renvoie Coordonnee
};

void afficher_liste_tirs(ListeTirs* listeT){
	if(listeT->premier!=NULL){	
		int i=0;		//déclaration de i compteur destiné a parcourir toute la liste dans la boucle while qui suit pour afficher des informations sur chaque élément de la liste dans la console
		printf("---Liste tirs %d: ---\n",listeT->nombre);
		ElementTirs* actuel=listeT->premier;
		while(i<listeT->nombre){
			printf("numero : %d adresse tirs: %hx tirs type : %d pos : (x=%d;y=%d) dir:%d portee: %d\n",i,actuel,actuel->t.t,actuel->t.pos.x,actuel->t.pos.y,actuel->t.dir,actuel->t.distanceMax);
			printf("actuel=actuel->suivant;\n");
			actuel=actuel->suivant;
			printf("i=%d;\n",i);
			i++;
		}
		printf("--------fin liste------\n");
	}
};			
