class Ball{

    double r,g,b; // crvena zelena plava
    double x,z; // koordinate
    double vx,vz; // brzine kretanja po osama;
    double radius; 
    bool visible; 

    public:
        Ball();
        void setColor(double r, double g, double b); //postavlja boju lopte
        void setPosition(double x, double z); // postavlja poziciju lopte na stolu
        void setV (double vx, double vz); //postavlja brzinu lopte
        void setVisible(bool v); //Postavlja vidljivost, ukoliko je na stolu je true ukoliko upadne u rupu je false
        bool getVisible();
        double getX(); 
        double getZ(); // geteri za poziciju
        void draw(); // funkcija koja isrctava lopte na stolu
        double getRadius(); //geter za precnik
        bool moving(); // Da li se lopta krece
        double distanceTo(double px, double pz); //oredjluje udaljenost lopte od rupa i drugih lopti
	    void collideHoles(); // Provera da li je kugla upala u rupu, menja njenu vidljivost
	    void collideCushions(); // Sudar sa martinelom, menaj brzinu
	    void collideBall(Ball& other); // Proverava da li su se kugle sudarile, i menja im brizne
	    void updateSpeed(double timeStep); // Updejtuje brzinu lopte, zaustavlja je ako je previse spora
	    void updatePosition(double timeStep); // Updejtuje poziciju lopte tokom vremena



};

