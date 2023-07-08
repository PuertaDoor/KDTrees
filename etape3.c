#include "etape3.h"

int max(int * tab, int taille){ /* retourne l'indice de l'entier le plus haut du tableau tab */
  int i;
  int indice = 0; /* on initialise l'entier indice a 0, la taille minimale du tableau de kppv etant de 1 */
  int max = -1;
  for (i=0 ; i<taille ; i++){ /* pour tous les elements de tab */
    if (max<tab[i]){ /* si un element est superieur au dernier maximum rencontre */
      max = tab[i]; /* le maximum devient cet element */
      indice = i; /* et l'indice de ce maximum est retenu aussi */
    }
  }
  return indice; /* et on retourne l'indice de l'element maximum du tableau */
}

int classe_majoritaire(point * tabkppv, int k, int classemax){
  int i;
  int classe_maj;
  int * tab = (int *)allocation_mem_init0(classemax+1,sizeof(int)); /* classemax sert ici a definir la taille du tableau pour en trouver le maximum (qui sera la classe majoritaire des kppv), ici le tableau est a classemax+1 de taille car les classes sont comprises dans l'intervalle [1,classemax] */
  for (i=0 ; i<k ; i++){ /* pour tous les elements du tableau de kppv */
    tab[tabkppv[i].classe]++; /* on incremente la valeur correspondante a la classe dans le tableau que la fonction max() traitera ensuite (l'indice du tableau = classe rencontree et sa valeur = nombre de fois que l'on a rencontre cette classe dans le tableau des kppv) */
  }
  classe_maj = max(tab,classemax+1); /* la classe majoritaire est donc le nombre maximum de fois que l'on a rencontre une classe dans le tableau de kppv, en cas d'egalite c'est la classe la plus proche de 1 qui l'emporte */
  libere_mem(&tab); /* on libere le tableau de classes ayant permis de trouver la classe majoritaire */
  return classe_maj; /* et on retourne la classe trouvee */
}
