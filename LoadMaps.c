#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LoadMaps.h"
#include "interface.h"

char* int_vers_char(int nombre){
	int i=0; 	//i variable qui va compter le nombre de chiffre du nombre entier nombre
	int n=nombre;	//n garde la valeur de nombre

	do{
		nombre=nombre/10;
		i++;

	}while(nombre>0);
	
	char* String_nombre=malloc(sizeof(char*)*(i+1)); // allocation dynamique de String_nombre chaîne de caractère qui comprendra nombre
	
	sprintf(String_nombre,"%d",n);		// fait la transcription de n (égale à nombre entré en argument selon sa déclaration) de int vers char*
	
	return(String_nombre); //on retourne cette chaîne de caractère
}

//fonction qui fait la correspondance entre le numero select et la carte qui lui correspond dans un switch et renvoie un FILE* 
void map_select(int select,char* nom){
	printf("maps_select : %d\n",select);
	char Nom[MAX_NOM]={"map"};	//variable Nom qui contient la chaîne "map" qui sera utilisé dans la fonction
	
	char* valeur=NULL;		//variable valeur pointeur de char qui sera utilisé pour contenir la chaîne de caractère représentant le nombre qui sera utilisé dans cette fonction, selon que la map en question fasse partie des map normal, des mapPreBoss ou des map Boss 
	if(select<MAPS){	//MAPS est le nombre de map normal différente présente dans les fichiers carte .txt .
		valeur=int_vers_char(select);
		strcat(nom,Nom);
		strcat(nom,valeur);
		strcat(nom,".txt");
	}
	else if(select<MAPS+3&&select>=MAPS){
		valeur=int_vers_char(select-MAPS);
		strcat(nom,Nom);
		strcat(nom,"PreBoss");
		strcat(nom,valeur);
		strcat(nom,".txt");
	}
	else if(select<MAPS+3+MAPS_BOSS&&select>=MAPS+3){//MAPS_BOSS le nombre de map de boss différente présente dans les fichier carte .txt
		valeur=int_vers_char(select-MAPS-3);
		strcat(nom,Nom);
		strcat(nom,"Boss");
		strcat(nom,valeur);
		strcat(nom,".txt");
	}
	free(valeur);
	
};

void tailleMap(int* tMapX, int* tMapY, TabNiveau niveauA, int select){
	printf("tailleMap %d\n",select);
	int x=0;	//variable x destinée à compter les caractères d'une ligne dans la double boucle à la fin de cette fonction
	int y=0;	//variable y destinée à compter le nombre de lignes de caractère du fichier texte hors-header

	bool X=false;	//booleen qui va permettre d'arrêter le comptage de x dés la fin de la première ligne
	char nom[MAX_NOM]={"\0"};	//nom chaîne de caractère qui va accueillir le nom du fichier a ouvrir correspondant a l'entier select donné en argument dans niveauA
	FILE* fNewMap=NULL;		//declaration du pointeur de fichier qui sera utilisé pour lire le fichier texte de la carte 
	map_select(niveauA.Nmap[select].s,nom);//fonction qui va former ne nom du fichier a ouvrir
	fNewMap=fopen(nom,"r");	//ouverture du fichier .txt en mode lecture seule
	if(fNewMap==NULL){
		printf("Le fichier n'a pu être ouvert\n");
		exit(-1);
	}
	else{
		fseek(fNewMap,0,0);	//On place le curseur de lecture du fichier au début
		char c=' ';		//c variable qui contiendra au fur et a mesure de la lecture le denier caractère lu
		while(c!='\n'){	//boucle tant qu'on a pas trouver un caractère passer la ligne
			
			c=fgetc(fNewMap);	//fonction de lecture d'un caractère, inscris dans c
			printf("%c",c);
			if(c=='p'){		
				c=fgetc(fNewMap);
				printf("%c",c);
				switch(c){	//switch case sur la valeur lue dans c pour retranscire la valeurs en int et l'inscrire dans la variable adéquat
					case '0':
						niveauA.Nmap[select].previous=0;
						break;
					case '1':
						niveauA.Nmap[select].previous=1;
						break;
					case '2':
						niveauA.Nmap[select].previous=2;
						break;
					case '3':
						niveauA.Nmap[select].previous=3;
						break;
					case '4':
						niveauA.Nmap[select].previous=4;
						break;
					
				}
			}
			if(c=='n'){
				c=fgetc(fNewMap);
				printf("%c",c);
				switch(c){	//switch case sur la valeur lue dans c pour retranscire la valeurs en int et l'inscrire dans la variable adéquat
					case '0':
						niveauA.Nmap[select].Next=0;
						break;
					case '1':
						niveauA.Nmap[select].Next=1;
						break;
					case '2':
						niveauA.Nmap[select].Next=2;
						break;
					case '3':
						niveauA.Nmap[select].Next=3;
						break;
					case '4':
						niveauA.Nmap[select].Next=4;
						break;
					
				}
			}
		}
		while(c!=EOF){			//on continue la boucle tant qu'on a pas trouver le signal EOF (fin du fichier)
			c=fgetc(fNewMap);
			if(c=='\n'){
				y++;
				X=true;
			}
			if(!X){
				x++;
			}	
		}
		
		*tMapX=x;		//Le pointeur tMapX donnée en argument prend la valeur calculée de x
		*tMapY=y;		//Le pointeur tMapY donnée en argument prend la valeur calculée de y
	fclose(fNewMap);		//fermeture du fichier
	}
	printf("fin tailleMap\n");
	
	
	return ;
};

