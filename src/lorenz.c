 #include <stdio.h>
 #include <stdlib.h>
 #include "lorenz.h"

#include <ctype.h> //pr verifier si un caractere est un operateur, un char ou un chiffre
#include <string.h> // pour utiliser les "types" string

void init(Coord *point) {
    printf("Coordonnée initiale x : ");
    scanf("%lf", &(point->x));
    printf("Coordonnée initiale y : ");
    scanf("%lf", &(point->y));
    printf("Coordonnée initiale z : ");
    scanf("%lf", &(point->z));
}

Params *ask_parametres_lorentz (){
    Params *params = malloc (sizeof(Params));
    printf("Choisir parametre Sigma : ");
    scanf("%lf", &(params->sigma));
    printf("Choisir parametre Rho : ");
    scanf("%lf", &(params->rho));
    printf("Choisir parametre Beta : ");
    scanf("%lf", &(params->beta));
    return params;
}


SimSettings* ask_simulation_settings() {
    SimSettings* sim = malloc(sizeof(SimSettings));
    printf("Choisir l'incrément de temps (dt) : ");
    scanf("%lf", &(sim->dt));
    printf("Choisir le temps maximal (Tmax) : ");
    scanf("%lf", &(sim->tmax));
    return sim;
}



void actualiser_ltz(Coord *point, Params *para, double dt) {
    double dx = para->sigma * (point->y - point->x);
    double dy = point->x * (para->rho - point->z) - point->y;
    double dz = point->x * point->y - para->beta * point->z;

    point->x += dx * dt;
    point->y += dy * dt;
    point->z += dz * dt;
}


void actualiser_oscillateur(Coord *point, Params *para, double dt) {
    double dx = -para->beta * point->x;
    double dy = para->sigma * (point->x - point->y);
    double dz = 0.0;

    point->x += dx * dt;
    point->y += dy * dt;
    point->z += dz * dt;
}

void actualiser_spirale(Coord *point, Params *para, double dt) {
    double dx = -point->y;
    double dy = point->x;
    double dz = para->rho * (1 - point->z);

    point->x += dx * dt;
    point->y += dy * dt;
    point->z += dz * dt;
}

void creation_sys(SysDynamique *systeme, void (*init_sys)(Coord*),
                      void (*actualiser_sys)(Coord*, Params*, double),
                      Params* params) {
    systeme->pt_init = init_sys;
    systeme->pt_actualiser = actualiser_sys;

    systeme->param = malloc(sizeof(Params));
    if (!systeme->param) {
        fprintf(stderr, "Erreur\n");
        exit(EXIT_FAILURE);
    }

    systeme->param->sigma = params->sigma;
    systeme->param->rho = params->rho;
    systeme->param->beta = params->beta;
}


void choisir_sys(SysDynamique *systeme, Params *params) {
    printf("Liste du choix du système dynamique :\n");
    printf("1 : Système de Lorentz.\n");
    printf("2 : Oscillateur simple.\n");
    printf("3 : Spirale.\n");
    printf("Votre choix :\n");

    int choix;

    scanf("%d",&choix);

    if (choix == 1) {
        printf("Vous avez choisi le système de Lorenz.\n");
        creation_sys(systeme, init, actualiser_ltz, params);
    }
    else if (choix == 2) {
        printf("Vous avez choisi le système d'oscillateur simple.\n");
        creation_sys(systeme, init, actualiser_oscillateur, params);
    }
    else if (choix == 3) {
        printf("Vous avez choisi le système de spirale.\n");
        creation_sys(systeme, init, actualiser_spirale, params);
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
        fprintf(f, "%lf %lf %lf %lf\n", t, pt->x, pt->y, pt->z);
        fct_actu(pt, params, dt);
        t += dt;
    }

    fclose(f);
    printf("Le fichier %s a été créé.\n", nom_fichier);
}


void gnuplot(char* nom_fichier) {

    // On ouvre un pipe pur ecrie a Gnuplot directement, qui agit comme un fichier
    // On utilise le parametre -p (persist) pour que le programme ne se ferme pas
    FILE *gnuplotPipe = popen("gnuplot -p", "w");
    if (gnuplotPipe == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture de Gnuplot.\n");
        return;
    }

    // On envoie des commandes avec fprintf
    // La premiere commande fait que la fenetre reste interactive
    fprintf(gnuplotPipe, "set terminal wxt\n");
    fprintf(gnuplotPipe, "set parametric\n");  // 
    fprintf (gnuplotPipe, "set style data lines \n"); // pour relier les points 
    fprintf(gnuplotPipe, "splot \"%s\" u 2:3:4\n", nom_fichier);


    fflush(gnuplotPipe);

    // On ferme le pipe apres avoir envoye toutes les commandes
    pclose(gnuplotPipe);
}



char * ask_notation_pol_inv(){  //notation polonaise inversee (NPI)
    char * res = malloc(1); //allocation initiale de la memory
    
    int size = 1; //taille actuelle preparee pour l'entree utilisateur
    int length = 0; //longueur de la chaine str lue (type dans string.h)
    char c;

    printf("Entrez la formule en notation polonaise inversee : \n");
    while (scanf(" %c", &c)==1 && c!='\n'){  //tant qu'il y a un caractere et pas de retour a la ligne, la boucle continue, pr pouvoir lire les expressions completes sans limite de taille
        if (length + 1 >= size){
            size = size*2;   //pour ne pas allocate trop de memoire pour la chaine de characteres lue, et pr ne pas trop repeter la boucle
            res = realloc (res,size); // creer un nouveau resultat pr agrandir dynamiquement la memoire en gardant le contenu d'avant
        }
        res[length] = c; //pr ajouter les caracteres 1 par 1
        length += 1; //pour incrementer la longueur a chaque iteration de la boucle while

    }
    res[length] = "\0"; //caractere de fin de chaine
    return res;
    }

double eval_npi(const char* npi,double x, double y, double z){
    double pile[100]; //creation d'une pile de taille fixe
    int top = -1; //indice du sommet de la pile = derniere case
    const char *npi_2 = npi;
    while (*npi_2 != "\0"){ //pr parcourir chaque caractere jusqu'a la fin de la chaine
        if (isspace(*npi_2)){ //ignore les espaces dans la formule a notation npi
            npi_2++; //avancer le pointeur 
        }

        if (*npi_2 == 'x') {
            pile[++top] = x;  // Ajoute la valeur de x au sommet de la pile
        } else if (*npi_2 == 'y') {
            pile[++top] = y;  // idem pr y
        } else if (*npi_2 == 'z') {
            pile[++top] = z;  // idem pr z
        } else if (*npi_2 == '+' || *npi_2 == '-' || *npi_2 == '*' || *npi_2 == '/') {
            if (top < 1) {  // Vérifie qu'il y a au moins deux opérandes
                printf("Erreur : pas assez d'opérandes.\n");
                return 0;  // Erreur si la pile est vide ou a un seul élément
    }
    }
    
}
