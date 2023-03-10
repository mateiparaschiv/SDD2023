#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
typedef struct Parc Parc;
struct Parc
{
	char* nume;
	int nrCopaci;
	float suprafata;
};

void afisareParc(Parc p)
{
	printf("%s %d %.2f ", p.nume, p.nrCopaci, p.suprafata);
}

void citireParc(Parc* p,FILE* fisier)
{
	char buffer[30];
	if (fisier != NULL)
	{
		fgets(buffer, 30, fisier);
		char* nume = strtok(buffer, "\n");
		p->nume = (char*)malloc(sizeof(char) *
			(strlen(nume) + 1));
		strcpy(p->nume, nume);
		fgets(buffer, 12, fisier);
		p->nrCopaci = atoi(buffer);
		fgets(buffer, 13, fisier);
		p->suprafata = atof(buffer);
	}
	else
	{
		printf("Nu s-a deschis fisierul");
	}

}
void citireParcuri(int *nr,Parc **vectorP,FILE *f)
{
	if (f)
	{
		char buffer[20];
		fgets(buffer,20,f);
		*nr = atoi(buffer);
		*vectorP = (Parc*)malloc(sizeof(Parc) * (*nr));
		for (int i = 0; i < *nr; i++)
			citireParc(&((*vectorP)[i]), f);
	}
}

void citireMatParcuri(int** nrParcuriLinie, Parc*** matriceParcuri, int* nrLinii, FILE* f) {
	if (f) {
		char buffer[10];
		fgets(buffer, 10, f);
		*nrLinii = atoi(buffer);
		*nrParcuriLinie = (int*)malloc(sizeof(int) * (*nrLinii));
		*matriceParcuri = (Parc**)malloc(sizeof(Parc*) * (*nrLinii));
		for (int i = 0; i < *nrLinii; i++)
		{
			citireParcuri((*nrParcuriLinie) + i, &((*matriceParcuri)[i]), f);
		}
	}
}

void afisareMatr(int* nrParcuriLinie, Parc * *matriceParcuri, int nrLinii) {
		for (int i = 0; i < nrLinii; i++) {
			for (int j = 0; j < nrParcuriLinie[i]; j++) {
				printf("\n");
				afisareParc(matriceParcuri[i][j]);
			}
		}
}

void dezalocare(int** nrParcuriLinie, Parc*** matriceParcuri, int* nrLinii)
	{
		for (int i = 0; i < (*nrLinii); i++)
		{
			for (int j = 0; j < (*nrParcuriLinie)[i]; j++)
			{
				free((*matriceParcuri)[i][j].nume);
			}
			free((*matriceParcuri)[i]);
		}
		
		free(*matriceParcuri);
		free(*nrParcuriLinie);
		
		*matriceParcuri = NULL;
		*nrParcuriLinie = NULL;

		*nrLinii = 0;
		
}

int main() 
{
	FILE* f = NULL;
	f = fopen("Matrice.txt","r");
	if (f != NULL) {
		int* nrParcuriLinie;
		Parc** matriceParcuri;
		int nrLinii;
		citireMatParcuri(&nrParcuriLinie,&matriceParcuri,&nrLinii,f);
		afisareMatr(nrParcuriLinie,matriceParcuri,nrLinii);
		dezalocare(&nrParcuriLinie, &matriceParcuri, &nrLinii);
		fclose(f);
	}
	
	return 0;
}