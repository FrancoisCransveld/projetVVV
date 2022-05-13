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
#include "ennemi.h"
#include "LoadMaps.h"
#include "interface.h"
#include "collision.h"

ListeEnnemi* creer_liste(void){
  	char nom[MAX_NOM]={"Bot1"};	//nom initial du premier ennemi
  
	ListeEnnemi* liste=malloc(sizeof(ListeEnnemi));	//allocation dynamique de la liste chaînée d'ennemi
	
	ElementEnnemi* ennemi=malloc(sizeof(ElementEnnemi));  //allocation dynamique d'un élément ennemi de la liste
	
	if(liste==NULL||ennemi==NULL){	//si une des allocations a échouées, une des pointeurs est égale à NULL et on sort du programme avec exit 
		exit(EXIT_FAILURE);
	}
		
	ennemi->e.vie=0;
	ennemi->e.pos.x=0;
	ennemi->e.pos.y=0;
	ennemi->e.type=vide;
	ennemi->suivant=NULL;
  	ennemi->precedent=NULL;		//initialisation des variables et des pointeurs de la liste chaînée et du premier élément 
  	ennemi->e.attente=false;		//Remarque on considère qu'il n'y a néanmoins pas d'élément dans la liste, en effet on indique quand même que liste->nombre=0
  	ennemi->e.nom=malloc(sizeof(char*)*MAX_NOM);
	strcpy(ennemi->e.nom,nom);
	liste->premier=ennemi;
  	liste->dernier=ennemi;
	liste->nombre=0;
	
	return (liste);		//on renvoie l'adresse de cette liste allouée dynamiquement
};


void nouvel_ennemi(ListeEnnemi* liste, char* nom, int vie, Coordonnee pos, TypeEnnemi t){
	
	ElementEnnemi* actuel=liste->dernier;	//On récupère le dernier élément de la liste car c'est à lui que l'on va lié notre nouvelle élément
	if(liste->nombre>0){			//il existe deux cas de figure soit on a déjà des éléments, donc liste->nombre>0
		ElementEnnemi* nouveau=malloc(sizeof(ElementEnnemi));	//on fait l'allocation de mémoire du nouvelle élément à ajouter à la liste

		nouveau->e.vie=vie;
		nouveau->e.pos=pos;
		nouveau->e.type=t;
		nouveau->e.dir=4;		//On donne au nouvelle élément les valeurs qui sont passé en argument de la fonction
		nouveau->e.attente=true;
		nouveau->suivant=NULL;		//le pointeur du nouvelle ElementEnnemi vers suivant est égale à NULL vu que c'est lui le dernier élément
		actuel->suivant=nouveau;	//le pointeur d'actuel vers l'élément suivant, pointe sur le pointeur nouveau
		nouveau->precedent=actuel;	//le pointeur du nouvelle ElementEnnemi vers le precedent, pointe sur l'ancien dernier élément qui se trouve dans le pointeur actuel
		
		nouveau->e.nom=malloc(sizeof(char*)*MAX_NOM);
		
		strcpy(nouveau->e.nom,nom);

		liste->nombre++;		//on incrémente le nombre d'élément de cette liste
		liste->dernier=nouveau;	//on détermine que le dernier élément de cette liste est à l'adresse du nouvelle élément
	}
	else if(liste->nombre==0){		//soit il n'existe pas encore d'élément dans la liste chaînée, donc listeT->nombre est égale à 0
		ElementEnnemi* nouveau=malloc(sizeof(ElementEnnemi));	//on fait l'allocation de mémoire du nouvelle élément à ajouter à la liste

		nouveau->e.vie=vie;
		nouveau->e.pos=pos;
		nouveau->e.type=t;		//On donne au nouvelle élément les valeurs qui sont passé en argument de la fonction
		nouveau->e.dir=4;
		nouveau->e.attente=true;
		nouveau->suivant=NULL;		//le pointeur du nouvelle ennemi vers suivant est égale à NULL vu que c'est lui le dernier élément
		nouveau->precedent=NULL;	//le pointeur du nouvelle ennemi  vers precedent est égale à NULL vu que c'est le seul élément
		
		nouveau->e.nom=malloc(sizeof(char*)*MAX_NOM);
		
		strcpy(nouveau->e.nom,nom);

		liste->nombre++;		//on incrémente le nombre d'élément de cette liste
		liste->dernier=nouveau;	//on détermine que le dernier élément de cette liste est à l'adresse du nouvelle élément
		liste->premier=nouveau;	//on détermine que le premier élément de cette liste est également à l'adresse du nouvelle élément vu que c'est le seul
	}
	
};

