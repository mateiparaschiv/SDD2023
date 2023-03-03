#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h> 
#include <string.h>
#include <stdlib.h>

struct DateCompanie {
	char* denumire;
	int nrAng;
	float CA;
};

void afisareCompanie(struct DateCompanie comp)
{
	printf("\n%s %d %.2f", comp.denumire, comp.nrAng, comp.CA);
}

struct DateCompanie citireDateCompanie(FILE* streamFisier)
{	struct DateCompanie dateCompanie;

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

void citireVectorCompanii(const char* numeFisier, struct DateCompanie** dt, int* dim) {
	FILE* f = NULL;
	f = fopen(numeFisier, "r");

	if (f == NULL) {
		printf("Eroare la deschiderea fisierului");
	}
	else {
		char buffer[100];
		fgets(buffer, 100, f);
		*dim = atoi(buffer);

		*dt = (struct DateCompanie*)malloc((*dim) * sizeof(struct DateCompanie));

		for (int i = 0; i < *dim; ++i) {
			(*dt)[i] = citireDateCompanie(f);
		}

		fclose(f);
	}
}

void citireFisier(char* numeFisier, int** v, int* dim)
{
	FILE* f = NULL;
	f = fopen(numeFisier, "r");
	if (f != NULL)
	{
		fscanf(f, "%d", dim);
		*v = (int*)malloc((*dim) * sizeof(int));
		for (int i = 0; i < (*dim); i++)
		{
			fscanf(f, "%d", (*v) + i);
		}

		fclose(f);
	}
	else 
	{
		printf("Eroare! Nu s-a putut deschide fisierul! \n");
	}
}

int main()
{
	/*FILE* streamFisier = NULL;
	int a, b;
	streamFisier = fopen("Numere.txt", "r");


	if (streamFisier != NULL)
	{
		fscanf(streamFisier, "%d ", &a);
		fscanf(streamFisier, "%d ", &b);
	}
	else printf("Nu s-a putut deschide fisierul. \n");
	printf("%d %d", a, b);*/
	int* v;
	int dim;
	citireFisier("vector.txt", &v, &dim);
	for (int i = 0; i < dim; i++)
	{
		printf("%d ", v[i]);
	}

	struct DateCompanie d;
	FILE* streamDateCompanie = NULL;
	streamDateCompanie = fopen("datecompanie.txt", "r");
	d = citireDateCompanie(streamDateCompanie); //functie
	fclose(streamDateCompanie);
	printf("\n\nAfisare date companie:");
	afisareCompanie(d);

	struct DateCompanie* vec;
	int dimCompanii;
	citireVectorCompanii("VectorCompanii.txt", &vec, &dimCompanii);
	printf("\n\nAfisare date companii:");
	for (int i = 0; i < dimCompanii; ++i)
	{
		afisareCompanie(vec[i]);
	}

	//dezalocare memorie

	return 0;
}