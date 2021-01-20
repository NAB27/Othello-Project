#include <stdio.h>
#include <stdlib.h>
/*Hello Stranger! here you will find the main code for our Othello project made by
Manal & Nabih, have fun! */
#include <stdio.h>
#include <stdlib.h>
int main()
{/*****recommencer*****/
printf("\t hello ! \n");
printf("\t voulez vous recommencez tapez la touche r\n ");
printf("\t voulez vous continuer votre jeu tapez la touche c\n");
char etat;
int i;
scanf("%c",&etat);
if (etat==114){
     printf("\t####****************************####\n");
     printf("\t##     OTHELLO GAME             ##\n");
     printf("\t####****************************####\n");
     printf("\t[-A-,-B-,-C-,-D-,-E-,-F-,-G-,-H-]\n");
     for(i=0;i<8;i++){
        printf("\t ---,---,---,---,---,---,---,---,\n ");
    }printf("\t[-A-,-B-,-C-,-D-,-E-,-F-,-G-,-H-]\n");}
/****les caracteristiques****/
FILE*fichier;//creation d'un fichier
//infos
char nom[20];
int score;
char mot_de_passe;
//enregistrement_nouvelle_partie
printf("donner le nom du joueur qui veut jouer par le blanc\n");
scanf("%s",&nom);
score=0;
fichier=fopen("projet_c","wba");
if(fichier==NULL){printf("erreur d'overture du fichier");
                exit(EXIT_FAILURE);}
fwrite(&nom,sizeof(nom),1,fichier);
fwrite(&score,sizeof(score),1,fichier);
printf("donner le nom du joueur qui veut jouer par le noir\n");
scanf("%s",&nom);
score=0;
fwrite(&nom,sizeof(nom),1,fichier);
fwrite(&score,sizeof(score),1,fichier);
fclose(fichier);}
/***les parties***/
//chaque joueur a une liste des paties chainees 
typedef struct partie_joueur{
//numero de la partie
int num_partie;
int score;
struct partie_joueur*suivant;}partie_joueur;
//une liste contient le nom du joueur et sa liste des parties
typedef struct parties{
char nom[20];
struct partie_joueur;
struct parties*suivant
}parties;
/***ajouter une partie***/
void*ajouter(parties*debut){
    printf("donner le nom du joueur");
    char nom[20];
    scanf("%s",&nom);
    parties*temp=debut;
    while((temp->suivant)!==NULL){if (strcmp(nom,temp->nom)==0){partie_joueur*temp1;
                                                              temp1=temp->(partie_joueur);
                                                            while(temp1->suivant!=NULL){temp1=temp1->suivant;}
                                                            partie_joueur*nouveau=(partie_joueur*)malloc(sizeof(partie_joueur));
                                                            nouveau->score=0;
                                                            nouveau->num_partie=(temp1->num_partie)+1;}
  temp=temp->suivant;}
    }
/***continuer en une partie deja souvgardee**/
void*continuer(parties*debut){
printf("donner le nom du joueur");
char nom[20];
scanf("%s",&nom);
printf("donner le numero de la partie");
int num_partie;
scanf("%d",&num_partie);
parties*temp=debut;
while(temp->suivant!=NULL){if (strcmp(nom,temp->nom)==0){partie_joueur*temp1;
                                                          temp1=temp->(partie_joueur);
                                                            while(temp1->suivant!=NULL){
                                                                if (temp1->num_partie=num_partie){printf("%d",&temp1->score);
                                                                                                  /**ajout d'une partie**/
                                                                                                  ajouter(parties*debut);}}}}}

/**affichage des 10 meilleurs scores****/
void*meill_scores(parties*debut){
    int i,j, s=0;
    int indice=0;
    parties*temp=debut;
    typedef struct meil_score{
          int score_t;
          char nom;}meil_score;
    meil_score*list;
    list=(meil_score*)malloc(20*sizeof(meil_score));
    while(temp->suivant!=NULL){ char nom[20];
                                nom=temp->nom;
                                partie_joueur*temp1=temp->(partie_joueur);
                               while(temp1->suivant!=NULL){s=s+temp1->score;//score de toute les partie jouees
                                                            }
                                                            meil_score*temp2;
                                                            temp2=(meil_score*)malloc(sizeof(meil_score));
                                                            temp2->score_t=s;
                                                            stcrpy(temp2->nom,nom);
                                                            list[indice]=temp2;
                               temp=temp->suivant;
                               indice=indice+1;
    return list}
    meil_score*l=meill_scores(parties*debut);
/****tri du tableau***/
for (i=0 ; i <indice+1; i++)
  {for (j=0 ; j <indice; j++){
      if ((l[j]->score)>(l[j+1]->score)) 
      {meil_score*tmp =l[j];
       l[j] =l[j+1];
      l[j+1] =tmp;}}}
/***meilleur score***/
printf("*******les meilleurs scores******");
for(i=0;i<indice+1;i++){
             printf("%d\t",l[i]->score);
             printf("%s\n",l[i]->nom);}}
/******jeu*****/
char board[8][8];
int i,j;
for(i=0;i<8;i++){
    for(j=0;j<8;j++){board[i][j]="_";}}
for(i=0;i<8;i++){
    for(j=0;j<8;j++){printf("%d",board[i][j]);}
    printf("\n");}
board[3][3]=board[4][4]=b;
board[3][4]=board[4][3]=n;/**suite**/

