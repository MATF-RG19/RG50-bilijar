
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "draw_functions.h"
#include "table.h"

Table table;
double camAngle1 = -90;
double camAngle2 = 20;

void display(void)
{
	
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

	

	glutDisplayFunc(display);


	glutMainLoop();
	return 0;
}
