#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>
/*************prototype*************/
int*chercher(FILE*Fichier);  //cherche si le joueur existe dans le fichier
void*creation_joueur();    //cree les nouveaux joueurs 
void*jeu();                    //le jeu complet
void position(short x, short y);   //la saisie du position par rapport aux notations prises
void Display(char Board[8][8]);      // affiche le taleau a chaque fois


//les structures

typedef struct securite{
char nom[20];
char mot_de_passe[16];
struct securite*suivant;}securite;

typedef struct mouvement mouvement; //structure  qui contient les données relatives au mouvement effectués par les joueurs
struct mouvement
{
    char coordonnee[10];
    char player[2];
    int numero;
    mouvement *suivant;
};

typedef struct historique historique; // liste qui contient le premier  mouvement effectué
struct historique
{
    mouvement *premier;

};

int*chercher(FILE*Fichier);
void*creation_joueur();
void*jeu();
void position(short x, short y);
void Display(char Board[8][8]);
int n,n2; // on va utiliser cette variable pour savoir si l'utilisateur veut que la partie soit enregistrée ou pas

typedef struct joueur{
char nom[20];
char score[20];
struct joueur*suivant;}joueur;


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






historique *initialmouvement() //fonction qui initialise la liste chainée historique
{
    historique *Historique = malloc(sizeof(*Historique));
    mouvement *mvt = malloc(sizeof(*mvt));

    if (Historique == NULL || mvt == NULL)
    {
        exit(EXIT_FAILURE);
    }

        mvt->numero = 0;
        strcpy(mvt->player,"vide");
        /*mvt->player = NULL;*/
        strcpy(mvt->coordonnee,"vide");
        /*mvt->coordonnee = NULL;*/
        mvt->suivant = NULL;

    Historique->premier = mvt;

    return Historique;
}

void insertmouvement(historique *Historique, char *newplayer, char *newcoordonnee) //fonction qui ajoute les mouvements dans la liste chainée historique
{
    mouvement *new = malloc(sizeof(*new));
    if (Historique == NULL || new == NULL)
    {
        exit(EXIT_FAILURE);
    }
         new->numero = new->numero + 1;
        strcpy(new->player,newplayer);
        //new->player = newplayer;
        strcpy(new->coordonnee,newcoordonnee);
        //new->coordonnee = newcoordonnee;

    new->suivant = Historique->premier;
    Historique->premier = new;
}

void showmouvement(historique *Historique)   //fonction qui affiche les mouvements effectuées durant le match
{
    if (Historique == NULL)
    {
        exit(EXIT_FAILURE);
    }

    mouvement *current = Historique->premier;// variable locale de type mouvement pour parcourir la liste chainée

    while (current != NULL)
    {
        printf("%d -> ", current->numero);
        printf("%c -> ", current->player);
        printf("%c -> ", current->coordonnee);
        current = current->suivant;
    }
    printf("NULL\n");
}


/****fonction qui cree les joueurs nouveaux pour les autres conserve meme score**/

void*creation_joueur(){
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
fprintf(fichier,"%s\n%d\n ",&nom,&score);}}  //pour les joueurs deja existes on garde le meme score
//l'ajout successif dans une liste chainee a partir d'un fichier
joueur*remplissage(){  
joueur*list=NULL;
joueur*joueur1;
joueur1=(joueur*)malloc(sizeof(joueur));
FILE*fichier;
fichier=fopen("manal","r");
while(fgets(joueur1->nom,20,fichier)&&fgets(joueur1->score,20,fichier)){joueur1->suivant=list;
                                                                          list=joueur1;}
return list;}
<<<<<<< Updated upstream
void*affichage_scores(joueur*list){ //tri de la liste
//tri de la liste chainee(tri a bulles)   
=======
void*affichage_scores(joueur*list){
//tri de la liste chainee(tri a bulles)
>>>>>>> Stashed changes
	joueur*p;
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
printf(" Liste vide !!\n"); return ;}
else { joueur*temp=list;
        while(temp!=NULL){
        printf("%s",temp->nom);
        printf("%s",temp->score);}}}

