 #include <stdio.h>
 #include <stdlib.h>
 #include "lorenz.h"

typedef struct {
    void (*pt_init)(double*,double*,double*); // Pointe vers la fonction init des coordonnées (x,y,z)
    void (*pt_actualiaser)(double*, double*, double*, double); // Pointe vers la fonction actualiser des coordonnées x, y,z et dt
    double param[3]; // Tableau fixé au système dynamique (Lorenz : σ, ρ, β)
} SysDynamique;

void ask_parametres_lorentz (){
    float sigma;
    float beta;
    printf("Choisir parametre sigma : ");
    scanf("%f", &sigma);
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
