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
	printf("tailleMap %d\n",select);
	int x=0;
	int y=0;
	//bool premierligne=false;
	bool X=false;
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
		case 3:
			fNewMap=fopen("map4.txt","r");
			break;
		case 4:
			fNewMap=fopen("map5.txt","r");
			break;
		case 5:
			fNewMap=fopen("map6.txt","r");
			break;
		case 6:
			fNewMap=fopen("map7.txt","r");
			break;
		default:
			break;
	}
	if(fNewMap==NULL){
		printf("Le fichier n'a pu être ouvert\n");
		//exit(ERROR_EXIT);
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
		case 3:
			fNewMap=fopen("map4.txt","r");
			break;
		case 4:
			fNewMap=fopen("map5.txt","r");
			break;
		case 5:
			fNewMap=fopen("map6.txt","r");
			break;
		case 6:
			fNewMap=fopen("map7.txt","r");
			break;
		/*case 7:
			fNewMap=fopen("map8.txt","r");
			break;
		case 8:
			fNewMap=fopen("map9.txt","r");
			break;*/
		default:
			break;
	}
	
	if(fNewMap==NULL){
		printf("Le fichier n'a pu être ouvert\n");
		//exit(ERROR_EXIT);
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
		/*
			if(niveauA->Nmap[select-1].Next==0||niveauA->Nmap[select-1].Next==2){
				nextMap.c=loadedMap;
				nextMap.taille.x=tMapX; 
				nextMap.taille.y=tMapY; 
				nextMap.previous=false;
				niveauA->Nmap[niveauA->next].loadStatus=false;
				niveauA->next=select;
			}
			else if(niveauA->Nmap[select-1].Next==1||niveauA->Nmap[select-1].Next==3){
				nextLRMap.c=loadedMap;
				nextLRMap.taille.x=tMapX; 
				nextLRMap.taille.y=tMapY; 
				nextLRMap.previous=false;
				niveauA->Nmap[niveauA->nextLR].loadStatus=false;
				niveauA->nextLR=select;
			}
		}
		else if(select<niveauA->current){
			if(niveauA->Nmap[select].Next==0||niveauA->Nmap[select].Next==2){
				nextMap.c=loadedMap;
				nextMap.taille.x=tMapX; 
				nextMap.taille.y=tMapY; 
				nextMap.previous=true;
				niveauA->Nmap[niveauA->next].loadStatus=false;
				niveauA->next=select;
			}
			else if(niveauA->Nmap[select].Next==1||niveauA->Nmap[select].Next==3){
				nextLRMap.c=loadedMap;
				nextLRMap.taille.x=tMapX; 
				nextLRMap.taille.y=tMapY; 
				nextLRMap.previous=true;
				niveauA->Nmap[niveauA->nextLR].loadStatus=false;
				niveauA->nextLR=select;
			}
		}*/
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

	int nombreMap=8;
	niveauA.nombreMap=nombreMap;
	initialisation_Map(&previousMap);
	initialisation_Map(&nextMap);
	initialisation_Map(&currentMap);
	niveauA.Nmap=malloc(sizeof(SelectionMap)*nombreMap);
	niveauA.Nmap[0].s=0;		// le numéro de cette carte est le 0
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
		case 3:
			fNewMap=fopen("map4.txt","r");
			break;
		case 4:
			fNewMap=fopen("map5.txt","r");
			break;
		case 5:
			fNewMap=fopen("map6.txt","r");
			break;
		case 6:
			fNewMap=fopen("map7.txt","r");
			break;
		default:
			break;
	}
	if(fNewMap==NULL){
		printf("Le fichier n'a pu être ouvert loadJoueur\n");
		
		//exit(ERROR_EXIT);
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
			case 3:
				fNewMap=fopen("map4.txt","r");
				break;
			case 4:
				fNewMap=fopen("map5.txt","r");
				break;
			case 5:
				fNewMap=fopen("map6.txt","r");
				break;
			case 6:
				fNewMap=fopen("map7.txt","r");
				break;
			default:
				break;
		}
		if(fNewMap==NULL){
			printf("Le fichier n'a pu être ouvert\n");
			
			//exit(ERROR_EXIT);
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
				/*if(!niveauA.Nmap[select].previous){
					if(niveauA.Nmap[niveauA.current].Next==0){
						Dy-=64;
					}
					else if(niveauA.Nmap[niveauA.current].Next==2){
						Dy+=64;
					}
				}
				else{
					if(niveauA.Nmap[select].Next==0){
						Dy+=64;
					}
					else if(niveauA.Nmap[select].Next==2){
						Dy-=64;
					}
				}*/
			/*abandonné pour le moment car trop compliqué 
			else if(select==niveauA.nextLR){
				if(!niveauA.Nmap[select].previous){
					if(niveauA.Nmap[niveauA.current].Next==3){
						Dx-=64;
					}
					else if(niveauA.Nmap[niveauA.current].Next==1){
						Dx+=64;
					}
				}
				else{
					if(niveauA.Nmap[select].Next==3){
						Dx+=64;
					}
					else if(niveauA.Nmap[select].Next==1){
						Dx-=64;
					}
				}
			}*/
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