void loadMap(int tMapX, int tMapY, TabNiveau* niveauA, int select){
	
	printf("loadMap\n");
	printf("X :%d Y :%d\n",tMapX,tMapY);
	char nom[MAX_NOM]={"\0"};	//nom chaîne de caractère qui va accueillir le nom du fichier a ouvrir correspondant a l'entier select donné en argument dans niveauA
	FILE* fNewMap=NULL;		//declaration du pointeur de fichier qui sera utilisé pour lire le fichier texte de la carte 
	map_select(niveauA->Nmap[select].s,nom);//fonction qui va former ne nom du fichier a ouvrir
	fNewMap=fopen(nom,"r");	//ouverture du fichier .txt en mode lecture seule
	
	if(fNewMap==NULL){
		printf("Le fichier n'a pu être ouvert\n");
		exit(-1);
	}
	else{
		char c;
		while(c!='\n'){	//boucle pour éviter de charger dans la map la pemière ligne du fichier texte qui contient des infos
			c=fgetc(fNewMap);
		}
		printf("Le fichier ouvert\n");
		char** loadedMap=malloc(sizeof(char *)*tMapY);// le double pointeur loadedMap récupérera le tableau de caractère de contenu dans le fichier texte ouvert 
		//	on fait demande d'allocation de mémoire pour un pointeur de char* fois la taille en y de la carte en premier lieu
		
		int x=0;//déclaration du compteur pour parcourir les caractères de chaque ligne dans le fichier
		int y=0;//déclaration du compteur pour parcourir les lignes de caractères du fichier
		*(loadedMap)=malloc(sizeof(char*)*tMapX);//demande d'allocation dynamique pour la taille de char* fois le nombre de caractère de la ligne
		do{
			*((loadedMap)+y)=malloc(sizeof(char*)*tMapX);
			for(x=0;x<tMapX;x++){
				c=fgetc(fNewMap);
				*(*((loadedMap)+y)+x)=c;
			}
			fgetc(fNewMap);
			y++;
		}while(c!=EOF);
		y=0;
		
		//succession de condition sur select pour savoir dans quel variable on doit enregister cette lecture du tableau de char** loadedMap
		if(select==niveauA->current){	
			currentMap.c=loadedMap;
			currentMap.taille.x=tMapX;
			currentMap.taille.y=tMapY; 		//ici currentMap car select est égale à la valeur de current compris dans niveauA qui garde l'état d'avancement dans le niveau du joueur
			currentMap.previous=false;
			niveauA->Nmap[niveauA->current].loadStatus=false;
			niveauA->current=select;
		}
		else if(select>niveauA->current){
			nextMap.c=loadedMap;
			nextMap.taille.x=tMapX; 
			nextMap.taille.y=tMapY; 		//ici nextMap car select est supérieur à la valeur de current compris dans niveauA qui garde l'état d'avancement dans le niveau du joueur
			nextMap.previous=false;
			niveauA->Nmap[niveauA->next].loadStatus=false;
			niveauA->next=select;
		}
		else if(select<niveauA->current){
			previousMap.c=loadedMap;
			previousMap.taille.x=tMapX;
			previousMap.taille.y=tMapY;		//ici previousMap car select est inférieur à la valeur de current compris dans niveauA qui garde l'état d'avancement dans le niveau du joueur
			previousMap.previous=true;
			niveauA->Nmap[niveauA->previous].loadStatus=false;
			niveauA->previous=select;
		}
		niveauA->Nmap[select].loadStatus=true; //on confirme que cette map du niveau est chargée.
		
		//Boucle affichant la map chargée en console
		do{

			for(x=0;x<tMapX;x++){
				printf("%c",*(*((loadedMap)+y)+x));
			}
			printf("\n");
			y++;
		}while(y<tMapY);
	fclose(fNewMap);
	}
	
	
};

