#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Header.h"
#include <pthread.h>

pthread_mutex_t dmutex = PTHREAD_MUTEX_INITIALIZER;
void * lire_clavier(void *arg) {
    joueur * charac = (joueur*)arg;
    char c;
    tcgetattr(0, &origtc);
    newtc = origtc;
    newtc.c_lflag &= ~ICANON;
    newtc.c_lflag &= ~ECHO;
    while(1) {
        tcsetattr(0, TCSANOW, &newtc);
        c = getchar();
        tcsetattr(0, TCSANOW, &origtc);
        pthread_mutex_lock(&dmutex);
        if (c=='z') {
            charac->direction = HAUT;
        }else if (c == 's') {
            charac->direction = BAS;
        }else if (c == 'd') {
            charac->direction = DROITE;
        }else if (c == 'q') {
            charac->direction = GAUCHE;
        }
        pthread_mutex_unlock(&dmutex);
        sleep(1);
    }
}


void calculer_direction(joueur *star) {
    if (star->direction == DROITE) {
        if (star->tableau[star->posl][star->posc + 1] != 1) {
            star->tableau[star->posl][star->posc] = 0;
            star->tableau[star->posl][star->posc + 1] = 2;
            star->posc += 1;
        }
        else {
            star->direction = GAUCHE;
            calculer_direction(star);
        }

    }
    else if (star->direction == GAUCHE) {
        if (star->tableau[star->posl][star->posc - 1 ]!= 1) {
            star->tableau[star->posl][star->posc] = 0;
            star->tableau[star->posl][star->posc - 1] = 2;
            star->posc -= 1;
        }
        else {
            star->direction = DROITE;
            calculer_direction(star);
        }
    }
    else if (star->direction == BAS) {
        if (star->tableau[star->posl + 1][star->posc] != 1) {
            star->tableau[star->posl][star->posc] = 0;
            star->tableau[star->posl + 1][star->posc] = 2;
            star->posl += 1;
        }
        else {
            star->direction = HAUT;
            calculer_direction(star);
        }

    }
    else if (star->direction == HAUT) {
        if (star->tableau[star->posl - 1][star->posc] != 1) {
            star->tableau[star->posl][star->posc] = 0;
            star->tableau[star->posl - 1][star->posc] = 2;
            star->posl -= 1;
        } else {
            star->direction = BAS;
            calculer_direction(star);
        }
    }
}

void afficher_plateau(int tableau[LIGNES][COLONNES]) {
    for (int i = 0; i < LIGNES; i++) {
        printf("\n");
        for (int j = 0; j < COLONNES; j++) {
            printf("%c", tableau[i][j]);
        }
    }
}

void *deplacer_star(void *arg) {
    joueur * star = (joueur *)arg;
    while(1) {
        pthread_mutex_lock(&dmutex);
        calculer_direction(star);
        // A compléter pour mettre à 0 la case précédente de l'étoile
        // et 1 sa nouvelle position avant d'afficher le plateau
        afficher_plateau(star->tableau);
        pthread_mutex_unlock(&dmutex);
        sleep(1);
    }
}



void generer_tableau(int tableau[LIGNES][COLONNES]) { // 35 = "#" et 32 = " "
	const char* filename = "tableau.txt";
	FILE* fp = fopen(filename, "r");
	int c;
	int i = 0;
	int j = 0;
	while (1) {
		c = fgetc(fp);
		if (feof(fp)) {
			break;
		}
		if (c == 10) {
			j++;
			i = 0;
		}
		else
		{
			tableau[j][i] = c;
			i++;
		}
	}
	fclose(fp);
}


int main(int argc, char* argv[]) {
	int tableau[LIGNES][COLONNES];
	generer_tableau(tableau);
    joueur joueur1;
    joueur1.tableau = tableau;
	afficher_plateau(tableau);
	printf("\n");
	return 0;
}