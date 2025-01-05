#include <stdio.h>
#include <stdlib.h>
#include "lorenz.h"
#include <math.h>
#include "gnuplot_i.h"
#include <ctype.h> //pr isspace (notation polonaise inversee)

void init(Coord *point)
{
    printf("Coordonnée initiale x : ");
    scanf("%lf", &(point->x));
    printf("Coordonnée initiale y : ");
    scanf("%lf", &(point->y));
    printf("Coordonnée initiale z : ");
    scanf("%lf", &(point->z));
}

Params *ask_parametres_lorentz()
{
    Params *params = malloc(sizeof(Params));
    printf("Choisir parametre Sigma : ");
    scanf("%lf", &(params->sigma));
    printf("Choisir parametre Rho : ");
    scanf("%lf", &(params->rho));
    printf("Choisir parametre Beta : ");
    scanf("%lf", &(params->beta));
    return params;
}

SimSettings *ask_simulation_settings()
{
    SimSettings *sim = malloc(sizeof(SimSettings));
    printf("Choisir l'incrément de temps (dt) : ");
    scanf("%lf", &(sim->dt));
    printf("Choisir le temps maximal (Tmax) : ");
    scanf("%lf", &(sim->tmax));
    return sim;
}

void actualiser_ltz(Coord *point, Params *para, double dt)
{
    double dx = para->sigma * (point->y - point->x);
    double dy = point->x * (para->rho - point->z) - point->y;
    double dz = point->x * point->y - para->beta * point->z;

    point->x += dx * dt;
    point->y += dy * dt;
    point->z += dz * dt;
}

void actualiser_oscillateur(Coord *point, Params *para, double dt)
{
    double dx = -para->beta * point->x;
    double dy = para->sigma * (point->x - point->y);
    double dz = 0.0;

    point->x += dx * dt;
    point->y += dy * dt;
    point->z += dz * dt;
}

void actualiser_spirale(Coord *point, Params *para, double dt)
{
    double dx = -point->y;
    double dy = point->x;
    double dz = para->rho * (1 - point->z);

    point->x += dx * dt;
    point->y += dy * dt;
    point->z += dz * dt;
}

void creation_sys(SysDynamique *systeme, void (*init_sys)(Coord *),
                  void (*actualiser_sys)(Coord *, Params *, double),
                  Params *params)
{
    systeme->pt_init = init_sys;
    systeme->pt_actualiser = actualiser_sys;

    systeme->param = malloc(sizeof(Params));
    if (!systeme->param)
    {
        fprintf(stderr, "Erreur\n");
        exit(EXIT_FAILURE);
    }

    systeme->param->sigma = params->sigma;
    systeme->param->rho = params->rho;
    systeme->param->beta = params->beta;
}

int choisir_sys(SysDynamique *systeme, Params *params)
{
    printf("Liste du choix du système dynamique :\n");
    printf("    1 : Système de Lorentz.\n");
    printf("    2 : Oscillateur simple.\n");
    printf("    3 : Spirale.\n");
    printf("    4 : Système personnalisé.\n");
    printf("Votre choix : ");

    int choix;

    scanf("%d", &choix);

    if (choix == 1)
    {
        printf("Vous avez choisi le système de Lorenz.\n");
        creation_sys(systeme, init, actualiser_ltz, params);
        return 1;
    }
    else if (choix == 2)
    {
        printf("Vous avez choisi le système d'oscillateur simple.\n");
        creation_sys(systeme, init, actualiser_oscillateur, params);
        return 2;
    }
    else if (choix == 3)
    {
        printf("Vous avez choisi le système de spirale.\n");
        creation_sys(systeme, init, actualiser_spirale, params);
        return 3;
    }
    else if (choix == 4)
    {
        printf("Vous avez choisi le système personnalisé.\n");
        return 4;
    }
    else
    {
        printf("Valeur invalide...\n");
        return choisir_sys(systeme, params);
    }
}

