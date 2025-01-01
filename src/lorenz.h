struct LorenzSettings {
    double sigma;
    double beta;
    double rho;
};

typedef struct LorenzSettings Params;

struct Coord {
    double x;
    double y;
    double z;
};

typedef struct Coord Coord;


struct SimSettings {  //pour simuler dans gnuplot
    double dt;    // Incrément de temps
    double tmax;  // Temps maximal de simulation
};

typedef struct SimSettings SimSettings;


struct SysDynamique {
    void (*pt_init)(Coord *point); // Pointe vers la fonction init des coordonnées (x,y,z)
    void (*pt_actualiser)(Coord * point, Params *para, double dt); // Pointe vers la fonction actualiser des coordonnées x, y,z et dt
    Params *param; // Tableau fixé au système dynamique (Lorenz : σ, ρ, β) + dt
};

typedef struct SysDynamique SysDynamique;

Coord* ask_position_initiale();
Params* ask_parametres_lorentz();
SimSettings* ask_simulation_settings();

void init_ltz(Coord*);
void actualiser_ltz(Coord*, Params*, double);
void creation_ltz(SysDynamique*);
void choisir_sys(SysDynamique*);
void generer_fichier(char*, void (*fct_actu)(Coord*, Params*, double), Coord*, Params*, SimSettings*);


