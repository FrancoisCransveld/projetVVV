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
#include "interface.h"
#include "joueur.h"
#include "menu.h"
#include "collision.h"
#include "score.h"
#include "keyboard.h"



void upDateKeyboard(int num){
	printf("updateKeyboard %d \n",selectionMenu);
	if(selectionMenu==1){
		jeu();
	}
	if(INPUT){
		INPUT=false;
	}
	else{
		UP=false;
		LEFT=false;
		RIGHT=false;
		DOWN=false;
		SPACE=false;
	}
	glutTimerFunc(30, upDateKeyboard, 0);
};

void upDateInvulnerabilite(int num){
	if(j.debutInvulnerabilite){
		j.debutInvulnerabilite=false;
		glutTimerFunc(2000, upDateInvulnerabilite, 5);
	}
	else{
		j.invulnerable=false;
	}
}

void upDateTirs(int num){
	printf("upDateTirs\n");
	if(selectionMenu==1){	
		if (SPACE == true){	//si on a appuyé la touche Espace SPACE=true
			if(j.tirs->nombre<j.maxTirs){	//si le nombre de tirs ne dépasse pas le maximum de tirs que peut tirer simultanément le joueur
				tirs(j.tirs,j.pos,pistolet,j.dir);	//alors on crée un nouveau tirs dans la liste j.tirs
			}
			SPACE=false;
		}
		if(j.tirs->nombre>0){	//si il existe au moins un tirs dans la liste j.tirs
		
			deplacement_tirs(j.tirs);	//on fait la demande de déplacement des tirs pour tous les tirs
			for(int i=0;i<liste->nombre;i++){			
										//double boucle pour vérifier la collision entre un ennemi et un tirs
				for(int tirs=0;tirs<j.tirs->nombre;tirs++){
					if(i<liste->nombre){			//étant donné qu'on est susceptible de supprimer des ennemis après un tirs, alors que l'ont doit 
										//encore tester qu'il n'y a pas de collision entre cette ennemi et les potentiel autre tirs, dans le
										//case ou l'ennemi est le dernier on va faire des tests sur un ennemi en dehors de la liste et faire
										//un segmentation fault. cette condition gère ce cas limite empêchant de faire des test en dehors de 
										//la liste des ennemis
						
						if(collision_tirs_ennemi(i,tirs)){ 	//test de collision entre le tirs (tirs) et l'ennemi (i) 
							retirer_vie_numero(liste, i,degat_tirs(j.tirs, tirs));	//si collision on retire les points de vies à l'ennemi 
							supprimer_tirs_numero(j.tirs,tirs);				//on supprime le tirs qui a touché
						}
					}
					
				}
			
			}
		}
		
	}
	glutTimerFunc(25, upDateTirs,1);
};

void upDateEnnemi(int num){
	printf("upDateEnnemi\n");
	bool colli=true;
	if(selectionMenu==1){
		action_ennemi(liste);
		colli=collisionEnnemiJoueur();
	}

	if(colli){
		glutTimerFunc(800, upDateEnnemi,2);
	}
	else{
		glutTimerFunc(120, upDateEnnemi,2); 
	}
};

