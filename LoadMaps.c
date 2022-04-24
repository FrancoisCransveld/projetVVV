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
//#include "jeu.h"
#include "interface.h"

//PRE:Prend en argument un int positif
//POST:renvoie la chaine de caractère correspondante à cet int
char* int_vers_char(int nombre){
	int i=0;
	int n=nombre;
	//printf("nombre :%d\n",nombre);
	do{
		nombre=nombre/10;
		i++;
		//printf("nombre :%d i: %d\n",nombre,i);
	}while(nombre>0);
	char* String_nombre=malloc(sizeof(char*)*(i+1));
	
	sprintf(String_nombre,"%d",n);
	
	return(String_nombre);
}
//fonction qui fait la correspondance entre le numero select et la carte qui lui correspond dans un switch et renvoie un FILE* 
void map_select(int select,char* nom){
	printf("maps_select : %d\n",select);
	char Nom[MAX_NOM]={"map"};
	
	char* valeur=NULL;
	if(select<MAPS){
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
	else if(select<MAPS+3+MAPS_BOSS&&select>=MAPS+3){
		valeur=int_vers_char(select-MAPS-3);
		strcat(nom,Nom);
		strcat(nom,"Boss");
		strcat(nom,valeur);
		strcat(nom,".txt");
	}
	free(valeur);
	/*strcat(nom,valeur);
	strcat(nom,".txt");*/
	/*switch(niveauA.Nmap[select].s){
		case 0:
			strcpy(nom,"map1.txt");
			break;
		case 1:
			strcpy(nom,"map2.txt");
			break;
		case 2:
			strcpy(nom,"map3.txt");
			break;
		case 3:
			strcpy(nom,"map4.txt");
			break;
		case 4:
			strcpy(nom,"map5.txt");
			break;
		case 5:
			strcpy(nom,"map6.txt");
			break;
		case 6:
			strcpy(nom,"map7.txt");
			break;
		default:
			break;
	}*/
};

//PRE:prend en argument deux pointeurs d'int pour renvoiyer la taille trouvée et un int qui correspond à la map qui devrai être traitée dans niveauA.Nmap[select]
//POST:calcul la taille d'une carte et renvoie cette taille via les argument d'entrée tMapX et tMapY
void tailleMap(int* tMapX, int* tMapY, TabNiveau niveauA, int select){
	printf("tailleMap %d\n",select);
	int x=0;
	int y=0;
	//bool premierligne=false;
	bool X=false;
	char nom[MAX_NOM]={"\0"};
	FILE* fNewMap=NULL;
	map_select(select,nom);
	fNewMap=fopen(nom,"r");
	if(fNewMap==NULL){
		printf("Le fichier n'a pu être ouvert\n");
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
				switch(c){
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
				switch(c){
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
		while(c!=EOF){
			c=fgetc(fNewMap);
			if(c=='\n'){
				y++;
				X=true;
			}
			if(!X){
				x++;
			}	
		}
		
		*tMapX=x;
		*tMapY=y;
	fclose(fNewMap);
	}
	printf("fin tailleMap\n");
	
	
	return ;
};
//PRE:en entrée la fonction reçoit la taille de la carte à charger, la structure du niveau niveauA, et un int select qui correspond au numéro 
//dans le tableau de la map sélectionné
//Fonction qui charge le fichier texte représentant une carte, dans une variable globale map. 
void loadMap(int tMapX, int tMapY, TabNiveau* niveauA, int select){
	
	printf("loadMap\n");
	printf("X :%d Y :%d\n",tMapX,tMapY);
	char nom[MAX_NOM]={"\0"};
	FILE* fNewMap=NULL;
	map_select(niveauA->Nmap[select].s,nom);
	fNewMap=fopen(nom,"r");
	
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
		char** loadedMap=malloc(sizeof(char *)*tMapY);
		
		int x=0;
		int y=0;
		*(loadedMap)=malloc(sizeof(char*)*tMapX);
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
		
		if(select==niveauA->current){
			currentMap.c=loadedMap;
			currentMap.taille.x=tMapX;
			currentMap.taille.y=tMapY; 
			currentMap.previous=false;
			niveauA->Nmap[niveauA->current].loadStatus=false;
			niveauA->current=select;
		}
		else if(select>niveauA->current){
			nextMap.c=loadedMap;
			nextMap.taille.x=tMapX; 
			nextMap.taille.y=tMapY; 
			nextMap.previous=false;
			niveauA->Nmap[niveauA->next].loadStatus=false;
			niveauA->next=select;
		}
		else if(select<niveauA->current){
			previousMap.c=loadedMap;
			previousMap.taille.x=tMapX;
			previousMap.taille.y=tMapY;
			previousMap.previous=true;
			niveauA->Nmap[niveauA->previous].loadStatus=false;
			niveauA->previous=select;
		}
		niveauA->Nmap[select].loadStatus=true; //on confirme que cette map du niveau est chargée.
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
//PRE:
//POST:
void Entree_sortie_Map( int select, Direction* entreeN, Direction* sortieN){
	char nom[MAX_NOM]={"\0"};
	FILE* fNewMap=NULL;
	map_select(select,nom);
	printf("%s\n",nom);
	fNewMap=fopen(nom,"r");
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
				switch(c){
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
				switch(c){
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
//PRE:le nombre de map dans niveauA.nombreMap doit être plus grand que 3
//POST:
void choix_map_aleatoire(void){
	
	Direction sortieC=0;
	Direction entreeC=4;
	Direction sortieN;
	Direction entreeN;
	
	//installer la première map, startMap
	printf("startmap\n");
	niveauA.Nmap[0].s=0;
	Entree_sortie_Map(0, &entreeN, &sortieN);
	niveauA.Nmap[0].Next=sortieN;
	niveauA.Nmap[0].previous=entreeN;
	niveauA.Nmap[0].ennemi=true;
	niveauA.Nmap[0].loadStatus=false;
	sortieC=sortieN;
	entreeC=entreeN;
	
	//sélection de toute les map du niveau hors startMap, pre-BossMap et BossMap
	printf("maps\n");
	for(int i=1;i<niveauA.nombreMap-2;i++){

		bool MapOK=true;
		int nRandom;
		do{
			nRandom=(rand()%MAPS);
			Entree_sortie_Map(nRandom, &entreeN, &sortieN);
			if(entreeN==sortieC){
				MapOK=false;
			}
			
		}while(MapOK);
		niveauA.Nmap[i].s=nRandom;
		niveauA.Nmap[i].Next=sortieN;
		niveauA.Nmap[i].previous=entreeN;
		niveauA.Nmap[i].ennemi=true;
		niveauA.Nmap[i].loadStatus=false;
		sortieC=sortieN;
		entreeC=entreeN;
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
	niveauA.Nmap[niveauA.nombreMap-2].previous=entreeN;
	niveauA.Nmap[niveauA.nombreMap-2].ennemi=true;
	niveauA.Nmap[niveauA.nombreMap-2].loadStatus=false;
	
	//selection BossMap, parmis les MapBoss
	printf("Boss\n");
	int nRandomBoss=(rand()%MAPS_BOSS);
	Entree_sortie_Map(nRandomBoss+3+MAPS, &entreeN, &sortieN);
	niveauA.Nmap[niveauA.nombreMap-1].s=nRandomBoss+3+MAPS;
	niveauA.Nmap[niveauA.nombreMap-1].Next=sortieN;
	niveauA.Nmap[niveauA.nombreMap-1].previous=entreeN;
	niveauA.Nmap[niveauA.nombreMap-1].ennemi=true;
	niveauA.Nmap[niveauA.nombreMap-1].loadStatus=false;
	
	for(int m=0;m<niveauA.nombreMap;m++){
		char nomA[MAX_NOM]={"\0"};
		map_select(niveauA.Nmap[m].s,nomA);
		printf("%s\n",nomA);
	}
}
//PRE: aucun pré-requis
//POST:initialisation d'une structure Map à zero pointeur tableau sur NULL et taille x, y à 0 et previous sur false.
void initialisation_Map(Map* initMap){
	
	initMap->c=NULL;
	initMap->taille.x=0;
	initMap->taille.y=0;
	initMap->previous=false;
	return ;
};
//PRE: prend en argument deux int pour la largeur et la hauteur des maps( cette fonction sera changé pour prendre une int qui déterminera le nombre de carte du niveau
//POST: Fait initialement une sélection de map aléatoirement et charge les maps nécessaire au jeux au fur et a mesure (pas encore finit )
void loadMaps(int *tMapX,int* tMapY){

	int nombreMap=8;
	niveauA.nombreMap=nombreMap;
	initialisation_Map(&previousMap);
	initialisation_Map(&nextMap);
	initialisation_Map(&currentMap);
	niveauA.Nmap=malloc(sizeof(SelectionMap)*nombreMap);
	choix_map_aleatoire();
	/*niveauA.Nmap[0].s=0;		// le numéro de cette carte est le 0
	niveauA.Nmap[0].Next=0;	// la sortie de cette carte est vers le haut
	niveauA.Nmap[0].loadStatus=false;//cette map n'est pas chargée en mémoire
	niveauA.Nmap[0].ennemi=true;
	niveauA.Nmap[1].s=3;
	niveauA.Nmap[1].Next=0;	//cette carte n'a pas de sortie
	niveauA.Nmap[1].loadStatus=false;
	niveauA.Nmap[1].ennemi=true;
	niveauA.Nmap[2].s=4;
	niveauA.Nmap[2].Next=0;	//cette carte n'a pas de sortie
	niveauA.Nmap[2].previous=2;
	niveauA.Nmap[2].loadStatus=false;
	niveauA.Nmap[2].ennemi=true;
	niveauA.Nmap[3].s=3;
	niveauA.Nmap[3].Next=0;	//cette carte n'a pas de sortie
	niveauA.Nmap[3].previous=2;
	niveauA.Nmap[3].loadStatus=false;
	niveauA.Nmap[4].s=3;
	niveauA.Nmap[4].Next=0;	//cette carte n'a pas de sortie
	niveauA.Nmap[4].previous=2;
	niveauA.Nmap[4].loadStatus=false;
	niveauA.Nmap[5].s=4;
	niveauA.Nmap[5].Next=0;	//cette carte n'a pas de sortie
	niveauA.Nmap[5].previous=2;
	niveauA.Nmap[5].loadStatus=false;
	niveauA.Nmap[6].s=4;
	niveauA.Nmap[6].Next=0;	//cette carte n'a pas de sortie
	niveauA.Nmap[6].previous=2;
	niveauA.Nmap[6].loadStatus=false;
	niveauA.Nmap[7].s=6;
	niveauA.Nmap[7].Next=5;	//cette carte n'a pas de sortie
	niveauA.Nmap[7].previous=2;
	niveauA.Nmap[7].loadStatus=false;
	*/
	niveauA.current=0;
	int i=0;
	do{
		tailleMap(tMapX,tMapY,niveauA, i);
		loadMap(*tMapX,*tMapY,&niveauA, i);
		i++;
	}while(i<2);
	for(i=0;i<nombreMap;i++){
		niveauA.Nmap[i].ennemi=true;
	}
	loadEnnemi(liste, 0);
	supprimer_ennemi_numero(liste, 0);
	camera.x=currentMap.taille.x/2;//position initiale de la camera affichant une map complète au centre. 
	camera.y=currentMap.taille.y/2;
	return;
}
//PRE:
//POST:cette fonction charge la prochaine map en fonction d'ou se dirige le joueur et d'ou est placée la camera 
void loadNext(int select){
	printf("loadNext %d\n",select);
	int tMapX=0;
	int tMapY=0;
	tailleMap(&tMapX,&tMapY,niveauA, select);
	loadMap(tMapX,tMapY,&niveauA, select);
	loadEnnemi(liste, select);
}
//PRE:Pas vraiment nécessaire pour le moment mais originellement cette foncton devait prendre un argument en entrée pour savoir ou charger la pos joueur (dans quel map)
//POST:Récupération de la position du joueur dans la map de niveauA.Nmap[0] (pour le moment)
Joueur loadJoueur(int select){
	
	printf("loadJoueur\n");
	Joueur J;	//déclaration d'une variable joueur locale
	int x=0;
	int y=0;
	char c=' ';
	bool END=true; //variable booleen pour sortir de la double boucle dés que l'on a trouver la position du joueur
	char nom[MAX_NOM]={"\0"};
	FILE* fNewMap=NULL;
	map_select(select,nom);
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
			if(c=='j'){
				J.pos.x=x;
				J.pos.y=y;
				END=false;
			}
			x++;
		}while(c!='\n'&&c!=EOF&&END);
		y++;
	}while(c!=EOF&&END);
	fclose(fNewMap);
	
	}
	J.vie=3;
	J.tirs=creer_liste_tirs();
	J.maxTirs=4;
	return J;
};
void loadEnnemi(ListeEnnemi* liste, int select){
	
	printf("loadEnnemi\n");
	Coordonnee e;	//tampon coordonnée des ennemis
	//int Dx=0;
	int Dy=0;//variation de position par rapport à currentmap de la position chargée des ennemis
	int x=0;
	int y=0;
	char c=' ';
	//bool END=true; //variable booleen pour sortir de la double boucle dés que l'on a trouver la position du joueur
	if(niveauA.Nmap[select].ennemi){
		char nom[MAX_NOM]={"\0"};
		FILE* fNewMap=NULL;
		map_select(select,nom);
		fNewMap=fopen(nom,"r");
		if(fNewMap==NULL){
			printf("Le fichier n'a pu être ouvert\n");
			
			exit(-1);
		}
		else{
			if(select==niveauA.current){
				//Dx=0;
				Dy=0;
			}
			else if(select==niveauA.next){
				Dy-=nextMap.taille.y;
			}
			else if(select==niveauA.previous){
				Dy+=currentMap.taille.y;
			}

			while(c!='\n'){	//boucle pour éviter de charger dans la map la pemière ligne du fichier texte qui contient des infos
				c=fgetc(fNewMap);
			}
			do{	//boucle parcourrant tous le fichier pour retrouver la position des ennemis dans la carte
				x=0;
				do{
					c=fgetc(fNewMap);
					switch(c){    //probablement pas utile, on verra si on modifie la fonction avec la sauvegarde de partie en cours
						case 'm':
							e.x=x;//+Dx;
							e.y=y+Dy;
							char Nmoto[MAX_NOM]={"moto"};
							nouvel_ennemi(liste, Nmoto,3, e, moto);
							break;
						case 'v':
							e.x=x;//+Dx;
							e.y=y+Dy;
							char Nvoiture[MAX_NOM]={"voiture"};
							nouvel_ennemi(liste, Nvoiture,5, e, voiture);
							break;
						case 'c':
							e.x=x;//+Dx;
							e.y=y+Dy;
							char Ncamion[MAX_NOM]={"camion"};
							nouvel_ennemi(liste, Ncamion,30, e, camion);
							break;
						case 'S':
							e.x=x;//+Dx;
							e.y=y+Dy;
							char NSUV[MAX_NOM]={"SUV"};
							nouvel_ennemi(liste, NSUV,20, e, SUV);
							break;
						default:
							break;
					}
					x++;
				}while(c!='\n'&&c!=EOF);
				y++;
		}while(c!=EOF);
		fclose(fNewMap);
		}
	
	afficher_liste(liste);
	}
	return ;
};

