#include "lorenz.h"
#include <stdio.h>

int main (){

    SysDynamique systeme;
    Coord *point;
    Params *params;

    point = ask_position_initiale();
    params = ask_parametres_lorentz();

    creation_ltz(&systeme);

    systeme.pt_initial(Coord* point);

    for (int i = 0; i < 50; i++) {
        actualiser_ltz(position, params);
    }

    return 0;
}
