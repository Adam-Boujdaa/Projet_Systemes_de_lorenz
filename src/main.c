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
    sim = ask_simulation_settings();
    

    creation_ltz(&systeme, params);

    systeme.pt_init(point);

    generer_fichier("lorenz.dat", systeme.pt_actualiser, point, systeme.param, sim);

    // Tracer avec Gnuplot
    printf("Simulation terminée. Visualisation avec Gnuplot...\n");
    system("gnuplot -e \"set parametric; splot 'lorenz.dat' u 2:3:4\"");


    return 0;
}