void generer_fichier(char *nom_fichier, void (*fct_actu)(Coord*, Params*, double), Coord *pt, Params *params, SimSettings *sim) {
    FILE *f = fopen(nom_fichier, "w");

    if (!f) {
        perror("Erreur lors de l'ouverture du fichier.");
        return;
    }

    double tmax = sim->tmax;
    double dt = sim->dt;
    double t = 0;

    while(t < tmax) {
        double vit = sqrt(pt->x * pt->x + pt->y * pt->y + pt->z * pt->z);
        fprintf(f, "%lf %lf %lf %lf %lf\n", t, pt->x, pt->y, pt->z, vit);
        fct_actu(pt, params, dt);
        t += dt;
    }

    fclose(f);
    printf("Le fichier %s a été crée.\n", nom_fichier);
}

void gnuplot(char* nom_fichier) {
    FILE *gnuplotPipe = popen("gnuplot -p", "w");
    if (gnuplotPipe == NULL) {
        fprintf(stderr, "Gnuplot n'ouvre pas, erreur.\n");
        return;
    }

    fprintf(gnuplotPipe, "set terminal wxt\n");
    fprintf(gnuplotPipe, "set parametric\n");

    fprintf(gnuplotPipe, "set palette model RGB defined ( 0 'blue', 1 'green', 2 'yellow', 3 'red' )\n"); // Définir la palette de couleurs

    fprintf(gnuplotPipe, "splot \"%s\" u 2:3:4:5 with points pt 7 ps 1.5 palette\n", nom_fichier); // Tracer en 3D avec la vitesse en couleur

    fflush(gnuplotPipe);
    pclose(gnuplotPipe);
}

/*
char * ask_notation_pol_inv(){  //notation polonaise inversee (NPI)
    char *res = malloc(1); //allocation initiale de la memory

    int size = 1; //taille actuelle preparee pour l'entree utilisateur
    int length = 0; //longueur de la chaine str lue (type dans string.h)
    char c;

    // Pour entrer la formule en notation polonaise inversee
    while (scanf("%c", &c) == 1) {
        if (c=='\n') {
            break; //tant qu'il y a un caractere et pas de retour a la ligne, la boucle continue, pr pouvoir lire les expressions completes sans limite de taille
        }
        else if (length + 1 >= size){
            size = size * 2;   //pour ne pas allocate trop de memoire pour la chaine de characteres lue, et pr ne pas trop repeter la boucle
            res = realloc(res, size); // creer un nouveau resultat pr agrandir dynamiquement la memoire en gardant le contenu d'avant
        }
        else if (!isspace(c)){ //pr ignorer les espaces
        res[length] = c; //pr ajouter les caracteres 1 par 1
        length ++; //pour incrementer la longueur a chaque iteration de la boucle while
        }
    }
    res[length] = '\0'; //caractere de fin de chaine
    return res;
    }

double eval_npi(const char* npi, Coord *point, Params *params){
    double pile[100]; //creation d'une pile de taille fixe
    int top = 0; //nb d'elechar *expression_x = ask_notation_pol_inv();ments dans la pile
    const char *npi_2 = npi;
    while (*npi_2 != '\0'){ //pr parcourir chaque caractere jusqu'a la fin de la chaine
        if (isspace(*npi_2)!=1){  //verifie si le caractere est un espace, pour l'ignorer apres si c'est le cas

            if (*npi_2 == 'x') { // Ajoute la valeur de x au sommet de la pile
                pile[top] = point->x;
                top++;
            } else if (*npi_2 == 'y') {
                pile[top] = point->y;  // idem pr y
                top++;
            } else if (*npi_2 == 'z') {
                pile[top] = point->z;  // idem pr z
                top++;
            } else if (*npi_2 == '+' || *npi_2 == '-' || *npi_2 == '*' || *npi_2 == '/') {
                if (top < 1) {  // Vérifie qu'il y a au moins deux opérandes
                    printf("Erreur : pas assez d'opérandes.\n");
                    return 0;
                }

                double b = pile[top-1]; //derniere valeur dans la pile
                double a = pile[top-2]; //avant derniere valeur

                if (*npi_2 == '+'){
                    pile[top-2]= a+b ; //addition
                }

                else if (*npi_2 == '-'){
                    pile[top-2]= a-b ; //soustraction
                }

                else if (*npi_2 == '*'){
                    pile[top-2]= a*b ; //multiplication
                }

                else if(*npi_2 == '/'){
                    pile[top-2] = a/b; //division
                }

                else {
                    printf("Erreur : operateur inconnu dans la formule de notation polonaise inversee \n");
                    return 0;
                }
                top --; //reduire le nombre d'elements dans la pile apres l'operation
            }
            else {
                printf("Caractere inconnu dans la formule de notation polonaise inversee \n");
                return 0;
            }
            npi_2++; //avancer le pointeur vers le caractere suivant
        }

        else {
        //ignore les espaces dans la formule a notation npi
                npi_2++; //avancer le pointeur
        }

    }
    if (top ==1) {
            return pile[0]; //retourne le dernier element comme resultat
        }
    else {
        printf("Erreur : pile incorrecte a la fin \n ");
        return 0;
    }
}
*/

