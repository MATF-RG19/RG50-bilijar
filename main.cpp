
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "draw_functions.h"
#include "table.h"

//Pre pocetka rada sam pogledao neke prethodne projekte kao i projekat kolege koji je radio bilijar pre mene.
// Takodje za dosta stvari sam koristio Khan akademiju, 
//https://www.khanacademy.org/science/physics/two-dimensional-motion/two-dimensional-projectile-mot/a/what-are-velocity-components
//Koristio sam red book 
//http://www.glprogramming.com/red/
// I generalno razgledao razne tutoriale po YT ali tada nisam kopirao linkove pa nmgu da ih okacim.
// Dosta parametara sam birao nasumicno, pa prepravljao nakon pokretanja ukoliko su losi, pa usled nedostatka 
//vremena dosta parametra je verovatno losije.


Table table;
double camAngle1 = -90;
double camAngle2 = 20;

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case ' ':
		// Restart na space.
		table.start();
		break;
	case 27:
		// Quit na exc
		exit(0);
		break;
	}
	
}


void passive(int x, int y)
{
	// Podesavanje ugla stapa
	int centre = glutGet(GLUT_WINDOW_WIDTH)/2;
	table.setStickAngle((x - centre) * 0.2 - camAngle1);
}

// Funkcija za reagovanje na pritiskanje dugmica na tastaturi koji se ne mogu prestaviti ASCII-jem
void special(int key, int x, int y)
{
	// Rotiranje kamere sa strelicama
	switch(key)
	{
	case GLUT_KEY_LEFT:
		camAngle1 -= 5;
		break;
	case GLUT_KEY_RIGHT:
		camAngle1 += 5;
		break;
	case GLUT_KEY_UP:
		camAngle2 -= 5;
		break;
	case GLUT_KEY_DOWN:
		camAngle2 += 5;
	}

	// Ogranjicenje ugla
	if(camAngle2 < 10) camAngle2 = 10;
	if(camAngle2 > 80) camAngle2 = 80;
}


void mouse(int button, int state, int x, int y)
{
	// Za udarac
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(!table.moving()) table.shoot();
	}
}


void display(void)
{
	
	int currentTime = glutGet(GLUT_ELAPSED_TIME); //Za dobijanje Delta t, ondnosno vremena izmedju frejmova.
	table.update(currentTime);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// Velicina prozora
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	// Perspektiva
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double fieldOfView = 50.0;
	double aspectRatio = (double)width / (double)height;
	double nearPlane = 0.1;
	double farPlane = 100.0;
	gluPerspective(fieldOfView, aspectRatio, nearPlane, farPlane);

	// Pozicija kamere
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0, 0, -8);
	glRotated(camAngle2, 1, 0, 0);
	glRotated(camAngle1, 0, 1, 0);

	// Osvetljenje 
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat lightAmbient[4] = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat lightDiffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightSpecular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightPosition[4] = {0.0f, 4.0f, 0.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	
	glEnable(GL_NORMALIZE);

	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    
	table.draw();

	
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	// inicijalizacija
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Bilijar");

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(passive);
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}
