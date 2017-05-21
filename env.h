#ifndef UTILITAIRE
#define UTILITAIRE

void axes(); /* Dessine le repère 3D */
void display();

typedef struct vitesse {
	float norme;
	float angle;
} vitesse;

typedef struct point {
	float x;
	float y;
	float z;
} point;

void affiche_vitesse(vitesse v);

#endif
