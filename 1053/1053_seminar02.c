#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>

struct Telefon {
	char* denumire;
	float memorie;
	int ani;
};

void citireTelefon(struct Telefon* t, char* denumireFisier) {
	FILE* f = NULL;
	f = fopen(denumireFisier, "r");
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
	fclose(f);
}

void afisareTelefon(struct Telefon t) {
	printf("%s %.2f %d", t.denumire, t.memorie, t.ani);
}

void citireVector(int** vector, int* nrElem, FILE* fisier) {
	fscanf(fisier, "%d", nrElem);
	*vector = (int*)malloc(sizeof(int) * (*nrElem));
	for (int i = 0; i < (*nrElem); i++)
	{
		fscanf(fisier, "%d", &((*vector)[i]));
	}
}

void main()
{
	FILE* f = NULL;
	f = fopen("fisier.txt", "r");
	if (f != NULL)
	{
		int a, b;
		fscanf(f, "%d", &a);
		fscanf(f, "%d", &b);
		printf("%d %d\n", a, b);
		fclose(f);
	}
	else
		printf("Nu s-a deschis fisierul!\n");

	FILE* g = NULL;
	g = fopen("vector_fisier.txt", "r");

	int* vector;
	int nrElem;
	if (g != NULL)
	{
		citireVector(&vector, &nrElem, g);
		fclose(g);
		for (int i = 0; i < nrElem; i++) {
			printf("%i\n", vector[i]);
		}
		free(vector);
	}

	else {
		printf("Nu s-a deschis fisierul!\n");
	}

	struct Telefon t;
	citireTelefon(&t, "fisierInput.txt");
	afisareTelefon(t);

	free(t.denumire);
}