#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h> 
#include <string.h>
#include <stdlib.h>
typedef struct DateCompanie DateCompanie;//pt a nu mai scrie struct

struct DateCompanie {
	char* denumire;
	int nrAng;
	float CA;
};

void afisareCompanie(DateCompanie comp)
{
	printf("\n%s %d %.2f", comp.denumire, comp.nrAng, comp.CA);
}

 DateCompanie citireDateCompanie(FILE* streamFisier)
{
	DateCompanie dateCompanie;

	if (streamFisier != NULL) {
		char buffer[20];
		fgets(buffer, 20, streamFisier);
		char* sir = strtok(buffer, "\n");

		dateCompanie.denumire = (char*)malloc(sizeof(char) * (strlen(sir) + 1));
		strcpy(dateCompanie.denumire, sir);

		fgets(buffer, 7, streamFisier);
		dateCompanie.nrAng = atoi(buffer);

		fgets(buffer, 9, streamFisier);
		dateCompanie.CA = atof(buffer);

	}
	return dateCompanie;
}

void citireVectorCompanii(FILE* streamFisier, DateCompanie** dt, int* dim) {

	if (streamFisier == NULL) {
		printf("Eroare la deschiderea fisierului");
	}
	else {
		char buffer[100];
		fgets(buffer, 100, streamFisier);
		*dim = atoi(buffer);

		*dt = (DateCompanie*)malloc((*dim) * sizeof(DateCompanie));

		for (int i = 0; i < *dim; ++i) {
			(*dt)[i] = citireDateCompanie(streamFisier);
		}
	}
}

void citireMatrice(DateCompanie ***matrice, char* numeFisier,int* nrLinii,int** dimensiuni)
{
	FILE* f = NULL;
	f = fopen(numeFisier, "r");
	if (f != NULL)
	{
		char buffer[50];
		fgets(buffer, 5, f);//+2 pentru sfarsit sir de caractere \0 si \n
		*nrLinii = atoi(buffer);
		*matrice = (DateCompanie**)malloc((*nrLinii) * sizeof(DateCompanie*));
		*dimensiuni = (int*)malloc(sizeof(int) * (*nrLinii));
		for (int i = 0; i < *nrLinii; i++)
		{
			citireVectorCompanii(f, (*matrice) + i, (*dimensiuni) + i);	//sau &((*matrice)[i]))
		}
		fclose(f);
	}
}

void afisMatrice(DateCompanie** matrice, int* dimensiuni, int nrLinii)
{
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < dimensiuni[i]; j++)
			afisareCompanie(matrice[i][j]); //matrice[i][j] = o companie
	}
}

void dezalocare(DateCompanie*** matrice, int** dimensiuni, int* nrLinii)
{
	for (int i = 0; i < *nrLinii; i++)
	{
		for (int j = 0; j < (*dimensiuni)[i]; j++)
			free((*matrice)[i][j].denumire);
		free((*matrice)[i]);
	}
	free(*matrice);
	free(*dimensiuni);
	*nrLinii = 0;
	*matrice = NULL;
	*dimensiuni = NULL;
}

int main()
{
	DateCompanie** matrice;
	int nrLinii;
	int* dimensiuni;

	citireMatrice(&matrice, "matrice.txt", &nrLinii, &dimensiuni);
	afisMatrice(matrice, dimensiuni, nrLinii);
	
	dezalocare(&matrice, &dimensiuni, &nrLinii);

	return 0;
}