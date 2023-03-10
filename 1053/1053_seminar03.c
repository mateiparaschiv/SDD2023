#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>

typedef struct Telefon Telefon;

struct Telefon {
	char* denumire;
	float memorie;
	int ani;
};

void citireTelefon(Telefon* t, FILE* f) {
	if (!f) {
		printf("\nEroare fisier");
		return;
	}
	char buffer[100];
	fgets(buffer, 100, f);
	char* p = strtok(buffer, "\n");
	t->denumire = (char*)malloc((strlen(p) + 1) * sizeof(char));
	strcpy(t->denumire, p);
	fgets(buffer, 100, f);
	t->memorie = atof(buffer);
	fgets(buffer, 100, f);
	t->ani = atoi(buffer);
}

void afisareTelefon(Telefon t) {
	printf("%s %.2f %d", t.denumire, t.memorie, t.ani);
}

void citire_telefoane(Telefon** telefoane, int* dim, FILE* f)
{
	if (!f) {
		printf("\nBAD!");
		return;
	}
	char buffer[100];
	fgets(buffer, 100, f);
	*dim = atoi(buffer);
	*telefoane = (Telefon*)malloc(sizeof(Telefon) * (*dim));
	for (int i = 0; i < *dim; i++) {
		citireTelefon(&((*telefoane)[i]), f);
	}
}

void citireMatriceTelefoane(Telefon*** telefoane, int* nrLinii, int** nrTelefoaneLinie, FILE* f) {
	if (!f) {
		printf("\nBAD!");
		return;
	}
	else
	{
		char buffer[30];
		fgets(buffer, 30, f);
		*nrLinii = atoi(buffer);
		*nrTelefoaneLinie = (int*)malloc((*nrLinii) * sizeof(int));
		*telefoane = (Telefon**)malloc((*nrLinii) * sizeof(Telefon*));
		for (int i = 0; i < (*nrLinii); i++)
		{
			//citire_telefoane(&((*telefoane)[i]), &((*nrTelefoaneLinie)[i]), f);
			citire_telefoane((*telefoane) + i, (*nrTelefoaneLinie) + i, f);
		}
	}
}

void afisareMatrice(Telefon** telefoane, int nrLinii, int* nrTelefoaneLinie) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrTelefoaneLinie[i]; j++) {
			printf("\n");
			afisareTelefon(telefoane[i][j]);
		}
	}
}

void dezalocare(Telefon*** telefoane, int* nrLinii, int** nrTelefoaneLinie) {
	for (int i = 0; i < (*nrLinii); i++)
	{
		for (int j = 0; j < (*nrTelefoaneLinie)[i]; j++)
			free((*telefoane)[i][j].denumire);
		free((*telefoane)[i]);
	}

	free(*nrTelefoaneLinie);
	(*nrTelefoaneLinie) = NULL;
	free(*telefoane);
	(*telefoane) = NULL;
	(*nrLinii) = 0;
}

void main(){
	Telefon** matTelefoane;
	int nrLinii;
	int* nrTelefoanePeLinie;
	FILE* f = NULL;
	f = fopen("matrice-telefoane.txt", "r");
	if (f != NULL) {
		citireMatriceTelefoane(&matTelefoane, &nrLinii, &nrTelefoanePeLinie, f);
		afisareMatrice(matTelefoane, nrLinii, nrTelefoanePeLinie);

		dezalocare(&matTelefoane, &nrLinii, &nrTelefoanePeLinie);
	}
}