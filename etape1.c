#include "etape1.h"

tpoints init_tpoints(int classemax){
  tpoints tp;
  tp.taille=0; /* taille du tableau de 0 car tableau vide */
  tp.tp = NULL; /* le tableau de points ne doit pas etre alloue tant qu"il est vide */
  tp.classemax = classemax;
  tp.dim = 2; /* Le nombre de dimensions est fixe dans le cadre de ce projet */
  return tp;
}

tpoints chargement_fichier(char *nomfic){
  tpoints tp; /* initialisation du pointeur vers le tableau de points final */
  FILE* fichier = NULL; /* initialisation du pointeur de fichier */
  int i=0; /* initialisation de l'iterateur qui permettra de remplir les bonnes cases du tableau tp */
  if ((fichier = fopen(nomfic,"r"))==NULL){ /* Si fichier non trouve */
    erreur("Fichier inexistant ou errone\n"); /* Alors on affiche l'erreur voulue et on arrete l'execution */
  }
  if (fscanf(fichier,"%d %d %d",&tp.taille,&tp.classemax,&tp.dim)!=3){ /* si la premiere ligne n'est pas de bon format */
    erreur("Mauvais format de fichier\n"); /* alors erreur et fin d'execution */
  }
  tp.tp = (point *)allocation_mem(tp.taille,sizeof(point)); /* on alloue d'office la memoire necessaire pour stocker un point a tp pour simplifier le traitement */
  while (fscanf(fichier,"%d %lf %lf",&tp.tp[i].classe,&tp.tp[i].x,&tp.tp[i].y)==3){ /* on lit les lignes tant qu'il y en a ou qu'elles sont au bon format en assignant les bonnes valeurs aux bonnes variables */
    i++; /* on incremente l'iterateur pour stocker l'eventuelle ligne d'apres dans les bonnes cellules du tableau */
  }
  return tp; /* et on retourne le tableau de points tp */
}

void ajout_point(tpoints *tp, int classe, double x, double y){
  int n;
  n = tp->taille; /* n = taille du tableau */
  if (tp->taille==0){ /* si le tableau est vide */
    tp->tp = (point *)allocation_mem(1,sizeof(point)); /* alors on alloue une case au tableau dans la memoire */
  }
  else { /* sinon */
    tp->tp = (point *)reallocation_mem((void **)&tp->tp,n+1,sizeof(point)); /* on realloue la memoire necessaire a l'ajout d'un point (en fin de tableau ici etant donne l'utilisation implicite de realloc) */
  }
  tp->taille++; /* on augmente la taille du tableau de 1 */
  tp->tp[n].classe = classe; /* et on stocke les donnees passees en argument */
  tp->tp[n].x = x;
  tp->tp[n].y = y;
}

void supprimer_derniere_saisie(tpoints *tp){
  if (tp->taille>0){ /* si le tableau n'est pas vide */
    tp->taille--; /* on diminue sa taille de 1 */
    if (tp->taille==0){ /* puis si la taille du tableau sans sa derniere saisie est nulle */
      libere_mem(&tp->tp); /* on libere la memoire allouee au tableau de points */
    }
    else {
      tp->tp = (point *)reallocation_mem((void **)&tp->tp,tp->taille,sizeof(point)); /* sinon on realloue la memoire avec une case de moins (la memoire occupee precedemment est liberee) */
    }
  }
}

void sauvegarde_fichier(char *nom, tpoints tp){
  int i; /* iterateur pour acceder aux differents elements du tableau de points */
  FILE* fichier = NULL; /* initialisation du pointeur vers le fichier */
  fichier = fopen(nom,"w"); /* on ouvre un fichier en ecriture seule (cree si inexistant donc ecrase) */
  if (fichier==NULL){ /* si le flux ne s'est pas bien cree */
    erreur("Fichier pas possible a creer ou ecraser, le flux ne s'est pas ouvert\n"); /* alors erreur et fin d'execution */
  }
  fprintf(fichier,"%d %d %d\n",tp.taille,tp.classemax,tp.dim); /* sinon on imprime la premiere ligne contenant les caracteristiques du tableau (les 3 premiers champs de la structure tpoints)*/
  for (i=0 ; i<tp.taille ; i++){ /* on imprime ligne par ligne dans le fichier les donnees */
    fprintf(fichier,"%d %f %f\n",tp.tp[i].classe,tp.tp[i].x,tp.tp[i].y);
  }
  fclose(fichier); /* et on ferme le flux menant au fichier */
}

void reinitialiser_tab(tpoints *tp){
  libere_mem(&tp->tp); /* on supprime le tableau entier en liberant la memoire qui lui etait allouee */
  tp->taille = 0; /* et la taille du tableau passe donc a 0 */
}
