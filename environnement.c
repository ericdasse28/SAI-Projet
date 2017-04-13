/* Programme créé le 12 Avril 2017 à 13:17
 * Auteur : Eric DASSE
 */
#include <stdio.h>
#include "GL/gl.h"
#include "GL/glut.h"

void display();
void Animer();
void mobile_test();
void clavier ( unsigned char touche, int x, int y );

float z0 = 0, x0 = 0, Y = 0;
float angle = 0, angle_droite = 0, angle_gauche = 0;

void specialPress(int key, int mouseX, int mouseY) {
	
	if (key == GLUT_KEY_UP) {
		glTranslatef(++x0, ++Y, 0);
	}
	
	if (key == GLUT_KEY_DOWN) {
		glTranslatef(--x0, --Y, 0);
	}
	
	if (key == GLUT_KEY_RIGHT) {
		glTranslatef(++x0, --Y, 0);
	}
	
	if (key == GLUT_KEY_LEFT) {
		glTranslatef(--x0, ++Y, 0);
	}

}

int main (int argc, char* argv[]) {
	
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE |GLUT_DEPTH);
  int width = 600 ;
  int height = 600 ;
  glutInitWindowSize(width,height);
  // Ou en fullscreen : glutFullScreen();
glEnable(GL_DEPTH_TEST);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutInitWindowPosition( 50, 50 );
  glutCreateWindow("snake");
  glClearColor( 0.30f, 0.16f,0.14f,0.0f);

  glutDisplayFunc(display);
  glutIdleFunc(Animer);
  glutKeyboardFunc(clavier);
  glutSpecialFunc(specialPress);
  //glutIdleFunc(vitesse);
  glutMainLoop();

  return 0;

}

void lines(int borne){
	glBegin(GL_LINES);
	glColor3f( 0.8f, 0.8f, 0.8f);
	
	int i;
	for( i=-borne;i<=borne;i++){
	
			glVertex2i(i,-borne);
			glVertex2i(i,borne);
	
	}
	
	for(i=-borne;i<=borne;i++){
	
			glVertex2i(-borne,i);
			glVertex2i(borne,i);
	
	}
	
	
	/* Murs */
	for (i = -borne; i<=borne; i++) {
		glVertex3f(borne,i,0);
		glVertex3f(borne,i,borne);
		
		glVertex3f(-borne,i,0);
		glVertex3f(-borne,i,borne);
		
		glVertex3f(i,-borne,0);
		glVertex3f(i,-borne,borne);
		
		glVertex3f(i,borne,0);
		glVertex3f(i,borne,borne);
	}
	
	
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


void display() {
	
	glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
     glLoadIdentity();   
  int eyex, eyey, eyez, cx, cy, cz, upx, upy, upz;
  eyex=30;
  eyey=20;
  eyez=15;
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
	
	glTranslatef(x0,Y,z0);
	//glRotatef(angle,0,0,1);
	 
	lines(150);
	axes();
	
	glutSwapBuffers();
}


void Animer() {
	/*
	x0 += .5;
	Y += .5;
	*/
	
	angle += .5;
	
	glutPostRedisplay();
}


void clavier ( unsigned char touche, int x, int y ) {

	
	if (touche == 'a') {
		printf("La souris est située à (%d, %d)",x,y);
		
	}
}	
		
