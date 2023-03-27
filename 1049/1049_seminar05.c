#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Avion Avion;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Avion
{
	char* denumire;
	int capacitate;
};

struct Nod
{
	Avion info;
	Nod* prev;
	Nod* next;
};

struct ListaDubla
{
	Nod* prim;
	Nod* ultim;
};

Avion initAvion(char* denumire, int capacitate)
{
	Avion a;
	a.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(a.denumire, denumire);
	a.capacitate = capacitate;
	return a;
}

void afisAvion(Avion a)
{
	printf("Avionul %s cu capacitatea: %d\n", a.denumire, a.capacitate);
}

void inserareLaInceput(Avion a, ListaDubla* lista)
{
	Nod* n;
	n = (Nod*)malloc(sizeof(Nod) * 1);

	n->prev = NULL;
	n->info = a;
	n->next = lista->prim;

	if (lista->prim)
	{
		lista->prim->prev = n;
		lista->prim = n;
	}
	else {
		lista->prim = lista->ultim=n;
	}
}

void inserareSfarsit(Avion a, ListaDubla* lista) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = a;
	nou->next = NULL;
	nou->prev = lista->ultim;
	if (lista->ultim != NULL) {
		lista->ultim->next = nou;
		lista->ultim = nou;
	}
	else {
		lista->prim = nou;
		lista->ultim = nou;
	}
}


void afisareLista(ListaDubla lista) {
	while (lista.prim != NULL)
	{	
		afisAvion(lista.prim->info);
		lista.prim = lista.prim->next;
	}
}

void afisareListaCirculara(ListaDubla lista) {
	Nod* aux = lista.prim;
	do {
		afisAvion(aux->info);
		aux = aux->next;
	} while (aux != lista.prim);	
}

void stergereLista(ListaDubla* lista)
{
	Nod* aux=lista->ultim;
	while (aux != NULL)
	{
		free(aux->info.denumire);
		aux = aux->prev;
		if (aux!=NULL)
		{
			free(aux->next);
		}
	}
	free(lista->prim);
	lista->prim = NULL;
	lista->ultim = NULL;
}

void conversie(ListaDubla lista, int* pozVect, Avion** vectAvioane)
{
	Nod* aux = lista.prim;
	while (aux)
	{
		(*vectAvioane)[*pozVect] = initAvion(aux->info.denumire, aux->info.capacitate);
		(*pozVect)++;
		aux = aux->next;
	}
}

int main()
{
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	inserareLaInceput(initAvion("Boeing", 500), &lista);
	inserareLaInceput(initAvion("Boeing 1", 530), &lista);
	inserareLaInceput(initAvion("Boeing 2", 400), &lista);

	inserareSfarsit(initAvion("TAROM1", 120), &lista);
	inserareSfarsit(initAvion("TAROM2", 190), &lista);
	inserareSfarsit(initAvion("TAROM3", 150), &lista);

	afisareLista(lista);

	/*lista.prim->prev = lista.ultim;
	lista.ultim->next = lista.prim;
	printf("Afisare lista\n");
	afisareListaCirculara(lista);*/

	int nrAvioane = 6;
	Avion* vectAvioane = (Avion*)malloc(sizeof(Avion) * nrAvioane);

	int pozVect = 0;
	conversie(lista, &pozVect, &vectAvioane);

	printf("Afisare vector:\n");
	for (int i = 0; i < pozVect; i++)
	{
		afisAvion(vectAvioane[i]);
		free(vectAvioane[i].denumire);
	}
	free(vectAvioane);

	stergereLista(&lista);
}