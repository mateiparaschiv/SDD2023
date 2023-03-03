#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct Parc
{
	char* nume;
	int nrCopaci;
	float suprafata;
};

void afisareParc(struct Parc p)
{
	printf("%s %d %.2f ", p.nume, p.nrCopaci, p.suprafata);
}

void citireParc(struct Parc* p, const char* numefisier)
{
	char buffer[30];
	FILE* f = NULL;
	f = fopen(numefisier, "r");
	if (f != NULL)
	{
		fgets(buffer, 30, f);
		char* nume = strtok(buffer, "\n");
		p->nume = (char*)malloc(sizeof(char) *
			(strlen(nume) + 1));
		strcpy(p->nume, nume);
		fgets(buffer, 12, f);
		p->nrCopaci = atoi(buffer);
		fgets(buffer, 13, f);
		p->suprafata = atof(buffer);
		fclose(f);
	}
	else
	{
		printf("Nu s-a deschis fisierul");
	}

}

void citireVector(int* dim, int** v, char* numefisier) {
	FILE* f = NULL;
	f = fopen(numefisier, "r");
	if (f != NULL)
	{
		fscanf(f, "%d", dim);
		*v = (int*)malloc(sizeof(int) * (*dim));
		for (int i = 0; i < *dim; i++) {
			fscanf(f, "%d", &((*v)[i]));
			//fscanf(f, "%d", (*v)+i);
		}
		fclose(f);
	}
	else
	{
		printf("Nu s-a deschis fisierul");
	}
}

int main() {
	int nr1;
	int nr2;
	FILE* f = NULL;
	f = fopen("fisier.txt", "r");
	if (f != NULL)
	{
		fscanf(f, "%d", &nr1);
		fscanf(f, "%d", &nr2);
		printf("%d %d", nr1, nr2);
		fclose(f);
	}
	else
	{
		printf("Nu s-a deschis fisierul");
	}

	int dim;
	int* v;
	citireVector(&dim, &v, "vector.txt");
	for (int i = 0; i < dim; i++) {
		printf("\n %d ", v[i]);
	}

	struct Parc p;
	citireParc(&p, "Text.txt");
	afisareParc(p);

	free(p.nume);
	free(v);

	return 0;
}
