#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Facultate Facultate;
struct Facultate {
	char* denumire;
	int nrStudenti;
};

typedef struct Nod Nod;
struct Nod {
	Facultate info;
	Nod* next;
};

typedef struct HashTable HashTable;
struct HashTable {
	int dimensiune;
	Nod** vectorHashTable;
};

Facultate initializareFacultate(const char* denumire, int nrStudenti) {
	Facultate facultate;

	facultate.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(facultate.denumire, denumire);

	facultate.nrStudenti = nrStudenti;
	return facultate;
}

void afisareFacultate(Facultate facultate) {
	printf("Facultatea cu numele %s are %d nr de studenti \n ", facultate.denumire, facultate.nrStudenti);
}

int hashFunction(char* denumire, int dimensiuneVector) {
	int nrCaractere = strlen(denumire);
	int pos = nrCaractere % dimensiuneVector;
	return pos;
}

HashTable initializeazaHashTable(int dimensiune) {
	HashTable tabela;
	tabela.dimensiune = dimensiune;
	tabela.vectorHashTable = (Nod **) malloc(sizeof(Nod*)*dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		tabela.vectorHashTable[i] = NULL;
	}
	return tabela;
}

void inserareListaLaFinal(Nod** cap, Facultate f)
{
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));
	nou->info = f;
	nou->next = NULL;
	if ((*cap) == NULL)
	{
		*cap = nou;
	}
	else
	{
		Nod* aux = *cap;
		while ((aux)->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
}

void inserareHashTable(HashTable tabela, Facultate f) {
	if (tabela.dimensiune > 0) {
		int poz = hashFunction(f.denumire, tabela.dimensiune);
		if (poz >= 0 && poz < tabela.dimensiune) {
			inserareListaLaFinal(&(tabela.vectorHashTable[poz]), f);
		}
	}	
}

void afisHashTable(HashTable tabela)
{
	for (int i = 0; i < tabela.dimensiune; i++)
	{
		if (tabela.vectorHashTable[i] != NULL)
		{
			while (tabela.vectorHashTable[i])
			{
				printf("Pozitia %d in hashTable= \n", i);
				afisareFacultate(tabela.vectorHashTable[i]->info);//am afisat facultatea
				tabela.vectorHashTable[i] = tabela.vectorHashTable[i]->next;
			}
		}
		else
			printf("Pozitia %d este goala\n", i);
	}
}

int main() {
	HashTable myTable = initializeazaHashTable(5);

	inserareHashTable(myTable, initializareFacultate("CSIE", 10000));
	inserareHashTable(myTable, initializareFacultate("FABIZ", 20000));
	inserareHashTable(myTable, initializareFacultate("MARK", 30000));
	inserareHashTable(myTable, initializareFacultate("ECO", 40000));
	inserareHashTable(myTable, initializareFacultate("MNG", 40000));

	afisHashTable(myTable);

}