void Entree_sortie_Map( int select, Direction* entreeN, Direction* sortieN){
	char nom[MAX_NOM]={"\0"};	//nom chaîne de caractère qui va accueillir le nom du fichier a ouvrir correspondant a l'entier select donné en argument dans niveauA
	FILE* fNewMap=NULL;		//declaration du pointeur de fichier qui sera utilisé pour lire le fichier texte de la carte 
	map_select(select,nom);	//fonction qui va former ne nom du fichier a ouvrir
	printf("%s\n",nom);
	fNewMap=fopen(nom,"r");	//ouverture du fichier .txt en mode lecture seule
	if(fNewMap==NULL){
		printf("Erreur fichier inexistant\n");
		exit(-1);
	}
	else{
		fseek(fNewMap,0,0);
		char c=' ';
		while(c!='\n'){
			
			c=fgetc(fNewMap);
			printf("%c",c);
			if(c=='p'){
				c=fgetc(fNewMap);
				printf("%c",c);
				switch(c){	//switch case sur la valeur lue dans c pour retranscire la valeurs en int et l'inscrire dans la variable adéquate, ici le pointeur *entreeN argument de la fonction qui sert aussi a passer cette information en dehors de la fonction
					case '0':
						*entreeN=0;
						break;
					case '1':
						*entreeN=1;
						break;
					case '2':
						*entreeN=2;
						break;
					case '3':
						*entreeN=3;
						break;
					case '4':
						*entreeN=4;
						break;
					
				}
			}
			if(c=='n'){
				c=fgetc(fNewMap);
				printf("%c",c);
				switch(c){	//switch case sur la valeur lue dans c pour retranscire la valeurs en int et l'inscrire dans la variable adéquate, ici le pointeur *sortieN argument de la fonction qui sert aussi a passer cette information en dehors de la fonction
					case '0':
						*sortieN=0;
						break;
					case '1':
						*sortieN=1;
						break;
					case '2':
						*sortieN=2;
						break;
					case '3':
						*sortieN=3;
						break;
					case '4':
						*sortieN=4;
						break;
					
				}
			}
		}
		
	}
	fclose(fNewMap);
	return;
}

