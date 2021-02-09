#include <stdlib.h>
#include <stdio.h>
#include <math.h>


const int chemin[8]={-11, -10, -9, -1, 1, 9, 10, 11};
const int table=100;

const int vide=0;   
const int noir=1;
const int blanc=2;
const int possi=3;

const int gagne=30;
const int perdre= -30;



long int tab;


int joueur (int, int *);
int aleatoire(int, int *);
int optimise(int, int *); 


void * jeu[9][4] = {
   {"joueur", "joueur", joueur},
   {"aleatoire", "contre ordinateur aleatoire", aleatoire},
   {"optimise", "contre ordinateur optimise", optimise},

   {NULL, NULL, NULL}
 };


typedef int (* fpc) (int, int *);



char pointp (int p) {
  static char pn[5] = ".BW*";
  return(pn[p]);
}



int adv (int combatant) {
  switch (combatant) {
  case 1: return 2; 
  case 2: return 1;
  default: printf("joueur invalide\n"); return 0;
  }
}



int * enregistrer (int * board) {
  int i, * nvtable;
  nvtable = (int *)malloc(table * sizeof(int));
  for (i=0; i<table; i++) nvtable[i] = board[i];
  return nvtable;
}



int * debut (void) {
  int i, * board;
  board = (int *)malloc(table * sizeof(int));
  for (i = 0; i<=9; i++) board[i]=possi;
  for (i = 10; i<=89; i++) {
     if (i%10 >= 1 && i%10 <= 8) board[i]=vide; else board[i]=possi;
  }
  for (i = 90; i<=99; i++) board[i]=possi;
  board[44]=blanc; board[45]=noir; board[54]=noir; board[55]=blanc;
  return board;
}



int totale (int combatant, int * board) {
  int i, t;
  t=0;
  for (i=1; i<=88; i++)
    if (board[i] == combatant) t++;
  return t;
}



void afficher (int * board) {
  int row, col;
  printf("    1 2 3 4 5 6 7 8 \n");
  for (row=1; row<=8; row++) {
    printf("%d  ", 10*row);
    for (col=1; col<=8; col++)
      printf("%c ", pointp(board[col + (10 * row)]));
    printf("\n");
  }    
}



int possim (int mouvement) {
  if ((mouvement >= 11) && (mouvement <= 88) && (mouvement%10 >= 1) && (mouvement%10 <= 8))
     return 1;
  else return 0;
}



int entrepiece(int square, int combatant, int * board, int dir) {
  while (board[square] == adv(combatant)) square = square + dir;
  if (board[square] == combatant) return square;
  else return 0;
}


int permuter (int mouvement, int combatant, int * board, int dir) {
  int c;
  c = mouvement + dir;
  if (board[c] == adv(combatant))
     return entrepiece(c+dir, combatant, board, dir);
  else return 0;
}



int ppossible (int mouvement, int combatant, int * board) {
  int i;
  if (!possim(mouvement)) return 0;
  if (board[mouvement]==vide) {
    i=0;
    while (i<=7 && !permuter(mouvement, combatant, board, chemin[i])) i++;
    if (i==8) return 0; else return 1;
  }   
  else return 0;
}



void fpermuter (int mouvement, int combatant, int * board, int dir) {
  int bracketer, c;
  bracketer = permuter(mouvement, combatant, board, dir);
  if (bracketer) {
     c = mouvement + dir;
     do {
         board[c] = combatant;
         c = c + dir;
        } while (c != bracketer);
  }
}


void deplacer (int mouvement, int combatant, int * board) {
  int i;
  board[mouvement] = combatant;
  for (i=0; i<=7; i++) fpermuter(mouvement, combatant, board, chemin[i]);
}


int deplacementpossible (int combatant, int * board) {
  int mouvement;
  mouvement = 11;
  while (mouvement <= 88 && !ppossible(mouvement, combatant, board)) mouvement++;
  if (mouvement <= 88) return 1; else return 0;
}



int suivantt (int * board, int ancombatant, int pf) {
  int opp;
  opp = adv(ancombatant);
  if (deplacementpossible(opp, board)) return opp;
  if (deplacementpossible(ancombatant, board)) {
    if (pf) printf("%c aucun mouvement possible! tourne est donnée à l'adverssaire\n", pointp(opp));
    return ancombatant;
  }
  return 0;
}



int * mouvementpossible (int combatant, int * board) {
  int mouvement, i, * mouvements;
  mouvements = (int *)malloc(65 * sizeof(int));
  mouvements[0] = 0;
  i = 0;
  for (mouvement=11; mouvement<=88; mouvement++) 
    if (ppossible(mouvement, combatant, board)) {
      i++;
      mouvements[i]=mouvement;
    }
  mouvements[0]=i;
  return mouvements;
}



