struct SysDynamique {
    void (*pt_init)(double*,double*,double*); // Pointe vers la fonction init des coordonnées (x,y,z)
    void (*pt_actualiser)(double*, double*, double*, double); // Pointe vers la fonction actualiser des coordonnées x, y,z et dt
    double param[3]; // Tableau fixé au système dynamique (Lorenz : σ, ρ, β)
}

struct lorenz_settings {
    float sigma;
    float beta;
    float rho;
}

struct coord {
    float x;
    float y;
    float z;
}