void choix_map_aleatoire(void){
	
	Direction sortieC=0;	//variable de direction qui serviront à vérifier les correspondances de type d'ouverture entre les maps, sortieC sortie de la dernière map enregistrée
	Direction sortieN;	//variable de direction qui serviront à vérifier les correspondances de type d'ouverture entre les maps, sortieN sortie de la nouvelle map sélectionnée aléatoirement et a testé
	Direction entreeN;	//variable de direction qui serviront à vérifier les correspondances de type d'ouverture entre les maps, entréeN entrée de la nouvelle map sélectionnée aléatoirement et a testé
	
	//installer la première map, startMap, enregistrement des informations de la carte dans la variable globale niveauA
	printf("startmap\n");
	niveauA.Nmap[0].s=0;
	Entree_sortie_Map(0, &entreeN, &sortieN);
	niveauA.Nmap[0].Next=sortieN;
	niveauA.Nmap[0].previous=entreeN;
	niveauA.Nmap[0].ennemi=true;
	niveauA.Nmap[0].loadStatus=false;
	sortieC=sortieN;
	
	
	//sélection de toute les map du niveau (les maps normales) hors startMap, pre-BossMap et BossMap 
	printf("maps\n");
	for(int i=1;i<niveauA.nombreMap-2;i++){	//boucle qui aura lieu autant de fois que le nombre de carte du niveau -1 pour la carte de départ non-aléatoire et -2 pour la carte PreBoss et Boss qui seront choisies après.

		bool MapOK=true;
		int nRandom;	//entier qui recevra la valeur random choisie à l'aide de rand()
		do{
			nRandom=(rand()%MAPS);	//rand() modulo le nombre de carte diférente pour être sur d'avoir un résultat parmis les cartes normal entre 0 et MAPS
			Entree_sortie_Map(nRandom, &entreeN, &sortieN);
			if(entreeN==sortieC){	//vérification que les ouvertures des cartes adjacentes correspondent
				MapOK=false;
			}
			
		}while(MapOK);	//on sort de la boucle de vérification si les ouvertures des cartes correspondent
		niveauA.Nmap[i].s=nRandom;
		niveauA.Nmap[i].Next=sortieN;
		niveauA.Nmap[i].previous=entreeN;	//enregistrement des informations de la carte dans la variable globale niveauA
		niveauA.Nmap[i].ennemi=true;
		niveauA.Nmap[i].loadStatus=false;
		sortieC=sortieN;
		
	}
	//selection pre-BossMap, qui fait le lien entre la dernière map et la map de boss qui sera toujours en entree 0
	printf("preBoss\n");
	int select=MAPS;
	if(sortieC==0){
		select=MAPS;
	}
	else if(sortieC==1){
		select+=1;
	}
	else if(sortieC==3){
		select+=2;	
	}
	Entree_sortie_Map(select, &entreeN, &sortieN);
	niveauA.Nmap[niveauA.nombreMap-2].s=select;
	niveauA.Nmap[niveauA.nombreMap-2].Next=sortieN;
	niveauA.Nmap[niveauA.nombreMap-2].previous=entreeN;	//enregistrement de la carte PreBoss correspondante à l'antepenultième carte normal aléatoire
	niveauA.Nmap[niveauA.nombreMap-2].ennemi=true;
	niveauA.Nmap[niveauA.nombreMap-2].loadStatus=false;
	
	//selection BossMap, parmis les MapBoss
	printf("Boss\n");
	int nRandomBoss=(rand()%MAPS_BOSS);
	Entree_sortie_Map(nRandomBoss+3+MAPS, &entreeN, &sortieN);	//selection aleatoire d'un carte de Boss parmis les (MAPS_BOSS) nombre de carte
	niveauA.Nmap[niveauA.nombreMap-1].s=nRandomBoss+3+MAPS;
	niveauA.Nmap[niveauA.nombreMap-1].Next=sortieN;
	niveauA.Nmap[niveauA.nombreMap-1].previous=entreeN;
	niveauA.Nmap[niveauA.nombreMap-1].ennemi=true;
	niveauA.Nmap[niveauA.nombreMap-1].loadStatus=false;
	
	for(int m=0;m<niveauA.nombreMap;m++){
		char nomA[MAX_NOM]={"\0"};
		map_select(niveauA.Nmap[m].s,nomA);	//affichage du résultat finale 
		printf("%s\n",nomA);
	}
}

