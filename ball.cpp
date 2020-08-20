#include "ball.h"
#include "draw_functions.h"
#include <GL/glut.h>
#include <cmath>
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

bool Ball::getVisible()
{
	return visible;
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


bool Ball::moving()
{
	if(!visible) return false; //ukoliko nije na stolu ne krece se
	return vx != 0 || vz != 0; // ukoliko je neka od brzina razlicita od 0, krece se
}

//Funkcija odredjuje 2D rastojanjee od lopte do neke pozicije.
double Ball::distanceTo(double px, double pz)
{
	
	double dx = x - px;
	double dz = z - pz;
	return sqrt(dx * dx + dz * dz);
}

void Ball::collideHoles()
{
	//X i Z kordinate stola za bilijar.
	double holes[6][2] =
	{
		{4, 2},
		{4, -2},
		{-4, 2},
		{-4, -2},
		{0, 2},
		{0, -2}
	};

	// Proverava za svaku rupu rastojanje do lopte.
	for(int i = 0; i < 6; i++)
	{
		
		if(distanceTo(holes[i][0], holes[i][1]) < 0.3) visible = false;
	}
}
// sudar sa martinelom
void Ball::collideCushions()
{
	
	if(!visible) return;

	// odbijanje od martinele, reflektuju se brzine.
	if(x - radius < -3.9 && vx < 0) vx = -vx;
	if(x + radius > +3.9 && vx > 0) vx = -vx;
	if(z - radius < -1.9 && vz < 0) vz = -vz;
	if(z + radius > +1.9 && vz > 0) vz = -vz;
}

// sudar sa drugom loptom
void Ball::collideBall(Ball& ball2)
{
	
	if(!visible) return;
	if(!ball2.visible) return;

	// Ukoliko su lopte udaljene jedna od druge.
	double distance = distanceTo(ball2.x, ball2.z);
	if(distance * 0.5 > radius) return;

	// normalizovan vektor izmedju lopti
	if(distance < 0.001) return;
	double ux = (ball2.x - x) / distance;
	double uz = (ball2.z - z) / distance;

	// normalne komponente brzine
	double n1 = vx * ux + vz * uz;
	double n2 = ball2.vx * ux + ball2.vz * uz;

	// Ignorisanje lopti koje se udaljavaju
	if(n1 < n2) return;

	// zamena normalnih komponenti brzine
	vx += n2 * ux - n1 * ux;
	vz += n2 * uz - n1 * uz;
	ball2.vx += n1 * ux - n2 * ux;
	ball2.vz += n1 * uz - n2 * uz;
}

// Menjanje brzine tokom vremena
void Ball::updateSpeed(double timeStep)
{
	
	if(!visible) return;

	double s = sqrt(vx * vx + vz * vz); // jednacina sa khan akademije za velicinu brzine razlozene na komponente
	double k = 4; //koeficijent trenja 

	// zaustavi spore lopte
	if(s < k * timeStep)
	{
		vx = 0;
		vz = 0;
		return;
	}

	// Trenje
	double f = 1 - k / s * timeStep; 
	if(f < 0) f = 0;
	vx *= f;
	vz *= f;
}

// Menjanje pozicije lopte tokom vremena u zavisnosti od brzine
void Ball::updatePosition(double timeStep)
{
	
	if(!visible) return;

	
	x += vx * timeStep;
	z += vz * timeStep;
}