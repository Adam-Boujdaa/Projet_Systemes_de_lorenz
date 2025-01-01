struct SysDynamique {
    void (*pt_init)(coord *point); // Pointe vers la fonction init des coordonnées (x,y,z)
    void (*pt_actualiser)(coord * point, lorenz_settings *para); // Pointe vers la fonction actualiser des coordonnées x, y,z et dt
    struct lorenz_settings param;; // Tableau fixé au système dynamique (Lorenz : σ, ρ, β)
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

struct lorenz_settings* ask_parametres_lorentz;
struct coord* ask_position_initiale;
void init_ltz(coord *point);
void actualiser_ltz(coord * point, lorenz_settings *para);
