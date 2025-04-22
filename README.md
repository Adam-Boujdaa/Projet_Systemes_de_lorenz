# Projet - Simulation de systèmes dynamiques

<img src="https://github.com/user-attachments/assets/1bef98a7-e196-48ff-a46f-16d0ca2df793" width="450"/>

## Description

Dans ce projet, un simulateur de systèmes dynamiques a été implementée : 

 Il offre une interface pour définir des paramètres de simulation et choisir entre trois systèmes dynamiques :

 - Le système de Lorenz
 - Un oscillateur simple
 - Un modèle de spirale

Après la definition des paramètres, le programme simule le comportement du système et génère des fichiers de données. Ensuite, ces données sont visualisées à l'aide de Gnuplot. Vous avez la possibilité d'entrer des expressions en notation polonaise inversée (NPI) pour mettre à jour la vitesse dans le système.

## Structure du projet

```Projet2025/
├── doc/
│   └── Documentation.pdf       # Documentation du projet
├── src/
│   ├── Makefile                # Fichier Makefile pour la compilation
│   ├── main.c                  # Fichier principal du programme
│   ├── lorenz.c                # Fonctions pour les systèmes dynamiques
│   ├── lorenz.h                # Structures et déclaration des fonctions
│   ├── lorenz.dat              # Fichier généré par la simulation
│   ├── gnuplot_i.c             # Code pour l'interface avec gnuplot
│   ├── gnuplot_i.h             # Déclarations pour l'interface avec gnuplot
├── README.md                   # Ce fichier
```


## Prérequis

Avant de compiler, vous devez vous assurer d'avoir les éléments suivants installés :

- GCC ou un autre compilateur.
- Gnuplot
- Bibliothèques standard C

## Installation

1. Commande pour installer Gnuplot :
```
sudo apt-get install gnuplot
```

2. Commande pour cloner le projet :
```
git clone https://github.com/Adam-Boujdaa/Projet2025.git
cd Projet2025
```

3. Commande pour compiler :
```
make
```

4. Executez le programme :
```
./lorenz.elf
```


## Utilisation

Etape 1 : On choisit les paramètres du système 
```
Choisir paramètre Sigma : 10
Choisir paramètre Rho : 28
Choisir paramètre Beta : 2.667
```

Etape 2 : On configure la simulation
```
Choisir l'incrément de temps (dt) : 0.01
Choisir le temps maximal (Tmax) : 10
```

Etape 3 : On choisit le système dynamique 
```
Liste du choix du système dynamique :
1 : Système de Lorenz.
2 : Oscillateur simple.
3 : Spirale.
4 : Systeme personnalyse
Votre choix : 1
```

Si on choisit l'option 4, on doit entrer les formules en NPI (Notation Polonaise inversee) :
```
Mise à jour de la vitesse selon x, en notation polonaise inversée :
x y +
Mise à jour de la vitesse selon y, en notation polonaise inversée :
y z *
Mise à jour de la vitesse selon z, en notation polonaise inversée :
z x -
```


Etape 4 : On initie les coordonnées du système dynamique
```
Coordonnée initiale x : 1.0
Coordonnée initiale y : 1.0
Coordonnée initiale z : 1.0
```


Etape 5 : Visualisation des résultats

```
Le fichier lorenz.dat a été créé.
```

Une fenêtre Gnuplot s'ouvre pour afficher les trajectoires en 3D.


  
## Notes techniques

Notation Polonaise Inversée (NPI) :

On utilise cette notation pour entrer des formules mathématiques sans parenthèses. 

Exemple : 

```x y +``` équivaut à ```x + (y * z)```

## Auteurs

- BOUDOUHI-MEZROUI Ayoub
- BOUJDAA Adam
- SAHLI Aziz

