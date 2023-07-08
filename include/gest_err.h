/* Module de gestion d'erreurs de M. HABRARD */

#ifndef GEST_ERR_H
#define GEST_ERR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/* Fonction permettant d'écrire dans stderr une erreur associee avec un nombre parametres variable et de clore l'execution du programme, utilisee pour la gestion d'erreur */
void erreur(char *s, ...);

#endif
