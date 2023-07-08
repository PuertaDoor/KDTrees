#include "main.h"

int mode,avec_pdd,dessin,fichier_charge,doit_suppr,aff_zone;
int k=1,c=1;
char *kstr = NULL;
char *cstr = NULL;

void initialiser_mlv(char* f){
  MLV_create_window(f, "icone", LARGEUR, HAUTEUR);
  MLV_clear_window(MLV_COLOR_WHITE);
}

void dessiner_checkbox(int x, int y, MLV_Color color, const char *text){
  MLV_draw_rectangle(x,y,10,10,color);
  MLV_draw_text(x+15,y,text,color);
}

void checked(int x, int y, MLV_Color color){
  MLV_draw_filled_rectangle(x,y,8,8,color);
  MLV_update_window();
}

void dessiner_zone(){

  /* zone d'affichage des kppv */
  MLV_draw_line((LARGEUR/2)-200, HAUTEUR/2, (LARGEUR/2)+200, HAUTEUR/2, MLV_COLOR_BLACK);
  MLV_draw_line(LARGEUR/2, (HAUTEUR/2)-200, LARGEUR/2, (HAUTEUR/2)+200, MLV_COLOR_BLACK);
  MLV_draw_rectangle((LARGEUR/2)-200, (HAUTEUR/2)-200, 400, 400, MLV_COLOR_BLACK);

  /* Valeur de K */
  MLV_draw_text_box(
    LARGEUR/2,
    HAUTEUR/4-30,
    200,
    30,
    "Valeur de K : ",
    1,
    MLV_COLOR_BLACK,
    MLV_COLOR_BLACK,
    MLV_COLOR_WHITE,
    MLV_TEXT_CENTER,
    MLV_HORIZONTAL_LEFT,
    MLV_VERTICAL_CENTER
  );

  MLV_draw_text(
    LARGEUR/2+95,
    HAUTEUR/4-22,
    kstr,
    MLV_COLOR_BLACK
  );

  /* Valeur de C */
  MLV_draw_text_box(
    LARGEUR/2+205,
    HAUTEUR/2-140,
    200,
    30,
    "Valeur de C : ",
    1,
    MLV_COLOR_BLACK,
    MLV_COLOR_BLACK,
    MLV_COLOR_WHITE,
    MLV_TEXT_CENTER,
    MLV_HORIZONTAL_LEFT,
    MLV_VERTICAL_CENTER
  );

  MLV_draw_text(
    LARGEUR/2+300,
    HAUTEUR/2-132,
    cstr,
    MLV_COLOR_BLACK
  );

  /* bouton suppression/annulation */

  if (doit_suppr==0){
    MLV_draw_text_box(
      LARGEUR/2+205,
      HAUTEUR/2-200,
      200,
      50,
      "Annulation dernier ajout",
      1,
      MLV_COLOR_BLACK,
      MLV_COLOR_WHITE,
      MLV_COLOR_RED,
      MLV_TEXT_CENTER,
      MLV_HORIZONTAL_CENTER,
      MLV_VERTICAL_CENTER
    );
  }
  else {
    MLV_draw_text_box(
      LARGEUR/2+205,
      HAUTEUR/2-200,
      200,
      50,
      "Annulation dernier ajout",
      1,
      MLV_COLOR_BLACK,
      MLV_COLOR_BLACK,
      MLV_COLOR_WHITE,
      MLV_TEXT_CENTER,
      MLV_HORIZONTAL_CENTER,
      MLV_VERTICAL_CENTER
    );
  }

  /* zone options mode */

  if (mode==0){ /* Mode creation */
    /* zone d'ajout */

    MLV_draw_text_box
    (
     LARGEUR/3+100,
     HAUTEUR/5,
     150,
     25,
     "Mode Creation",
     1,
     MLV_COLOR_BLACK,
     MLV_COLOR_BLACK,
     MLV_COLOR_WHITE,
     MLV_TEXT_CENTER,
     MLV_HORIZONTAL_CENTER,
     MLV_VERTICAL_CENTER
     );

    MLV_draw_text_box
    (
     LARGEUR/3+100,
     HAUTEUR/5+30,
     150,
     25,
     "Mode KPPV",
     1,
     MLV_COLOR_BLACK,
     MLV_COLOR_WHITE,
     MLV_COLOR_RED,
     MLV_TEXT_CENTER,
     MLV_HORIZONTAL_CENTER,
     MLV_VERTICAL_CENTER
    );
  }
  else {
    MLV_draw_text_box
    (
     LARGEUR/3+100,
     HAUTEUR/5,
     150,
     25,
     "Mode Creation",
     1,
     MLV_COLOR_BLACK,
     MLV_COLOR_WHITE,
     MLV_COLOR_RED,
     MLV_TEXT_CENTER,
     MLV_HORIZONTAL_CENTER,
     MLV_VERTICAL_CENTER
     );

    MLV_draw_text_box
    (
     LARGEUR/3+100,
     HAUTEUR/5+30,
     150,
     25,
     "Mode KPPV",
     1,
     MLV_COLOR_BLACK,
     MLV_COLOR_BLACK,
     MLV_COLOR_WHITE,
     MLV_TEXT_CENTER,
     MLV_HORIZONTAL_CENTER,
     MLV_VERTICAL_CENTER
    );
  }

  /* options d'affichage */
  MLV_draw_text_box(
    LARGEUR*3/4,
    HAUTEUR*2/5,
    300,
    150,
    "Options d'affichage",
    10,
    MLV_COLOR_BLACK,
    MLV_COLOR_WHITE,
    MLV_COLOR_RED,
    MLV_TEXT_CENTER,
    MLV_HORIZONTAL_CENTER,
    MLV_VERTICAL_TOP
  );

  dessiner_checkbox(
    LARGEUR*3/4+5,
    HAUTEUR*2/5+30,
    MLV_COLOR_BLACK,
    "Voisinage"
  );

  dessiner_checkbox(
    LARGEUR*3/4+5,
    HAUTEUR*2/5+60,
    MLV_COLOR_BLACK,
    "Avec prise de décision"
  );

  dessiner_checkbox(
    LARGEUR*3/4+5,
    HAUTEUR*2/5+90,
    MLV_COLOR_BLACK,
    "Afficher zones"
  );

  /* chargement fichier de donn�es en mode cr�ation */

  MLV_draw_text_box
    (
     LARGEUR*3/4,
     HAUTEUR*4/5,
     300,
     60,
     "Chargement de donnees\nUniquement en mode Creation",
     10,
     MLV_COLOR_BLACK,
     MLV_COLOR_WHITE,
     MLV_COLOR_RED,
     MLV_TEXT_CENTER,
     MLV_HORIZONTAL_CENTER,
     MLV_VERTICAL_CENTER
     );


  /* zone de sauvegarde */

  MLV_draw_text_box
    (
     LARGEUR*3/4,
     HAUTEUR*4/5 + 70,
     300,
     30,
     "Sauvegarde des donnees",
     10,
     MLV_COLOR_BLACK,
     MLV_COLOR_WHITE,
     MLV_COLOR_RED,
     MLV_TEXT_CENTER,
     MLV_HORIZONTAL_CENTER,
     MLV_VERTICAL_CENTER
     );


  /* reinitialiser fenetre */

  MLV_draw_text_box(
    LARGEUR-175,
    0,
    175,
    30,
    "Réinitialisation fenêtre",
    10,
    MLV_COLOR_BLACK,
    MLV_COLOR_WHITE,
    MLV_COLOR_RED,
    MLV_TEXT_CENTER,
    MLV_HORIZONTAL_CENTER,
    MLV_VERTICAL_CENTER
  );

  if (avec_pdd==1){
    checked(LARGEUR*3/4+6,HAUTEUR*2/5+61,MLV_COLOR_BLACK);
  }
  else {
    checked(LARGEUR*3/4+6,HAUTEUR*2/5+61,MLV_COLOR_RED);
  }

  if (dessin==1){
    checked(LARGEUR*3/4+6,HAUTEUR*2/5+31,MLV_COLOR_BLACK);
  }
  else {
    checked(LARGEUR*3/4+6,HAUTEUR*2/5+31,MLV_COLOR_RED);
  }

  if (aff_zone==1){
    checked(LARGEUR*3/4+6,HAUTEUR*2/5+91,MLV_COLOR_BLACK);
  }
  else {
    checked(LARGEUR*3/4+6,HAUTEUR*2/5+91,MLV_COLOR_RED);
  }

  MLV_update_window();

}

