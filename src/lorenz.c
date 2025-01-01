 #include <stdio.h>
 #include <stdlib.h>
 #include "lorenz.h"

Coord *ask_position_initiale(){       // Permet de demander la position initiale
    Coord* position = malloc(sizeof(Coord));
    printf("Choisir coordonnee x : ");
    scanf("%lf", &(position->x));
    printf("Choisir coordonnee y : ");
    scanf("%lf", &(position->y));
    printf("Choisir coordonnee z : ");
    scanf("%lf", &(position->z));
    return position;
}

Params *ask_parametres_lorentz (){
    Params *params = malloc (sizeof(Params));
    printf("Choisir parametre Sigma : ");
    scanf("%lf", &(params->sigma));
    printf("Choisir parametre Rho : ");
    scanf("%lf", &(params->rho));
    printf("Choisir parametre Beta : ");
    scanf("%lf", &(params->beta));
    return params;
}

SimSettings* ask_simulation_settings() {
    SimSettings* sim = malloc(sizeof(SimSettings));
    printf("Choisir l'incrément de temps (dt) : ");
    scanf("%lf", &(sim->dt));
    printf("Choisir le temps maximal (Tmax) : ");
    scanf("%lf", &(sim->tmax));
    return sim;
}


void init_ltz(Coord *point) {
    point->x = 1.0;
    point->y = 2.0;
    point->z = 3.0;
}


void actualiser_ltz(Coord *point, Params *para, double dt) {
    double dx = para->sigma * (point->y - point->x);
    double dy = point->x * (para->rho - point->z) - point->y;
    double dz = point->x * point->y - para->beta * point->z;

    point->x += dx * dt;
    point->y += dy * dt;
    point->z += dz * dt;
}


void creation_ltz(SysDynamique *systeme, Params *params) {
    systeme->pt_init = init_ltz;
    systeme->pt_actualiser = actualiser_ltz;

    systeme->param = malloc(sizeof(Params));
    if (!systeme->param) {
        fprintf(stderr, "Erreur\n");
        exit(EXIT_FAILURE);
    }
    
    systeme->param->sigma = params->sigma;
    systeme->param->rho = params->rho;
    systeme->param->beta = params->beta;
}

void choisir_sys(SysDynamique *systeme, Params *params) {
    printf("Liste du choix du système dynamique :\n");
    printf("1 : Système de Lorentz.\n");
    printf("Votre choix :\n");

    int choix;

    scanf("%d",&choix);

    if (choix == 1) {
        printf("Vous avez choisi le système de Lorenz.\n");
        creation_ltz(systeme, params);
    }
}


void generer_fichier(char *nom_fichier, void (*fct_actu)(Coord*, Params*, double), Coord *pt, Params *params, SimSettings *sim) {
    FILE *f = fopen(nom_fichier, "w");

    if (!f) {
        perror("Erreur lors de l'ouverture du fichier.");
        return;
    }

    double tmax = sim->tmax;
    double dt = sim->dt;
    double t = 0;

    while(t < tmax) {
        fprintf(f, "%lf %lf %lf %lf\n", t, pt->x, pt->y, pt->z);
        fct_actu(pt, params, dt);
        t += dt;
    }

    fclose(f);
    printf("Le fichier %s a été créé.\n", nom_fichier);
}