int joueur (int combatant, int * board) {
  int mouvement;
  printf("%c entrer le mouvement voulu? :", pointp(combatant)); scanf("%d", &mouvement);
  return mouvement;
}



int aleatoire(int combatant, int * board) {
  int r, * mouvements;
  mouvements = mouvementpossible(combatant, board);
  r = mouvements[(rand() % mouvements[0]) + 1];
  free(mouvements);
  return(r);
}



int btweentwo (int combatant, int * board) {
  int i, ot, pt, p; 
  pt=0; ot = 0;                
  p = adv(combatant); 
  for (i=1; i<=88; i++) {
    if (board[i]==combatant) pt++;
    if (board[i]==p) ot++;
  }
  return (pt-ot);
}


int minmax (int combatant, int * board, int ply, int (* evalfn) (int, int *)) {
  int i, max, ntm, nvs, meuillermvt, * mouvements, * nvtable;
  int meuilleurch (int, int *, int, int (*) (int, int *)); 
  int mauvch (int, int *, int, int (*) (int, int *)); 
  mouvements = mouvementpossible(combatant, board);
  max = perdre - 1; 
  for (i=1; i <= mouvements[0]; i++) {
    nvtable = enregistrer(board); tab = tab + 1;
    deplacer(mouvements[i], combatant, nvtable);
    ntm = suivantt(nvtable, combatant, 0);
    if (ntm == 0) {  
         nvs = btweentwo(combatant, nvtable);
         if (nvs > 0) nvs = gagne;
         if (nvs < 0) nvs = perdre; 
    }
    if (ntm == combatant)   
       nvs = meuilleurch(combatant, nvtable, ply-1, evalfn);
    if (ntm == adv(combatant))
       nvs = mauvch(combatant, nvtable, ply-1, evalfn);
    if (nvs > max) {
        max = nvs;
        meuillermvt = mouvements[i]; 
    }
    free(nvtable);
  }
  free(mouvements);
  return(meuillermvt);
}


int meuilleurch (int combatant, int * board, int ply, 
               int (* evalfn) (int, int *)) {
  int i, max, ntm, nvs, * mouvements, * nvtable;
  int mauvch (int, int *, int, int (*) (int, int *)); 
  if (ply == 0) return((* evalfn) (combatant, board));
  mouvements = mouvementpossible(combatant, board);
  max = perdre - 1;
  for (i=1; i <= mouvements[0]; i++) {
    nvtable = enregistrer(board); tab = tab + 1;
    deplacer(mouvements[i], combatant, nvtable);
    ntm = suivantt(nvtable, combatant, 0);
    if (ntm == 0) {
         nvs = btweentwo(combatant, nvtable);
         if (nvs > 0) nvs = gagne;
         if (nvs < 0) nvs = perdre;
    }
    if (ntm == combatant) 
       nvs = meuilleurch(combatant, nvtable, ply-1, evalfn);
    if (ntm == adv(combatant))
       nvs = mauvch(combatant, nvtable, ply-1, evalfn);
    if (nvs > max) max = nvs;
    free(nvtable);
  }
  free(mouvements);
  return(max);
}



int mauvch (int combatant, int * board, int ply, 
               int (* evalfn) (int, int *)) {
  int i, min, ntm, nvs, * mouvements, * nvtable;
  if (ply == 0) return((* evalfn) (combatant, board));
  mouvements = mouvementpossible(adv(combatant), board);
  min = gagne+1;
  for (i=1; i <= mouvements[0]; i++) {
    nvtable = enregistrer(board); tab = tab + 1;
    deplacer(mouvements[i], adv(combatant), nvtable);
    ntm = suivantt(nvtable, adv(combatant), 0);
    if (ntm == 0) {
         nvs = btweentwo(combatant, nvtable);
         if (nvs > 0) nvs = gagne;
         if (nvs < 0) nvs = perdre;
    }
    if (ntm == combatant) 
       nvs = meuilleurch(combatant, nvtable, ply-1, evalfn);
    if (ntm == adv(combatant))
       nvs = mauvch(combatant, nvtable, ply-1, evalfn);
    if (nvs < min) min = nvs;
    free(nvtable);
  }
  free(mouvements);
  return(min);
}


int optimise(int combatant, int * board) { 
  return(minmax(combatant, board, 1, btweentwo));  
}

