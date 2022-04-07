#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include "LoadMaps.h"
//#include "jeu.h"
#include "interface.h"
//PRE:prend en argument deux pointeurs d'int pour renvoiyer la taille trouvée et un int qui correspond à la map qui devrai être traitée dans niveauA.Nmap[select]
//POST:calcul la taille d'une carte et renvoie cette taille via les argument d'entrée tMapX et tMapY
void tailleMap(int* tMapX, int* tMapY, TabNiveau niveauA, int select){
	printf("tailleMap\n");
	int x=0;
	int y=0;
	FILE* fNewMap=NULL;
	switch(niveauA.Nmap[select].s){
		case 0:
			fNewMap=fopen("map1.txt","r");
			break;
		case 1:
			fNewMap=fopen("map2.txt","r");
			break;
		case 2:
			fNewMap=fopen("map3.txt","r");
			break;
		default:
			break;
	}
	if(fNewMap==NULL){
		printf("Le fichier n'a pu être ouvert\n");
		//exit(ERROR_EXIT);
	}
	else{
		char c=' ';
		while(c!=EOF){
			c=fgetc(fNewMap);
			if(c=='\n'){
				y++;
			}
			else{
				x++;
			}	
		}
		*tMapX=x/y;
		*tMapY=y;	
	}
	fclose(fNewMap);
	return ;
};
//PRE:en entrée la fonction reçoit la taille de la carte à charger, la structure du niveau niveauA, et un int select qui correspond au numéro 
//dans le tableau de la map sélectionné
//Fonction qui charge le fichier texte représentant une carte, dans une variable globale map. 
void loadMap(int tMapX, int tMapY, TabNiveau* niveauA, int select){
	
	printf("loadMap\n");
	printf("X :%d Y :%d\n",tMapX,tMapY);
	FILE* fNewMap=NULL;
	switch(niveauA->Nmap[select].s){
		case 0:
			fNewMap=fopen("map1.txt","r");
			break;
		case 1:
			fNewMap=fopen("map2.txt","r");
			break;
		case 2:
			fNewMap=fopen("map3.txt","r");
			break;
		default:
			break;
	}
	
	if(fNewMap==NULL){
		printf("Le fichier n'a pu être ouvert\n");
		//exit(ERROR_EXIT);
	}
	else{
		printf("Le fichier ouvert\n");
		char** loadedMap=malloc(sizeof(char *)*tMapY);
		char c;
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
		
		if(currentMap.c==NULL||select==niveauA->current){
			currentMap.c=loadedMap;
			currentMap.taille.x=tMapX;
			currentMap.taille.y=tMapY; 
			currentMap.previous=false;
			niveauA->current=select;
		}
		else if(select>niveauA->current){
			if(niveauA->Nmap[select-1].Next==0||niveauA->Nmap[select-1].Next==2){
				nextMap.c=loadedMap;
				nextMap.taille.x=tMapX; 
				nextMap.taille.y=tMapY; 
				nextMap.previous=false;
				niveauA->next=select;
			}
			else if(niveauA->Nmap[select-1].Next==1||niveauA->Nmap[select-1].Next==3){
				nextLRMap.c=loadedMap;
				nextLRMap.taille.x=tMapX; 
				nextLRMap.taille.y=tMapY; 
				nextLRMap.previous=false;
				niveauA->nextLR=select;
			}
		}
		else if(select<niveauA->current){
			if(niveauA->Nmap[select].Next==0||niveauA->Nmap[select].Next==2){
				nextMap.c=loadedMap;
				nextMap.taille.x=tMapX; 
				nextMap.taille.y=tMapY; 
				nextMap.previous=true;
				niveauA->next=select;
			}
			else if(niveauA->Nmap[select].Next==1||niveauA->Nmap[select].Next==3){
				nextLRMap.c=loadedMap;
				nextLRMap.taille.x=tMapX; 
				nextLRMap.taille.y=tMapY; 
				nextLRMap.previous=true;
				niveauA->nextLR=select;
			}
		}
		niveauA->Nmap[select].loadStatus=true; //on confirme que cette map du niveau est chargée.
		do{

			for(x=0;x<tMapX;x++){
				printf("%c",*(*((loadedMap)+y)+x));
			}
			printf("\n");
			y++;
		}while(y<tMapY);
	}
	fclose(fNewMap);
	
};
//PRE: aucun pré-requis
//POST:initialisation d'une structure Map à zero pointeur tableau sur NULL et taille x, y à 0 et previous sur false.
void initialisation_Map(Map* initMap){
	
	initMap->c=NULL;
	initMap->taille.x=0;
	initMap->taille.y=0;
	initMap->previous=false;
	return ;
};