void modifier_ennemi(ListeEnnemi* liste, int numero, char nom[], int vie, Coordonnee pos, TypeEnnemi t,bool a){
	int i=0;				//compteur pour se retrouver dans le parcours de la liste
	int decalage=numero;			//decalage sera le nombre de fois que devra être effectué le saut d'un élément vers son suivant ou précédent selon ce qui sera calculé
	bool SensCroissant=true;		//booleen qui détermine le sens dans lequel on parcours la liste (en passant par actuel->suivant SensCroissant=true, 
						//en passante par actuel->precedent SensCroissant=false)
	ElementEnnemi* actuel=NULL;		//On déclare le pointeur de l'élément actuel, mais on attend de vérifier par quelle coté de la 
						//liste chaînée on commence (premier ou dernier)
	if(numero<liste->nombre){		//on vérifie que le numero de l'élément dans la liste est bien compris dans les limites de celle-ci
		if(numero<liste->nombre/2){	//si numero est plus petit que la moitié entière de liste->nombre
			actuel=liste->premier;	//on commence par le premier et SensCroissant reste à true
		}
		else{					//sinon 
			actuel=liste->dernier;		//on commence par le dernier élément de la liste et le booleen SensCroissant passe à false
			SensCroissant=false;		// decalage est adapté pour que l'on tombe bien sur l'élément depuis le dernier en autant de saut precedent depuis actuel
			decalage=liste->nombre-numero-1; // que nécessaire 
		}

			while(i<decalage){		//boucle tant que i est plus petit que decalage
				if(SensCroissant){
					actuel=actuel->suivant;	
				}					//on parcours la liste chaînée via les pointeur d'élément suivant ou précédent, decalage nombre de fois.
				else{
					actuel=actuel->precedent;
				}
				i++;			//i tiens le compte du nombre de saut vers precedent ou suivant (autrement dis le décalage par rapport au premier ou au dernier) 
			}
		actuel->e.vie=vie;
		actuel->e.pos=pos;		//ici on donne à l'élément trouvé les valeurs passée en argument de la fonction
		actuel->e.type=t;
		actuel->e.attente=a;
		actuel->e.nom=malloc(sizeof(char*)*MAX_NOM);
		strcpy(actuel->e.nom,nom);
	}
};