void avoirmvt (int (* plans) (int, int *), int combatant, int * board, 
              int pf) {
  int mouvement;
  if (pf) afficher(board);
  mouvement = (* plans)(combatant, board);
  if (ppossible(mouvement, combatant, board)) {
     if (pf) printf("%c déplacée vers %d\n", pointp(combatant), mouvement);
     deplacer(mouvement, combatant, board);
  }
  else {
     printf("mouvement impossible %d\n", mouvement);
     avoirmvt(plans, combatant, board, pf);
  }
}

void game (int (* blplans) (int, int *), 
              int (* whplans) (int, int *), int pf) {
  int * board;
  int combatant;
  board = debut();
  combatant = noir;
  do {
    if (combatant == noir) avoirmvt(blplans, noir, board, pf);
    else avoirmvt(whplans, blanc, board, pf);
    combatant = suivantt(board, combatant, pf);
  }
  while (combatant != 0);
  if (pf) {
     printf("Partie finie! resultat:\n");
     afficher(board);
  }
}


int * aleatoireboard (void) {
  int combatant, enccom, i, * board;
  board = debut();
  combatant = noir;
  i=1;
  do {
    if (combatant == noir) avoirmvt(aleatoire, noir, board, 0);
    else avoirmvt(aleatoire, blanc, board, 0);
    enccom = combatant;
    combatant = suivantt(board, combatant, 0);
    if (enccom == combatant) {
       free(board);
       return(aleatoireboard());
    }
    i++;
  }
  while (combatant != 0 && i<=8);
  if (combatant==0) {
     free(board);
     return(aleatoireboard());
  }
  else return(board);
}


void rr (void) {
  int i, j, k, tdiff, combatant, igagnes, jgagnes, * g1, * g2;
  long int itab, jtab;

  i=1;
  while (jeu[i+1][0] != NULL) {
    j = i + 1;
    while (jeu[j][0] != NULL) { 
      igagnes = 0; jgagnes = 0; itab = 0; jtab = 0;
      for (k=1; k<=5; k++) {
        g1 = aleatoireboard();
        g2 = enregistrer(g1);
        combatant = noir;
        do {
          if (combatant == noir) {
             tab = 0;
             avoirmvt((fpc)jeu[i][2], noir, g1, 0);
             itab = itab + tab;
      }
          else {
             tab = 0;
             avoirmvt((fpc)jeu[j][2], blanc, g1, 0);
             jtab = jtab + tab;
      }
          combatant = suivantt(g1, combatant, 0);
        }
        while (combatant != 0);

        tdiff = btweentwo(noir, g1);
        if (tdiff>0) igagnes++;
        if (tdiff<0) jgagnes++;
        free(g1);

        combatant = noir;
        do {
          if (combatant == noir) {
             tab = 0;
             avoirmvt((fpc)jeu[j][2], noir, g2, 0);
             jtab = jtab + tab;
      }
          else {
             tab = 0;
             avoirmvt((fpc)jeu[i][2], blanc, g2, 0);
             itab = itab + tab;
          }
          combatant = suivantt(g2, combatant, 0);
        }
        while (combatant != 0);       
        tdiff = btweentwo(blanc, g2);
        if (tdiff>0) igagnes++;
        if (tdiff<0) jgagnes++;
        free(g2);
      }
      printf("%s gagnes=%d tab=%ld || %s gagnes=%d tab=%ld\n",
              jeu[i][0], igagnes, itab, 
              jeu[j][0], jgagnes, jtab);

      j++;
    }     
    i++;
  }

}          

void jeux (void) {
 int i, p1, p2, pf;
 int (* fr1)(int, int *);  int (* fr2)(int, int *);
 char * jj;

  i=0;
  printf("combatant 1: "); 
  while (jeu[i][0] != NULL) {
     jj=jeu[i][1]; printf("%d (%s)\n", i, jj);
     printf("          ");   
     i++;
  }
  printf(": ");
  scanf("%d", &p1);

  i=0;
  printf("combatant 2: ");
  while (jeu[i][0] != NULL) {
     jj=jeu[i][1]; printf("%d (%s)\n", i, jj);
     printf("          ");   
     i++;
  }
  printf(": ");
  scanf("%d", &p2);

  fr1 = jeu[p1][2]; fr2 = jeu[p2][2];
  if (fr1 == joueur || fr2 == joueur) pf = 1;
  else {
    printf("       \n");
    printf("Aucun joueur n'est détecté ");
    scanf("%d", &pf);
  }

  game(fr1, fr2, pf);
}



int main (void) {
  
       jeux();
       fflush(stdin);
       printf("vous voulez recommencer? (y)oui ou (n)non? "); 
     if (getchar() == 'y'){
                jeux();
                fflush(stdin);

}}
    


