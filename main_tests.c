#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"


#define NB_PROIES 20
#define NB_PREDATEURS 20


/* Parametres globaux de l'ecosysteme */
float p_ch_dir = 0.01;
float p_reproduce_proie = 1;
float p_reproduce_predateur = 1;
int temps_repousse_herbe = -15;


int main(void) {

  srand(time(NULL));

  /* Tableau temoin du monde */
  int monde[SIZE_X][SIZE_Y];
  for (int i = 0; i < SIZE_X; i++) {
    for (int j = 0; j < SIZE_Y; j++) {
      monde[i][j] = 0;
    }
  }

  /* Creation des listes et des animaux pour les tests */
  Animal *liste_proies = NULL;
  Animal *liste_predateurs = NULL;

  Animal *a1 = creer_animal(0,0,10.5);
  Animal *a2 = creer_animal(2,2,30.0);
  Animal *a3 = creer_animal(2,1,10.5);
  Animal *a4 = creer_animal(1,4,30.0);

  /* Test de la fonction ajouter_en_tete */
  liste_proies = ajouter_en_tete_animal(liste_proies, a1);
  liste_proies = ajouter_en_tete_animal(liste_proies, a3);
  liste_predateurs = ajouter_en_tete_animal(liste_predateurs, a2);
  liste_predateurs = ajouter_en_tete_animal(liste_predateurs, a4);

  /* Test de la fonction enlever_animal */
  enlever_animal(&liste_proies, a3);
  enlever_animal(&liste_predateurs, a4);

  /* Test des fonctions regissant les comportements des animaux */
  rafraichir_predateurs(&liste_predateurs, &liste_proies);
  rafraichir_proies(&liste_proies, monde);

  /* Test de la fonction d'affichage */
  afficher_ecosys(liste_proies, liste_predateurs);

  /* Liberation de la memoire allouee pour verifier l'absence
  de fuite memoire */
  liberer_liste_animaux(liste_proies);
  liberer_liste_animaux(liste_predateurs);

  return 0;
}
