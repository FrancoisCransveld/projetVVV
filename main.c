#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "LoadMaps.h"
#include "jeu.h"

//#include ""

int main (int argc,char* argv[]){
	
	int t_map_X=0;
	int t_map_Y=0;
	srand(time(NULL));
	//glutInit(&argc,argv);
	//GlutCreateWindow("VeloVsVoiture");
	//glutDisplayFunc(display);
	loadMaps(&t_map_X, &t_map_Y);
	//glutMainLoop();
	return 0;
}
