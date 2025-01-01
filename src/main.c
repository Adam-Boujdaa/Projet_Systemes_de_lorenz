#include "lorenz.h"
#include <stdio.h>

int main (){

    SysDynamique systeme;
    Coord *point;
    Params *params;

    // Demander les paramètres et la position initiale
    point = ask_position_initiale();
    params = ask_parametres_lorentz();
    sim = ask_simulation_settings();
    
    // Créer le système dynamique de Lorenz
    creation_ltz(&systeme);

    systeme.pt_initial(Coord* point);

    for (int i = 0; i < 50; i++) {
        actualiser_ltz(position, params);
    }


    //Ouvrir un fichier pour stocker les résultats
    FILE *file = fopen("lorenz.dat", "w");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier lorenz.dat");
        return 1;
    }

   // Simulation
    double t = 0;
    while (t < sim->Tmax) {
        ecrire_resultats(file, t, point);           // Écrire les résultats dans le fichier
        systeme.pt_actualiser(point, params);      // Actualiser les coordonnées
        t += sim->dt;                              // Incrémenter le temps
    }
    fclose(file); //closer le fichier

    // Tracer avec Gnuplot
    printf("Simulation terminée. Visualisation avec Gnuplot...\n");
    system("gnuplot -e \"set parametric; splot 'lorenz.dat' u 2:3:4\"");


    return 0;
}
