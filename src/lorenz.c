 #include <stdio.h>
 #include <stdlib.h>
 #include "lorenz.h"

struct lorenz_settings* ask_parametres_lorentz (){
    struct lorenz_settings *params = malloc (sizeof(struct lorenz_settings));
    printf("Choisir parametre sigma : \n");
    scanf("%f", &(params->sigma));
    printf("Choisir parametre rho : \n");
    scanf("%f", &(params->rho));
    printf("Choisir parametre beta : \n");
    scanf("%f", &(params->beta));
    return params;
}

struct coord* ask_position_initiale(){       // Permet de demander la position initiale
    struct coord * position = malloc(sizeof(struct coord));
    printf("Choisir coordonnee x : \n");
    scanf("%f", &(position->x));
    printf("Choisir coordonnee y : \n");
    scanf("%f", &(position->y));
    printf("Choisir coordonnee z : \n");
    scanf("%f", &(position->z));
    return position;
}

void init_ltz(coord *point) {
    point->x = x
    point->y = y
    point->z = z
}

void actualiser_ltz(lorenz_settings *para) {
    double dx = para->sigma * (point->y - point->x);
    double dy = point->x * (para->rho - point->z) - point->y;
    double dz = point->x * point->y - para->beta * point->z;

    point->x += dx * dt;
    point->y += dy * dt;
    point->z += dz * dt;
}
