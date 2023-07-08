/* Module d'allocation de M. HABRARD, dispense en cours magistral de Programmation Imperative II */

#include "allocation.h"

void * allocation_mem(size_t nobjets, size_t taille){
  void * pt;
  pt = malloc(nobjets * taille); /* allocation */
  if (pt==NULL){ /* on verifie si l'allocation a marche */
    erreur("La memoire %d %d n'a pas pu etre allouee",nobjets,taille);
  }
  return pt;
}

void * allocation_mem_init0(size_t nobjets, size_t taille){
  void * pt;
  pt = calloc(nobjets,taille); /* allocation avec initialisation des valeurs a 0 */
  if (pt==NULL){ /* on verifie si l'allocation a marche */
    erreur("La memoire %d %d n'a pas pu etre allouee",nobjets,taille);
  }
  return pt;
}

void * reallocation_mem(void **pt, size_t nobjets, size_t taille){
  void *pt_realloc = realloc(*pt, nobjets*taille);
  if (pt_realloc!=NULL) /* on verifie si realloc a bien marche */
    *pt = pt_realloc; /* si oui, alors pt pointe sur la nouvelle adresse avec la bonne memoire */
  else
    erreur("Impossible de reallouer la memoire %d * %d a l'adresse %p",nobjets,taille,*pt); /* sinon erreur */

  return pt_realloc;
}

void libere_mem(void *pt){
  void ** adr_pt = (void **)pt;
  if ((*adr_pt)!=NULL)
    free(*adr_pt); /* liberation de *pt */

  *adr_pt = NULL; /* *pt pointe maintenant sur NULL, c'est-a-dire rien */
}