//Fait initialement une sélection de map aléatoirement et charge les maps nécessaire au jeux au fur et a mesure 
void loadMaps(int *tMapX,int* tMapY){
	//int* tMapX;
	//int* tMapY;
	int nombreMap=3;
	initialisation_Map(&nextLRMap);
	initialisation_Map(&nextMap);
	initialisation_Map(&currentMap);
	niveauA.Nmap=malloc(sizeof(SelectionMap)*nombreMap);
	niveauA.Nmap[0].s=0;		// le numéro de cette carte est le 0
	niveauA.Nmap[0].Next=0;	// la sortie de cette carte est vers le haut
	niveauA.Nmap[0].loadStatus=false;//cette map n'est pas chargée en mémoire
	niveauA.Nmap[1].s=1;
	niveauA.Nmap[1].Next=1;	//cette carte n'a pas de sortie
	niveauA.Nmap[1].loadStatus=false;
	niveauA.Nmap[2].s=2;
	niveauA.Nmap[2].Next=5;	//cette carte n'a pas de sortie
	niveauA.Nmap[2].loadStatus=false;
	niveauA.current=0;
	int i=0;
	initialisation_Map(&nextLRMap);
	do{
		tailleMap(tMapX,tMapY,niveauA, i);
		loadMap(*tMapX,*tMapY,&niveauA, i);
		/*if(currentMap.c==NULL){
			currentMap=nextMap;
			camera.x=currentMap.taille.x/2;//position initiale de la camera affichant une map complète au centre. 
			camera.y=currentMap.taille.y/2;
			nextMap.taille.x=0;
			nextMap.taille.y=0;
			printf("truc mauc X :%d Y :%d\n",currentMap.taille.x,currentMap.taille.y);
			nextMap.c=NULL;
		}*/
		
		i++;
	}while(i<3);
	camera.x=currentMap.taille.x/2;//position initiale de la camera affichant une map complète au centre. 
	camera.y=currentMap.taille.y/2;
	return;
}
void LoadNext(){
	
	/*int nextLoad;
	if(currentMap.Num.Next==j.dir){
		nextLoad=currentMap.Num.s+1;
		if(currentMap.Num.Next==0||currentMap.Num.Next==2){
			currentMap=nextMap;
			currentMap=
		}
	else{
		nextLoad=currentMap.Num.s-1;
	}
	
	tailleMap(tMapX,tMapY,niveauA[nextLoad].s);
	nextMap.taille.x=*tMapX;
	nextMap.taille.y=*tMapY;
	loadMap(*tMapX,*tMapY,niveauA[nextLoad]);
	if(*/
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
	FILE* fNewMap=NULL;
	switch(select){    //probablement pas utile, on verra si on modifie la fonction avec la sauvegarde de partie en cours
		case 0:
			fNewMap=fopen("map1.txt","r");
			break;
		case 1:
			fNewMap=fopen("map2.txt","r");
			break;
		case 2:
			fNewMap=fopen("map3.txt","r");
			break;
		default:
			break;
	}
	if(fNewMap==NULL){
		printf("Le fichier n'a pu être ouvert loadJoueur\n");
		
		//exit(ERROR_EXIT);
	}
	else{
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
	return J;
}
