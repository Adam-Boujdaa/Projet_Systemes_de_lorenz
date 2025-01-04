#include <stdlib.h>
#include <stdio.h>
#include "lorenz.h"


int main (){
    SysDynamique systeme;
    Coord *point;
    Params *params;
    SimSettings *sim;

    // Demander les paramètres et la position initiale
    point = ask_position_initiale();
    params = ask_parametres_lorentz();
    printf("Definir parametres avec la notation polonaise inversee : \n");
    char *notation = ask_notation_pol_inv();
    if (notation){  //pr verifier que ca existe 
        printf("Formule en notation polonaise inversee (NPI) saisie : %s \n", notation);
    }
    else {
        printf("Erreur notation polonaise inversee \n");
    }

    sim = ask_simulation_settings();

    

    choisir_sys(&systeme, params);
    systeme.pt_init(point);

    generer_fichier("lorenz.dat", systeme.pt_actualiser, point, systeme.param, sim);

    gnuplot("lorenz.dat");

    // Tracer avec Gnuplot
    printf("Simulation terminée. Visualisation avec Gnuplot...\n");

    return 0;
}