void initialisation_Map(Map* initMap){
	
	initMap->c=NULL;
	initMap->taille.x=0;
	initMap->taille.y=0;
	initMap->previous=false;
	return ;
};

void preparation_niveau(int nombreMap){
	nombreMap=8;			//Nombre de carte composant le niveau
					//a faire préparer un menu ou modifier la taille du niveau, donc changer cette variable avant de commencer la partie
	niveauA.nombreMap=nombreMap;	
	initialisation_Map(&previousMap);
	initialisation_Map(&nextMap);		//initialisation des variables globale Map deu jeu à 0
	initialisation_Map(&currentMap);
	niveauA.Nmap=malloc(sizeof(SelectionMap)*nombreMap);
	choix_map_aleatoire();
	score=0;			//initialisation du score de la partie à 0
	niveauA.current=0;		//initialisation de l'avancement du joueur dans le niveau niveauA.current à 0 le début
}

void loadMaps(void){
	
	int* tMapX=malloc(sizeof(int*));	//pointeur tMapX d'int de la taille d'un int, contiendra la taille en x (la largeur) de la map 
	int* tMapY=malloc(sizeof(int*));	//pointeur tMapY d'int de la taille d'un int,	contiendra la taille en y (la longueur) de la map 
	int i=0;				//compteur pour parcourir le nombre de fois que doivent être effectuée les différentes boucles
	do{
		tailleMap(tMapX,tMapY,niveauA, i);	//calcul des dimension de la carte
		loadMap(*tMapX,*tMapY,&niveauA, i);	//chargement de carte i
		i++;
	}while(i<2);
	for(i=0;i<niveauA.nombreMap;i++){
		niveauA.Nmap[i].ennemi=true;		//réinitialisation du chargement possible des ennemis pour toutes les cartes
	}
	loadEnnemi(liste, 0);	//chargement des ennemis dans la liste des ennemis liste, 0 première carte, 1 deuxième carte du tableau niveauA.Nmap[]
	loadEnnemi(liste, 1);
	supprimer_ennemi_numero(liste, 0);	
	camera.x=currentMap.taille.x/2;//position initiale de la camera au centre de la carte currentMap
	camera.y=currentMap.taille.y/2;
	free(tMapX);
	free(tMapY);
	return;
}

void loadNext(int select){
	printf("loadNext %d\n",select);
	int tMapX=0;	//tMapX d'int de la taille d'un int, contiendra la taille en x (la largeur) de la map 
	int tMapY=0;	//tMapY d'int de la taille d'un int,	contiendra la taille en y (la longueur) de la map 
	tailleMap(&tMapX,&tMapY,niveauA, select);//calcul des dimension de la carte select
	loadMap(tMapX,tMapY,&niveauA, select);//chargement de carte select
	loadEnnemi(liste, select);	//chargement des ennemis dans la liste des ennemis liste, de la carte select
}

