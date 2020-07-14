#include <math.h>
#include <GL/glut.h>
#include "draw_functions.h"
#include "table.h"


Table::Table()
{

	//Neka struktura ili klasa koja ce da sadrzi lopte i stapove.

	//TO DO 

}

void Table::draw()
{


	//"https://tug.org/pracjourn/2007-4/walden/color.pdf"


	// Pod na kojem je sto
	glColor3d(0.5, 0.5, 0.4); 
	glPushMatrix();
	glTranslated(0, -2, 0);
	drawCuboid(20, 0.1, 20);
	glPopMatrix();

	// Zidovi
	glColor3d(0.3, 0.5, 0.6); 
	glPushMatrix();
	

	//Prednji i Zadnji
	glTranslated(-10, 0, 0); 
	drawCuboid(0.1, 20, 20);
	
	glTranslated(+20, 0, 0); 
	drawCuboid(0.1, 20, 20);
	
	glColor3d(0.3, 0.5, 0.6); 

	//Levi Desni
	glTranslated(-10, 0, -10); 
	drawCuboid(20, 20, 0.1);

	glTranslated(  0, 0, +20); 
	drawCuboid(20, 20, 0.1);
	
	glPopMatrix();


	double hsize = 0.5; // Velicina rupe

	// povrsina stola
	glColor3d(0, 0.3, 0.2); 
	glPushMatrix();
	glTranslated(0, -0.1, 0);
	drawCuboid(8.4, 0.2, 4.4);
	glPopMatrix();

	// ivice od kojih ce lopta da se odbija
	glColor3d(0, 0, 0.5); 
	glPushMatrix();
	glTranslated(-4, 0, +0); 
	drawCuboid(0.1, 0.2, 4.0 - hsize);
	glTranslated(+8, 0, +0); 
	drawCuboid(0.1, 0.2, 4.0 - hsize);
	glTranslated(-2, 0, -2); 
	drawCuboid(4.0 - hsize, 0.2, 0.1);
	glTranslated(-4, 0, +0); 
	drawCuboid(4.0 - hsize, 0.2, 0.1);
	glTranslated(+0, 0, +4); 
	drawCuboid(4.0 - hsize, 0.2, 0.1);
	glTranslated(+4, 0, +0); 
	drawCuboid(4.0 - hsize, 0.2, 0.1);
	glPopMatrix();

	// ivice stola
	glColor3d(0.3, 0.2, 0.2); 
	glPushMatrix();
	glTranslated(-4.2, 0, +0.0); 
	drawCuboid(0.3, 0.3, 4.7);
	glTranslated(+8.4, 0, +0.0); 
	drawCuboid(0.3, 0.3, 4.7);
	glTranslated(-4.2, 0, -2.2); 
	drawCuboid(8.2, 0.3, 0.3);
	glTranslated(+0.0, 0, +4.4); 
	drawCuboid(8.2, 0.3, 0.3);
	glPopMatrix();

	// rupe
	glColor3d(0.0, 0.0, 0.0); 
	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	glTranslated(+4, 2, 0); glutSolidCone(hsize * 0.4, 0.01, 20, 1);
	glTranslated(-4, 0, 0); glutSolidCone(hsize * 0.4, 0.01, 20, 1);
	glTranslated(-4, 0, 0); glutSolidCone(hsize * 0.4, 0.01, 20, 1);
	glTranslated(0, -4, 0); glutSolidCone(hsize * 0.4, 0.01, 20, 1);
	glTranslated(+4, 0, 0); glutSolidCone(hsize * 0.4, 0.01, 20, 1);
	glTranslated(+4, 0, 0); glutSolidCone(hsize * 0.4, 0.01, 20, 1);
	glPopMatrix();

	// nogari
	glColor3d(0.2, 0.2, 0.2); 
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(+3.5, +1.5, 0.1); drawCylinder(0.2, 0.2, 2);
	glTranslated(+0.0, -3.0, 0.0); drawCylinder(0.2, 0.2, 2);
	glTranslated(-7.0, +0.0, 0.0); drawCylinder(0.2, 0.2, 2);
	glTranslated(+0.0, +3.0, 0.0); drawCylinder(0.2, 0.2, 2);
	glPopMatrix();



}