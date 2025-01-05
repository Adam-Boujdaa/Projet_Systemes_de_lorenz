#include <stdlib.h>
#include <stdio.h>
#include "lorenz.h"

int main()
{
    SysDynamique systeme;
    Coord *point = malloc(sizeof(Coord));
    Params *params;
    SimSettings *sim;

    // Demander les paramètres et la position initiale + demander mise a jour de vitesse npi

    params = ask_parametres_lorentz();
    sim = ask_simulation_settings();
    if (choisir_sys(&systeme, params) == 4)
    {
        ask_maj_vitesse(point, sim, params);
    }
    systeme.pt_init(point);

    // pr laisser le user choisir si il veut une maj de la vitesse ou non

    // partie simulation gnuplot
    generer_fichier("lorenz.dat", systeme.pt_actualiser, point, systeme.param, sim);

    // Tracer avec Gnuplot
    printf("Simulation terminée. Visualisation avec Gnuplot...\n");

    gnuplot("lorenz.dat");

    return 0;
}
