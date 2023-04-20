#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Nod Nod;
typedef struct Biblioteca Biblioteca;
typedef struct HashTable HashTable;

struct Biblioteca
{
	long id;
	char* nume;
	int nrCarti;
};

struct Nod
{
	Biblioteca info;
	Nod* next;
};

struct HashTable {
	int dim;
	Nod** vector;
};

Biblioteca initializeazaBib(long id, char* nume, int nrCarti)
{
	Biblioteca b;
	b.id = id;
	b.nrCarti = nrCarti;
	b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	return b;
}

void afisareBib(Biblioteca b)
{
	printf("Biblioteca %s are id-ul %ld si %i carti\n", b.nume, b.id, b.nrCarti);
}

HashTable initializareHashTable(int dim) {
	HashTable h;
	h.dim = dim;
	h.vector = (Nod**)malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < dim; i++) {
		h.vector[i] = NULL;
	}
	return h;
}
int Hash(int dim, long id) {
	return id % dim;
	//return strlen(denumire) % dim;
}

void inserareFinal(Nod** cap, Biblioteca b)
{
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));
	nou->info = b;
	nou->next = NULL;
	if (*cap != NULL)
	{
		Nod* aux = *cap;
		while (aux->next)
			aux = aux->next;
		aux->next = nou;
	}
	else
		*cap = nou;
}

void inserareHashTable(Biblioteca b, HashTable tabelaH) {
	if (tabelaH.dim > 0) {	
		int pozitie = Hash(tabelaH.dim,b.id);
		if (pozitie >= 0 && pozitie < tabelaH.dim) {
			inserareFinal(&(tabelaH.vector[pozitie]),b);
		}
	}
}

void afisareHashtable(HashTable h) {
	for (int i = 0; i < h.dim; i++) {
		if (h.vector[i] != NULL) {
			printf("pozitia din tabel %d\n", i);
			while (h.vector[i]) {
				afisareBib(h.vector[i]->info);
				h.vector[i] = h.vector[i]->next;
			}
		}
		else {
			printf("pozitia %d este goala\n", i);
		}
	}
}

void main() {
	HashTable h = initializareHashTable(5);
	inserareHashTable(initializeazaBib(123, "Bib1", 130), h);
	inserareHashTable(initializeazaBib(128, "Bib2", 130), h);
	inserareHashTable(initializeazaBib(125, "Bib3", 130), h);
	inserareHashTable(initializeazaBib(228, "Bib4", 130), h);
	afisareHashtable(h);

}