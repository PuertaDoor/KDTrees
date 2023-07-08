/* Module d'allocation de M. HABRARD, dispense en cours magistral de Programmation Imperative II */

#ifndef ALLOCATION_H_
#define ALLOCATION_H_

#include <stdio.h>
#include <stdlib.h>
#include "gest_err.h" /* utile pour gerer les impossibilites d'allocation */

/* Fait la meme chose que malloc mais avec la verification de la bonne allocation de memoire en plus */
void * allocation_mem(size_t nobjets, size_t taille);

/* Fait la meme chose que calloc mais avec la verification de la bonne allocation de memoire en plus */
void * allocation_mem_init0(size_t nobjets, size_t taille);

/* Fait la meme chose que realloc et met a jour le pointeur pt vers celui retourne par la fonction si la realloc a marche et renvoie une erreur et stoppe l'execution sinon */
void * reallocation_mem(void **pt, size_t nobjets, size_t taille);

/* Fait la meme chose que free mais n'execute la fonction free que si *pt pointe sur quelque chose puis fait pointer *pt sur NULL */
void libere_mem(void *pt);

#endif
