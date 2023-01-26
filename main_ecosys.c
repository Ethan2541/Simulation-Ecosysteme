#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"

#define MAXENERGIEPROIES 100
#define MAXENERGIEPREDATEURS 100

#define NB_PROIES 20
#define NB_PREDATEURS 40
#define T_WAIT 40000
#define MAX_ITER 200


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir = 0.01;
float p_reproduce_proie = 0.4;
float p_reproduce_predateur = 0.5;
int temps_repousse_herbe = -15;


int main(void) {

  /* A completer. Part 2:
   * exercice 4, questions 2 et 4
   * exercice 6, question 2
   * exercice 7, question 3
   * exercice 8, question 1
   */


   /* Initialisation de la graine pour la generation pseudo-aleatoire */
   srand(time(NULL));

   int monde[SIZE_X][SIZE_Y];

   /* Initialisation des cases du tableau a 0 */
   for (int i = 0; i < SIZE_X; i++) {
     for (int j = 0; j < SIZE_Y; j++) {
       monde[i][j] = 0;
     }
   }


   /* Creation des listes chainees */
   Animal *liste_proies = NULL;
   Animal *liste_predateurs = NULL;


   /* On remplit la liste des proies */
   for (int i = 0; i < NB_PROIES; i++) {
     ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, MAXENERGIEPROIES * (double) rand() / RAND_MAX, &liste_proies);
   }

   /* On remplit la liste des predateurs */
   for (int i = 0; i < NB_PREDATEURS; i++) {
     ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, MAXENERGIEPREDATEURS * (double) rand() / RAND_MAX, &liste_predateurs);
   }


   /* Ouverture du fichier texte de suivi de population
   en mode ecriture */
   FILE *f = fopen("Evol_Pop.txt", "w");

   /* On verifie si le fichier existe */
   if (f == NULL) {
   	printf("FICHIER INEXISTANT\n");
   	return 1;
   }

   /* Declaration des compteurs */
   int nbProies = compte_animal_rec(liste_proies);
   int nbPredateurs = compte_animal_rec(liste_predateurs);
   int compteur;

   for (compteur = 0; (nbProies > 0) && (compteur <= MAX_ITER); compteur ++) {

     /* Ecriture dans le fichier texte */
     fprintf(f, "%d %d %d\n", compteur, nbProies, nbPredateurs);

     /* Affichage de l'ecosysteme */
     afficher_ecosys(liste_proies, liste_predateurs);
     clear_screen();

     /* On passe a la generation suivante en rafraichissant
     le monde et ses entites */
     rafraichir_proies(&liste_proies, monde);
     rafraichir_predateurs(&liste_predateurs, &liste_proies);
     rafraichir_monde(monde);

     /* On incremente le compteur de generations et on compte
     le nombre de proies et de predateurs */
     nbProies = compte_animal_rec(liste_proies);
     nbPredateurs = compte_animal_rec(liste_predateurs);
     compteur++;
   }


   /* Fermeture du fichier */
   fclose(f);

   /* Liberation de la memoire allouee */
   liberer_liste_animaux(liste_proies);
   liberer_liste_animaux(liste_predateurs);

  return 0;
}
