#include "gen_fic_alea_donnees.h"

void usage(char *s){
  erreur("Usage : %s <nomfichier> <entier> <entier> <entier>\nnombre de points puis nombre de classes puis nombre de dimensions (trois entiers superieurs a 0, nombre de dimensions == 2)\n",s);
}

void generation_fichier_aleatoire(char *nomfichier, int n, int c, int d){
  int i,j;
  int classe;
  double coord;
  FILE* fichier = NULL; /* initialisation */

  fichier = fopen(nomfichier, "w"); /* on ouvre en ecriture le fichier de nom nomfichier, le fichier est cree dans le repertoire courant s'il n'existe pas */
  if (fichier==NULL){
    erreur("Impossible de creer le fichier %s",nomfichier);
  }
  srand(time(NULL)); /* initialisation de la pseudo-aleatoire */
  fprintf(fichier,"%d %d %d\n",n,c,d); /* on imprime sur la premiere ligne du fichier le nombre de points a generer, l'intervalle entre 1 et c des classes et le nombre de dimensions */
  for (i=0 ; i<n ; i++){ /* n points à generer donc n lignes */

    classe = 1 + rand()%c; /* la classe d'un point est comprise entre 1 et c */
    fprintf(fichier,"%d",classe); /* on imprime d'abord la classe */

    for (j=0 ; j<d ; j++){
      /* on convertit rand en double et on divise son nombre renvoye par RAND_MAX, une constante de stdlib nous permettant ici de generer un nombre aleatoire compris entre 0 et 1
      (la valeur retournee par rand ne peut etre plus haut que RAND_MAX), qu'on multiplie par 2 pour generer un nombre entre 0 et 2, qui devient un intervalle [-1;1] avec la soustraction de 1 */
      coord = -1 + ((double)rand()/(double)RAND_MAX) * 2;
      fprintf(fichier," %f",coord); /* on met un espace devant pour correspondre a un format de fichier lisible */
    }

    fprintf(fichier,"\n"); /* on a fini d'imprimer la ligne */
  }
  fclose(fichier); /* on ferme le flux menant au fichier */
}

int main(int argc, char *argv[]){
  if (argc!=5) /* on a besoin de 4 arguments */
    usage(argv[0]);
  else if (atoi(argv[2])<1 || atoi(argv[3])<1 || atoi(argv[4])!=2)
    usage(argv[0]);
  generation_fichier_aleatoire(argv[1],atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));
  return EXIT_SUCCESS;
}
