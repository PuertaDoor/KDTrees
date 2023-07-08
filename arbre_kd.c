#include "arbre_kd.h"

arbre_kd arbre_vide(){
  return NULL; /* retourne le pointeur NULL vu que nous avons defini les arbres comme etant des pointeurs */
}

int est_vide_arbre_kd(arbre_kd a){
  return a==arbre_vide(); /* test booleeen renvoyant 1 si a est vide (pointe sur NULL) et 0 sinon */
}

element noeud(arbre_kd a){
  return a->noeud; /* retourne le point courant de l'arbre a */
}

arbre_kd fils_gauche(arbre_kd a){
  return a->fg; /* retourne le champ fg (fils gauche) du noeud courant */
}

arbre_kd fils_droit(arbre_kd a){
  return a->fd; /* retourne le champ fd (fils droit) du noeud courant */
}

zone zone_noeud(arbre_kd a){
  return a->z; /* retourne la zone courante */
}

int est_feuille(arbre_kd a){
  return !est_vide_arbre_kd(a) && est_vide_arbre_kd(fils_gauche(a)) && est_vide_arbre_kd(fils_droit(a)); /* si a n'est pas vide et ses fils droit et gauche sont vides, alors a est une feuille */
}

arbre_kd creer_noeud(element e){
  arbre_kd a = (arbre_kd)allocation_mem(1,sizeof(struct_branche)); /* on alloue la memoire necessaire a la mise en place d'un noeud */
  a->noeud = e; /* le point courant est le point passe en parametre */
  a->fg = arbre_vide(); /* on cree un noeud donc a fortiori une feuille, sinon on creerait un arbre */
  a->fd = arbre_vide();
  a->z.supg.x = -1; /* la zone de travail de notre projet est [-1,1]x[-1,1] */
  a->z.supg.y = -1;
  a->z.infd.x = 1;
  a->z.infd.y = 1;
  return a; /* et on retourne le noeud ainsi cree */
}

arbre_kd creer_noeud_zone(element e, zone z){
  arbre_kd a = creer_noeud(e); /* on cree le noeud avec comme point e */
  a->z = z; /* et la zone associee a ce noeud est la zone z passee en parametre */
  return a; /* on renvoie le noeud ainsi cree */
}

arbre_kd inserer_filsgauche(arbre_kd a, arbre_kd filsgauche){
  if (!est_vide_arbre_kd(a)){ /* si le noeud courant n'est pas vide */
    a->fg = filsgauche; /* alors son fils gauche devient filsgauche, passe en parametre */
    a->fg->z = zone_noeud(a); /* et la zone associee a ce fils est la meme que son noeud parent, modifiee ensuite au besoin dans les fonctions d'insertion de point */
  }
  return a;
}

arbre_kd inserer_filsdroit(arbre_kd a, arbre_kd filsdroit){ /* meme logique que pour l'insertion du fils gauche mais avec le fils droit du noeud courant */
  if (!est_vide_arbre_kd(a)){
    a->fd = filsdroit;
    a->fd->z = zone_noeud(a);
  }
  return a;
}

