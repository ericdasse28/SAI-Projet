#include <stdio.h>
#include <math.h>
#include <time.h>
#include "GL/gl.h"
#include "GL/glut.h"

#include "utilitaire.h"

double angle = 0;
int atBegin = 0; //Cf. fonction Animer()...
int eyex = -150, eyey = -100, eyez = 30, cx, cy, cz, upx, upy, upz; //Paramètres de la caméra
Obstacle tab_obstacles[NB_OBSTACLES]; //Tableau qui contient tous les obstacles (rochers, arbres, ...)

int longueur_arene = 50;

void Animer();
void afficher_mobile(Point p);
void affiche_arene_pyramide(int borne);
void afficher_maison();
void dessiner_obstacles();
void initialisation_objets();
void keyPress(unsigned char touche, int x, int y);













int main (int argc, char* argv[]) {

	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  int width = 600 ;
  int height = 600 ;
  glutInitWindowSize(width,height);
  // Ou en fullscreen : glutFullScreen();

  glutInitWindowPosition( 50, 50 );
  glutCreateWindow("Anaconda");
 	glEnable(GL_DEPTH_TEST);
 
 	glutDisplayFunc(display);
 	glutKeyboardFunc(keyPress);
 	glutIdleFunc(Animer);
 
 	initialisation_objets();
 
 	glutMainLoop();
  
  
  return EXIT_SUCCESS;
}










//--------------------------------------------------------------------------------------

/* Fonctions utilitaires */







void lines(int borne){
	glBegin(GL_LINES);
	//glColor3f( 0.8f, 0.8f, 0.8f);
	
	int i;
	for( i=-borne;i<=borne;i+=5){
	
			glVertex2i(i,-borne);
			glVertex2i(i,borne);
	
	}
	
	for(i=-borne;i<=borne;i+=5){
	
			glVertex3f(-borne,i, 0.1);
			glVertex3f(borne,i, 0.1);
	
	}
	
	
	/* Murs */
/*	for (i = -borne; i<=borne; i++) {
		glVertex3f(borne,i,0);
		glVertex3f(borne,i,borne);
		
		glVertex3f(-borne,i,0);
		glVertex3f(-borne,i,borne);
		
		glVertex3f(i,-borne,0);
		glVertex3f(i,-borne,borne);
		
		glVertex3f(i,borne,0);
		glVertex3f(i,borne,borne);
	}
	
*/	
	glEnd();
}


void axes() {
	glBegin(GL_LINES);
	
		//X en rouge
		glColor3f( 0.9,0.1,0.2);
		glVertex3f(0,0,0);
		glVertex3f(100,0,0);
		
		//Y en vert
		glColor3f(0.1,0.9,0.2);
		glVertex3f(0,100,0);
		glVertex3f(0,0,0);
		
		//Z en bleu
		glColor3f(0.1,0.2,0.9);
		glVertex3f(0,0,0);
		glVertex3f(0,0,100);
		
	glEnd();
}





//-----------------------------------------------------------------------------------------------
 /* Arène de jeu */




//Dessin de l'arène de jeu
void affiche_arene_pyramide(int borne) {

	
	
	
	
	/*Calcul du point sommet de la pyramide (situé sur l'axe central)*/
	int z = -50;
	
	
	/*Dessin des triangles*/
	
	glColor3f(0.7, 0.6, 0.2);
	glBegin(GL_TRIANGLES);
	
		glVertex3f(-borne, -borne, 0);
		glVertex3f(-borne, borne, 0);
		glVertex3f(0, 0, z);
		
		
		glVertex3f(-borne, -borne, 0);
		glVertex3f(borne, -borne, 0);
		glVertex3f(0, 0, z);
		
		glVertex3f(borne, -borne, 0);
		glVertex3f(borne, borne, 0);
		glVertex3f(0, 0, z);
		
		
		glVertex3f(borne, borne, 0);
		glVertex3f(-borne, borne, 0);
		glVertex3f(0, 0, z);
		
	glEnd();
	
	
	/*Traçage des contours du triangles*/
	/*
	glBegin(GL_LINES);
		
		glColor3f(0.2, 0.2, 0.2);
		
		glVertex3f(-borne, -borne, 0);
		glVertex3f(0, 0, z);
		
		glVertex3f(-borne, borne, 0);
		glVertex3f(0, 0, z);
		
		
		glVertex3f(borne, -borne, 0);
		glVertex3f(0, 0, z);		
		
		glVertex3f(borne, borne, 0);
		glVertex3f(0, 0, z);
		
		
	glEnd();
	*/
	
	
	/*On dessine le rectangle pour le sol*/
	glBegin(GL_QUADS);
	
		glColor3f(0.8, 0.8, 0.8);
		
		glVertex2i(-borne, -borne);
		glVertex2i(-borne, borne);
		glVertex2i(borne, borne);
		glVertex2i(borne, -borne);
		
	glEnd();
	
	
}







