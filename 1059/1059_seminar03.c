#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<stdio.h> 
#include<string.h>

typedef struct Jucator Jucator;

struct Jucator {
	int numarJucator;
	char* numeJucator;
	float pretJucator;
};

Jucator citire_jucator(FILE* fisier) {
	Jucator jucator;

	if (fisier != NULL) {
		char buffer[20];

		fgets(buffer, 5, fisier);
		jucator.numarJucator = atoi(buffer);

		fgets(buffer, 20, fisier);
		char* sir = strtok(buffer, "\n");

		jucator.numeJucator = (char*)malloc((strlen(sir) + 1) * sizeof(char));
		strcpy(jucator.numeJucator, sir);

		fgets(buffer, 10, fisier);
		jucator.pretJucator = atof(buffer);

	}
	return jucator;
}

void afisareJucator(Jucator jucator) {
	printf("\nNumar: %d", jucator.numarJucator);
	printf("\nNume: %s", jucator.numeJucator);
	printf("\nPret: %0.2f", jucator.pretJucator);
}

void citireJucatori(Jucator** vector,int* nr_elem,FILE* f) {
	if (f != NULL)
	{
		char buffer[20];
		fgets(buffer, 5, f);
		*nr_elem = atoi(buffer);
		*vector = (Jucator*)malloc((*nr_elem) * sizeof(Jucator));
		for (int i = 0; i < *nr_elem; i++)
		{
			(*vector)[i] = citire_jucator(f);
		}
	}
}

void citireMatriceJucator(Jucator*** matrice_juc, int* nr_linii, 
	char* nume_fis, int** nr_jucatori_linie) {
	FILE* f = fopen(nume_fis, "r");
	if (f != NULL) {
		char buffer[20];
		fgets(buffer, 5, f);
		*nr_linii = atoi(buffer);
		*matrice_juc = (Jucator**)malloc(sizeof(Jucator*) * (*nr_linii));
		*nr_jucatori_linie = (int*)malloc(sizeof(int) * (*nr_linii));
		for (int i = 0; i < *nr_linii; i++) {
			//citireJucatori( & ((*matrice_juc)[i]), &(*nr_jucatori_linie)[i], f);
			citireJucatori( *matrice_juc+i, &(*nr_jucatori_linie)[i], f);
		}
		fclose(f);
	}
}

void afisare_matrice(Jucator** matrice_juc,int nr_linii,int* nr_jucatori_linie) {
	for(int i=0;i<nr_linii;i++)
		for (int j = 0; j < nr_jucatori_linie[i]; j++)
		{
			afisareJucator(matrice_juc[i][j]);
		}
}

int main() {

	Jucator** matrice_jucatori;
	int nr_linii;
	int* vector;

	citireMatriceJucator(&matrice_jucatori, &nr_linii, "matrice.txt", &vector);
	afisare_matrice(matrice_jucatori, nr_linii, vector);
	return 0;
}