Coordonnee load_respawn_Joueur(int select){
	
	printf("loadJoueur\n");
	
	int x=0;	//variable x destinée à compter les caractères d'une ligne dans la double boucle à la fin de cette fonction
	int y=0;	//variable y destinée à compter le nombre de lignes de caractère du fichier texte hors-header
	char c=' ';	//c variable qui contiendra au fur et a mesure de la lecture le denier caractère lu
	bool END=true; //variable booleen pour sortir de la double boucle dés que l'on a trouver la position du joueur
	char nom[MAX_NOM]={"\0"};
	Coordonnee CoordonneeRespawn;	//variable structure coordonnee qui contiendra la position en x et y du point de respawn du joueur
	FILE* fNewMap=NULL;
	map_select(niveauA.Nmap[select].s,nom);
	fNewMap=fopen(nom,"r");
	
	if(fNewMap==NULL){
		printf("Le fichier n'a pu être ouvert loadJoueur\n");
		
		exit(-1);
	}
	else{
	
	while(c!='\n'){	//boucle pour éviter de charger dans la map la pemière ligne du fichier texte qui contient des infos
		c=fgetc(fNewMap);
	}
	do{	//boucle parcourrant tous le fichier pour retrouver la position du joueur dans la carte
		x=0;
		do{
			c=fgetc(fNewMap);
			if(c=='j'){	//vérification du caractère c avec la valeur 'j' qui représente dans la carte la position du joueur
				CoordonneeRespawn.x=x;	//On enregistre dans la variable CoordonneeRespawn la valeur de x et y ou on retrouve le caractère 'j'
				CoordonneeRespawn.y=y;	//
				END=false;		//variable booleen pour sortir de la double boucle lorsque la position du joueur est trouvée 
			}
			x++;
		}while(c!='\n'&&c!=EOF&&END);
		y++;
	}while(c!=EOF&&END);
	fclose(fNewMap);
	
	}
	j.dir=4;	//direction dans laquel le joueur est tournée indéfinie donc 4
	return CoordonneeRespawn;//on renvoie la position de j
};
Joueur loadJoueur(int select){
	
	printf("loadJoueur\n");
	Joueur J;	//déclaration d'une variable joueur locale
	int x=0;	//variable x destinée à compter les caractères d'une ligne dans la double boucle à la fin de cette fonction
	int y=0;	//variable y destinée à compter le nombre de lignes de caractère du fichier texte hors-header
	char c=' ';	//c variable qui contiendra au fur et a mesure de la lecture le denier caractère lu
	bool END=true; //variable booleen pour sortir de la double boucle dés que l'on a trouver la position du joueur
	char nom[MAX_NOM]={"\0"};
	FILE* fNewMap=NULL;
	map_select(niveauA.Nmap[select].s,nom);
	fNewMap=fopen(nom,"r");
	
	if(fNewMap==NULL){
		printf("Le fichier n'a pu être ouvert loadJoueur\n");
		
		exit(-1);
	}
	else{
	
	while(c!='\n'){	//boucle pour éviter de charger dans la map la pemière ligne du fichier texte qui contient des infos
		c=fgetc(fNewMap);
	}
	do{	//boucle parcourrant tous le fichier pour retrouver la position du joueur dans la carte
		x=0;
		do{
			c=fgetc(fNewMap);
			if(c=='j'){	//vérification du caractère c avec la valeur 'j' qui représente dans la carte la position du joueur
				J.pos.x=x;//On enregistre dans la variable j la valeur de x et y ou on retrouve le caractère 'j'
				J.pos.y=y;//
				END=false;//variable booleen pour sortir de la double boucle lorsque la position du joueur est trouvée 
			}
			x++;
		}while(c!='\n'&&c!=EOF&&END);
		y++;
	}while(c!=EOF&&END);
	fclose(fNewMap);
	
	}
	J.vie=3;	//initialisation des différente valeur des variables composant le joueur, ici le nombre de vie avant le game over
	J.hp=5;	//le nombre de hp (point de vie/ healthpoint) avant de perdre une vie.  
	J.dir=4;	//la direction de base de joueur
	J.tirs=creer_liste_tirs();//La liste chaînée des tirs du joueur
	J.maxTirs=4;	//Le nombre de tirs maximum que le joueur peut effectuer en même temps
	return J;	//on retourne cette structure J initialisé 
};
void loadEnnemi(ListeEnnemi* liste, int select){
	
	printf("loadEnnemi\n");
	afficher_liste(liste);
	Coordonnee e;	//tampon coordonnée des ennemis
	int Dy=0;//variation de position par rapport à currentmap de la position chargée des ennemis
	int x=0;	//variable x destinée à compter les caractères d'une ligne dans la double boucle à la fin de cette fonction
	int y=0;	//variable y destinée à compter le nombre de lignes de caractère du fichier texte hors-header
	char c=' ';	//c variable qui contiendra au fur et a mesure de la lecture le denier caractère lu
	if(niveauA.Nmap[select].ennemi){	//condition vérifiant que la carte du niveau autorise le chargement des ennemis, si false les ennemis ne seront pas chargé
		char nom[MAX_NOM]={"\0"};
		FILE* fNewMap=NULL;
		map_select(niveauA.Nmap[select].s,nom);
		fNewMap=fopen(nom,"r");
		if(fNewMap==NULL){
			printf("Le fichier n'a pu être ouvert\n");
			
			exit(-1);
		}
		else{
			if(select==niveauA.current){	//condition vérifiant que select est égale a current (la map centrale)
				Dy=0;			//auquel cas on ne dois pas effectuer de variation de la position calculéed des ennemis dans la map en train d'être chargée
			}
			else if(select==niveauA.next){	//condition vérifiant que select est égale a next (la map supérieur)
				Dy-=nextMap.taille.y;	//auquel cas on dois effectuer de variation de la position calculée des ennemis dans la map en train d'être chargée, moins variation de la taille de la hauteur de la carte supérieur
			}
			else if(select==niveauA.previous){//condition vérifiant que select est égale a previous (la map inférieur)
				Dy+=currentMap.taille.y;//auquel cas on dois effectuer de variation de la position calculée des ennemis dans la map en train d'être chargée, plus la variation de la taille de la hauteur de la carte centrale
			}

			while(c!='\n'){	//boucle pour éviter de charger dans la map la pemière ligne du fichier texte qui contient des infos
				c=fgetc(fNewMap);
			}
			do{	//boucle parcourrant tous le fichier pour retrouver la position des ennemis dans la carte
				x=0;
				do{
					c=fgetc(fNewMap);
					switch(c){    //switch sur la valeur de c qui s'il est égale à {'m','v','c','S'} correspond à un ennemi d'un type repris dans l'enum TypeEnnemi
						case 'm':
							e.x=x;
							e.y=y+Dy;	//on place l'ennemi sur le plateau globale en modifiant la position en y dans le tableau de char** avec la variation calculée selon que l'on est sur previous, current, ou next Map
							char Nmoto[MAX_NOM]={"moto"};
							nouvel_ennemi(liste, Nmoto,3, e, moto);//on crée un nouvel ennemi dans la liste d'ennemi liste avec les caractéristique de position 
							break;
						case 'v':
							e.x=x;
							e.y=y+Dy;	//on place l'ennemi sur le plateau globale en modifiant la position en y dans le tableau de char** avec la variation calculée selon que l'on est sur previous, current, ou next Map
							char Nvoiture[MAX_NOM]={"voiture"};
							nouvel_ennemi(liste, Nvoiture,5, e, voiture);
							break;
						case 'c':
							e.x=x;
							e.y=y+Dy;	//on place l'ennemi sur le plateau globale en modifiant la position en y dans le tableau de char** avec la variation calculée selon que l'on est sur previous, current, ou next Map
							char Ncamion[MAX_NOM]={"camion"};
							nouvel_ennemi(liste, Ncamion,30, e, camion);
							break;
						case 'S':
							e.x=x;
							e.y=y+Dy;	//on place l'ennemi sur le plateau globale en modifiant la position en y dans le tableau de char** avec la variation calculée selon que l'on est sur previous, current, ou next Map
							char NSUV[MAX_NOM]={"SUV"};
							nouvel_ennemi(liste, NSUV,20, e, SUV);
							break;
						default:
							break;
					}
					x++;
				}while(c!='\n'&&c!=EOF);//boucle se finissant sur le caractère de fin de ligne ou de fin de fichier
				y++;
		}while(c!=EOF);	//boucle se finissant sur le caractère de fin de fichier
		fclose(fNewMap);
		}
	
	afficher_liste(liste);
	niveauA.Nmap[select].ennemi=false; //bloque le chargement des ennemis de la carte qui vient d'être chargée
	}
	return ;
};

