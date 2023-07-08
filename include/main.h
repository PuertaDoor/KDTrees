#ifndef AFFICHAGE_H_
#define AFFICHAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include <string.h>
#include "gest_err.h" /* en-tête du module de gestion d'erreurs dans le terminal */
#include "allocation.h" /* en-tête du module contenant les fonctions d'allocation de notre programme */
#include "etape1.h" /* en-tête du module definissant les structures et fonctions de gestion des points avec tableau et de sauvegarde/chargement des fichiers */
#include "etape2.h" /* en-tête du module cherchant les k-ppv par tri de tableau */
#include "etape3.h" /* en-tête du module de l'election de la classe majoritaire (quand la case "avec prise de decision" est activee) */
#include "arbre_kd.h" /* en-tête du module definissant les arbres k-d et leurs zones associees, ainsi que les fonctions de gestion */
#include "etape5.h" /* en-tête du module de recherche des k-ppv par arbre k-d */

#define LARGEUR 1600 /* definition de la plupart des ecrans en 16:9 */
#define HAUTEUR 900

/* fonction d'initialisation de la fenetre */
void initialiser_mlv(char* f);

/* fonction dessinant toutes les zones, zones de texte et d'interaction */
void dessiner_zone();

/* gere les clics de l'utilisateur en fonction du moment / de l'endroit vise */
void gestion_click(tpoints *tp);

#endif
