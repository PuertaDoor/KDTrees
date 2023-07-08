/* Cette partie utilise le tri pivot pour traiter les k-ppv, voici la source explicative de l'algorithme utilise pour trier le tableau : https://fr.wikipedia.org/wiki/Tri_rapide */

#include "etape2.h"

double distance_euclidienne(double x1, double y1, double x2, double y2){ /* distance euclidienne entre deux points (x1,y1) et (x2,y2) */
  return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)); /* la distance euclidienne entre deux points d'un plan cartesien equivaut a la norme du vecteur ayant pour extremites ces deux points */
}

void echanger_points(point *x, point *y){ /* fonction d'echange basique entre deux points, ici faisant partie d'un meme tableau (sert pour le tri pivot) */
  point tmp = *x;
  *x = *y;
  *y = tmp;
}

int partition(tpoints tp, int premier, int dernier, int pivot, double x, double y){ /* fonction servant pour le tri pivot, partitionne un sous tableau et le range en ordre croissant selon les distances euclidiennes entre le point (x,y) et les points du sous tableau */
  int i,j=premier;
  echanger_points(&tp.tp[pivot],&tp.tp[dernier]); /* on echange le pivot avec le dernier point dans la partie du tableau situee entre premier et dernier, tp.tp[pivot] devient donc le dernier point de la partie du tableau traitee */
  for (i=premier ; i<dernier ; i++){
    if (distance_euclidienne(x,y,tp.tp[i].x,tp.tp[i].y)<=distance_euclidienne(x,y,tp.tp[dernier].x,tp.tp[dernier].y)){
      echanger_points(&tp.tp[i],&tp.tp[j]);
      j++;
    }
  }
  echanger_points(&tp.tp[dernier],&tp.tp[j]);
  return j;
}

void tri_tpoints(tpoints tp, int premier, int dernier, double x, double y){ /* tri pivot du tableau de points en fonction d'un point donne en parametre */
  int pivot;
  srand(time(NULL));
  if (premier<dernier){
    pivot = premier + rand()%(dernier-premier+1);
    pivot = partition(tp,premier,dernier,pivot,x,y);
    tri_tpoints(tp,premier,pivot-1,x,y);
    tri_tpoints(tp,pivot+1,dernier,x,y);
  }
}

point * trouver_kppv(tpoints tp, int k, double x, double y){
  int i; /* interateur pour parcourir le tableau et creer une copie des k premieres valeurs de ce tableau tp */
  point * tabkppv = NULL; /* on initialise le tableau de points contenant les kppv du point (x,y) */
  int n = tp.taille;
  if (k>n){
    printf("k trop grand, on prendra donc tous les points du tableau"); /* si k est plus grand que la taille du tableau, alors la liste des kppv sera le tableau entier de points */
    k = n;
  }
  tabkppv = (point *)allocation_mem(k,sizeof(point)); /* on alloue k cases au tableau des kppv */
  tri_tpoints(tp,0,n-1,x,y); /* on trie le tableau de points tp */
  for (i=0 ; i<k ; i++){ /* et on remplit tabkppv avec les k premieres valeurs de ce tableau trie */
    tabkppv[i] = tp.tp[i];
  }
  return tabkppv; /* puis on retourne le pointeur sur ce tableau */
}