void supprimer_ennemi_numero(ListeEnnemi* liste, int numero){
	
	if(liste==NULL){		//si la liste est vide et que l'on tente de supprimer un élément on sort de la fonction
		exit(EXIT_FAILURE);
	}
	int i=0;			//début du même algorithme de placement dans la liste que la fonction précédente modifier_ennemi();
	int decalage=numero;
	bool SensCroissant=true;
	if(liste->premier!=NULL){

		ElementEnnemi* actuel=NULL;
		ElementEnnemi* precedent=NULL;	//pointeur d'ElementEnnemi vers precedent tampon pour la suite du programme et raccomoder la chaîne	
		ElementEnnemi* suivant=NULL;		//pointeur d'ElementEnnemi vers suivant tampon pour la suite du programme et raccomoder la chaîne	
		
		if(numero<liste->nombre){
			if(numero<liste->nombre/2){
				actuel=liste->premier;
			}
			else{
				actuel=liste->dernier;
				SensCroissant=false;
				decalage=liste->nombre-numero-1;
			}

				while(i<decalage){
					if(SensCroissant){
						actuel=actuel->suivant;
					}
					else{
						actuel=actuel->precedent;
					}
					i++;
				}		//fin du placement dans la liste actuel est l'élément que nous voulions modifier (int numero)
			precedent=actuel->precedent;	//on récupère l'adresse du précédent élément de actuel dans precedent
			suivant=actuel->suivant;	//on récupère l'adresse du suivant élément de actuel dans suivant
			if(!actuel->e.attente){
				if(precedent==NULL&&suivant==NULL){	//s'il sont tous les deux NULL, c'est qu'on a qu'un seul élément
					char nom[5]={"vide"};
					actuel->e.vie=0;
					strcpy(actuel->e.nom,nom);
					actuel->e.pos.x=-64;
					actuel->e.pos.y=-64;
					actuel->e.type=vide;
					liste->premier=NULL;		//la liste ne pointera plus vers aucun premier élément, la liste sera vide en sortie de la fonction
				 	liste->dernier=NULL;		//la liste ne pointera plus vers aucun dernier élément, la liste sera vide en sortie de la fonction
					
				}
				else {
					if(precedent==NULL){	//si seulement precedent est NULL, on est sur le premier élément de la liste 
						suivant->precedent=NULL;		//le pointeur de l'élément suivant precedent sera vide
						liste->premier=actuel->suivant;	//et suivant ou actuel->suivant devient le premier élément de la liste
					}
					else if(suivant==NULL){	//si seulement suivant est NULL, on est sur le dernier élément de la liste 
						precedent->suivant=NULL;		//le pointeur de l'élément precedent suivant sera vide
						liste->dernier=actuel->precedent;	//et precedent ou actuel->precedent devient le dernier élément de la liste
					}
					else{				//sinon on se trouve au millieu de la liste chaînée
						precedent->suivant=actuel->suivant;	//on rechaîne l'élément suivant de precedent avec l'element suivant ou actuel->suivant
						suivant->precedent=actuel->precedent;	//on rechaîne l'élément precedant de suivant avec l'élément précédent ou actuel->precedent
					}
					
				}
				free(actuel);		//on libère actuel qui n'est plsu lié à rien dans la liste 
				liste->nombre--;	//on décrémente le nombre d'élément de la liste
				afficher_liste(liste);
			}
		}
	}
};
void supprimer_liste_ennemi(ListeEnnemi* liste){
	
	printf("suprimer_liste_ennemi %d\n",liste->nombre);
	int nombreEnnemis=liste->nombre;		//déclaration d'un entier qui aura le nombre d'élément ennemi de la liste
	if(liste->premier!=NULL){
		int i=0;				//compteur pour la boucle
		ElementEnnemi* actuel=liste->premier;	//déclaration d'un pointeur vers le premier élément de la liste chainée
		while(i<nombreEnnemis){		//boucle tant qu'on a pas parcouru toute la liste
			actuel->e.attente=false;	//on doit les sortir du mode inactif sinon on ne peut pas les supprimers
			actuel=actuel->suivant;
			i++;	
		}
		i=0;
		while(i<nombreEnnemis){		
			supprimer_ennemi_numero(liste, 0);	//suppression de tous les élément Ennemi de la liste
			i++;	
		}
		liste->nombre=0;	//la liste ne possède plus d'ennemi nombre=0
		liste->premier=NULL;	//le pointeur vers le premier élément et le dernier sont NULL
		liste->dernier=NULL;
	}

};

void retirer_vie_numero(ListeEnnemi* liste, int numero, int degat){
	int i=0;				//même algorithme de placement dans la liste d'ennemi que dans modifier_ennemi()
	int decalage=numero;
	bool SensCroissant=true;
	ElementEnnemi* actuel=NULL;
	if(numero<liste->nombre){
		if(numero<liste->nombre/2){
			actuel=liste->premier;
		}
		else{
			actuel=liste->dernier;
			SensCroissant=false;
			decalage=liste->nombre-numero-1;
		}

			while(i<decalage){
				if(SensCroissant){
					actuel=actuel->suivant;
				}
				else{
					actuel=actuel->precedent;
				}
				i++;
			}			//actuel est le pointeur de l'ElementEnnemi correspondant à (int numero)
		actuel->e.vie-=(degat+1);	//les points de vie de cette ennemi sont adaptés
		actuel->e.attente=false;	//l'ennemi s'il est touché est sorti de son status pacif/inactif
		if(actuel->e.vie<1){		//si la vie de l'ennemi est inférieur à 1 (donc 0 ou moins) c'est qu'il a été tué.
			switch (actuel->e.type){	//en fonction du type d'ennemi on gagne plus ou moins de point dans la variable score
				case 0:		
					score+=5;
					break;
				case 1:
					score+=2;
					break;
				case 2:
					score+=20;
					break;
				case 3:
					score+=50;
					break;
				case 4:
					score+=0;
					break;
			}
			supprimer_ennemi_numero(liste, numero);
		}
		
	}
};