/*########livrable2########*/
void position(short x, short y){
COORD pos ={x,y};  //la position
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void Display(char Board[8][8])
{
	system("cls");  //supprimer le contenu d'ecran a chaque fois

 int i,j;
 printf("  +---+---+---+---+---+---+---+---+\n");
 for(i=0;i<8;i++)
 {
  printf("%d",i+1);
  for(j=0;j<8;j++){
  printf(" |%c ",Board[i][j]);}
 printf("\n  +---+---+---+---+---+---+---+---+\n");}
 printf("   A   B   C   D   E   F   G   H  ");
}

void*jeu(){
Intro:     //label

system("cls");
int i,j,W,Done,Melon=0;
char A,B,pos[2],X,Y,Board[8][8];
for(i=0;i<8;i++)
{
 for(j=0;j<8;j++)
 Board[i][j]=' ';
}
printf("\t\t  ####****************************####\n");
printf("\t\t  ##\t      OTHELLO GAME    \t    ##\n");
printf("\t\t  ####****************************####\n");
Sleep(3000);
printf("Entrer le symbole de 1er joueur: ");
scanf("%c",&A);
printf("Entrer le symbole du deuxieme joueur: ");
scanf("%c",&B);
if(A==B)
{
 printf("les symboles se ressemblent........");  //les memes symboles
 Sleep(1000);
 goto Intro;
}
char tICK = A;
char Tick = B;
char *Quote[3]={"Le jeu","commence","maintenant!!!"};
for(i=0;i<3;i++)
{
 printf("\n\n \t\t\t%s",Quote[i]);
 Sleep(500);
}
Sleep(1000);
Board[3][3]=A; Board[3][4]=B;
Board[4][3]=B; Board[4][4]=A;
start:
Display(Board);
A = tICK;
printf("(%c) votre tour........",A);
Sleep(1000);
printf("\nEntrer votre Position: ( tq A3,B4)");
gets(pos);
pos[0]=toupper(pos[0]); //la gestion de position par rapport au tableau
if(pos[0]=='A'){
X = 0; insertmouvement(history, A, pos);} // on insere la position donnee une seule fois en depant de le premier indice coordonnee
else if(pos[0]=='B'){
X = 1; insertmouvement(history, A, pos);}
else if(pos[0]=='C'){
X = 2; insertmouvement(history, A, pos);}
else if(pos[0]=='D'){
X = 3; insertmouvement(history, A, pos);}
else if(pos[0]=='E'){
X = 4; insertmouvement(history, A, pos);}
else if(pos[0]=='F'){
X = 5; insertmouvement(history, A, pos);}
else if(pos[0]=='G'){
X = 6; insertmouvement(history, A, pos);}
else if(pos[0]=='H'){
X = 7; insertmouvement(history, A, pos);}
else
{
 printf("Entrer une autre fois...");
 Sleep(500);
 goto start;
}
if(pos[1]=='1')
Y = 0;
else if(pos[1]=='2')
Y = 1;
else if(pos[1]=='3')
Y = 2;
else if(pos[1]=='4')
Y = 3;
else if(pos[1]=='5')
Y = 4;
else if(pos[1]=='6')
Y = 5;
else if(pos[1]=='7')
Y = 6;
else if(pos[1]=='8')
Y = 7;
else
{
 printf("Entrer une autre fois...");
 Sleep(500);
 goto start;
}
if(Board[Y][X]!=' ')
{
 printf("Entrer une autre fois...");
 Sleep(500);
 goto start;
}
//      POSITION VALIDE
if((Board[Y-1][X-1]!=A) &&(Board[Y-1][X]!=A) &&(Board[Y-1][X+1]!=A)&&(Board[Y][X-1]!=A)&&(Board[Y][X+1]!=A)&&(Board[Y+1][X-1]!=A)&&(Board[Y+1][X]!=A)&&(Board[Y+1][X+1]!=A)){
   printf("position invalide");
   goto start;}
Board[Y][X]=A;
B = Tick;
//teste du cote gauche
for(j=X-1;j>=0;j--)
{
 if(Board[Y][j]==B)
 Board[Y][j]=A;
 else
 break;
}
if(Board[Y][j]!=A)
{
 for(j=X-1;j>=0;j--)
 {
  if(Board[Y][j]==A)
  Board[Y][j]=B;
  else
  break;
 }
}
// teste du cote droit
for(j=X+1;j<8;j++)
{
 if(Board[Y][j]==B)
 Board[Y][j]=A;
 else
 break;
}
if(Board[Y][j]!=A)
{
 for(j=X+1;j<8;j++)
 {
  if(Board[Y][j]==A)
  Board[Y][j]=B;
  else
  break;
 }
}
//teste de la pratie haute
for(i=Y-1;i>=0;i--)
{
 if(Board[i][X]==B)
 Board[i][X]=A;
 else
 break;
}
if(Board[i][X]!=A)
{
 for(i=Y-1;i>=0;i--)
 {
  if(Board[i][X]==A)
  Board[i][X]=B;
  else
  break;
 }
}
// teste de la partie basse
for(i=Y+1;i<8;i++)
{
 if(Board[i][X]==B)
 Board[i][X]=A;
 else
 break;
}
if(Board[i][X]!=A)
{
 for(i=Y+1;i<8;i++)
 {
  if(Board[i][X]==A)
  Board[i][X]=B;
  else
  break;
 }
}
// teste de la partie droite de la diagonale
i = Y-1; j = X-1;
while(i>=0 && j>=0)
{
 if(Board[i][j]==B)
 Board[i][j]=A;
 else
 break;
 i--; j--;
}
if(Board[i][j]!=A)
{
 i = Y-1; j = X-1;
 while(i>=0 && j>=0)
 {
  if(Board[i][j]==A)
  Board[i][j]=B;
  else
  break;
  i--; j--;
 }
}
// teste de la partie gauche de la diagonale
i = Y-1; j = X+1;
while(i>=0 && j<8)
{
 if(Board[i][j]==B)
 Board[i][j]=A;
 else
 break;
 i--; j++;
}
if(Board[i][j]!=A)
{
 i = Y-1; j = X+1;
 while(i>=0 && j<8)
 {
  if(Board[i][j]==A)
  Board[i][j]=B;
  else
  break;
  i--; j++;
 }
}
//teste de la partie gauche de la contre diagonale
i = Y+1; j = X-1;
while(i<8 && j>=0)
{
 if(Board[i][j]==B)
 Board[i][j]=A;
 else
 break;
 i++; j--;
}
if(Board[i][j]!=A)
{
 i = Y+1; j = X-1;
 while(i<8 && j>=0)
 {
  if(Board[i][j]==A)
  Board[i][j]=B;
  else
  break;
  i++; j--;
 }
}
// teste de la patie droite du contre diagonale
i = Y+1; j = X+1;
while(i<8 && j<8)
{
 if(Board[i][j]==B)
 Board[i][j]=A;
 else
 break;
 i++; j++;
}
if(Board[i][j]!=A)
{
 i = Y+1; j = X+1;
 while(i<8 && j<8)
 {
  if(Board[i][j]==A)
  Board[i][j]=B;
  else
  break;
  i++; j++;
 }
}
Display(Board);
Sleep(500);
Done = 1;
for(i=0;i<8;i++)
{
 for(j=0;j<8;j++)
 {
  if(Board[i][j]==' ')
  Done = 0;
 }
}
if(Done==1)
goto end;
/*                                */
printf("(%c) votre Tour........",B);
printf("\nEntrer votre Position: ( tq A3,B4)");
Sleep(1000);
again:
X = rand()%8;
Y = rand()%8;
W = 0;
    if (Board[Y][X]!=' ')
goto again;
    if (Board[Y+1][X]==A)
 W++;
 if (Board[Y][X+1]==A)
 W++;
 if(Board[Y+1][X+1]==A)
 W++;
 if(Board[Y-1][X]==A)
 W++;
 if(Board[Y][X-1]==A)
 W++;
 if(Board[Y-1][X-1]==A)
 W++;
 if(Board[Y+1][X-1]==A)
 W++;
 if(Board[Y-1][X+1]==A)
 W++;
if(W==0 && Melon<15)
goto again;
Board[Y][X] = B;
Melon++;
//gauche
for(j=X-1;j>=0;j--)
{
 if(Board[Y][j]==A)
 Board[Y][j]=B;
 else
 break;
}
if(Board[Y][j]!=B)
{
 for(j=X-1;j>=0;j--)
 {
  if(Board[Y][j]==B)
  Board[Y][j]=A;
  else
  break;
 }
}
// a droite
for(j=X+1;j<8;j++)
{
 if(Board[Y][j]==A)
 Board[Y][j]=B;
 else
 break;
}
if(Board[Y][j]!=B)
{
 for(j=X+1;j<8;j++)
 {
  if(Board[Y][j]==B)
  Board[Y][j]=A;
  else
  break;
 }
}
// haut
for(i=Y-1;i>=0;i--)
{
 if(Board[i][X]==A)
 Board[i][X]=B;
 else
 break;
}
if(Board[i][X]!=B)
{
 for(i=Y-1;i>=0;i--)
 {
  if(Board[i][X]==B)
  Board[i][X]=A;
  else
  break;
 }
}
// bas
for(i=Y+1;i<8;i++)
{
 if(Board[i][X]==A)
 Board[i][X]=B;
 else
 break;
}
if(Board[i][X]!=B)
{
 for(i=Y+1;i<8;i++)
 {
  if(Board[i][X]==B)
  Board[i][X]=A;
  else
  break;
 }
}
// gauche diagonale
i = Y-1; j = X-1;
while(i>=0 && j>=0)
{
 if(Board[i][j]==A)
 Board[i][j]=B;
 else
 break;
 i--; j--;
}
if(Board[i][j]!=B)
{
 i = Y-1; j = X-1;
 while(i>=0 && j>=0)
 {
  if(Board[i][j]==B)
  Board[i][j]=A;
  else
  break;
  i--; j--;
 }
}
// droite diagonale
i = Y-1; j = X+1;
while(i>=0 && j<8)
{
 if(Board[i][j]==A)
 Board[i][j]=B;
 else
 break;
 i--; j++;
}
if(Board[i][j]!=B)
{
 i = Y-1; j = X+1;
 while(i>=0 && j<8)
 {
  if(Board[i][j]==B)
  Board[i][j]=A;
  else
  break;
  i--; j++;
 }
}
// droite contre diagonale
i = Y+1; j = X-1;
while(i<8 && j>=0)
{
 if(Board[i][j]==A)
 Board[i][j]=B;
 else
 break;
 i++; j--;
}
if(Board[i][j]!=B)
{
 i = Y+1; j = X-1;
 while(i<8 && j>=0)
 {
  if(Board[i][j]==B)
  Board[i][j]=A;
  else
  break;
  i++; j--;
 }
}
// gauche contre diagonale
i = Y; j = X;
while(i<8 && j<8)
{
 if(Board[i][j]==A)
 Board[i][j]=B;
 else
 break;
 i++; j++;
}
if(Board[i][j]!=B)
{
 i = Y; j = X;
 while(i<8 && j<8)
 {
  if(Board[i][j]==B)
  Board[i][j]=A;
  else
  break;
  i++; j++;
 }
}
Display(Board);
Sleep(500);
Done = 1;
for(i=0;i<8;i++)
{
 for(j=0;j<8;j++)
 {
  if(Board[i][j]==' ')
  Done = 0;
 }
}
if(Done==1)
goto end;
goto start;
end:
Sleep(1000);
int Pla=0,Opp=0;
for(i=0;i<8;i++)
{
 for(j=0;j<8;j++)
 {
  if(Board[i][j]==A)
  Pla++;
  if(Board[i][j]==B)
  Opp++;
 }
}
system("cls");
if(Pla>Opp)
{
 position(30,10);
 printf("vous avez reussi !!!!!!");
 printf("vous voulez voir votre historique? (y=1/n=0)");
scanf("%d",&n);
if (n==1){showmouvement(history);}
 printf("vous voulez sauvgarder la parite? (y=1/n=0)");
scanf("%d",&n2);
if (n==1){save(history);}
}
if(Pla<Opp)
{
 position(30,10);
 printf("votre adversaire a ruessi !!!!!!");
 printf("vous voulez voir votre historique? (y=1/n=0)");
scanf("%d",&n);
if (n==1){showmouvement(history);}
 printf("vous voulez sauvgarder la parite? (y=1/n=0)");
scanf("%d",&n2);
if (n==1){save(history);}
}
if(Pla==Opp)
{
 position(30,10);
 printf("egalite !!!!!!");
 printf("vous voulez voir votre historique? (y=1/n=0)");
scanf("%d",&n);
if (n==1){showmouvement(history);}

 printf("vous voulez sauvgarder la parite? (y=1/n=0)");
scanf("%d",&n2);
if (n==1){save(history);}}
getch();}


/*####################livrable3#################*/

void ajout_acces_securise(char nom[20],char mot_de_passe[16],securite*list){
//infos sous forme srtucture de donnee
if (list==NULL){printf("la liste est vide");}
// liste chainee contenant tout les utilisateurs inscrits
securite*jou;
jou=(securite*)malloc(sizeof(securite));
strcpy(jou->nom,nom);
strcpy(jou->mot_de_passe,mot_de_passe);
//l'ajout
jou->suivant=list;
list=jou;
}

//deja enregistre
void connection(securite*debut){
    char nom_util[20],mot_de_passe[20];
    char choix[20];
    printf("est ce que vous etes deja inscrit dans ce jeu ");
    scanf("%s",&choix);
    if(strcpy(choix,'oui')==0){
            printf("donner votre nom d'utilisateur");
            scanf("%s",&nom_util);
            printf("donner votre mot de passe ");
            scanf("%s",&mot_de_passe);
            securite*temp=debut;
            while((temp->suivant)!=NULL){if(strcpy(nom_util,temp->nom)==0)
                                         {if (strcpy(mot_de_passe,temp->mot_de_passe)==0)
                                           printf("bienvenue");}
                                          else{printf("mot de passe incorrect");}}}
   else{
    printf("entrer votre nom d'utilisateur");
    scanf("%s",&nom_util);
    printf("choisissez votre mot de passe ");
            scanf("%s",&mot_de_passe);
    //creation d'un espace utilisateur
    securite*utilisateur=(securite*)malloc(sizeof(securite));
    strcpy(utilisateur->nom,nom_util);
    strcpy(utilisateur->mot_de_passe,mot_de_passe);
    utilisateur->suivant=debut;
    debut=utilisateur;}
}

void save_pointeur(historique *Historique)   //fonction qui affiche les mouvements effectuées durant le match
{
        FILE *saved;
        saved = fopen(C:\\Users\\user\\Documents\\Studies\\ENSIAS\\othelloproject.txt, w); //le chemin du fichier qui contiendra le sauvgardage

    if (Historique == NULL)
    {
        exit(EXIT_FAILURE);
    }

    mouvement *current = Historique->premier;// variable locale de type mouvement pour parcourir la liste chainée

    while (current != NULL)
    {
        fprintf(saved,"%c",current->coordonnee);
        current = current->suivant;
    }
    printf("NULL\n");
    int fclose(saved);
}*/
void load ();
 int I,J;
    FILE *saved;
    saved = fopen(C:\\Users\\user\\Documents\\Studies\\ENSIAS\\othelloproject.txt, r); //le chemin du fichier qui contiendra le sauvgardage
        if (saved == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int fclose(saved);
 return 0;
void save (char tab[8][8]){
 int I,J;
    FILE *saved;
    saved = fopen(C:\\Users\\user\\Documents\\Studies\\ENSIAS\\othelloproject.txt, w); //le chemin du fichier qui contiendra le sauvgardage

    for (I=0; I<9; I++){
        for (J=0; J<10; J++){
           fprintf(saved,"%c",&tab[I][J]);}}
    int fclose(saved);
 return 0;
}



///#####################################MAIN#############################################
int main(){
historique history = initialmouvement();
int i;
char car;
printf("si vous voulez recomencer le jeu tapez");
scanf("%s",&car);
if(car==114){
printf("\t\t  ####****************************####\n");
printf("\t\t  ##\t      OTHELLO GAME    \t    ##\n");
printf("\t\t  ####****************************####\n");
printf("\t\t  a  b  c  d  e  f  g  h\n");
for(i=0;i<8;i++){
printf("\t\t%d:__,__,__,__,__,__,__,__,\n",i+1);}}
<<<<<<< Updated upstream
typedef struct joueur{
char nom[20];
char score[20];
struct joueur*suivant;}joueur;
jeu();}






=======
jeu();
>>>>>>> Stashed changes


}