arbre_kd inserer_bis(arbre_kd a, point p, int dim_comp, zone z){ /* fonction auxiliaire de la fonction inserer, avec comme parametres le noeud courant a, le point p a inserer, la zone courante z et le booleen dim_comp permet de choisir l'axe de comparaison des coordonnees en fonction de la profondeur dans l'arbre */
  zone z_tmp;
  if (!est_vide_arbre_kd(a)){ /* si l'arbre a n'est pas vide */
    z_tmp = zone_noeud(a); /* alors on affecte a z_tmp la zone courante */
  }
  if (est_vide_arbre_kd(a)){ /* si l'arbre a est vide */
    return creer_noeud_zone(p,z); /* l'arbre a devient une feuille avec la zone courante z passee en parametre et le point courant p passe en parametre */
  }
  if (est_feuille(a)){ /* sinon si l'arbre est une feuille */
    if (!dim_comp){ /* si dim_comp==0, on prend comme axe de comparaison l'axe x */
      if (p.x < a->noeud.x){ /* si le point a inserer se situe a gauche du point courant dans la zone de travail generale */
        a = inserer_filsdroit(a,creer_noeud_zone(p,z)); /* alors on l'insere dans le fils droit */
        a->fd->z.infd.x = a->noeud.x; /* la zone associee au fils droit prend comme cote droit la coordoonnee x du point courant */
        return a; /* et on retourne le pointeur sur l'arbre ainsi cree */
      }
      else { /* si le point a inserer se situe a droite ou dans la meme abscisse que celle du point courant */
        a = inserer_filsgauche(a,creer_noeud_zone(p,z)); /* on l'insere dans le fils gauche du noeud courant */
        a->fg->z.supg.x = a->noeud.x; /* la zone associee au fils gauche prend comme cote gauche la coordonnee x du point courant */
        return a; /* et on retourne le pointeur sur l'arbre ainsi cree */
      }
    }
    else { /* si dim_comp==1, on prend comme axe de comparaison l'axe y */
      if (p.y < a->noeud.y){ /* si le point p se situe au-dessus du point courant dans la zone de travail generale */
        a = inserer_filsdroit(a,creer_noeud_zone(p,z)); /* alors on l'insere dans le fils droit */
        a->fd->z.infd.y = a->noeud.y; /* la zone associee a ce point prend comme cote inferieur la coordonnee y du point courant */
        return a;
      }
      else { /* si le point a inserer se situe en-dessous du point courant ou sur la meme ligne dans la zone de travail generale */
        a = inserer_filsgauche(a,creer_noeud_zone(p,z)); /* alors on l'insere dans le fils droit */
        a->fg->z.supg.y = a->noeud.y; /* la zone associee a ce point prend comme cote superieur la coordonnee y du point courant */
        return a; /* et on retourne le pointeur sur l'arbre ainsi cree */
      }
    }
  }
  else { /* si l'arbre n'est pas une feuille */
    if (!dim_comp){ /* si l'axe de comparaison courant est l'abscisse cartesienne */
      if (p.x < a->noeud.x){ /* si le point p se situe a gauche du point courant dans notre espace de travail */
        z_tmp.infd.x = a->noeud.x; /* alors la zone a laquelle appartiendra potentiellement le point est mise a jour */
        a->fd = inserer_bis(a->fd,p,1-dim_comp,z_tmp); /* et on insere recursivement en modifiant dim_comp pour le faire passer sur l'autre axe */
      }
      else { /* si le point p se situe a droite ou sur le meme axe que le point courant dans notre espace de travail */
        z_tmp.supg.x = a->noeud.x; /* alors la zone a laquelle appartiendra potentiellement le point est mise a jour */
        a->fg = inserer_bis(a->fg,p,1-dim_comp,z_tmp); /* et on insere recursivement en modifiant dim_comp pour le faire passer sur l'autre axe */
      }
    }
    else { /* si l'axe de comparaison courant est l'ordonnee cartesienne */
      if (p.y < a->noeud.y){ /* si le point p se situe au-dessus du point courant dans notre espace de travail */
        z_tmp.infd.y = a->noeud.y; /* alors la zone a laquelle appartiendra potentiellement le point est mise a jour */
        a->fd = inserer_bis(a->fd,p,1-dim_comp,z_tmp); /* et on insere recursivement en modifiant dim_comp pour le faire passer sur l'autre axe */
      }
      else { /* si le point p se situe en-dessous ou sur la meme ligne que le point courant */
        z_tmp.supg.y = a->noeud.y; /* alors la zone a laquelle appartiendra potentiellement le point est mise a jour */
        a->fg = inserer_bis(a->fg,p,1-dim_comp,z_tmp); /* et on insere recursivement en modifiant dim_comp pour le faire passer sur l'autre axe */
      }
    }
    return a; /* on renvoie le pointeur sur le nouvel arbre a */
  }
}

arbre_kd inserer(arbre_kd a, point p){
  zone z; /* on initialise la zone de l'arbre k-d a a sa taille maximum (ici [-1,1]x[-1,1])*/
  z.supg.x = -1;
  z.supg.y = -1;
  z.infd.x = 1;
  z.infd.y = 1;
  return inserer_bis(a,p,0,z); /* et on retourne l'arbre a avec le point p insere */
}

