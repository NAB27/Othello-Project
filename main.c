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
typedef struct joueur{
char nom[20];
char score[20];
struct joueur*suivant;}joueur;

typedef struct securite{
char nom[20];
char mot_de_passe[16];
struct securite*suivant;}securite;



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
void*affichage_scores(joueur*list){ //tri de la liste
//tri de la liste chainee(tri a bulles)   
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
printf("Entrer votre symbole et de votre adversaire ");
scanf("%c %c",&A,&B);
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
if(pos[0]=='A')
X = 0;
else if(pos[0]=='B')
X = 1;
else if(pos[0]=='C')
X = 2;
else if(pos[0]=='D')
X = 3;
else if(pos[0]=='E')
X = 4;
else if(pos[0]=='F')
X = 5;
else if(pos[0]=='G')
X = 6;
else if(pos[0]=='H')
X = 7;
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
if(Board[Y][X]!=' ')
goto again;
 if(Board[Y+1][X]==A)
 W++;
 if(Board[Y][X+1]==A)
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
 printf("vous avez ruessi !!!!!!");
}
if(Pla<Opp)
{
 position(30,10);
 printf("votre adversaire a ruessi !!!!!!");
}
if(Pla==Opp)
{
 position(30,10);
 printf("egalite !!!!!!");
}
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






///#####################################MAIN#############################################
int main(){
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
typedef struct joueur{
char nom[20];
char score[20];
struct joueur*suivant;}joueur;
jeu();}








}
