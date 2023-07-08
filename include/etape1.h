#ifndef ETAPE1_H_
#define ETAPE1_H_

#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "allocation.h"

/* Etape 1.1 : implementation de la structure point */
typedef struct {
  double x; /* abscisse du point */
  double y; /* ordonnee du point */
  int classe; /* classe du point */
} point;

/* Etape 1.2 : implementation du tableau de structures point de taille variable */
typedef struct {
  int taille; /* taille du tableau */
  int classemax; /* classe maximum des points du tableau */
  int dim; /* dimension des points du tableau */
  point * tp; /* tableau de points de taille dynamique */
} tpoints;

/* retourne un tableau de points vide */
tpoints init_tpoints();

/* Etape 1.3 : implementation de la fonction de chargement de donnees, ayant pour paramètre le flux a lire (ici un fichier), et retourne un tableau de points de la taille du nombre de lignes de donnees du fichier */
tpoints chargement_fichier(char *nomfic);

/* permet d'ajouter un point avec ses trois champs au tableau tp et augmente la taille du tableau de 1 */
void ajout_point(tpoints *tp, int classe, double x, double y);

/* permet de supprimer le dernier element du tableau tp */
void supprimer_derniere_saisie(tpoints *tp);

/* fonction de sauvegarde des informations presentes dans tp dans un fichier nom */
void sauvegarde_fichier(char *nom, tpoints tp);

/* libere la memoire allouee au tableau de points et passe sa taille a 0 */
void reinitialiser_tab(tpoints *tp);

#endif
