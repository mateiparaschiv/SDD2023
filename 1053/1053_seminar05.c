#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Elev Elev;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Elev 
{
	char* nume;
	int varsta;
};

struct Nod
{
	Elev info;
	Nod* next;
	Nod* prev;
};

struct ListaDubla
{
	Nod* prim;
	Nod* ultim;
};

void afisareElev(Elev e)
{
	printf("Elevul cu numele %s are varsta de %d\n"
		, e.nume, e.varsta);
}

Elev initializareElev(char* nume, int varsta)
{
	Elev e;
	e.nume = (char*)malloc(sizeof(char) 
		* (strlen(nume) + 1));
	strcpy(e.nume, nume);
	e.varsta = varsta;
	return e;
}

void inserareInceput(ListaDubla* lista, Elev e) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = e;
	nou->prev = NULL;
	nou->next = lista->prim;

	if (lista->prim) {
		lista->prim->prev = nou;	
	}
	else {
		 lista->ultim = nou;
	}
	lista->prim = nou;
}

void inserareFinal(ListaDubla* lista, Elev e) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = e;
	nou->prev = lista->ultim;
	nou->next = NULL;
	if (lista->ultim)lista->ultim->next = nou;
	else lista->prim = nou;
	lista->ultim = nou;
}

void AfisareNoduri(ListaDubla lista) {
	while (lista.prim != NULL) {
		afisareElev(lista.prim->info);
		lista.prim = lista.prim->next;
	}
}

void AfisareNoduriCirc(ListaDubla lista) {
	Nod* aux = lista.prim; 
	do {
		afisareElev(aux->info);
		aux = aux->next;
	} while (aux != lista.prim);
}

void stergereLista(ListaDubla* lista)
{
	Nod* aux = lista->ultim;
		while (aux != NULL)
		{
			free(aux->info.nume);
			aux = aux->prev;
			if(aux)
			{
				free(aux->next); 
			}
		}
		free(lista->prim);
		lista->prim = NULL;
		lista->ultim = NULL;
}

void main()
{
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	inserareInceput(&lista, initializareElev("Ion", 12));
	inserareInceput(&lista, initializareElev("Maria", 122));
	inserareFinal(&lista, initializareElev("Ana", 32));
	inserareFinal(&lista, initializareElev("Mihai", 19));
	inserareFinal(&lista, initializareElev("Cornel", 20));
	AfisareNoduri(lista);
	stergereLista(&lista);

	//lista.prim->prev = lista.ultim;
	//lista.ultim->next = lista.prim;
	//printf("\n\n");
	//AfisareNoduriCirc(lista);
}