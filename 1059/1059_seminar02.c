#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<stdio.h> 
#include<string.h>

struct Jucator {
	int numarJucator;
	char* numeJucator;
	float pretJucator;
};

struct Jucator citire_jucator(FILE* fisier) {
	struct Jucator jucator;

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

void afisareJucator(struct Jucator jucator) {
	printf("\nNumar: %d", jucator.numarJucator);
	printf("\nNume: %s", jucator.numeJucator);
	printf("\nPret: %0.2f", jucator.pretJucator);
}

void citire_vector(FILE* fisier, int* dimensiune, int** v) {
	if (fisier != NULL) {
		fscanf(fisier, "%d", dimensiune);
		*v = (int*)malloc((*dimensiune) * sizeof(int));
		for (int i = 0; i < (*dimensiune); i++)
		{
			fscanf(fisier, "%d", (*v) + i);
		}
	}
}

int main() {
	/*FILE* streamFisier = NULL;
	streamFisier = fopen("fisier_1.txt", "r");
	//fopen_s(&streamFisier, "fisier_1.txt", "r");

	int var1, var2;

	if (streamFisier != NULL) {
		fscanf(streamFisier, "%d", &var1);
		fscanf(streamFisier, "%d", &var2);
	}
	else {
		printf("Fisierul nu exista\n");
	}

	fclose(streamFisier);

	printf("Var1 = %d\nVar2 = %d\n", var1, var2);*/

	int dimensiune;
	int* v;
	FILE* streamFisier2 = NULL;
	streamFisier2 = fopen("fisier_2.txt", "r");
	citire_vector(streamFisier2, &dimensiune, &v);
	for (int i = 0; i < dimensiune; i++)
		printf("%d ", v[i]);
	fclose(streamFisier2);

	FILE* streamFisier3 = NULL;
	streamFisier3 = fopen("fisier_3.txt", "r");
	struct Jucator mijlocas = citire_jucator(streamFisier3);
	afisareJucator(mijlocas);
	
	//dezalocare memorie

	return 0;
}