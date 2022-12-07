#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Header.h"
#include <pthread.h>

char symbole(int tableau[LIGNES][COLONNES], int i, int j) {
	if (tableau[i][j] == 1) {
		return 'x';
	}
	if (tableau[i][j] == 2) {
		return 'o';
	}
	else {
		return ' ';
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
	afficher_plateau(tableau);
	printf("\n");

	return 0;
}