void modifier_pos_ennemi(ListeEnnemi* liste, int numero, Coordonnee pos){
	int i=0;				//début du même algorithme de placement dans la liste que la fonction précédente modifier_ennemi();
	int decalage=numero;
	bool SensCroissant=true;
	ElementEnnemi* actuel=NULL;
	if(numero<liste->nombre){
		if(numero<liste->nombre/2){
			actuel=liste->premier;
		}
		else{
			actuel=liste->dernier;
			SensCroissant=false;
			decalage=liste->nombre-numero-1;
		}

			while(i<decalage){
				if(SensCroissant){
					actuel=actuel->suivant;
				}
				else{
					actuel=actuel->precedent;
				}
				i++;
			}			//fin du placement dans la liste actuel est l'élément que nous voulions modifier (int numero)
		actuel->e.pos=pos;		//la position de l'ennemi est initialisé à la position donné en entrée
	}
};
Direction dir_ennemi(ListeEnnemi* liste, int numero){
	int i=0;			//début du même algorithme de placement dans la liste que la fonction précédente modifier_ennemi();
	int decalage=numero;
	bool SensCroissant=true;
	Direction dir=4;		//variable type énumération Direction qui sera renvoyé à la fonction appelante 
	ElementEnnemi* actuel=NULL;
	if(numero<liste->nombre){
		if(numero<liste->nombre/2){
			actuel=liste->premier;
		}
		else{
			actuel=liste->dernier;
			SensCroissant=false;
			decalage=liste->nombre-numero-1;
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
					//fin du placement dans la liste actuel est l'élément que nous voulions modifier (int numero)
		dir=actuel->e.dir;	// on récupère la direction de l'ennemi actuel dans la variable dir qui sera renvoyé dans le return
	}
	return dir;
};

void modifier_pos_ennemis(ListeEnnemi* liste, Coordonnee variation){
	int i=0;				//compteur pour la boucle qui va parcourir toute la liste d'ennemi

	ElementEnnemi* actuel=liste->premier;	//pointeur ElementEnnemi actuel qui est initialisé a l'adresse du premier élément de la liste
	int nombreMax=liste->nombre;		//nombreMax le nombre maximum d'élément de la liste
	for(i=0;i<nombreMax;i++){		//boucle for qui parcour toute la liste
	
		actuel->e.pos.x+=variation.x;	//On applique la variation de position donné en entré pour la position de l'ennemi actuel en x et y
		actuel->e.pos.y+=variation.y;

		actuel=actuel->suivant;
	}
	supprimer_ennemi_hors_portee(liste);	// On fait appel à la fonction de suppression des ennemis qui sont trop loin car on vient de déplacer de beaucoup tous les ennemis

};


void supprimer_ennemi_hors_portee(ListeEnnemi* liste){
	ElementEnnemi* actuel=liste->premier;	
	int nombreMax=liste->nombre;		//déclaration de la variable qui représente le nombre d'ennemi de la liste
	int* registre=NULL;			//déclaration du registre tableau d'int alloué dynamiquement qui enregistrera tous les ennemis qui se trouve trop
						// loin par rapport à la camera, puis les supprimera
	int nombreRegistre=0;			//taille du registre
	for(int i=0;i<nombreMax;i++){
		if(actuel->e.pos.y>camera.y+(CAM_RANGE*8)||actuel->e.pos.y<camera.y-(CAM_RANGE*8)){	//condition vérifiant si l'ennemi est trop loins de la caméra
													// si la condition est vérifié l'ennemi devra être supprimé et est 
													//donc ajouté au registre
			actuel->e.attente=false;		
			if(registre==NULL){
				registre=malloc(sizeof(int*));

			}
			else{
				registre=realloc(registre, sizeof(int*)*nombreRegistre+1);

			}
			*(registre+nombreRegistre)=i;
			nombreRegistre++;
			actuel=actuel->suivant;
		}
		else{
			actuel=actuel->suivant;	//sinon on passe juste à l'ennemi suivant
		}
	}

	for(int n=0;n<nombreRegistre;n++){
		printf("%d ",*(registre+n));
	}

	for(int n=nombreRegistre;n>0;n--){		//on parcours la boucle du haut vers le bas pour éviter de modifier les positions des éléments, suivant, qui se 
							//trouve après un élément éliminé.
							//boucle parcourant le tableau d'int registre contenant les numeros des ennemis à éliminer
		afficher_liste(liste);
		supprimer_ennemi_numero(liste,*(registre+(n-1)));
		afficher_liste(liste);
	}
	free(registre);	//on libère le registre
	afficher_liste(liste);
};
void activer_ennemi_a_portee(ListeEnnemi* liste){
	ElementEnnemi* actuel=liste->premier;
	int nombreMax=liste->nombre;
	for(int i=0;i<nombreMax;i++){	//boucle qui va parcourir toute la liste d'ennemi et vérifier s'il se trouve avant ou après la dictance d'activation par rapport
					// à la position caméra
		if(actuel->e.pos.y<camera.y+(CAM_RANGE+4)&&actuel->e.pos.y>camera.y-(CAM_RANGE+4)){

			actuel->e.attente=false;	//l'ennemi est activé
		}
		else{	
			actuel->e.attente=true;	//l'ennemi est mis en attente
		}
		actuel=actuel->suivant;
	}
};
Coordonnee pos_Ennemi(ListeEnnemi* liste,int numero){
	Coordonnee ennemiPos;	//déclaration de la structure Coordonnee qui sera renvoyé en fin de la fonction et qui contiendra pas position de l'ennemi (int numero)
	ennemiPos.x=128;
	ennemiPos.y=128;
	if(liste->premier!=NULL){		
	int i=0;			//début du même algorithme de placement dans la liste que la fonction précédente modifier_ennemi();		
	int decalage=numero;
	bool SensCroissant=true;
	ElementEnnemi* actuel=NULL;
	if(numero<liste->nombre){
		if(numero<liste->nombre/2){
			actuel=liste->premier;
		}
		else{
			actuel=liste->dernier;
			SensCroissant=false;
			decalage=liste->nombre-numero-1;
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
	}				//fin du placement dans la liste actuel est l'élément que nous voulions modifier (int numero)
	ennemiPos=actuel->e.pos;	// on récupère la position de l'ennemi dans ennemiPos

	}
	return(ennemiPos);
}

void replacement_ennemi(int x, int y, Map* map){
	

	int mjX, mjY;
 	//variable pour le placement du joueur dans la carte sur lequel il se trouve (next, nextLR ou current).
	//recherche position par rapport à current 
	if(y<0||y>=currentMap.taille.y){  //position verticale en dehors 0 et taille currentMap
			
			mjX=x;				//x ne change pas
			if(y<0){			//si au dessus, alors la position dans nextMap est à la fin, donc à la taille de next+y (y est négatif)
				map->c=nextMap.c;       //j est juste au dessus de currentMap, donc dans nextMap
				mjY=y+nextMap.taille.y;
			}		
			else{			//si en dessous, alors la position dans previousMap est au début, donc à y-la hauteur de current	
				map->c=previousMap.c;       //j est juste au dessus de currentMap, donc dans nextMap
				mjY=y-currentMap.taille.y;
			}
	}
	else{
		map->c=currentMap.c;
		mjX=x;
		mjY=y;
	}
	map->taille.x=mjX;	//Coordonnée de j dans la carte logique/le plateau qui le concerne contenu dans map->taille
	map->taille.y=mjY;
	return ;

};

void action_ennemi(ListeEnnemi* liste){
	ElementEnnemi* actuel=liste->premier;	
	for(int i=0;i<liste->nombre;i++){		//Boucle qui parcours toute la liste d'ennemi et fait l'appel de la fonction d'action qui
							// correspond au type de l'ennemi en cours de traitement dans la boucle qui dépend du type de l'ennemi
		if(!actuel->e.attente){
			switch(actuel->e.type){
				case voiture:
					action_voiture(&(actuel->e),i);
					break;
				case moto:
					action_moto(&(actuel->e),i);
					break;
				case camion:
					
					break;
				case SUV:
					
					break;
				case vide:
					break;
				
			}
		}
		actuel=actuel->suivant;
	}
};

void action_voiture(Ennemi* voiture,int numero){
	int x=voiture->pos.x;			//garde la position initial de l'ennemi avant le déplacement,au case ou l'ennemi venait a entré en collision avec 
						//un ennemi ou le décors, cette valeur lui sera réapliqué avant la fin de la fonction. Annulant l'action de déplacement tentée.
	int y=voiture->pos.y;
	if(voiture->pos.x-j.pos.x<0){		//algorithme de déplacement automatique de l'ennemi type voiture. La voiture va simplement essayé de venir vers le joueur en se plaçant d'abord juste à la même position en x puis en ajustant sa position en y vers le joueur
		voiture->pos.x++;
		voiture->dir=1;
	}
	else if(voiture->pos.x-j.pos.x>0){
		voiture->pos.x--;
		voiture->dir=3;
	}
	else{
		if(voiture->pos.y-j.pos.y<0){
			voiture->pos.y++;
			voiture->dir=2;
		}
		else if(voiture->pos.y-j.pos.y>0){
			voiture->pos.y--;
			voiture->dir=0;
		}
	}
	bool collisionEnnemi=false;		//booleen qui vérifie si on a fait une collision avec au moins un ennemi avec la position calculée par l'algorithme
	for(int i=0;i<liste->nombre;i++){	//boucle allant tester tous les ennemis de la liste avec l'ennemi en cours d'action
		if(i!=numero){			//il ne faut pas vérifier l'ennemi en cours avec lui même(le résulta est d'office une collision ce qui bloque les ennemis)
			if(collision_ennemi_ennemi(i,numero)){	//compare les hitBox des ennemis pour savoir si il y a collision entre un ennemi et l'ennemi en cours
				collisionEnnemi=true;
			}
		}
	}
	if(!collisionEnnemi){		//s'il n'y a pas eu de collision entre ennemi on continue	
		Map Emap;
		bool DIFFERENTMAP;	//booleen qui indiquera après son retour de la fonction HitBoxEnnemi_collision_decors si la limite inférieure doite de la hitBox (en bas et à droite)
					//est sur une autre carte de collision avec le décors que celle qui sera rendue par le fonction replacement_ennemi pour la position de l'ennemi
					//qui réprésente également la limite supérieure et gauche de la hitBox
		replacement_ennemi(voiture->pos.x,voiture->pos.y,&Emap);	
		Coordonnee limiteBD;
		limiteBD=HitBoxEnnemi_collision_decors(voiture->type,voiture->dir,Emap.taille,&DIFFERENTMAP);	//On va déterminer la valeur des limites de la hitBox de l'ennemi
		if(!DIFFERENTMAP){	//si tous est sur la même map
			if(collision_ennemi_decor(Emap.taille,limiteBD,voiture->dir,Emap.c)){	//on fait une vérification pour la collision avec le décors conteni 
													//dans le tableau de char (char**) Emap.c
													//remarque cette fonction renvoie un booleen inverse qui indique si 
													//l'ennemi peut se déplacer
				
			}
			else{
				printf("Ennemi bloqué\n");
				voiture->pos.x=x;		
				voiture->pos.y=y;
			}
		}
		else{			//sinon on détermine ma carte sur laquel il faut faire le test pour la limite inférieur droite qui dépend de la direction prise par l'ennemi
					//En effet si l'ennemi se dirige vers le haut, il ne fait nul besoin de chercher celle-ci, car le test de collision 
					//s'effectue uniquement avec la limite supérieur dont nous connaisions déjà la map sur laquel se trouvait cette limite dans Emap.c
			if(voiture->dir==0){
				if(collision_ennemi_decor(Emap.taille,limiteBD,voiture->dir,Emap.c)){
					
				}
				else{
					printf("Ennemi bloqué\n");
					voiture->pos.x=x;
					voiture->pos.y=y;
				}
			}
			else if(voiture->dir==2){	//La directon vers le base demandera systématiquement dans ce cas-ci de retrouver la carte ou se trouve la limite inférieur
				if(voiture->pos.y<0){	//comme on sait qu'elle est différent de Emap.c elle doit être forcément vu que cette limite est en dessous
							//currentmap.c, ou
							//previousMap.c. On peut le connaitre juste en connaissant le position ou devrait se trouver l'ennemi après déplacement 
							//sur le grid global
					Emap.c=currentMap.c;
				}
				else if(voiture->pos.y<64){
					Emap.c=previousMap.c;
				}
				if(collision_ennemi_decor(Emap.taille,limiteBD,voiture->dir,Emap.c)){
				
				}
				else{
					printf("Ennemi bloqué\n");
					voiture->pos.x=x;
					voiture->pos.y=y;
				}
			}
			else{
				Map differentMap;
				if(voiture->pos.y<0){
					differentMap=currentMap;
				}
				else if(voiture->pos.y<64){
					differentMap=previousMap;
				}
				if(collision_ennemi_decor_limiteMap(Emap.taille,limiteBD,voiture->dir,Emap.c,differentMap.c)){
					
				}
				else{
					printf("Ennemi bloqué\n");
					voiture->pos.x=x;
					voiture->pos.y=y;
				}
			}
		}
	}
	else{	//ici la condition de non-collisiont avec les ennemis n'était pas remplie donc
		voiture->pos.x=x;	//on rend la position initial au début de la fonction action à l'ennemi, ce qui annule le déplacement souhaité
		voiture->pos.y=y;
	}
	
};

//cette fonction est pareil a action_voiture seul l'algorithme de déplacement de la moto est différent
void action_moto(Ennemi* moto, int numero){
	int x=moto->pos.x;
	int y=moto->pos.y;
	if((moto->pos.x-moto->pos.y)%2==0){	// les ennemis de type moto se déplacent en alternant à chaque déplacement la direction vers laquel il se rapproche du joueur
		if(moto->pos.x-j.pos.x<0){
			moto->pos.x++;
			moto->dir=1;
		}
		else if(moto->pos.x-j.pos.x>0){
			moto->pos.x--;
			moto->dir=3;
		}
	}
	else{
		if(moto->pos.y-j.pos.y<0){
			moto->pos.y++;
			moto->dir=2;
		}
		else if(moto->pos.y-j.pos.y>0){
			moto->pos.y--;
			moto->dir=0;
		}
	}
	
	bool collisionEnnemi=false;
	for(int i=0;i<liste->nombre;i++){
		if(i!=numero){
			if(collision_ennemi_ennemi(i,numero)){
				collisionEnnemi=true;
			}
		}
	}
	if(collisionEnnemi){
		moto->pos.x=x;
		moto->pos.y=y;
	}
	else{
		Map Emap;
		bool DIFFERENTMAP;
		replacement_ennemi(moto->pos.x,moto->pos.y,&Emap);
		Coordonnee limiteBD;
		limiteBD=HitBoxEnnemi_collision_decors(moto->type,moto->dir,Emap.taille,&DIFFERENTMAP);
		if(!DIFFERENTMAP){
			if(collision_ennemi_decor(Emap.taille,limiteBD,moto->dir,Emap.c)){
				
			}
			else{
				printf("Ennemi bloqué\n");
				moto->pos.x=x;
				moto->pos.y=y;
			}
		}
		else{
			if(moto->dir==0){
				if(collision_ennemi_decor(Emap.taille,limiteBD,moto->dir,Emap.c)){
					
				}
				else{
					printf("Ennemi bloqué\n");
					moto->pos.x=x;
					moto->pos.y=y;
				}
			}
			else if(moto->dir==2){
				if(y<0){
					Emap.c=currentMap.c;
				}
				else if(y<64){
					Emap.c=previousMap.c;
				}
				if(collision_ennemi_decor(Emap.taille,limiteBD,moto->dir,Emap.c)){
				
				}
				else{
					printf("Ennemi bloqué\n");
					moto->pos.x=x;
					moto->pos.y=y;
				}
			}
			else{
				Map differentMap;
				if(y<0){
					differentMap=currentMap;
				}
				else if(y<64){
					differentMap=previousMap;
				}
				if(collision_ennemi_decor_limiteMap(Emap.taille,limiteBD,moto->dir,Emap.c,differentMap.c)){
					
				}
				else{
					printf("Ennemi bloqué\n");
					moto->pos.x=x;
					moto->pos.y=y;
				}
			}
		}
	}
};
//PRE: prend en argument la liste
//post:affiche cette liste dans la console
void afficher_liste(ListeEnnemi* liste){
	int i=0;
	printf("---Liste ennemi %d: ---\n",liste->nombre);
	ElementEnnemi* actuel=liste->premier;
	while(i<liste->nombre){
	printf(" nom ennemi :%s vie : %d pos : (x=%d;y=%d) type :%d\n",actuel->e.nom,actuel->e.vie,actuel->e.pos.x,actuel->e.pos.y,actuel->e.type);
	actuel=actuel->suivant;
	i++;
	}
	printf("-----------fin liste----------\n");
};			
