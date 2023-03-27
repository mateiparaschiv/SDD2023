#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Nod Nod;
typedef struct Cofetarie Cofetarie;
typedef struct ListaDubla ListaDubla;

struct Cofetarie {
	char* denumire;
	int* preturi;
	int dim;
};

struct Nod {
	Nod* prev;
	Nod* next;
	Cofetarie info;
};

struct ListaDubla {
	Nod* primulNod;
	Nod* ultimulNod;
};

Cofetarie initializareCofetarie(char* denumire, int* preturi, int dim) {
	Cofetarie c;
	c.denumire = (char*)malloc(sizeof(char) * (strlen(denumire)+1));
	strcpy(c.denumire, denumire);
	c.dim = dim;
	c.preturi = (int*)malloc(sizeof(int) * c.dim);
	for (int i=0; i < c.dim; i++) {
		c.preturi[i] = preturi[i];
	}
	return c;
}

void afisare(Cofetarie c) {
	printf("Denumirea este: %s cu dimesiunea de %d. \n", c.denumire,c.dim);
}

ListaDubla inserareInceput(ListaDubla lista, Cofetarie c)
{
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod) * 1);
	nou->prev = NULL;
	nou->next = lista.primulNod;
	nou->info = c;

	if (lista.primulNod != NULL)
	{
		lista.primulNod->prev = nou;
	}
	else
	{
		lista.ultimulNod = nou;
	}
	lista.primulNod = nou;

	return lista;
}

ListaDubla inserareFinal(ListaDubla lista, Cofetarie c)
{
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod) * 1);
	nou->next = NULL;
	nou->prev = lista.ultimulNod;
	nou->info = c;

	if (lista.ultimulNod != NULL)
	{
		lista.ultimulNod->next = nou;
		lista.ultimulNod = nou;
	}
	else
	{
		lista.primulNod = nou;
		lista.ultimulNod = nou;
	}

	return lista;
}

void afisareListaDubluInlantuita(ListaDubla lista) {
	while (lista.primulNod != NULL) {
		afisare(lista.primulNod->info);
		lista.primulNod=lista.primulNod->next;
	}
}

int main() {
	ListaDubla lista;
	lista.primulNod = NULL;
	lista.ultimulNod = NULL;
	Cofetarie c, c1;

	c = initializareCofetarie("Cofetarie1", NULL, 0);
	lista = inserareInceput(lista, c);
	c1 = initializareCofetarie("Cofetarie2", NULL, 0);
	lista = inserareInceput(lista, c1);

	lista = inserareFinal(lista, initializareCofetarie("Cofetarie3", NULL, 0));

	afisareListaDubluInlantuita(lista);
}