
#include "env.h"

#define NB_ROCHERS 50
#define NB_OBSTACLES 100

typedef struct Point {

	int x;
	int y;
	int z;
	
} Point;


typedef struct Obstacle {

	Point p;
	int rayon;
	
} Obstacle;






void affiche_arene_pyramide(int borne);
