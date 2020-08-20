#include <math.h>
#include <GL/glut.h>
#include "draw_functions.h"
#include "table.h"

Table::Table()
{
    
	//https://tug.org/pracjourn/2007-4/walden/color.pdf

    balls[0].setColor(0.9, 0.9, 0.9); // bela
	balls[1].setColor(1.0, 0.9, 0.2); // zuta
	balls[2].setColor(0.1, 0.2, 0.7); // tamno plava
	balls[3].setColor(1.0, 0.0, 0.0); // crvena
	balls[4].setColor(0.4, 0.0, 0.5); // tamno ljubicasta
	balls[5].setColor(1.0, 0.5, 0.3); // svetlo narandzasta
	balls[6].setColor(0.2, 0.8, 0.4); // zelena
	balls[7].setColor(1.0, 0.5, 0.8); // svetlo ljubicasta
	balls[8].setColor(0.0, 0.0, 0.0); // crna
	balls[9].setColor(0.6, 0.5, 0.2); // tamno zuta
	balls[10].setColor(0.2, 0.5, 1.0); // plava
	balls[11].setColor(1.0, 0.2, 0.3); // svetlo crvena
	balls[12].setColor(0.7, 0.0, 0.7); // ljubicasta
	balls[13].setColor(0.8, 0.3, 0.0); // narandzasta
	balls[14].setColor(0.0, 0.3, 0.2); // tamno zelena
	balls[15].setColor(0.5, 0.0, 0.0); // tamno crvena
	

	time = 0;
	stickAngle = 90;


}

void Table::setStickAngle(double angle)
{
	stickAngle = angle;
}

void Table::start(){
	//Pocetna pozicija za belu loptu
	balls[0].setPosition(2, 0);
	balls[0].setV(0, 0);
	balls[0].setVisible(true);

	// Pocetna pozicija za ostale lopte, pravim trougao.
	int k = 1;
	for(int i = 1; i < 6; i++)
	{
		for(int j = 1; j < i + 1; j++)
		{
			
			double r = balls[k].getRadius();
			double x = (6 - i * 2) * r - 2;
			double z = (j * 2 - i - 1) * r;
			balls[k].setPosition(x, z);
			balls[k].setV(0, 0);
			balls[k].setVisible(true);
			k++;
		}
	}
}

int Table::num_of_visible()
{
	int number = 0;
	for(int i = 0; i < 16; i++)
	{
		if(balls[i].getVisible()) number++;
	}
	return number;
}

// Provera da li se neka lopta krece
bool Table::moving()
{
	
	for(int i = 0; i < 16; i++)
	{
		if(balls[i].moving()) return true;
	}

	
	return false;
}


void Table::shoot()
{
	const double s = 15; // Brzina udarca
	const double pi = 3.14;
	double a = stickAngle * pi / 180 + pi; // Ugao sa kojim udaramo loptu, 

	// Postavljanje brzine 
	balls[0].setV(s * sin(a), s * cos(a));
}


void Table::update(int currentTime)
{
	double timeStep = 0.001; 
	int i, j;
	
	while(time < currentTime)
	{
		// Provera da li kugla upada u rupu, ili udara u martinelu ili udara u drugu kuglu
		for(i = 0; i < 16; i++)
		{
			
			balls[i].collideHoles();
			balls[i].collideCushions();

			
			for(j = 0; j < i; j++)
			{
				balls[i].collideBall(balls[j]);
			}
		}

		// Menjanje brzina i pozicije kako vreme tece
		for(i = 0; i < 16; i++)
		{
			balls[i].updateSpeed(timeStep);
			balls[i].updatePosition(timeStep);
		}

		// Vracanje bele kugle na sto ukoliko je upala u rupu.
		if(!moving() && !balls[0].getVisible())
		{
			balls[0].setPosition(0, 0);
			balls[0].setV(0, 0);
			balls[0].setVisible(true);
		}

		;
		// Ukoliko su sve lopte upale, zapocni igru ponovo.
		if(num_of_visible() == 1) start();

		time++;
	}
}

void Table::draw()
{
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


	double hsize = 0.6; // Velicina rupe

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

	//Crtanje kugli
	for(int i = 0; i < 16; i++)
	{
		balls[i].draw();
	}

	//Crtanje stapa

	if(!moving())
	{
		glColor3d(0.7, 0.6, 0.5); 
		glPushMatrix();
		glTranslated(balls[0].getX(), 0, balls[0].getZ());
		glRotated(stickAngle, 0, 1, 0);
		glTranslated(0, 0.15, 0.4);
		glRotated(-5, 1, 0, 0);
		drawCylinder(0.02, 0.06, 5.0);
		glPopMatrix();
	}



}