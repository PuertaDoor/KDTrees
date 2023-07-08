#ifndef GEN_FIC_ALEA_DONNEES_
#define GEN_FIC_ALEA_DONNEES_

#include <stdio.h>
#include <stdlib.h>
#include <time.h> /* pour gerer l'aleatoire */
#include "gest_err.h" /* pour la gestion d'erreurs */

/* affiche l'aide du programme en cas de mauvaise entree */
void usage(char *s);

/* cree un fichier de jeux de donnees avec pour parametres le nom du fichier de sortie, le nombre de points a generer, le nombre de classes et le nombre de dimensions */
void generation_fichier_aleatoire(char *nomfichier, int n, int c, int d);

#endif
