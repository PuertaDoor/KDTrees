#include "etape5.h"

int est_dans_zone(point p, zone z_tmp){
  return p.x >= z_tmp.supg.x && p.y >= z_tmp.supg.y && p.x <= z_tmp.infd.x && p.y <= z_tmp.infd.y; /* si le point p est a droite du cote gauche, en-dessous du cote superieur, a gauche du cote droit et au-dessus du cote inferieur de la zone z, alors le point p est dans la zone z */
}

point point_proche_dans_zone(point p, zone z_tmp){
  point p_proche; /* on declare le point qui sera retourne */
  if (p.x>z_tmp.infd.x){ /* si le point p est a droite de z_tmp */
    p_proche.x = z_tmp.infd.x; /* le point le plus proche de p a pour abscisse le cote droit de z_tmp */
  }
  else if (p.x<=z_tmp.infd.x && p.x>=z_tmp.supg.x){ /* sinon si le point p est dans le meme alignement horizontal que z_tmp */
    p_proche.x = p.x; /* alors le point proche a pour abscisse l'abscisse du point p (imaginer une ligne verticale partant du point p et allant jusqu'au bord superieur ou inferieur de la zone pour comprendre) */
  }
  else { /* sinon (point p a gauche de z_tmp) */
    p_proche.x = z_tmp.supg.x; /* le point le plus proche de p a pour abscisse le cote gauche de z_tmp */
  }
  if (p.y<z_tmp.supg.y){ /* si le point p est au-dessus de z_tmp */
    p_proche.y = z_tmp.supg.y; /* alors l'ordonnee du point le plus proche de p est celle du cote superieur de z_tmp */
  }
  else if (p.y>=z_tmp.supg.y && p.y<=z_tmp.infd.y){ /* sinon si le point p est dans le meme alignement vertical que z_tmp */
    p_proche.y = p.y; /* alors l'ordonnee de p_proche prend la valeur de celle de p (imaginer une ligne horizontale partant du point p et allant jusqu'au bord gauche ou droit de la zone pour comprendre) */
  }
  else { /* sinon (p en-dessous de z_tmp) */
    p_proche.y = z_tmp.infd.y; /* l'ordonnee du point le plus proche prend celle du bord inferieur de z_tmp */
  }
  return p_proche; /* et on retourne le point le plus proche de p dans z_tmp ainsi cree */
}

int indice_select_max_liste_points(point * liste, point p, int taille){ /* permet de retourner l'indice du point le plus eloigne de p present dans la liste passee en parametre (taille = taille de la liste) */
  int i;
  int indice = 0; /* indice minimum */
  point p_max = p; /* distance de 0 entre p et lui-meme, plus petite distance possible */
  for (i=0 ; i<taille ; i++){ /* pour tous les points de la liste */
    if (distance_euclidienne(p.x,p.y,p_max.x,p_max.y)<=distance_euclidienne(p.x,p.y,liste[i].x,liste[i].y)){ /* si le distance maximum enregistree entre p et un point de la liste jusqu'alors est egalee ou depassee par celle avec un autre point de cette liste */
      p_max = liste[i]; /* alors le point le plus eloigne devient celui rencontre */
      indice = i; /* et on retient sa position dans la liste des kppv */
    }
  }
  return indice; /* on retourne ainsi l'indice trouve */
}

point max_liste_points(point * liste, point p, int taille){ /* retourne le point le plus eloigne de p present dans la liste passee en parametre (taille = taille de la liste) */
  int i;
  point p_max = p; /* distance de 0 entre p et lui-meme, plus petite distance possible */
  for (i=0 ; i<taille ; i++){ /* pour tous les points de la liste */
    if (distance_euclidienne(p.x,p.y,p_max.x,p_max.y)<=distance_euclidienne(p.x,p.y,liste[i].x,liste[i].y)){ /* si le distance maximum enregistree entre p et un point de la liste jusqu'alors est egalee ou depassee par celle avec un autre point de cette liste */
      p_max = liste[i]; /* alors le point le plus eloigne devient celui rencontre */
    }
  }
  return p_max; /* et on retourne ce point a la fin du parcours de la liste */
}

int peut_faire_partie_kppv(point p, point * liste, zone z, int taille_liste){ /* retourne 1 si le point le plus proche de p appartenant a z peut faire partie de la liste (ici la liste des kppv) */
  point p_proche = point_proche_dans_zone(p,z);
  point p_max = max_liste_points(liste,p,taille_liste);
  return distance_euclidienne(p.x,p.y,p_proche.x,p_proche.y)<distance_euclidienne(p.x,p.y,p_max.x,p_max.y);
}


