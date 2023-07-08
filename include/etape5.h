#ifndef ETAPE_5_H
#define ETAPE_5_H

#include <stdio.h>
#include <stdlib.h>
#include "gest_err.h"
#include "etape2.h"
#include "allocation.h"
#include "arbre_kd.h"

/* recherche les k-ppv du point p dans l'arbre a */
point * rechercher(arbre_kd a, point p, int k);

/* met a jour la liste des k-ppv en ignorant ou ajoutant le point p_tmp (point courant) en fonction de de la position de p_tmp avec les autres elements dans la liste par rapport a p (point dont on rehcerche les kppv) */
point * maj_liste(point p, point p_tmp, point * liste, int * taille_liste, int k);

/* calcule le point le plus proche de p appartenant a la zone z_tmp */
point point_proche_dans_zone(point p, zone z_tmp);

/* retourne 1 si p est dans la zone z_tmp et 0 sinon */
int est_dans_zone(point p, zone z_tmp);

/* retourne le point de la liste ayant la distance euclidienne la plus elevee avec le point p */
point max_liste_points(point * liste, point p, int taille);

#endif