int estNombre(char *s){
  int i;
  for (i=0 ; s[i]!='\0' ; i++){
    if (s[i]<'0' || s[i]>'9'){
      return 0;
    }
  }
  return 1;
}

int traitement_input_int(tpoints tp, int x, int y, char *txt){
  char *input;
  int nb;
  MLV_wait_input_box(x-30,y,x+30,y+30,MLV_COLOR_BLACK,MLV_COLOR_BLACK,MLV_COLOR_WHITE,"Entrez la valeur : ",&input);
  while (!estNombre(input)){
    MLV_wait_input_box(x-30,y,x+30,y+30,MLV_COLOR_BLACK,MLV_COLOR_BLACK,MLV_COLOR_WHITE,"Entrez la valeur (valeur > 0) : ",&input);
  }
  nb = atoi(input);
  libere_mem(&input);
  if (nb>0){
    if (strcmp(txt,"C")==0){
      if (nb>tp.classemax){
        return tp.classemax;
      }
      else {
        return nb;
      }
    }
    if (strcmp(txt,"K")==0){
      return nb;
    }
  }
  return 1;
}

void convert_double_to_fenetre(double x, double y, int * fen_x, int * fen_y){
  *fen_x = LARGEUR/2 + x*200;
  *fen_y = HAUTEUR/2 + y*200;
}

