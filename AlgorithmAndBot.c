#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>

int*chercher(FILE*Fichier);  //cherche si le joueur existe dans le fichier
void*creation_joueurr();    //cree les nouveaux joueurs 
int n,n2; // on va utiliser cette variable pour savoir si l'utilisateur veut que la partie soit enregistrée ou pas

typedef struct joueurr{
char nom[20];
char score[20];
struct joueurr*suivant;}joueurr;
/*#####livrable1#######*/

int*chercher(FILE*Fichier){
    char motFr[30], motR[30];
    Fichier = fopen("projet_c.txt", "r");
    if (!Fichier)
         printf("\aERREUR: Impossible d'ouvrir le fichier\n");
    printf("\tentrer votre nom slv\t");
    scanf("%s",&motR);
    while(fgets(motFr,30,Fichier) != NULL)
    {if (strstr(motFr,motR) != NULL){
          printf("||||joueur deja existe bienvenue autre fois||||\n");    //deja existe 
          return 1;}
    }
    fclose(Fichier);
    printf("|||bienvenue nouveau joueur entrer vos infos(nom) pour l'enregistrement|||\n ");    
    return 0;}

void*creation_joueurr(){
FILE*fichier;
fichier=fopen("projet_c","w+"); //la recherche premierement
//infos
char nom[20];
int score;
char mot_de_passe;
if((chercher(fichier))==0){
scanf("%s",nom);
score=0;
fprintf(fichier,"%s\n%d\n ",&nom,&score);}
/*****le deuxieme***/
if(chercher(fichier)==0){  //nouveau joueur
scanf("%s",nom);
score=0;                    //score nul
fprintf(fichier,"%s\n%d\n ",&nom,&score);}}


void*affichage_scores(joueurr*list){
//tri de la liste chainee(tri a bulles)
    joueurr*p;
    int d=1;
    char permu[20];
    while(d==1)
    {d=0;
    for(p=list;p!=NULL;p=p->suivant)
    {if((p->score)>((p->suivant)->score))
        {strcpy(permu,(p->score));
         strcpy((p->score),((p->suivant)->score));
         strcpy(((p->suivant)->score),permu);
        d=1;
        }}}
/*affichages des scores***/    //la pracours de liste triee
if (list==NULL){
printf(" Liste vide !!\n"); return 0 ;}
else { joueurr*temp=list;
        while(temp!=NULL){
        printf("%s",temp->nom);
        printf("%s",temp->score);}}}


const int chemin[8]= {-11, -10, -9, -1, 1, 9, 10, 11};
const int table=100;
const int vide=0;
const int noir=1;
const int blanc=2;
const int possi=3;
const int gagne=30;
const int perdre= -30;
typedef struct securite{
char nom[20];
char mot_de_passe[16];
struct securite*suivant;}securite;


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
    case 1:
        return 2;
    case 2:
        return 1;
    default:
        printf("joueur invalide\n");
        return 0;
    }
}



int * enregistrer (int * latabl) {
    int i, * nvtable;
    nvtable = (int *)malloc(table * sizeof(int));
    for (i=0; i<table; i++) nvtable[i] = latabl[i];
    return nvtable;
}



int * debut (void) {
    int i, * latabl;
    latabl = (int *)malloc(table * sizeof(int));
    for (i = 0; i<=9; i++) latabl[i]=possi;
    for (i = 10; i<=89; i++) {
        if (i%10 >= 1 && i%10 <= 8) latabl[i]=vide;
        else latabl[i]=possi;
    }
    for (i = 90; i<=99; i++) latabl[i]=possi;
    latabl[44]=blanc;
    latabl[45]=noir;
    latabl[54]=noir;
    latabl[55]=blanc;
    return latabl;
}



int totale (int combatant, int * latabl) {
    int i, t;
    t=0;
    for (i=1; i<=88; i++)
        if (latabl[i] == combatant) t++;
    return t;
}

void afficher (int * latabl) {
    int row, col;
    printf("    1 2 3 4 5 6 7 8 \n");
    for (row=1; row<=8; row++) {
        printf("%d  ", 10*row);
        for (col=1; col<=8; col++)
            printf("%c ", pointp(latabl[col + (10 * row)]));
        printf("\n");
    }
}



int possim (int mouvement) {
    if ((mouvement >= 11) && (mouvement <= 88) && (mouvement%10 >= 1) && (mouvement%10 <= 8))
        return 1;
    else return 0;
}



int entrepiece(int square, int combatant, int * latabl, int dir) {
    while (latabl[square] == adv(combatant)) square = square + dir;
    if (latabl[square] == combatant) return square;
    else return 0;
}


int permuter (int mouvement, int combatant, int * latabl, int dir) {
    int c;
    c = mouvement + dir;
    if (latabl[c] == adv(combatant))
        return entrepiece(c+dir, combatant, latabl, dir);
    else return 0;
}



