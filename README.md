# Simulation Ecosystème

## Objectif
Ce projet a été réalisé dans le cadre du module `LU2IN018 - C Avancé` à _Sorbonne Université_. Il consiste en simuler l'activité de proies et de prédateurs dans un environnement considéré torique.

## Fonctionnement
- Tous les animaux peuvent se déplacer d'une case à chaque étape de la simulation, et meurent s'ils sont à court d'énergie.
- Les proies sont de plus capables de se reproduire et de se nourrir d'herbe sur les cases vides de l'environnement.
- Les prédateurs quant à eux peuvent se nourrir des proies.

## Structure
- Les fonctions du projet sont déclarées dans le fichier `ecosys.h` et définies dans le fichier `ecosys.c`. Ces fonctions sont éprouvées dans le fichier `main_tests.c`
- La simulation est contenue dans le fichier `main_ecosys.c` et est obtenue en exécutant 'main_ecosys'.

Des graphes sont fournis dans le dossier courant, et permettent de se représenter l'évolution de la population (proies et prédateurs) au sein de l'écosystème à partir du fichier texte `Evol_Pop.txt`.

## Compilation
- Pour compiler le programme dans son ensemble, il suffit de taper la commande `make`.
- Pour nettoyer le répertoire, taper `make clean`
