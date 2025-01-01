struct SysDynamique {
    void (*pt_init)(coord *point); // Pointe vers la fonction init des coordonnées (x,y,z)
    void (*pt_actualiser)(coord * point, lorenz_settings *para); // Pointe vers la fonction actualiser des coordonnées x, y,z et dt
    struct lorenz_settings* param; // Tableau fixé au système dynamique (Lorenz : σ, ρ, β) + dt
};

struct LorenzSettings {
    float sigma;
    float beta;
    float rho;
    float dt;
};

struct Coord {
    float x;
    float y;
    float z;
};

typedef struct Coord Coord;
typedef struct LorenzSettings Params;

Params* ask_parametres_lorentz;
Coord* ask_position_initiale;
void init_ltz(Coord *point);
void actualiser_ltz(Coord * point, Params *para);
void creation_ltz(SysDynamique *systeme);
void choisir_sys(SysDynamique* systeme);

