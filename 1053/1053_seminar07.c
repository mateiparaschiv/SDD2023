#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>
#include<string.h>

typedef struct Farfurie Farfurie;
typedef struct Nod Nod;
typedef struct HasTable HasTable;

struct Farfurie {
	long id;
	char* culoare;
	float pret;
};

struct Nod {
	Farfurie info;
	Nod* next;
};

struct HasTable{
	int dim;
	Nod** vector;
};

Farfurie initFarfurie(long id, const char* culoare, float pret) {
	Farfurie f;
	f.culoare = (char*)malloc(sizeof(char) * (strlen(culoare) + 1));
	strcpy(f.culoare, culoare);
	f.id = id;
	f.pret = pret;
	return f;
}

void afisareFarfurie(Farfurie f) {
	printf("Farfuria cu id-ul %ld si culoarea %s are pretul %.2f\n", f.id, f.culoare, f.pret);
}

HasTable initializare(int dim) {
	HasTable h;
	h.dim = dim;
	h.vector = (Nod**)malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < dim; i++)
		h.vector[i] = NULL;
	return h;
}

int FunctieHas(long id, int dim)
{
	return id % dim;
}

void inserareFinal(Nod** cap, Farfurie f)
{
	Nod* nou= (Nod*)malloc(sizeof(Nod));
	nou->info = f;
	nou->next = NULL;

	if (!(*cap))
	{
		(*cap) = nou;
	}
	else
	{
		Nod* aux = *cap;
		while (aux->next)
		{
			aux = aux->next;

		}
		aux->next = nou;
	}
}

void inserareInHasTable(HasTable h, Farfurie f) {
	if (h.dim > 0) {
		int pozitie = FunctieHas(f.id, h.dim);
		if (pozitie >= 0 && pozitie < h.dim) {
			inserareFinal(&(h.vector[pozitie]), f);
		}
	}
}

void traversareHashTable(HasTable h) {
	for (int i = 0; i < h.dim; i++) {
		if(h.vector[i] == NULL){
			printf("Pozitie goala in HashTable %d\n", i);
		}
		else {
			Nod* aux = h.vector[i];
			printf("Pozitie in HashTable %d\n", i);
			while (aux) {
				afisareFarfurie(aux->info);
				aux = aux->next;
			}
		}
	}
}

void main() {
	HasTable h;
	h = initializare(7);
	inserareInHasTable(h, initFarfurie(120, "Verde", 20.5));
	inserareInHasTable(h, initFarfurie(127, "Verde", 20.5));
	inserareInHasTable(h, initFarfurie(121, "Verde", 20.5));
	inserareInHasTable(h, initFarfurie(128, "Verde", 20.5));
	inserareInHasTable(h, initFarfurie(130, "Verde", 20.5));

	traversareHashTable(h);
}