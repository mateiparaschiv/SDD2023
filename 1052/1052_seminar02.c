#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct Student {
	int id;
	float medie;
	char* nume;
};

void afisareStudent(struct Student s) {
	printf("%d\n", s.id);
	printf("%.2f\n", s.medie);
	printf("%s\n", s.nume);
}

void citireStudent(char* numeFisier, struct Student* s) {

	FILE* f = NULL;
	fopen_s(&f, numeFisier, "r");

	if (f != NULL) {
		char buffer[30];

		fgets(buffer, 30, f);

		s->id = atoi(buffer);

		fgets(buffer, 30, f);

		s->medie = atof(buffer);

		fgets(buffer, 30, f);

		char* sir = strtok(buffer, "\n");

		s->nume = (char*)malloc(sizeof(char) * (strlen(sir) + 1));

		strcpy(s->nume, sir);

		fclose(f);

	}
	else {
		printf("Fisierul nu a putut fi deschis!\n");
	}
}

void citireVector(char* numefisier, int* dim, int** vector)
{
	FILE* f = NULL;
	f = fopen(numefisier, "r");
	if (f != NULL) {
		fscanf(f, "%d", dim);
		*vector = (int*)malloc((*dim) * sizeof(int));
		for (int i = 0; i < *dim; i++) {
			fscanf(f, "%d", (*vector) + i);
		}

		fclose(f);
	}
	else {
		printf("FISIERUL NU S_A PUTU DESCHIDE\n");
	}
}

int main()
{
	//FILE* f = NULL;
	//f = fopen("fisier.txt", "r");
	////fopen_s(&f, "fisier.txt", "r");
	////fscanf muta cursorul pe urmatoarea linie
	//int x, y;
	//if (f != NULL)
	//{
	//	int citire = fscanf(f, "%d", &x);
	//	fscanf(f, "%d", &y);
	//	//citire = fscanf(f, "%d", &y);
	//	//printf("%d", citire);

	//}
	//else {
	//	printf("FISIERUL NU S_A PUTU DESCHIDE\n");
	//}
	//
	//printf("%d \n %d", x, y);
	//
	//fclose(f);

	int dim;
	int* vector;
	citireVector("vector.txt", &dim, &vector);
	for (int i = 0; i < dim; i++) {
		printf("%d", vector[i]);
	}
	printf("Afisare student \n");

	struct Student s;
	citireStudent("Student.txt", &s);

	//printf("%d", s.id);

	afisareStudent(s);

	return 0;
}