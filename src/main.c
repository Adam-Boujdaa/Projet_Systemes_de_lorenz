#include <stdlib.h>
#include <stdio.h>
#include "lorenz.h"


int main (){
    SysDynamique systeme;
    Coord *point = malloc(sizeof(Coord));
    Params *params;
    SimSettings *sim;


    // Demander les paramètres et la position initiale + demander mise a jour de vitesse npi
    params = ask_parametres_lorentz();
    choisir_sys(&systeme, params);
    systeme.pt_init(point);
    sim = ask_simulation_settings();


    // pr laisser le user choisir si il veut une maj de la vitesse ou non 
    int maj = 0;
    printf("Mettre a jour la vitesse ? \n Oui : 1 \n Non : 0 \n");
    scanf("%d", &maj);
    
    if (maj==1){        
        printf("mise a jour de la vitesse selon x, en notation polonaise inversee :\n");
        char *expression_x = ask_notation_pol_inv();
        printf("mise a jour de la vitesse selon y, en notation polonaise inversee :\n");
        char *expression_y = ask_notation_pol_inv();
        printf("mise a jour de la vitesse selon z, en notation polonaise inversee :\n");
        char *expression_z = ask_notation_pol_inv();

        printf("Expression pour x: %s\n", expression_x);
        printf("Expression pour y: %s\n", expression_y);
        printf("Expression pour z: %s\n", expression_z);        
        
        
        //mise a jour de vitesse :
        double dt = sim->dt;
        double dx = eval_npi(expression_x, point->x, point->y, point->z );
        double dy = eval_npi(expression_y, point->x, point->y, point->z );
        double dz = eval_npi(expression_z, point->x, point->y, point->z );
        point->x += dx*dt; //nouvelle position = ancienne position + vitesse*dt
        point->y += dy*dt;
        point->z += dz*dt;
    
    }    

    //partie simulation gnuplot
    generer_fichier("lorenz.dat", systeme.pt_actualiser, point, systeme.param, sim);
    gnuplot("lorenz.dat");

    // Tracer avec Gnuplot
    printf("Simulation terminée. Visualisation avec Gnuplot...\n");

    return 0;
}
