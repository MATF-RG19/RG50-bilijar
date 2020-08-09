#include "ball.h"
#include "draw_functions.h"
#include <GL/glut.h>
Ball::Ball()
{
	setColor(0, 0, 0);
	setPosition(0, 0);
	setV(0, 0);
	setVisible(true);
	radius = 0.1;
}

void Ball::setColor(double r, double g, double b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

void Ball::setPosition(double x, double z)
{
	this->x = x;
	this->z = z;
}


double Ball::getX()
{
	return this->x;
}


double Ball::getZ()
{
	return this->z;
}

void Ball::setV(double vx, double vz)
{
	this->vx = vx;
	this->vz = vz;
}

void Ball::setVisible(bool v)
{
	this->visible = v;
}

double Ball::getRadius(){
    return this->radius;
}

void Ball::draw()
{
	if(!visible) return;

	glColor3d(r, g, b); 
	setShininess(1.0); 
	glPushMatrix();
	glTranslated(x, radius, z);
	glRotated(180, 1, 0, 0);
	drawSphere(radius);
	glPopMatrix();
}