point * maj_liste(point p, point p_tmp, point * liste, int * taille_liste, int k){
  int i;
  if (liste==NULL){ /* si la liste est vide */
    liste = (point *)allocation_mem(1,sizeof(point)); /* alors on alloue une case dans la memoire a la liste */
    liste[0] = p_tmp; /* la liste contient p_tmp */
    *taille_liste = 1; /* on met a jour la taille de la liste egalement */
  }
  else if (*taille_liste<k){ /* si la liste peut encore contenir des points quelle que soit leur distance avec p (i.e. si elle n'est pas completement remplie) */
    liste = (point *)reallocation_mem((void **)&liste,*taille_liste+1,sizeof(point)); /* alors on augmente de 1 la taille de la liste */
    liste[*taille_liste] = p_tmp; /* et le dernier element de la liste (alors vide) prend comme valeur le point courant */
    *taille_liste+=1;
  }
  else { /* sinon (si la liste contient k elements) */
    i = indice_select_max_liste_points(liste,p,k); /* on selectionne l'indice du point le plus eloigne de p present dans la liste */
    if (distance_euclidienne(p.x,p.y,p_tmp.x,p_tmp.y)<distance_euclidienne(p.x,p.y,liste[i].x,liste[i].y)){ /* si la distance entre p et le point courant est inferieure a celle entre p et ce point le plus eloigne */
      liste[i] = p_tmp; /* alors le point courant prend la place de cet element dans la liste */
    }
  }
  return liste; /* on retourne ensuite le pointeur sur cette liste */
}

point * rechercher_bis(arbre_kd a, point p, int k, point * liste, int * taille_liste){ /* fonction auxiliaire de la fonction rechercher, avec le noeud courant a, le point p dont on recherche les kppv, le nombre k de kppv, la liste des kppv et la taille actuelle de cette liste */
  if (!est_vide_arbre_kd(a)){ /* s'il y a un point courant */
    liste = maj_liste(p,noeud(a),liste,taille_liste,k); /* alors on peut potentiellement mettre a jour la liste */
    if (!est_feuille(a)){ /* si le noeud courant a au moins un fils */
      if (est_vide_arbre_kd(fils_gauche(a))){ /* si ce fils n'est pas le fils gauche */
        if (est_dans_zone(p,zone_noeud(fils_droit(a))) || peut_faire_partie_kppv(p,liste,zone_noeud(fils_droit(a)),*taille_liste)) /* alors on verifie si le fils droit peut faire partie des kppv */
          liste = rechercher_bis(fils_droit(a),p,k,liste,taille_liste); /* et on recherche recursivement dans ce fils droit si oui */
      }
      else if (est_vide_arbre_kd(fils_droit(a))){ /* si ce fils n'est pas le fils droit */
        if (est_dans_zone(p,zone_noeud(fils_gauche(a))) || peut_faire_partie_kppv(p,liste,zone_noeud(fils_gauche(a)),*taille_liste)) /* alors on verifie si le fils gauche peut faire partie des kppv */
          liste = rechercher_bis(fils_gauche(a),p,k,liste,taille_liste); /* et on recherche recursivement dans ce fils gauche si oui */
      }
      else { /* sinon (si le noeud courant a deux fils non vides), alors on fait le traitement comme décrit dans l'énoncé */
        if (est_dans_zone(p,zone_noeud(fils_gauche(a)))){
          liste = rechercher_bis(fils_gauche(a),p,k,liste,taille_liste);
          if (peut_faire_partie_kppv(p,liste,zone_noeud(fils_droit(a)),*taille_liste)){
            liste = rechercher_bis(fils_droit(a),p,k,liste,taille_liste);
          }
        }
        if (est_dans_zone(p,zone_noeud(fils_droit(a)))){
          liste = rechercher_bis(fils_droit(a),p,k,liste,taille_liste);
          if (peut_faire_partie_kppv(p,liste,zone_noeud(fils_gauche(a)),*taille_liste)){
            liste = rechercher_bis(fils_gauche(a),p,k,liste,taille_liste);
          }
        }
        if (!est_dans_zone(p,zone_noeud(fils_gauche(a))) && !est_dans_zone(p,zone_noeud(fils_droit(a)))){
          if (peut_faire_partie_kppv(p,liste,zone_noeud(fils_gauche(a)),*taille_liste)){
            liste = rechercher_bis(fils_gauche(a),p,k,liste,taille_liste);
            if (peut_faire_partie_kppv(p,liste,zone_noeud(fils_droit(a)),*taille_liste)){
              liste = rechercher_bis(fils_droit(a),p,k,liste,taille_liste);
            }
          }
          else if (peut_faire_partie_kppv(p,liste,zone_noeud(fils_droit(a)),*taille_liste)){
            liste = rechercher_bis(fils_droit(a),p,k,liste,taille_liste);
            if (peut_faire_partie_kppv(p,liste,zone_noeud(fils_gauche(a)),*taille_liste)){
              liste = rechercher_bis(fils_gauche(a),p,k,liste,taille_liste);
            }
          }
        }
      }
    }
  }
  return liste;
}

point * rechercher(arbre_kd a, point p, int k){
  point * kppv = NULL; /* on initialise la liste des kppv */
  int taille_kppv = 0; /* la liste est vide donc sa taille est a 0 */
  return rechercher_bis(a,p,k,kppv,&taille_kppv); /* et on retourne les kppv trouves par la fonction auxiliaire de recherche */
}