void convert_fenetre_to_double(int x, int y, double * tab_x, double * tab_y){
  *tab_x = (x - LARGEUR/2.0)/200.0;
  *tab_y = (y - HAUTEUR/2.0)/200.0;
}

void draw_point(int cl, int x, int y){
  MLV_draw_filled_circle(x,y,4,MLV_rgba(255-cl%255,(cl*100)%255,255/cl,MLV_ALPHA_OPAQUE));
  MLV_update_window();
}

void draw_tab(tpoints tp){
  int taille = tp.taille;
  double x,y;
  int fen_x,fen_y;
  int i;
  for (i=0; i<taille; i++){
    x = tp.tp[i].x;
    y = tp.tp[i].y;
    convert_double_to_fenetre(x,y,&fen_x,&fen_y);
    draw_point(tp.tp[i].classe,fen_x,fen_y);
  }
}

void supp_derniere_saisie_ecran(tpoints *tp){
  supprimer_derniere_saisie(tp);
  MLV_clear_window(MLV_COLOR_WHITE);
  dessiner_zone();
  draw_tab(*tp);
}

void ajout_coord(tpoints *tp, int x, int y){
  double tp_x,tp_y;
  draw_point(c,x,y);
  convert_fenetre_to_double(x,y,&tp_x,&tp_y);
  ajout_point(tp, c, tp_x, tp_y);
}

void vider_zone(tpoints *tp){
  reinitialiser_tab(tp);
  fichier_charge = 0;
  aff_zone = 0;
  MLV_clear_window(MLV_COLOR_WHITE);
  dessiner_zone();
}

/* ---------------- Mode KPPV -------------- */

void affiche_tabkppv(point * tabkppv){
  int i;
  double x,y;
  int fen_x,fen_y;
  for (i=0 ; i<k ; i++){
    x = tabkppv[i].x;
    y = tabkppv[i].y;
    convert_double_to_fenetre(x,y,&fen_x,&fen_y);
    draw_point(128,fen_x,fen_y);
  }
}

