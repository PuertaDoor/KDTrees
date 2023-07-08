/* Ce module utilise le tri pivot de cette page web pour traiter les k-ppv : https://fr.wikipedia.org/wiki/Tri_rapide */

#ifndef ETAPE2_H_
#define ETAPE2_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "etape1.h"
#include "allocation.h"
#include "gest_err.h"

/* retourne la distance euclidienne entre deux points (x1,y1) et (x2,y2) */
double distance_euclidienne(double x1, double y1, double x2, double y2);

/* echange la place en memoire des deux points dont l'adresse est passee en parametre */
void echanger_points(point *x, point *y);

/* trie le tableau de points tp par rapport au point (x,y) en fonction de la distance euclidienne entre (x,y) et tous ses points */
void tri_tpoints(tpoints tp, int premier, int dernier, double x, double y);

/* trouve les K plus proches voisins du point (x,y) */
point * trouver_kppv(tpoints tp, int k, double x, double y);

#endif
