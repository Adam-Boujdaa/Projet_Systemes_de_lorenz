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



void init_oscillateur(Coord* point) {
    point->x = 1.0;
    point->y = 0.0;
    point->z = 0.0;
}

void actualiser_oscillateur(Coord *point, Params *para, double dt) {
    double dx = -para->beta * point->x;
    double dy = para->sigma * (point->x - point->y);
    double dz = 0.0;

    point->x += dx * dt;
    point->y += dy * dt;
    point->z += dz * dt;
}

void init_spirale(Coord* point) {
    point->x = 0.5;
    point->y = 0.5;
    point->z = 0.5;
}

void actualiser_spirale(Coord *point, Params *para, double dt) {
    double dx = -point->y;
    double dy = point->x;
    double dz = para->rho * (1 - point->z);

    point->x += dx * dt;
    point->y += dy * dt;
    point->z += dz * dt;
}

void creation_sys(SysDynamique *systeme, void (*init_sys)(Coord*),
                      void (*actualiser_sys)(Coord*, Params*, double),
                      Params* params) {
    systeme->pt_init = init_sys;
    systeme->pt_actualiser = actualiser_sys;

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
    printf("2 : Oscillateur simple.\n");
    printf("3 : Spirale.\n");
    printf("Votre choix :\n");

    int choix;

    scanf("%d",&choix);

    if (choix == 1) {
        printf("Vous avez choisi le système de Lorenz.\n");
        creation_sys(systeme, init_ltz, actualiser_ltz, params);
    }
    if (choix == 2) {
        printf("Vous avez choisi le système d'oscillateur simple.\n");
        creation_sys(systeme, init_oscillateur, actualiser_oscillateur, params);
    }
    if (choix == 1) {
        printf("Vous avez choisi le système de spirale.\n");
        creation_sys(systeme, init_spirale, actualiser_spirale, params);
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


void gnuplot(char* nom_fichier) {

    // On ouvre un pipe pur ecrie a Gnuplot directement, qui agit comme un fichier
    // On utilise le parametre -p (persist) pour que le programme ne se ferme pas
    FILE *gnuplotPipe = popen("gnuplot -p", "w");
    if (gnuplotPipe == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture de Gnuplot.\n");
        return;
    }

    // On envoie des commandes avec fprintf
    // La premiere commande fait que la fenetre reste interactive
    fprintf(gnuplotPipe, "set terminal wxt\n");
    fprintf(gnuplotPipe, "set parametric\n");  // 
    fprintf (gnuplotPipe, "set style data lines \n"); // pr relier les pts 
    fprintf(gnuplotPipe, "splot \"%s\" u 2:3:4\n", nom_fichier);


    fflush(gnuplotPipe);

    // On ferme le pipe apres avoir envoye toutes les commandes
    pclose(gnuplotPipe);
}
