#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"



/* PARTIE 1*/

/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}

/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}







/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {

  /* Verification des coordonnees */
  assert((x <= SIZE_X) && (x >= 0) && (y <= SIZE_Y) && (y >= 0));

  /* Creation et ajout en tete de l'animal */
  Animal *animal = creer_animal(x, y, energie);
  *liste_animal = ajouter_en_tete_animal(*liste_animal, animal);
}





/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {

  /* Verification si liste vide et si animal valable */
  assert(liste);
  assert(animal);

  Animal *a = *liste;
  Animal *prec = a;

  /* On verifie s'il s'agit du premier element */
  if (a == animal) {
    *liste = a->suivant;
    free(a);
    return ;
  }

  a = a->suivant;

  /* On parcourt toute la liste */
  while (a != NULL) {

    /* On verifie si l'element suivant est l'animal cherche */
    if (a == animal) {
      prec->suivant = a->suivant;
      free(a);
      return ;
    }
    else {
      prec = a;
      a = a->suivant;
    }
  }

  return ;
}





/* A Faire. Part 1, exercice 5, question 2 */
Animal* liberer_liste_animaux(Animal *liste) {

  /* On suppose la liste non vide */

  /* On libere l'espace memoire des elements de la liste un a un */
  while (liste != NULL) {
    Animal *temp = liste;
    liste = liste->suivant;
    free(temp);
  }

  return NULL;
}







/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}







/* Part 1. Exercice 4, question 1 */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {

    unsigned int i, j;
    char ecosys[SIZE_X][SIZE_Y];
    int nbpred=0,nbproie=0;
    Animal *pa=NULL;

    /* On initialise le tableau avec des boucles imbriquees*/
    for (i = 0; i < SIZE_X; i++) {
      for (j = 0; j < SIZE_Y; j++) {
        ecosys[i][j] = ' ';
      }
    }


    /* On ajoute les proies */
    pa = liste_proie;

    while (pa != NULL) {
      ecosys[pa->x][pa->y] = '*';

      nbproie++;
      pa = pa->suivant;
    }


    /* On ajoute les predateurs de la meme facon */
    pa = liste_predateur;

    while(pa != NULL) {

      /* Affichage conditionnel du symbole des predateurs */
      if ((ecosys[pa->x][pa->y] == '*') || (ecosys[pa->x][pa->y] == '@')) {
        ecosys[pa->x][pa->y] = '@';
      }

      else {
        ecosys[pa->x][pa->y] = 'O';
      }

      nbpred++;
      pa = pa->suivant;
    }


    /* On affiche le tableau  ainsi que la mise en page */
    printf("+");
    for (int i = 0; i < SIZE_Y; i++) {
      printf("-");
    }
    printf("+\n");

    for (int i = 0; i < SIZE_X; i++) {
      printf("|");
      for (int j = 0; j < SIZE_Y; j++) {
        printf("%c", ecosys[i][j]);
      }
      printf("|\n");
    }

    printf("+");
    for (int i = 0; i < SIZE_Y; i++) {
      printf("-");
    }
    printf("+\n");
}





void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}





/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
    float p;

    while (la != NULL) {

      /* On teste la probabilite (flottant aleatoire entre 0 et 1)
      et on change aleatoirement la direction si necessaire */
      p = rand() / RAND_MAX;

      if (p <= p_ch_dir) {
        (la->dir)[0] = (rand() % 3) - 1;
        (la->dir)[1] = (rand() % 3) - 1;
      }

      /* On fait bouger la proie en considerant le monde torique */
      la->x = (la->x + (la->dir)[0] + SIZE_X) % SIZE_X;
      la->y = (la->y + (la->dir)[1] + SIZE_Y) % SIZE_Y;


      /* On verifie que les coordonnees sont valides */
      assert((la->x >= 0) && (la->x < SIZE_X) && (la->y >= 0) && (la->y < SIZE_Y));

      la = la->suivant;
    }
}





/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
    double p;
    Animal *pa = *liste_animal;

    while (pa != NULL) {

      /* Probabilite aleatoire */
      p = (double) rand() / RAND_MAX;

      if (p <= p_reproduce) {

        /* On ajoute le bebe avant le parent pour eviter qu'il ne se reproduise
        lors du meme appel de la fonction */
        pa->energie /= 2;
        ajouter_animal(pa->x, pa->y, pa->energie, liste_animal);
      }

      pa = pa->suivant;
    }
}





/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {

    /* On fait bouger les proies */
    bouger_animaux(*liste_proie);
    Animal *pa = *liste_proie;

    while (pa != NULL) {

      /* Les proies mangent si de l'herbe est presente.
      On definit alors un temps de repousse sur la case mangee */
      if (monde[pa->x][pa->y] >= 0) {
        pa->energie += monde[pa->x][pa->y];
        monde[pa->x][pa->y] = temps_repousse_herbe;
      }

      /* Les proies se fatiguent */
      pa->energie--;

      /* Les proies meurent si leur energie est nulle ou negative */
      if (pa->energie <= 0) {
      	Animal *temp = pa;
      	pa = pa->suivant;
        enlever_animal(liste_proie, temp);
      }
      else {
      	pa = pa->suivant;
      }
    }

    /* On fait se reproduire les proies en vie */
    reproduce(liste_proie, p_reproduce_proie);
}





/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {

    while (l != NULL) {

      /* On verifie s'il y a un animal ayant des coordonnees correspondantes
      (on retourne le premier valide) */
      if ((l->x == x) && (l->y == y)) {
        return l;
      }

      l = l->suivant;
    }
    return NULL;
}





/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {

    // On bouge les predateurs
    bouger_animaux(*liste_predateur);

    Animal *pa = *liste_predateur;

    while (pa != NULL) {

      /* On verifie si des proies se situent au meme endroit que le predateur
      Si c'est le cas, la proie est mangee (donc disparait) et le predateur
      "herite" de son energie */
      Animal *proie = animal_en_XY(*liste_proie, pa->x, pa->y);

      if (proie != NULL) {
        pa->energie += proie->energie;
        enlever_animal(liste_proie, proie);
      }

      /* Les predateurs se fatiguent */
      pa->energie--;

      /* On retire de la liste le predateur  si son energie est
      negative ou nulle */
      if (pa->energie <= 0) {
      	Animal *temp = pa;
      	pa = pa->suivant;
        enlever_animal(liste_predateur, temp);
      }
      else {
      	pa = pa->suivant;
      }
    }

    /* On fait se reproduire les predateurs */
    reproduce(liste_predateur, p_reproduce_predateur);

}





/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){

    /* On fait pousser l'herbe en incrementant chaque case */
    for (int i = 0; i < SIZE_X; i++) {
      for (int j = 0; j < SIZE_Y; j++) {
        monde[i][j]++;
      }
    }
}
