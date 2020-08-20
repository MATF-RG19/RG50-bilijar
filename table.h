#include <vector>
#include "ball.h"
class Table
{
	Ball balls[16]; //Lopte
    int time;          // vreme za animaciju kretanja lopti kako bi usporile
	double stickAngle; //Ugao stapa

public:
	Table();
	void start(); //funkcija za pocetak, ili restart igre
	void draw(); // Crtanje stola
	int num_of_visible(); //Funkcija koja broji koliko ima vidljivih lopti
	void setStickAngle(double angle); // Funkcija koja postavlja ugao stapa
	bool moving(); // Funkcija koja prikazuje da li se lopte pomeraju
	void shoot(); // Funkcija za udarac
	void update(int currentTime); // Funkcija koja updejtuje sta se desava na stolu.
};