char *ask_notation_pol_inv()
{
    char *res = malloc(1); // Allocation initiale
    int length = 0;        // Longueur de la chaîne lue
    char c;

    // Lire les caractères jusqu'à la fin de la ligne
    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (!isspace(c))
        {                                   // Ignorer les espaces
            res = realloc(res, length + 2); // Allouer plus de mémoire si nécessaire
            res[length++] = c;              // Ajouter le caractère
        }
    }
    res[length] = '\0'; // Ajouter le caractère de fin de chaîne
    return res;
}

double eval_npi(const char *npi, Coord *coord, Params *params) {
    double pile[100]; // Création d'une pile de taille fixe
    int top = 0;      // Nombre d'éléments dans la pile

    while (*npi) {  // Parcourir chaque caractère de la chaîne jusqu'à la fin
        if (!isspace(*npi)) {  // Ignorer les espaces
            if (*npi == 'x') pile[top++] = coord->x;
            else if (*npi == 'y') pile[top++] = coord->y;
            else if (*npi == 'z') pile[top++] = coord->z;
            else if (*npi == 's') pile[top++] = params->sigma;
            else if (*npi == 'b') pile[top++] = params->beta;
            else if (*npi == 'r') pile[top++] = params->rho;

            else if (*npi == '+' || *npi == '-' || *npi == '*' || *npi == '/') {
                if (top < 2) {
                    printf("Erreur : pas assez d'opérandes.\n");
                    return 0;
                }
                double b = pile[--top];  // Dernière valeur dans la pile
                double a = pile[--top];  // Avant-dernière valeur

                if (*npi == '+') pile[top++] = a + b;
                else if (*npi == '-') pile[top++] = a - b;
                else if (*npi == '*') pile[top++] = a * b;
                else if (*npi == '/') {
                    if (b == 0) {
                        printf("Erreur : division par zéro.\n");
                        return 0;
                    }
                    pile[top++] = a / b;
                }
            } else {
                printf("Erreur : caractère inconnu '%c'.\n", *npi);
                return 0;
            }
        }
        npi++;  // Passer au caractère suivant
    }

    if (top == 1) return pile[0];  // Retourner le dernier élément comme résultat
    printf("Erreur : pile incorrecte à la fin.\n");
    return 0;
}

void gnuplot_interface(char *nom_fichier)
{
    gnuplot_ctrl *h;
    h = gnuplot_init();

    gnuplot_cmd(h, "set terminal wxt\n");
    gnuplot_cmd(h, "set parametric\n");
    gnuplot_cmd(h, "splot \"%s\" u 2:3:4\n", nom_fichier);
    gnuplot_cmd(h, "pause -1");

    // gnuplot_close(h);
}

void ask_maj_vitesse(Coord *point, SimSettings *sim, Params *params)
{
    while (getchar() != '\n'); //vider le tampon d'entree
    printf("mise a jour de la vitesse selon x, en notation polonaise inversee : \n");
    char *expression_x = ask_notation_pol_inv();
    printf("mise a jour de la vitesse selon y, en notation polonaise inversee : \n");
    char *expression_y = ask_notation_pol_inv();
    printf("mise a jour de la vitesse selon z, en notation polonaise inversee : \n");
    char *expression_z = ask_notation_pol_inv();

    printf("Expression pour x: %s\n", expression_x);
    printf("Expression pour y: %s\n", expression_y);
    printf("Expression pour z: %s\n", expression_z);

    // mise a jour de vitesse :
    double dt = sim->dt;
    double dx = eval_npi(expression_x, point, params);
    double dy = eval_npi(expression_y, point, params);
    double dz = eval_npi(expression_z, point, params);

    point->x += dx * dt; // nouvelle position = ancienne position + vitesse*dt
    point->y += dy * dt;
    point->z += dz * dt;
}


