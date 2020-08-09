class Ball{

    double r,g,b; // crvena zelena plava
    double x,z; // koordinate
    double vx,vz; // brzine kretanja po osama;
    double radius; // poluprecnik; 
    bool visible;

    public:
        Ball();
        void setColor(double r, double g, double b);
        void setPosition(double x, double z);
        void setV (double vx, double vz);
        void setVisible(bool v);
        double getX();
        double getZ(); // geteri za poziciju
        void draw();
        double getRadius();




};