void supp_point_kppv(tpoints tp){
  MLV_clear_window(MLV_COLOR_WHITE);
  doit_suppr = 0;
  dessiner_zone();
  draw_tab(tp);
  MLV_update_window();
}

void mode_kppv(tpoints tp, int x, int y){
  if (k<=tp.taille){
    int classe_maj;
    double tp_x,tp_y,rayon;
    point * kppv = NULL;
    point p,pcercle;
    arbre_kd a = chargement_arbre_kd_tp(tp);
    p.classe = 0;
    convert_fenetre_to_double(x,y,&tp_x,&tp_y);
    p.x = tp_x;
    p.y = tp_y;
    kppv = rechercher(a,p,k);
    detruire_arbre(a);
    MLV_draw_filled_circle(x,y,5,MLV_COLOR_BLACK);
    doit_suppr = 1;
    dessiner_zone();
    affiche_tabkppv(kppv);
    if (avec_pdd){
      classe_maj = classe_majoritaire(kppv, k, tp.classemax);
      draw_point(classe_maj,x,y);
    }
    if (dessin){
      pcercle = max_liste_points(kppv,p,k);
      rayon = distance_euclidienne(tp_x,tp_y,pcercle.x,pcercle.y);
      MLV_draw_circle(x,y,(int)(rayon*200),MLV_COLOR_BLACK);
      MLV_actualise_window();
    }
  }
}

/* ---------------------- DESSIN DE ZONE ------------------------ */

void zones_bis(arbre_kd a, int axe, int supgx, int supgy, int infdx, int infdy){
  int x,y;
  if (!est_feuille(a)){
    convert_double_to_fenetre(a->noeud.x,a->noeud.y,&x,&y);
    if (!axe){
      MLV_draw_line(x,supgy,x,infdy,MLV_COLOR_BLACK);
      if (!est_vide_arbre_kd(a->fd))
        zones_bis(a->fd,1-axe,supgx,supgy,x,infdy);
      if (!est_vide_arbre_kd(a->fg))
        zones_bis(a->fg,1-axe,x,supgy,infdx,infdy);
    }
    else {
      MLV_draw_line(supgx,y,infdx,y,MLV_COLOR_BLACK);
      if (!est_vide_arbre_kd(a->fd))
        zones_bis(a->fd,1-axe,supgx,supgy,infdx,y);
      if (!est_vide_arbre_kd(a->fg))
        zones_bis(a->fg,1-axe,supgx,y,infdx,infdy);
    }
  }
}

void zones(tpoints tp){
  arbre_kd a = chargement_arbre_kd_tp(tp);
  int supgx = LARGEUR/2-200;
  int supgy = HAUTEUR/2-200;
  int infdx = LARGEUR/2+200;
  int infdy = HAUTEUR/2+200;
  zones_bis(a,0,supgx,supgy,infdx,infdy);
  detruire_arbre(a);
  MLV_update_window();
}