//--------------------------------------------------------------------------------------
/* Construction des obstacles */



//Initialisation du tableau des obstacles
void initialisation_objets() {


	srand(time(NULL));
	
	printf("%d\n", NB_ROCHERS);
	
	
	/*Dessin des rochers*/
	for (int i = 0; i < NB_ROCHERS; i++) {
	
		int test_signe = rand()%2; //0 ou 1
		int signe;
		
		if (test_signe == 0)
			signe = -1;
		else
			signe = 1;
			
			
		Point p;
		p.x = signe*(rand()%longueur_arene);
		p.y = signe*(rand()%longueur_arene);
		p.z = 0;
		
		
		tab_obstacles[i].p = p;
		tab_obstacles[i].rayon = 1;
		printf("Point p (%d, %d, %d)\n", p.x, p.y, p.z);
		
	}
		
}



//Affichage d'un rocher
void afficher_rocher(Point p) {

	glPushMatrix();
	
		glTranslatef(p.x, p.y, p.z);
		
		glColor3f(0.5, 0.5, 0.5);
		glutSolidDodecahedron();
		
		
	glPopMatrix();
	
}






//Dessin de tous les obstacles
void dessiner_obstacles() {


	/*Dessin des rochers*/
	for (int i = 0; i < NB_ROCHERS; i++) {
	
		afficher_rocher(tab_obstacles[i].p);
		//printf("Point p (%d, %d, %d)\n", p.x, p.y, p.z);
		
	}
		


}








//Affichage du mobile (serpent dans notre cas)
void afficher_mobile(Point p) {

	glPushMatrix();
	
		glTranslatef(p.x, p.y, p.z+2.5);
		glColor3f(0.9, 0.2, 0.3);
		glutSolidCube(5);
		
	glPopMatrix();
	
}






















/*Fonctions utilitaires*/
void keyPress(unsigned char touche, int x, int y) {

	if (touche == 's') {
	
		atBegin = 1;
		eyex = -30;
		eyey = 0;
		eyez = 20;
		
	}
	
	
	
}









void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
     glLoadIdentity();   
  
  
  cx = cy = cz = 0;
  upx = upy = 0;
  upz=1;
  
  
   int left,right, bottom, top, near, far;
  right=top=1;
  left=bottom=-1;
  near=2;
  far=100000;
  glFrustum(left,right, bottom, top, near, far);

  gluLookAt(eyex, eyey, eyez, cx, cy, cz, upx, upy, upz);
  glRotatef(angle,0,0,1);
  
  
  /*
  	GLUquadricObj *pObj;
  pObj = gluNewQuadric();
  gluQuadricNormals(pObj, GLU_SMOOTH);
  gluSphere(pObj, 10, 1024, 1024);
  gluDeleteQuadric(pObj);
  */
  
  affiche_arene_pyramide(longueur_arene);
  
  glColor3f(0.1, 0.1, 0.1);
  lines(longueur_arene);
  
  
    axes();
  
  //afficher_rocher();
  dessiner_obstacles();
  
  Point p;
  p.x = 0; p.y = 0; p.z = 0;
  afficher_mobile(p);
  
  
  glutSwapBuffers();
}



void Animer() {
	/*
	x0 += .5;
	Y += .5;
	*/
	
	if (atBegin == 0)
		angle += .5;
		
	else {
		angle = 0;
	}
	
	glutPostRedisplay();
}
