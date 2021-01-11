
    /*Hello Stranger! here you will find the main code for our Othello project made by
Manal & Nabih, have fun! */
#include <stdio.h>
#include <stdlib.h>

int main()
{

char etat;
int re;
/*par une saisie du mot recomencer*/
printf("est ce que tu veux jouer entrer recommencer");
scanf("%s",&etat);
re=strcmp(etat,"recommencer");
if(re==0){
 int i;
 printf("\t    A   B   C   D   E   F   G   H  ");
 for(i=0;i<8;i++){
  printf("\t  +---+---+---+---+---+---+---+---+\n");}
 printf("\t    A   B   C   D   E   F   G   H  \n ");}
/*par la touche entrer comme symbole de recommencer**/
scanf("%d",&re);
if (re=13 )/**le code ascii de la touche entrer ***/{
int i;
 printf("\t    A   B   C   D   E   F   G   H  ");
 for(i=0;i<8;i++){
  printf("\t  +---+---+---+---+---+---+---+---+\n");}
 printf("\t    A   B   C   D   E   F   G   H  \n ");}}