int profondeur_arbre(arbre_kd a){
  if (est_vide_arbre_kd(a)){ /* si l'arbre a est vide */
    return 0; /* alors sa profondeur est de 0 */
  }
  else { /* sinon */
    if (profondeur_arbre(fils_gauche(a))<profondeur_arbre(fils_droit(a))){ /* si la profondeur du fils gauche est inferieure a celle du fils droit */
      return 1+profondeur_arbre(fils_droit(a)); /* alors la profondeur de l'arbre est de 1 plus la profondeur du fils droit (car la profondeur d'un arbre est la profondeur maximale d'un noeud de cet arbre) */
    }
    else { /* sinon */
      return 1+profondeur_arbre(fils_gauche(a)); /* on retourne 1 plus la profondueur du fils gauche */
    }
  }
}

int nb_noeuds(arbre_kd a){
  if (est_vide_arbre_kd(a)){ /* si l'arbre a est vide */
    return 0; /* alors il n'a pas de noeud donc son nombre de noeuds est de 0 */
  }
  else { /* sinon */
    return 1+nb_noeuds(fils_gauche(a))+nb_noeuds(fils_droit(a)); /* son nombre de noeuds vaut 1 (le noeud courant existe) + le nombre de noeuds de son fils gauche + le nombre de noeuds de son fils droit */
  }
}

void afficher_arbre_kd_bis(arbre_kd a, int prof){ /* fonction auxiliaire de afficher_arbre_kd prenant en parametre le noeud courant de l'arbre a et la profondeur de ce noeud */
  int i;
  if (!est_vide_arbre_kd(a)){ /* si l'arbre n'est pas vide */
    printf("(%f,%f)\n",a->noeud.x,a->noeud.y); /* alors on affiche le point courant */
    for (i=0 ; i<prof-1 ; i++){ /* le nombre de tabulations correspond a la profondeur du noeud courant (permet un affichage plus lisible) */
      printf("  ");
    }
    printf("Zone : (%f,%f)x(%f,%f)\n",a->z.supg.x,a->z.supg.y,a->z.infd.x,a->z.infd.y); /* on affiche la zone courante au meme niveau que son point correspondant */
    for (i=0 ; i<prof ; i++){ /* le nombre de tabulations equivaut a la profondeur du noeud courant + 1 puisque les fils du noeud courant sont a profondeur(noeud_courant)+1 */
      printf("  ");
    }
    printf("Fils gauche : ");
    afficher_arbre_kd_bis(fils_gauche(a),prof+1); /* on affiche recursivement le fils gauche */
    for (i=0 ; i<prof ; i++){
      printf("  ");
    }
    printf("Fils droit : ");
    afficher_arbre_kd_bis(fils_droit(a),prof+1); /* on affiche recursivement le fils droit */
  }
  else { /* si l'arbre est vide */
    printf("NULL\n"); /* on ecrit NULL puisque le pointeur de l'arbre vide est NULL */
  }
}

void afficher_arbre_kd(arbre_kd a){
  afficher_arbre_kd_bis(a,1); /* on appelle la fonction auxiliaire avec 1 comme profondeur initiale (cette valeur n'a que peu d'importance en soi tant que l'affichage reste coherent et que le code correspondant suit) */
  printf("\n"); /* et on saute une ligne pour une meilleure lisibilite dans la sortie */
}

arbre_kd chargement_arbre_kd_tp(tpoints tp){
  arbre_kd a = arbre_vide(); /* on cree l'arbre */
  int i; /* iterateur parcourant le tableau de points */
  for (i=0 ; i<tp.taille ; i++){
    a = inserer(a,tp.tp[i]); /* on insere un par un les points en parcourant le tableau */
  }
  return a; /* et on retourne le pointeur sur l'arbre ainsi cree */
}

void detruire_arbre(arbre_kd a){
  if (!est_vide_arbre_kd(a)){ /* si l'arbre n'est pas vide (puisque s'il est vide pas besoin de le detruire) */
    detruire_arbre(a->fg); /* on detruit les deux fils recursivement (en realite on supprime recursivement les feuilles de l'arbre jusqu'a ce que l'arbre soit une feuille) */
    detruire_arbre(a->fd);
    libere_mem(&a); /* et on libere la memoire allouee a l'arbre etant devenu une feuille */
  }
}