void switchMap(){
	
	bool switchPrevious=false;	//booleen qui gardera la vérification que l'on doit effectuer un switchMap avec previousMap
	bool switchNext=false;		//booleen qui gardera la vérification que l'on doit effectuer un switchMap avec previousMap
	int tamponCam=0;		//entier qui gardera la valeur à appliquer à la composante en y de la position de la camera 
	int tamponJ=0;			//entier qui gardera la valeur à appliquer à la composante en y de la position de j
	int nextLoad;			//correspond au numero dans le tableau niveauA.Nmap de la carte à charger (fonction loadMap, mais qui sera appelé par la fonction LoadNext)
	Coordonnee variationE;//variable qui sera envoyer à modifier_pos_ennemis(ListeEnnemi* liste, Coordonnee variation) pour déplacer les ennemis
	variationE.x=0;	//entier pour la variation des ennemis qu'on initialise a 0
	variationE.y=0;	//entier pour la variation des ennemis qu'on initialise a 0
	if(camera.y<=-nextMap.taille.y/2){		//condition vérifiant si la camera est à une position sur l'axe vertical plus petite que -32 case (remarque dans glut  								// l'axes y a son sens positif vers le bas et négatif vers le haut).
		tamponCam=camera.y+nextMap.taille.y;	
		tamponJ=j.pos.y+nextMap.taille.y;	//on donne les nouvelles valeurs des éléments après le switch au tampon 
		variationE.y+=nextMap.taille.y;
		switchNext=true;			//on enregistre que le switch s'effectue avec nextMap
	}
	if(camera.y>=((previousMap.taille.y/2)+currentMap.taille.y)){
		if(nextMap.taille.y!=0){
			tamponCam=camera.y-nextMap.taille.y;
			tamponJ=j.pos.y-nextMap.taille.y;	//on donne les nouvelles valeurs des éléments après le switch au tampon 
			variationE.y-=nextMap.taille.y;
			switchPrevious=true;		//on enregistre que le switch s'effectue avec previousMap
		}
		else{
			tamponCam=camera.y-currentMap.taille.y;
			tamponJ=j.pos.y-currentMap.taille.y;	//on donne les nouvelles valeurs des éléments après le switch au tampon 
			variationE.y-=currentMap.taille.y;
			switchPrevious=true;		//on enregistre que le switch s'effectue avec previousMap
		}
	}
	
	if(switchNext||switchPrevious){	//si on a une des deux booleen a true c'est que l'on doit effectuer une rotation de carte
		printf("switchMap\n");
		modifier_pos_ennemis(liste,variationE);	//les valeurs tampons de la camera et de joueur, ainsi que la variation pour les ennemis sur l'axe des y 
		camera.y=tamponCam;				//est appliqué au variable en question		
		j.pos.y=tamponJ;
	}
	if(switchNext){	//si on a un switch vers next lié à la position de la caméra à la moitié de nextMap.
	//On passe currentMap à previousMap et nextMap à currentMap et on va recharger l'éventuelle nextMap
		printf("ici 1");
		previousMap=currentMap;
		currentMap=nextMap;
		nextMap.c=NULL;		//nextMap avant d'être rechargé est réinitialisé à zero
		nextMap.taille.y=0;
		nextMap.taille.x=0;
		niveauA.Nmap[niveauA.previous].loadStatus=false;//on change le status de previous avant de modifié sa position dans le tableau
		niveauA.Nmap[niveauA.previous].ennemi=true;	//Les ennemis pourront être rechargé pour cette carte
		niveauA.previous=niveauA.current;
		niveauA.current=niveauA.next;
		nextLoad=niveauA.next+1;	//la prochaine carte à chargée sera à la position niveauA.next+1 du tableau niveauA.nMap
		
	}
	if(switchPrevious){
	//On passe currentMap à currentMap à nextMap et previousMap à currentMap et on va recharger l'éventuelle previousMap
		nextMap=currentMap;
		currentMap=previousMap;
		previousMap.c=NULL;		//previousMap avant d'être rechargé est réinitialisé à zero
		previousMap.taille.y=0;
		previousMap.taille.x=0;
		niveauA.Nmap[niveauA.next].loadStatus=false;//on change le status de previous avant de modifié sa position dans le tableau
		niveauA.Nmap[niveauA.next].ennemi=true;	//Les ennemis pourront être rechargé pour cette carte
		niveauA.next=niveauA.current;
		niveauA.current=niveauA.previous;
		nextLoad=niveauA.previous-1;	//la prochaine carte à chargée sera à la position niveauA.previous-1 du tableau niveauA.nMap
		
		
	}
	if(nextLoad<niveauA.nombreMap&&nextLoad>=0){
		printf("prochaine Map loade :%d nextMap %d previousMap %d currentmap %d",nextLoad,niveauA.next,niveauA.previous,niveauA.current);
		printf("cam x%d y%d\n",camera.x,camera.y);
		loadNext(nextLoad);	//On fait le chargement de la carte nextLoad et des ennemis présent dessus
	}

};
void mort(){
	j.vie--;
	j.hp=5;
	supprimer_liste_ennemi(liste);
	if(j.vie<=0){
		game_over();
	}
	else{
		liste = creer_liste();
		niveauA.current=0;
		niveauA.next=1;
		loadMaps();
		j.pos=load_respawn_Joueur(niveauA.current);
		
	}
};
void game_over(){
	
	selectionMenu=5;
	inscription_score();
	
};
void jeu()
{
	printf("jeu \n");
	glutKeyboardFunc(KeyboardJeu);		//fonction de glut gérant le clavier
	glutSpecialFunc(KeyboardSpecialJeu);
	if (LEFT == true)
	{
		moveLeft(j);		//va se déplacer vers la gauche si on appuie sur q
	
	}
	if (RIGHT == true)
	{
		
		moveRight(j);		//va se déplacer vers la droite si on apppuie sur d
		
	}
	if (UP == true)
	{
		moveUp(j);		//on se déplace vers le haut en appuyant sur z
		
	}
	
	if (DOWN == true)
	{
		
        	moveDown(j);		//on se déplace vers le bas en appuyant sur s
		
	}
	if (j.hp<=0){

		mort();		
	}
	if(j.invulnerable&&j.debutInvulnerabilite){
		upDateInvulnerabilite(5);
	}
	glutPostRedisplay();
};
