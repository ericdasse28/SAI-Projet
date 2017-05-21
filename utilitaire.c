#include "GL/gl.h"
#include "GL/glut.h"
#include <math.h>

#include "env.h"
#include "utilitaire.h"

void affiche_vitesse(vitesse v) {
	float vx = v.norme * cosf(v.angle);
	float vy = v.norme * sinf(v.angle);
		
	glBegin(GL_LINES);
	
		glColor3f(0.9,0.1,0.9);
		glVertex2f(0,0);		
		glVertex2f(vx, vy);
		
	glEnd();
}



void affiche_arene_pyramide(int borne) {

	/*On dessine le rectangle pour le sol*/
	glBegin(GL_QUADS);
	
		glColor3f(0.8, 0.8, 0.8);
		
		glVertex2i(-borne, -borne);
		glVertex2i(-borne, borne);
		glVertex2i(borne, -borne);
		glVertex2i(borne, borne);
		
	glEnd();
	
	
	
	/*Calcul du point sommet de la pyramide (situé sur l'axe central)*/
	
	
	/*Dessin des triangles*/
	
	
	
	
}
