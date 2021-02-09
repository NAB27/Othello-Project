#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<gtk/gtk.h>

// structures
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
}
void load (){
 int i,i;
    FILE *saved;
    saved = fopen(C:\\Users\\user\\Documents\\Studies\\ENSIAS\\othelloproject.txt, r); //le chemin du fichier qui contiendra le sauvgardage
        if (saved == NULL)
    {
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<9;i++){
        for (int j=0; i<9;i++){
            fgets(Board[i][j], 3, (FILE*)saved); //3 est le nombre de caractere qu'on veut lire - 1, donc c'est 2 l'indice ligne et colonne 
        }
    }
        int fclose(saved);
    }


void save (char tab[8][8]){
 int I,J;
    FILE *saved;
    saved = fopen(C:\\Users\\user\\Documents\\Studies\\ENSIAS\\othelloproject.txt, w); //le chemin du fichier qui contiendra le sauvgardage

    for (I=0; I<9; I++){
        for (J=0; J<9; J++){
           fprintf(saved,"%c",&tab[I][J]);}}
    int fclose(saved);
}