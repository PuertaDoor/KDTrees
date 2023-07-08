#ifndef ARBRE_KD_H_
#define ARBRE_KD_H_

#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "etape1.h"
#include "allocation.h"
#include "gest_err.h"

typedef point element;

typedef struct {
  double x;
  double y;
} coords;

typedef struct {
  coords supg;
  coords infd;
} zone; /* une zone est definie par son coin superieur gauche et son coin inferieur droit ici (MLV gere les ordonnees en partant du haut de l'ecran) */

typedef struct branche {
  element noeud;
  zone z;
  struct branche * fg;
  struct branche * fd;
} struct_branche; /* une zone est associee a chaque point en fonction de sa place dans l'arbre */

typedef struct_branche * arbre_kd;

/* renvoie un arbre vide */
arbre_kd arbre_vide();

/* renvoie 1 si a est un arbre vide, 0 sinon */
int est_vide_arbre_kd(arbre_kd a);

/* retourne 1 si l'arbre a est une feuille (i.e. s'il n'a pas de fils ou alors s'ils sont tous vides) */
int est_feuille(arbre_kd a);

/* renvoie le noeud courant de l'arbre a */
element noeud(arbre_kd a);

/* renvoie le fils gauche de l'arbre a */
arbre_kd fils_gauche(arbre_kd a);

/* renvoie le fils droit de l'arbre a */
arbre_kd fils_droit(arbre_kd a);

/* retourne la zone associee au noeud a */
zone zone_noeud(arbre_kd a);

/* renvoie un arbre ayant pour element e et des fils vides */
arbre_kd creer_noeud(element e);

/* renvoie l'arbre a avec comme fils gauche filsgauche */
arbre_kd inserer_filsgauche(arbre_kd a, arbre_kd filsgauche);

/* renvoie l'arbre a avec comme fils droit filsdroit */
arbre_kd inserer_filsdroit(arbre_kd a, arbre_kd filsdroit);

/* insere un point p dans l'arbre a et retourne l'arbre a modifie */
arbre_kd inserer(arbre_kd a, point p);

/* renvoie la profondeur de l'arbre a (inutilise mais utile pour des idees d'amelioration) */
int profondeur_arbre(arbre_kd a);

/* renvoie le nombre de noeuds de l'arbre a (inutilise mais utile pour des idees d'amelioration) */
int nb_noeuds(arbre_kd a);

/* affiche l'arbre kd a sur le terminal */
void afficher_arbre_kd(arbre_kd a);

/* cree un arbre kd a partir d'un tableau de points et le retourne */
arbre_kd chargement_arbre_kd_tp(tpoints tp);

/* detruit l'arbre a de la memoire */
void detruire_arbre(arbre_kd a);

#endif
