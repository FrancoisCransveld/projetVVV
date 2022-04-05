#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include "LoadMaps.h"
#include "jeu.h"

//calcul la taille d'une carte
void tailleMap(int* tMapX, int* tMapY, int select){
	int x=0;
	int y=0;
	FILE* fNewMap=NULL;
	switch(select){
		case 0:
			fNewMap=fopen("map1.txt","r");
			break;
		case 1:
			fNewMap=fopen("map2.txt","r");
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

//Fonction qui charge le fichier texte représentant une carte une variable globale map
void loadMap(int tMapX, int tMapY, Selection select){
	
	printf("X :%d Y :%d\n",tMapX,tMapY);
	FILE* fNewMap=NULL;
	switch(select.s){
		case 0:
			fNewMap=fopen("map1.txt","r");
			break;
		case 1:
			fNewMap=fopen("map2.txt","r");
			break;
		default:
			break;
	}
	
	if(fNewMap==NULL){
		printf("Le fichier n'a pu être ouvert\n");
		//exit(ERROR_EXIT);
	}
	else{
		char c;
		int x=0;
		int y=0;
		*(nextMap.c)=malloc(sizeof(char*)*tMapX);
		do{
			*((nextMap.c)+y)=malloc(sizeof(char*)*tMapX);
			for(x=0;x<tMapX;x++){
				c=fgetc(fNewMap);
				*(*((nextMap.c)+y)+x)=c;
			}
			fgetc(fNewMap);
			y++;
		}while(c!=EOF);
		y=0;
		
		//currentMap=nextMap;
		do{

			for(x=0;x<tMapX;x++){
				printf("%c",*(*((nextMap.c)+y)+x));
			}
			printf("\n");
			y++;
		}while(y<tMapY);
	}
	fclose(fNewMap);
};
//Fait initialement une sélection de map aléatoirement et charge les maps nécessaire au jeux au fur et a mesure 
void loadMaps(int *tMapX,int* tMapY){
	//int* tMapX;
	//int* tMapY;
	int nombreMap=2;
	niveauA=malloc(sizeof(Selection)*nombreMap);
	niveauA[0].s=0;
	niveauA[0].Next=0;
	niveauA[1].s=1;
	niveauA[1].Next=4;
	int i=0;
	do{
		tailleMap(tMapX,tMapY,niveauA[i].s);
		tailleNext.x=*tMapX;
		tailleNext.y=*tMapY;
		
		loadMap(*tMapX,*tMapY,niveauA[i]);
		if(currentMap==NULL){
			currentMap=nextMap;
			tailleCurrent.x=tailleNext.x;
			tailleCurrent.y=tailleNext.y;
			camera.x=tailleCurrent.x/2;//position initiale de la camera affichant une map complète au centre. 
			camera.y=tailleCurrent.y/2;
			tailleNext.x=0;
			tailleNext.y=0;
			printf("X :%d Y :%d\n",tailleCurrent.x,tailleCurrent.y);
			nextMap=NULL;
		}
		i++;
	}while(nextMap==NULL);
	
	return;
}
void LoadNext(){
	
	int nextLoad;
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
	tailleNext.x=*tMapX;
	tailleNext.y=*tMapY;
	loadMap(*tMapX,*tMapY,niveauA[nextLoad]);
	if(
}
Joueur loadJoueur(int select){
	
	Joueur J;
	int x=0;
	int y=0;
	char c=' ';
	FILE* fNewMap=NULL;
	switch(select){
		case 0:
			fNewMap=fopen("map1.txt","r");
			break;
		case 1:
			fNewMap=fopen("map2.txt","r");
			break;
		default:
			break;
	}
	if(fNewMap==NULL){
		printf("Le fichier n'a pu être ouvert\n");
		//exit(ERROR_EXIT);
	}
	else{
	do{
		x=0;
		do{
			c=fgetc(fNewMap);
			if(c=='j'){
				J.pos.x=x;
				J.pos.y=y+tailleNext.y;

			}
			x++;
		}while(c!='\n'&&c!=EOF);
		y++;
	}while(c!=EOF);
	fclose(fNewMap);
	}
	J.vie=3;
	return J;
}
