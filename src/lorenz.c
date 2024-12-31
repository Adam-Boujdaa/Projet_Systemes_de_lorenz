 #include <stdio.h>
 #include <stdlib.h>
 #include "lorenz.h"

typedef struct {
    void (*pt_init)(double*,double*,double*); // Pointe vers la fonction init des coordonnées (x,y,z)
    void (*pt_actualiser)(double*, double*, double*, double); // Pointe vers la fonction actualiser des coordonnées x, y,z et dt
    double param[3]; // Tableau fixé au système dynamique (Lorenz : σ, ρ, β)
} SysDynamique;

void ask_parametres_lorentz (){
    float sigma;
    float beta;
    float rho;
    printf("Choisir parametre sigma : ");
    scanf("%f", &sigma);
    printf("Choisir parametre rho : ");
    scanf("%f", &rho);
    printf("Choisir parametre beta : ");
    scanf("%f", &beta);
}

void ask_coordonnees(){
    float x;
    float y;
    float z;
    printf("Choisir coordonnee x : ");
    scanf("%f", &x);
    printf("Choisir coordonnee y : ");
    scanf("%f", &y);
    printf("Choisir coordonnee z : ");
    scanf("%f", &z);
}

void init_ltz(double* x, double* y, double* z) {
    *x = 1.0
    *y = 2.0
    *z = 3.0
}

void actualiaser_ltz(double* x, double* y, double* z, double dt) {
    double sigma = 10.0;
    double rho = 28.0;
    double beta = 8.0 / 3.0;

    double dx = sigma * (*y - *x);
    double dy = *x * (rho - *z) - *y;
    double dz = *x * *y - beta * *z;

    *x += dx * dt;
    *y += dy * dt;
    *z += dz * dt;
}

