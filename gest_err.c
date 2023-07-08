/* Module de gestion d'erreurs de M. HABRARD */

#include "gest_err.h"

void erreur(char *s, ...){
  va_list arg;
  va_start(arg,s);
  fprintf(stderr,"Erreur : ");
  vfprintf(stderr,s,arg);
  va_end(arg);
  exit(EXIT_FAILURE);
}
