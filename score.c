#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "jeu.h"
#include "menu.h"
#include "interface.h"
#include "keyboard.h"
#include "ennemi.h"
#include "score.h"
#include "LoadMaps.h"
//PRE:
//POST: crée une liste chainée d'ennemi et renvoie un pointeur vers cette structure contenant l'adresse du premier élément créé. Cet élément est initialiser avec nom=Bot1 et hp=1 et le pointeur suivant=NULL
ListeScore* creer_liste_score(void){
	
	printf("creer_listeScore\n");
	char nom[MAX_NOM]={"\0"};
	ListeScore* listeSc=malloc(sizeof(ListeScore));
	ElementScore* eScore=malloc(sizeof(ElementScore));
	if(listeSc==NULL||eScore==NULL){
		exit(EXIT_FAILURE);
	}
	
	eScore->element.sco=0;
	eScore->element.place=0;
	eScore->suivant=NULL;
	strcpy(eScore->element.nom,nom);
	listeSc->premier=eScore;
	listeSc->nombre=0;
	
	return(listeSc);
};
void nouvel_elementScore(ListeScore* listeSc, char nom[], int EntreeScore,int place){
	
	ElementScore* actuel;
	ElementScore* nouveau=malloc(sizeof(ElementScore));
	nouveau->element.sco=EntreeScore;
	nouveau->element.place=place;
	nouveau->suivant=NULL;
	strcpy(nouveau->element.nom,nom);
	
	if(listeSc->premier!=NULL){
		actuel=listeSc->premier;
		while(actuel->suivant!=NULL){
			actuel=actuel->suivant;
		}
		actuel->suivant=nouveau;
		
	}
	else{
		actuel=nouveau;
		listeSc->premier=actuel;
	}
	listeSc->nombre++;
};
//PRE:l'int numero est le numéro dans la liste chainée de l'élément que l'on veut modifier ( attention on commence à 1 pas zero)
//POST:
void suprimer_elementScore_n(ListeScore* listeSc,int numero){
	int i=0;
	if(numero<=listeSc->nombre){
		ElementScore* actuel=listeSc->premier;
		if(listeSc->nombre>1){
			ElementScore* suivant;
			suivant=actuel->suivant;
			if(numero!=1){
				numero--;
				while(i<numero-1){
					actuel=suivant;
					suivant=suivant->suivant;
					i++;
				}
				actuel->suivant=suivant->suivant;
				free(suivant);
			}
			else{
				listeSc->premier=suivant;
				free(actuel);
			}
		}
		else {
			listeSc->premier=NULL;
			free(actuel);
		}
		listeSc->nombre--;
			
	}
	else{
		printf("Impossible, il n'y a plus d'ennemi ou le numero de l'ennemi est en dehors de la liste!\n");
	}
	
};
void suprimer_liste_elementScore(ListeScore* listeSc){
	int i=0;
	int nombreElem=listeSc->nombre;
	if(listeSc->premier!=NULL){
		
		while(i<nombreElem){
			printf("suppression %d\n",i);
			suprimer_elementScore_n(listeSc,1);
			afficher_listeSc(listeSc);
			i++;	
		}
		printf("tous supprime\n");
		listeSc->premier=NULL;
		listeSc->nombre=0;
	}
	else{
		printf("Impossible, il n'y a plus d'element score!\n");
	}
};
//PRE:l'int numero est le numéro dans la liste chainée de l'élément que l'on veut modifier ( attention on commence à 1 pas zero)
//POST:
void modifier_elementScore(ListeScore* listeSc,int numero,int EntreeScore,int place,char* nom){
	int i=0;
	ElementScore* actuel=listeSc->premier;
	if(numero<=listeSc->nombre+1){
		while(i<numero-1){
			actuel=actuel->suivant;
			i++;
		}
		actuel->element.sco=EntreeScore;
		actuel->element.place=place;
		strcpy(actuel->element.nom,nom);
	}
	if(listeSc->nombre==0&&numero==1){
		listeSc->nombre=1;
	}
};
void afficher_listeSc(ListeScore* listeSc){
	int i=0;
	printf("---Liste score %d: ---\n",listeSc->nombre);
	ElementScore* actuel=listeSc->premier;
	while(i<listeSc->nombre){
	printf(" nom :%s score : %d place : %d adresse: %hx\n",actuel->element.nom,actuel->element.sco,actuel->element.place,actuel);
	if(actuel->suivant!=NULL){
		actuel=actuel->suivant;
	}
	i++;
	}
	printf("-----------fin liste----------\n");
};			
int transcr_char_int(char valeur){
    
	int val=0;
	bool continuer=true;
	do{
	        if(('0'+val)==valeur){
	        	continuer=false;
	        }
	        else{
	        	val++;
	        }
	}while(continuer);

	return val;
}
int recuperer_tableau_score(ListeScore* listeSc){
	
	FILE* fTabScore=NULL;
	int tailleTableau=0;
	fTabScore=fopen("tableau_des_score.txt","r");
	if(fTabScore==NULL){
		printf("recuperer_tableau echoue ! Le fichier n'a pu être ouvert\n");
	}
	else{
		printf("fichier ouvert\n");
		char actuel=' ';
		
		int i=0;
		bool Header=true;
		do{
			
			actuel=fgetc(fTabScore);
			printf("%c",actuel);
			if(actuel=='T'){
				actuel=fgetc(fTabScore);
				printf("%c",actuel);
				while(actuel!='\n'){
					tailleTableau*=10;
					tailleTableau+=transcr_char_int(actuel);
					actuel=fgetc(fTabScore);
					printf("%c",actuel);
				}
				Header=false;
				printf("taille tab :%d\n",tailleTableau);
			}
		}while(actuel!=EOF&&Header);
		if(tailleTableau>0){
			do{
				int scoreActuel=0;
				int place=0;
				char nom[MAX_NOM]={"\0"};
				
				actuel=fgetc(fTabScore);
				printf("%c",actuel);
				if(actuel=='P'){
					actuel=fgetc(fTabScore);
					printf("%c",actuel);
					while(actuel!=' '){
						place*=10;
						place+=transcr_char_int(actuel);
						actuel=fgetc(fTabScore);
						printf("%c",actuel);
					}
				}
				actuel=fgetc(fTabScore);
				printf("%c",actuel);
				if(actuel=='S'){
					actuel=fgetc(fTabScore);
					printf("%c",actuel);
					while(actuel!=' '){
						scoreActuel*=10;
						scoreActuel+=transcr_char_int(actuel);
						actuel=fgetc(fTabScore);
						printf("%c",actuel);
					}
				}
				actuel=fgetc(fTabScore);
				printf("%c",actuel);
				if(actuel=='N'){
					actuel=fgetc(fTabScore);
					printf("%c",actuel);
					int lettreNom=0;
					
					while(actuel!='\n'){
						nom[lettreNom]=actuel;
						actuel=fgetc(fTabScore);
						printf("%c",actuel);
						if(lettreNom<MAX_NOM){
							lettreNom++;
						}
					}
				}
				if(i==0&&listeSc->premier!=NULL){
					modifier_elementScore(listeSc,1,scoreActuel,place,nom);
				}
				else{
					nouvel_elementScore(listeSc,nom,scoreActuel,i+1);
				}
				i++;
			}while(i<tailleTableau&&actuel!=EOF);
		}
	fclose(fTabScore);
	}
	return tailleTableau;
}
void inscrire_tableau_score(ListeScore* listeSc){
	
	FILE* fTabScore=NULL;
	int tailleTableau=listeSc->nombre;
	int boucle=0;
	char CharActuel;
	int i=0;
	ElementScore* actuel=listeSc->premier;
	fTabScore=fopen("tableau_des_score.txt","w");
	if(fTabScore==NULL){
		printf("Inscrire echouer! Le fichier n'a pu être ouvert\n");
		exit(1);
	}
	else{
		printf("inscrire fichier ouvert!\n");
		fputc('T',fTabScore);
		char* nombreActuel=int_vers_char(tailleTableau);
		do{
			CharActuel=nombreActuel[i];
			if(CharActuel!='\0'){
				fputc(CharActuel,fTabScore);
			}
			i++;
		}while(CharActuel!='\0');
		i=0;
		fputc('\n',fTabScore);
		
		do{
			int scoreActuel=actuel->element.sco;
			int place=boucle+1;
			char nom[MAX_NOM]={"\0"};
			strcpy(nom,actuel->element.nom);

			fputc('P',fTabScore);
			nombreActuel=int_vers_char(place);
			do{
				CharActuel=nombreActuel[i];
				if(CharActuel!='\0'){
					fputc(CharActuel,fTabScore);
				}
				i++;
			}while(CharActuel!='\0');
			i=0;
			fputc(' ',fTabScore);
			fputc('S',fTabScore);
			nombreActuel=int_vers_char(scoreActuel);
			do{
				CharActuel=nombreActuel[i];
				if(CharActuel!='\0'){
					fputc(CharActuel,fTabScore);
				}
				i++;
			}while(CharActuel!='\0');
			i=0;
			fputc(' ',fTabScore);
			fputc('N',fTabScore);
			
			CharActuel=nom[i];
			while(CharActuel!='\0'&&i<MAX_NOM){
				fputc(CharActuel,fTabScore);
				i++;
				CharActuel=nom[i];
			}
			i=0;
			fputc('\n',fTabScore);
			actuel=actuel->suivant;
			boucle++;
		}while(boucle<tailleTableau);
		free(nombreActuel);
		fclose(fTabScore);
	}
	
}
int inserer_nouveau_score_selon_classement(ListeScore* listeSc,ScoreJ* Nouveau){
	
	int Rplace=0;
	if(listeSc!=NULL){
		ElementScore* actuel=listeSc->premier;
		ElementScore* precedent=NULL;
		ElementScore* nouveau=malloc(sizeof(ElementScore));
		nouveau->element=*Nouveau;
		nouveau->suivant=NULL;
		
		int tailleListe=listeSc->nombre;
		//int placeNouveau=tailleListe;
		bool decalage=false;
		for(int i=0;i<tailleListe;i++){
			if(actuel->element.sco<nouveau->element.sco&&(!decalage)){
				nouveau->element.place=actuel->element.place;
				if(precedent!=NULL){
					precedent->suivant=nouveau;
				}
				Rplace=nouveau->element.place;
				nouveau->suivant=actuel;
				decalage=true;
				printf("ajout \n");
			}
			if(decalage){
				actuel->element.place++;
			}
			precedent=actuel;
			actuel=actuel->suivant;
		}
		if(Rplace==1){
			printf("ajout debut\n");
			listeSc->premier=nouveau;
		}
		if(Rplace==0){
			printf("ajout fin\n");
			precedent->suivant=nouveau;
		}
		listeSc->nombre++;
	}
	return Rplace;
}
bool encodage_nom(char* nom,int* nombreLettre){
	
	printf("encodage_nom nlettre:%d\n",*nombreLettre);
	
	char NouvelleLettre='\0';
	bool fin=false;
	
	
		glutKeyboardFunc(Keyboard);
		printf("%c\n",lettre);
		if(lettre!='\r'&&lettre!='\0'){
			printf("!= n\n");
			NouvelleLettre=lettre;
			(*nombreLettre)++;
			if(*nombreLettre<MAX_NOM&&NouvelleLettre!='\b'){
				strcat(nom,&NouvelleLettre);
			}
			else if(NouvelleLettre=='\b'){
				printf("backspace\n");
				(*nombreLettre)--;
				nom[*nombreLettre-1]='\0';
			}
			NouvelleLettre='\0';
			lettre='\0';
		}
		else if(lettre=='\r'){
			printf("enter\n");
			fin=true;
			lettre='\0';
		}
	printf("lettre %c nouvelle: %c\n",lettre,NouvelleLettre);
	return fin;
	
}
void inscription_score(int n){
	
	printf("Inscription_score\n");

	if(selectionMenu==5||selectionMenu==6){
		if(selectionMenu==5){
			printf("Inscription_score 5\n");
			selectionMenu=6;
			char vide[2]={"\0"};
			strcpy(nomEncode,vide);
			nombreLettre=0;
			encodage_nom(nomEncode,&nombreLettre);

		}
		else if(selectionMenu==6){
			printf("Inscription_score 6\n");
			if(encodage_nom(nomEncode,&nombreLettre)){
				
				ScoreJ newScore;
				printf("newScore\n");
				strcpy(newScore.nom,nomEncode);
				
				newScore.sco=score;
				newScore.place=0;
				int placeClassement=0;
				printf("creer_liste\n");
				ListeScore* listeSc=creer_liste_score();
				printf("recuperer tab\n");
				newScore.place=recuperer_tableau_score(listeSc);
				afficher_listeSc(listeSc);
				if(newScore.place>0){
					printf("place=%d\n",newScore.place);	placeClassement=inserer_nouveau_score_selon_classement(listeSc,&newScore);
				}
				else if(newScore.place==0){
					printf("place=%d\n",newScore.place);
					modifier_elementScore(listeSc,0,newScore.sco,newScore.place+1,nomEncode);
				}
				afficher_listeSc(listeSc);
				printf("inscrire Tab\n");
				
				inscrire_tableau_score(listeSc);
				suprimer_liste_elementScore(listeSc);
				free(listeSc);
				MENU=true;
				selectionMenu=0;
				printf("Inscription_score 0\n");
			}
		}
		glutTimerFunc(50, inscription_score,4);
	} 
}