int ppossible (int mouvement, int combatant, int * latabl) {
    int i;
    if (!possim(mouvement)) return 0;
    if (latabl[mouvement]==vide) {
        i=0;
        while (i<=7 && !permuter(mouvement, combatant, latabl, chemin[i])) i++;
        if (i==8) return 0;
        else return 1;
    }
    else return 0;
}



void fpermuter (int mouvement, int combatant, int * latabl, int dir) {
    int bracketer, c;
    bracketer = permuter(mouvement, combatant, latabl, dir);
    if (bracketer) {
        c = mouvement + dir;
        do {
            latabl[c] = combatant;
            c = c + dir;
        } while (c != bracketer);
    }
}


void deplacer (int mouvement, int combatant, int * latabl) {
    int i;
    latabl[mouvement] = combatant;
    for (i=0; i<=7; i++) fpermuter(mouvement, combatant, latabl, chemin[i]);
}


int deplacementpossible (int combatant, int * latabl) {
    int mouvement;
    mouvement = 11;
    while (mouvement <= 88 && !ppossible(mouvement, combatant, latabl)) mouvement++;
    if (mouvement <= 88) return 1;
    else return 0;
}



int suivantt (int * latabl, int ancombatant, int pf) {
    int opp;
    opp = adv(ancombatant);
    if (deplacementpossible(opp, latabl)) return opp;
    if (deplacementpossible(ancombatant, latabl)) {
        if (pf) printf("%c aucun mouvement possible! tourne est donnée à l'adverssaire\n", pointp(opp));
        return ancombatant;
    }
    return 0;
}



int * mouvementpossible (int combatant, int * latabl) {
    int mouvement, i, * mouvements;
    mouvements = (int *)malloc(65 * sizeof(int));
    mouvements[0] = 0;
    i = 0;
    for (mouvement=11; mouvement<=88; mouvement++)
        if (ppossible(mouvement, combatant, latabl)) {
            i++;
            mouvements[i]=mouvement;
        }
    mouvements[0]=i;
    return mouvements;
}



int joueur (int combatant, int * latabl) {
    int mouvement;
    printf("%c entrer le mouvement voulu? :", pointp(combatant));
    scanf("%d", &mouvement);
    return mouvement;
}



int aleatoire(int combatant, int * latabl) {
    int r, * mouvements;
    mouvements = mouvementpossible(combatant, latabl);
    r = mouvements[(rand() % mouvements[0]) + 1];
    free(mouvements);
    return(r);
}



int btweentwo (int combatant, int * latabl) {
    int i, ot, pt, p;
    pt=0;
    ot = 0;
    p = adv(combatant);
    for (i=1; i<=88; i++) {
        if (latabl[i] == combatant) pt++;
        if (latabl[i] == p) ot++;
    }
    return (pt-ot);
}


int alphabeta (int combatant, int * latabl, int ply, int (* vff) (int, int *)) {
    int meuilleurch (int, int *, int, int (*) (int, int *));
    int mauvch (int, int *, int, int (*) (int, int *));
    int i;
    int max;
    int ntm;
    int nvs;
    int meuillermvt;
    int * mouvements;
    int * nvtable;


    mouvements = mouvementpossible(combatant, latabl);
    max = perdre - 1;
    for (i=1; i <= mouvements[0]; i++) {
        nvtable = enregistrer(latabl);
        tab = tab + 1;
        deplacer(mouvements[i], combatant, nvtable);
        ntm = suivantt(nvtable, combatant, 0);
        if (ntm == 0) {
            nvs = btweentwo(combatant, nvtable);
            if (nvs > 0) nvs = gagne;
            if (nvs < 0) nvs = perdre;
        }
        if (ntm == combatant)
            nvs = meuilleurch(combatant, nvtable, ply-1, vff);
        if (ntm == adv(combatant))
            nvs = mauvch(combatant, nvtable, ply-1, vff);
        if (nvs > max) {
            max = nvs;
            meuillermvt = mouvements[i];
        }
        free(nvtable);
    }
    free(mouvements);
    return(meuillermvt);
}


int meuilleurch (int combatant, int * latabl, int ply,int (* vff) (int, int *)) 
{
    int i;
    int max;
    int ntm;
    int nvs;
    int * mouvements;
    int * nvtable;
    int mauvch (int, int *, int, int (*) (int, int *));
    if (ply == 0) return((* vff) (combatant, latabl));
    mouvements = mouvementpossible(combatant, latabl);
    max = perdre - 1;
    for (i=1; i <= mouvements[0]; i++) {
        nvtable = enregistrer(latabl);
        tab = tab + 1;
        deplacer(mouvements[i], combatant, nvtable);
        ntm = suivantt(nvtable, combatant, 0);
        if (ntm == 0) {
            nvs = btweentwo(combatant, nvtable);
            if (nvs > 0) nvs = gagne;
            if (nvs < 0) nvs = perdre;
        }
        if (ntm == combatant)
            nvs = meuilleurch(combatant, nvtable, ply-1, vff);
        if (ntm == adv(combatant))
            nvs = mauvch(combatant, nvtable, ply-1, vff);
        if (nvs > max) max = nvs;
        free(nvtable);
    }
    free(mouvements);
    return(max);
}



