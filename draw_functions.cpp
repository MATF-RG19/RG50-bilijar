#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "draw_functions.h"


void drawSphere(double radius)
{
	GLUquadric* quad = gluNewQuadric();
    int slices = 30;
    int stacks = 30;
	gluSphere(quad, radius, slices, stacks);
}


void drawCuboid(double width, double height, double depth)
{
	glPushMatrix();
	glScaled(width, height, depth);
	glutSolidCube(1);
	glPopMatrix();
}


void drawCylinder(double baseRadius, double topRadius, double height)
{

	GLUquadric* quad = gluNewQuadric();

    int slices = 30;
    int stacks = 1;

	
	glPushMatrix();
	glRotated(180, 0, 1, 0);
	gluDisk(quad, 0, baseRadius, slices, stacks);
	glPopMatrix();

	
	gluCylinder(quad, baseRadius, topRadius, height, slices, stacks);

	
	glPushMatrix();
	glTranslated(0, 0, height);
	gluDisk(quad, 0, topRadius, slices, stacks);
	glPopMatrix();
}

void setShininess(double s)
{
	// sjaj
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);

	// boja
	float colour[4];
	colour[0] = (float)s;
	colour[1] = (float)s;
	colour[2] = (float)s;
	colour[3] = 1;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colour);
}


