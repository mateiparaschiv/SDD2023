#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Caine Caine;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Caine {
	char* rasa;
	int varsta;
};

struct Nod {
	Caine info;
	Nod* next;
};

struct HashTable {
	int nrElemente;
	Nod** vector;
};

Caine creareCaine(char* nume, int varsta) {
	Caine caine;
	caine.rasa = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(caine.rasa, nume);
	caine.varsta = varsta;
	return caine;
}

void afisareCaine(Caine caine) {
	printf("\nCainele de rasa %s are varsta %d", caine.rasa, caine.varsta);
}

int functieHash(char* rasa,int nrElemente) {
	return strlen(rasa) % nrElemente;
}

void initializareHashTable(HashTable* tabela, int nrElemente) {
	(*tabela).nrElemente = nrElemente;
	(*tabela).vector = (Nod**)malloc(sizeof(Nod*) * nrElemente);
	for (int i = 0; i < nrElemente; i++) {
		(*tabela).vector[i] = NULL;
	}
}

void inserareFinal(Nod** cap, Caine a)
{
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->info = a;
	if (*cap)
	{
		Nod* aux = *cap;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*cap = nou;
	}
}

void inserareinHashTable(HashTable tabela, Caine a) {
	if (tabela.nrElemente > 0) {
		int pozitie = functieHash(a.rasa, tabela.nrElemente);
		if (pozitie>=0 && pozitie < tabela.nrElemente) {
			inserareFinal(&(tabela.vector[pozitie]), a);
		}
	}
}

void afisareHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.nrElemente; i++){
		if(tabela.vector[i] != NULL){
			Nod* aux = tabela.vector[i];
			while (aux) {
				printf("\nPozitia este: %d", i);
				afisareCaine(aux->info);
				aux = aux->next;
			}
		}
		else {
			printf("\nPozitia %d este goala.", i);
		}
	}
}

int main() {
	int nrElemente = 6;
	HashTable tabela;
	initializareHashTable(&tabela, nrElemente);
	inserareinHashTable(tabela, creareCaine("Labrador", 10));
	inserareinHashTable(tabela, creareCaine("Cane Corso", 12));
	inserareinHashTable(tabela, creareCaine("Labrador", 8));
	inserareinHashTable(tabela, creareCaine("Husky", 15));

	afisareHashTable(tabela);
}