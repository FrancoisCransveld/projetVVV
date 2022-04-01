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
void loadMap(int tMapX, int tMapY, int select){
	
	printf("X :%d Y :%d\n",tMapX,tMapY);
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
		char c;
		nextMap=malloc(sizeof(char*)*tMapY);
		int x=0;
		int y=0;
		*(nextMap)=malloc(sizeof(char*)*tMapX);
		do{
			*(nextMap+y)=malloc(sizeof(char*)*tMapX);
			for(x=0;x<tMapX;x++){
				c=fgetc(fNewMap);
				*(*(nextMap+y)+x)=c;
			}
			fgetc(fNewMap);
			y++;
		}while(c!=EOF);
		y=0;
		//currentMap=nextMap;
		do{

			for(x=0;x<tMapX;x++){
				printf("%c",*(*(nextMap+y)+x));
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
	int select[2]={0,1};
	int i=0;
	do{
		tailleMap(tMapX,tMapY,select[i]);
		tailleNext.x=*tMapX;
		tailleNext.y=*tMapY;
		
		loadMap(*tMapX,*tMapY,select[i]);
		if(currentMap==NULL){
			currentMap=nextMap;
			tailleCurrent.x=tailleNext.x;
			tailleCurrent.y=tailleNext.y;
			tailleNext.x=0;
			tailleNext.y=0;
			printf("X :%d Y :%d\n",tailleCurrent.x,tailleCurrent.y);
			nextMap=NULL;
		}
		i++;
	}while(nextMap==NULL);
	
	return;
}
