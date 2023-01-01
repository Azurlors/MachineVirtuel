#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <termios.h>

#define LIGNES 9
#define COLONNES 24

#define TRUE 256
#define FALSE 0

static struct termios origtc, newtc;

enum direction {HAUT,BAS,GAUCHE,DROITE};
typedef struct{
    int **tableau; //tableau du jeu
    int posl; // ligne actuelle de l'étoile
    int pl; // ligne précédente de l'étoile
    int posc; // colonne actuelle de l'étoile
    int pc; // colonne précédente de l'étoile
    enum direction direction; // direction actuelle de l'étoile
} joueur;

void * lire_clavier(void *arg);
void clearScreen();
void afficher_plateau(int tableau[LIGNES][COLONNES]);
void placer_star(joueur *star);