void gestion_click(tpoints *tp){
  int x,y;
  char *nomfic;
  MLV_wait_mouse(&x,&y);

  if (x>=LARGEUR/2+205 && x<=LARGEUR/2+405 && y>=HAUTEUR/2-140 && y<=HAUTEUR/2-110){
    c = traitement_input_int(*tp,x,y,"C");
    MLV_clear_window(MLV_COLOR_WHITE);
    draw_tab(*tp);
    sprintf(cstr,"%d",c);
    dessiner_zone();
  }

  if (x>=LARGEUR/2 && x<=LARGEUR/2+200 && y>=HAUTEUR/4-30 && y<=HAUTEUR/4){
    k = traitement_input_int(*tp,x,y,"K");
    MLV_clear_window(MLV_COLOR_WHITE);
    draw_tab(*tp);
    sprintf(kstr,"%d",k);
    dessiner_zone();
  }
  /* zone reinitialiser */

  if (x>=LARGEUR-175 && x<=LARGEUR && y>=0 && y<=30){
    vider_zone(tp);
  }

  /* checkbox zones */

  if (x>=LARGEUR*3/4+5 && x<=LARGEUR*3/4+15 && y>=HAUTEUR*2/5+90 && y<=HAUTEUR*2/5+100){
    if (aff_zone==0){
      checked(LARGEUR*3/4+6,HAUTEUR*2/5+91,MLV_COLOR_BLACK);
      aff_zone = 1;
      zones(*tp);
    }
    else {
      checked(LARGEUR*3/4+6,HAUTEUR*2/5+91,MLV_COLOR_RED);
      aff_zone = 0;
      MLV_clear_window(MLV_COLOR_WHITE);
      dessiner_zone();
      draw_tab(*tp);
    }
  }

  /*zone choix du mode*/

  /* creation */

  if((x >= LARGEUR/3+100 && x<= LARGEUR/3+250) && (y >= HAUTEUR/5 && y <= HAUTEUR/5+25)){
    mode = 0;
  }
  if((x >= LARGEUR/3+100 && x<= LARGEUR/3+250) && (y >= HAUTEUR/5+30 && y <= HAUTEUR/5+55)){
    mode = 1;
  }
  if (mode==0){ /* Mode creation */
    /* zone d'ajout */

    MLV_draw_text_box
    (
     LARGEUR/3+100,
     HAUTEUR/5,
     150,
     25,
     "Mode Creation",
     1,
     MLV_COLOR_BLACK,
     MLV_COLOR_BLACK,
     MLV_COLOR_WHITE,
     MLV_TEXT_CENTER,
     MLV_HORIZONTAL_CENTER,
     MLV_VERTICAL_CENTER
     );

    MLV_draw_text_box
    (
     LARGEUR/3+100,
     HAUTEUR/5+30,
     150,
     25,
     "Mode KPPV",
     1,
     MLV_COLOR_BLACK,
     MLV_COLOR_WHITE,
     MLV_COLOR_RED,
     MLV_TEXT_CENTER,
     MLV_HORIZONTAL_CENTER,
     MLV_VERTICAL_CENTER
     );

    MLV_actualise_window();

    if(k>0 && c>0 && (x >= LARGEUR/2-200 && x <= LARGEUR/2+200) && (y >= HAUTEUR/2-200 && y <= HAUTEUR/2+200))
      ajout_coord(tp, x, y);

    /* zone annulation */

    if(x >= LARGEUR/2+205 && x<= LARGEUR/2+405 && y >= HAUTEUR/2-200 && y<=HAUTEUR/2-150)
      supp_derniere_saisie_ecran(tp);

    /* zone sauvegarde */
    if((x >= LARGEUR*3/4 && x<= LARGEUR*3/4+300) && (y>= HAUTEUR*4/5+70 && y <= HAUTEUR*4/5+100)){
      MLV_wait_input_box(LARGEUR/2-20,HAUTEUR/2-20,LARGEUR/2+20,HAUTEUR/2+20,MLV_COLOR_BLACK,MLV_COLOR_BLACK,MLV_COLOR_WHITE,"Entrez le chemin du fichier a sauvegarder : ",&nomfic);
      sauvegarde_fichier(nomfic, *tp);
      libere_mem(&nomfic);
    }

    /* zone de chargement */

    if((x >= LARGEUR*3/4 && x <= LARGEUR*3/4+300) && (y >= HAUTEUR*4/5 && y <= HAUTEUR*4/5+60) && fichier_charge==0){
      MLV_wait_input_box(LARGEUR/2-20,HAUTEUR/2-20,LARGEUR/2+20,HAUTEUR/2+20,MLV_COLOR_BLACK,MLV_COLOR_BLACK,MLV_COLOR_WHITE,"Entrez le chemin du fichier a charger : ",&nomfic);
      *tp = chargement_fichier(nomfic);
      libere_mem(&nomfic);
      fichier_charge = 1;
      draw_tab(*tp);
    }
  }
  if (mode==1){ /* Mode KPPV */

    MLV_draw_text_box
    (
     LARGEUR/3+100,
     HAUTEUR/5+30,
     150,
     25,
     "Mode KPPV",
     1,
     MLV_COLOR_BLACK,
     MLV_COLOR_BLACK,
     MLV_COLOR_WHITE,
     MLV_TEXT_CENTER,
     MLV_HORIZONTAL_CENTER,
     MLV_VERTICAL_CENTER
     );

    MLV_draw_text_box
    (
     LARGEUR/3+100,
     HAUTEUR/5,
     150,
     25,
     "Mode Creation",
     1,
     MLV_COLOR_BLACK,
     MLV_COLOR_WHITE,
     MLV_COLOR_RED,
     MLV_TEXT_CENTER,
     MLV_HORIZONTAL_CENTER,
     MLV_VERTICAL_CENTER
     );

    MLV_actualise_window();

    /* zone affichage */
    if (x>=LARGEUR*3/4+5 && x<=LARGEUR*3/4+15 && y>=HAUTEUR*2/5+30 && y<=HAUTEUR*2/5+40){
      if (dessin==0){
        checked(LARGEUR*3/4+6,HAUTEUR*2/5+31,MLV_COLOR_BLACK);
        dessin = 1;
      }
      else {
        checked(LARGEUR*3/4+6,HAUTEUR*2/5+31,MLV_COLOR_RED);
        dessin = 0;
      }
    }

    if (x>=LARGEUR*3/4+5 && x<=LARGEUR*3/4+15 && y>=HAUTEUR*2/5+60 && y<=HAUTEUR*2/5+70){
      if (avec_pdd==0){
        checked(LARGEUR*3/4+6,HAUTEUR*2/5+61,MLV_COLOR_BLACK);
        avec_pdd = 1;
      }
      else {
        checked(LARGEUR*3/4+6,HAUTEUR*2/5+61,MLV_COLOR_RED);
        avec_pdd = 0;
      }
    }

    /* zone d'ajout */

    if((x >= LARGEUR/2-200 && x <= LARGEUR/2+200) && (y >= HAUTEUR/2-200 && y <= HAUTEUR/2+200) && doit_suppr==0){
      mode_kppv(*tp,x,y);
    }

    /* zone annulation */

    if(x >= LARGEUR/2+205 && x<=LARGEUR/2+405 && y>=HAUTEUR/2-200 && y<=HAUTEUR/2-150 && doit_suppr){
      supp_point_kppv(*tp);
    }
    MLV_update_window();
  }
}

int main(){
  tpoints tp;
  char *classemax_str;
  int classemax;
  char* f = "Module d'affichage du traitement des KPPV";

  mode = 0;
  fichier_charge = 0;
  doit_suppr = 0;
  avec_pdd = 0;
  dessin = 0;
  initialiser_mlv(f);
  MLV_wait_input_box(
    LARGEUR/3,
    HAUTEUR/4,
    LARGEUR/4+100,
    HAUTEUR/4+10,
    MLV_COLOR_BLACK,
    MLV_COLOR_BLACK,
    MLV_COLOR_WHITE,
    "Entrez la classe maximum que vous voulez traiter : ",
    &classemax_str
  );

  classemax = atoi(classemax_str);
  cstr = strdup("1");
  kstr = strdup("1");
  libere_mem(&classemax_str);
  if (classemax<1){
    erreur("La classe maximum doit etre >= a 1\n");
  }

  tp = init_tpoints(classemax);
  dessiner_zone();

  while (1){
    gestion_click(&tp);
  }

  libere_mem(&kstr);
  libere_mem(&cstr);


  MLV_wait_seconds(1000);

  MLV_free_window();
  return EXIT_SUCCESS;
}
