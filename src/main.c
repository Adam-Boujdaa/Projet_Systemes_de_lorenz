#include "lorenz.h"
#include <stdio.h>

int main (){

    SysDynamique systeme;
    struct coord* point;
    struct lorenz_settings* params;

    struct coord* point = ask_position_initiale();
    params = ask_parametres_lorentz ();

    creation_ltz(&systeme);

    systeme.pt_initial(coord* point);

    for (int i = 0; i < 50; i++) {
        systeme_actualiser_ltz(position, params);
    }

    return 0;
}