int mauvch (int combatant, int * latabl, int ply,int (* vff) (int, int *)) 
{
    int i;
     int min;
     int ntm;
     int nvs;
      int* mouvements;
      int* nvtable;
    if (ply == 0) return((* vff) (combatant, latabl));
    mouvements = mouvementpossible(adv(combatant), latabl);
    min = gagne+1;
    for (i=1; i <= mouvements[0]; i++) {
        nvtable = enregistrer(latabl);
        tab = tab + 1;
        deplacer(mouvements[i], adv(combatant), nvtable);
        ntm = suivantt(nvtable, adv(combatant), 0);
        if (ntm == 0) {
            nvs = btweentwo(combatant, nvtable);
            if (nvs > 0) nvs = gagne;
            if (nvs < 0) nvs = perdre;
        }
        if (ntm == combatant)
            nvs = meuilleurch(combatant, nvtable, ply-1, vff);
        if (ntm == adv(combatant))
            nvs = mauvch(combatant, nvtable, ply-1, vff);
        if (nvs < min) min = nvs;
        free(nvtable);
    }
    free(mouvements);
    return(min);
}


int optimise(int combatant, int * latabl) {
    return(alphabeta(combatant, latabl, 1, btweentwo));
}

void avoirmvt (int (* plans) (int, int *), int combatant, int * latabl,
               int pf) {
    int mouvement;
    if (pf) afficher(latabl);
    mouvement = (* plans)(combatant, latabl);
    if (ppossible(mouvement, combatant, latabl)) {
        if (pf) printf("%c déplacée vers %d\n", pointp(combatant), mouvement);
        deplacer(mouvement, combatant, latabl);
    }
    else {
        printf("mouvement impossible %d\n", mouvement);
        avoirmvt(plans, combatant, latabl, pf);
    }
}

void game (int (* blplans) (int, int *),
           int (* whplans) (int, int *), int pf) {
    int * latabl;
    int combatant;
    latabl = debut();
    combatant = noir;
    do {
        if (combatant == noir) avoirmvt(blplans, noir, latabl, pf);
        else avoirmvt(whplans, blanc, latabl, pf);
        combatant = suivantt(latabl, combatant, pf);
    }
    while (combatant != 0);
    if (pf) {
        printf("Partie finie! resultat:\n");
        afficher(latabl);
    }
}


int * aleatoirelatabl (void) {
    int combatant, enccom, i, * latabl;
    latabl = debut();
    combatant = noir;
    i=1;
    do {
        if (combatant == noir) avoirmvt(aleatoire, noir, latabl, 0);
        else avoirmvt(aleatoire, blanc, latabl, 0);
        enccom = combatant;
        combatant = suivantt(latabl, combatant, 0);
        if (enccom == combatant) {
            free(latabl);
            return(aleatoirelatabl());
        }
        i++;
    }
    while (combatant != 0 && i<=8);
    if (combatant==0) {
        free(latabl);
        return(aleatoirelatabl());
    }
    else return(latabl);
}


void rr (void) {
    int i, j, k, tdiff, combatant, igagnes, jgagnes, * g1, * g2;
    long int itab, jtab;

    i=1;
    while (jeu[i+1][0] != NULL) {
        j = i + 1;
        while (jeu[j][0] != NULL) {
            igagnes = 0;
            jgagnes = 0;
            itab = 0;
            jtab = 0;
            for (k=1; k<=5; k++) {
                g1 = aleatoirelatabl();
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
    int (* fr1)(int, int *);
    int (* fr2)(int, int *);
    char * jj;

    i=0;
    printf("combatant 1: ");
    while (jeu[i][0] != NULL) {
        jj=jeu[i][1];
        printf("%d (%s)\n", i, jj);
        printf("          ");
        i++;
    }
    printf(": ");
    scanf("%d", &p1);

    i=0;
    printf("combatant 2: ");
    while (jeu[i][0] != NULL) {
        jj=jeu[i][1];
        printf("%d (%s)\n", i, jj);
        printf("          ");
        i++;
    }
    printf(": ");
    scanf("%d", &p2);

    fr1 = jeu[p1][2];
    fr2 = jeu[p2][2];
    if (fr1 == joueur || fr2 == joueur) pf = 1;
    else {
        printf("       \n");
        printf("Aucun joueur n'est détecté ");
        scanf("%d", &pf);
    }

    game(fr1, fr2, pf);
}



int main (void) {
int i;
char car;
printf("si vous voulez recomencer le jeu tapez r ");
scanf("%s",&car);
if(car==114){
printf("\t\t  ####****************************####\n");
printf("\t\t  ##\t      OTHELLO GAME    \t    ##\n");
printf("\t\t  ####****************************####\n");
printf("\t\t  a  b  c  d  e  f  g  h\n");
for(i=0;i<8;i++){
printf("\t\t%d:__,__,__,__,__,__,__,__,\n",i+1);}}
    jeux();
    fflush(stdin);

    }
}
