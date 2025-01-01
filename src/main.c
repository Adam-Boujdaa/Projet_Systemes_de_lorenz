#include "lorenz.h"
#include <stdio.h>

int main (){

    printf("Choisir les parametres de Lorenz: \n");
    ask_parametres_lorentz();

    printf("Choisir la position initiale : \n");
    ask_position_initiale();

    printf("\nParamètres saisis : sigma = %f, rho = %f, beta = %f\n", params->sigma, params->rho, params->beta);
    printf("Position initiale : x = %f, y = %f, z = %f\n", position->x, position->y, position->z);



    return 0;
}
