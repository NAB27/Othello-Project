/*Hello Stranger! here you will find the main code for our Othello project made by
Manal & Nabih, have fun! */
#include <stdio.h>
#include <stdlib.h>
int main()
{/*****la partie 1 et 2******/
    /*****recommencer*****/
printf("\t hello ! \n");
printf("\t voulez vous recommencez tapez la touche r\n ");
printf("\t voulez vous continuer votre jeu tapez la touche c\n");
char etat;
int i;
scanf("%c",&etat);
if (etat==114){
    printf(" \t voila! votre espace :\n");
    printf("\t[-A-,-B-,-C-,-D-,-E-,-F-,-G-,-H-]\n");
    for(i=0;i<8;i++){
<<<<<<< HEAD
        printf("\t ---,---,---,---,---,---,---,---,\n ");
    }printf("\t[-A-,-B-,-C-,-D-,-E-,-F-,-G-,-H-]\n");}
/****les caracteristiques****/
FILE*fichier=NULL;//creatio d'un fichier
//infos
char nom[20];
int score;
char mot_de_passe;
//enregistrement
printf("donner le nom du joueur qui veut jouer par le blanc\n");
scanf("%s",&nom);
score=0;
fopen(fichier,"w");
fwrite(&nom,sizeof(nom),1,fichier);
fwrite(&score,sizeof(score),1,fichier);
printf("donner le nom du joueur qui veut jouer par le noir\n");
scanf("%s",&nom);
score=0;
fwrite(&nom,sizeof(nom),1,fichier);
fwrite(&score,sizeof(score),1,fichier);
fclose(fichier);}
