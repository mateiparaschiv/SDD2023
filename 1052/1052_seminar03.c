#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct Student Student;


struct Student {
	int id;
	float medie;
	char* nume;
};

void afisareStudent(Student s) {
	printf("%d\n", s.id);
	printf("%.2f\n", s.medie);
	printf("%s\n", s.nume);
}

void citireStudent(FILE* file, Student* s) {

	if (file != NULL) {
		char buffer[30];

		fgets(buffer, 30, file);

		s->id = atoi(buffer);

		fgets(buffer, 30, file);

		s->medie = atof(buffer);

		fgets(buffer, 30, file);

		char* sir = strtok(buffer, "\n");

		s->nume = (char*)malloc(sizeof(char) * (strlen(sir) + 1));

		strcpy(s->nume, sir);

	}
	else {
		printf("Fisierul nu a putut fi deschis!\n");
	}
}

Student* citireVectorStudenti(FILE* f, int* n) {
	if (f != NULL) {
		char buffer[21];
		 
		fgets(buffer, 5, f);
		*n = atoi(buffer);

		Student* vector =(Student*) malloc(sizeof(Student) * (*n));
		for (int i = 0; i < *n; i++) {
			citireStudent(f, &vector[i]);
		}
		return vector;
	}
}

Student** citireMatriceStudenti(FILE* file, int* n, int** nrStudPeLinie) {
	if (file != NULL) {
		char buffer[30];

		fgets(buffer, 30, file);
		(*n) = atoi(buffer);

		Student** matrice = (Student**)malloc(sizeof(Student*) * (*n));
		*nrStudPeLinie = (int*)malloc(sizeof(int) * (*n));
		for (int i = 0; i < (*n); i++) {
			matrice[i] = citireVectorStudenti(file, (*nrStudPeLinie) + i);
		}
		return matrice;
	}
}

void afisareMatriceStudent(Student** matriceStudenti, int nrLinii, int* nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			afisareStudent(matriceStudenti[i][j]);
		}
	}
}

void dezalocare(Student*** matrice, int** vectorNrStudentiPeLinie, int* nrLiniiStudenti) {
	for (int i = 0; i < (*nrLiniiStudenti); i++) {
		for (int j = 0; j < (*vectorNrStudentiPeLinie)[i]; j++) {
			free((*matrice)[i][j].nume);
		}
		free((*matrice)[i]);
	}
	free(*matrice);
	free(*vectorNrStudentiPeLinie);
	*matrice = NULL;
	*vectorNrStudentiPeLinie = NULL;
	(*nrLiniiStudenti) = 0;
}

int main()
{
	int* vectorNrStudentiPeLinie;
	int nrLiniiStudenti;
	Student** matriceStudenti;
	FILE* fisier = NULL;
	fisier = fopen("Studenti.txt", "r");
	if (fisier != NULL) {
		matriceStudenti = citireMatriceStudenti(fisier, &nrLiniiStudenti, &vectorNrStudentiPeLinie);
		fclose(fisier);
		afisareMatriceStudent(matriceStudenti, nrLiniiStudenti, vectorNrStudentiPeLinie);
	}
	else {
		printf("Eroare");
	}
	dezalocare(&matriceStudenti, &vectorNrStudentiPeLinie, &nrLiniiStudenti);

	return 0;
}