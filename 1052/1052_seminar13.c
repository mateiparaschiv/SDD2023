#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>
#include<string.h>

typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;
typedef struct Produs Produs;

typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Nod {
	int ID;
	Nod* next;
	Nod* prev;
};

struct ListaDubla {
	Nod* first;
	Nod* last;
};

struct Produs {
	int id;
	char* denumire;
};

struct NodPrincipal {
	Produs info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar {
	NodPrincipal* info;
	NodSecundar* next;
};

void push(ListaDubla* ld, int ID) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = ld->first;
	nou->prev = NULL;
	nou->ID = ID;

	if (ld->first == NULL) {
		ld->first = ld->last = nou;
	}
	else {
		ld->first->prev = nou;
		ld->first = nou;
	}
}

void put(ListaDubla* ld, int ID) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->prev = ld->last;
	nou->ID = ID;

	if (ld->last == NULL) {
		ld->first = ld->last = nou;
	}
	else {
		ld->last->next = nou;
		ld->last = nou;
	}
}

int pop(ListaDubla* ld) {
	int ID = -1;
	if (ld->first) {
		ID = ld->first->ID;
		Nod* aux = ld->first;
		ld->first = ld->first->next;
		if (ld->first == NULL) {
			ld->last = NULL;
		}
		free(aux);
	}
	return ID;
}

Produs initProdus(int id, const char* denumire)
{
	Produs produs;
	produs.id = id;
	produs.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(produs.denumire, denumire);

	return produs;
}

void inserareListaPrincipala(NodPrincipal** cap, Produs produs) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = produs;
	nou->next = NULL;
	nou->vecini = NULL;
	NodPrincipal* aux = *cap;
	if (*cap) {
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*cap = nou;
	}
}

void inserareListaSecundara(NodSecundar** cap, NodPrincipal* info)
{
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->info = info;
	nou->next = NULL;
	if (*cap)
	{
		NodSecundar* aux = *cap;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
	else
	{
		*cap = nou;
	}
}

void afisareProdus(Produs p) {
	printf("\nProdusul %s cu id-ul %d.", p.denumire, p.id);
}

NodPrincipal* cautareNodId(NodPrincipal* graf, int id) {
	while (graf && id != graf->info.id)
	{
		graf = graf->next;
	}
	return graf;
}

void inserareMuchie(int id1, int id2, NodPrincipal* graf)
{
	NodPrincipal* nod1 = cautareNodId(graf, id1);
	NodPrincipal* nod2 = cautareNodId(graf, id2);
	if (nod1 != NULL && nod2 != NULL)
	{
		inserareListaSecundara(&(nod2->vecini), nod1);
		inserareListaSecundara(&(nod1->vecini), nod2);
	}
}

void parcurgere(NodPrincipal* graf)
{
	while (graf != NULL)
	{
		afisareProdus(graf->info);
		NodSecundar* vecini = graf->vecini;
		printf("\nVecini:");
		while (vecini!=NULL)
		{
			afisareProdus(vecini->info->info);
			vecini = vecini->next;
		}
		printf("\n");
		graf = graf->next;
	}
}

int count(NodPrincipal*graf)
{
	int nrNoduri = 0;
	while (graf)
	{
		nrNoduri++;
		graf = graf->next;
	}
	return nrNoduri;
}

void parcurgereInLatime(NodPrincipal* graf, int idStart)
{
	ListaDubla coada;
	coada.first = NULL;
	coada.last = NULL;
	int nrNoduri = count(graf);
	int* vizitate = (int*)malloc(sizeof(int)*nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
	{
		vizitate[i] = 0;
	}
	put(&coada, idStart);
	vizitate[idStart - 1] = 1;
	while (coada.first)
	{
		int idCautat=pop(&coada);
		NodPrincipal* nodCrt = cautareNodId(graf, idCautat);
		afisareProdus(nodCrt->info);
		NodSecundar* vecini = nodCrt->vecini;
		while (vecini) 
		{
			if (vizitate[vecini->info->info.id - 1] == 0)
			{
				put(&coada, vecini->info->info.id);
				vizitate[vecini->info->info.id - 1] = 1;
			}
			vecini = vecini->next;
		}
	}
}

void main() {
	NodPrincipal* graf = NULL;
	inserareListaPrincipala(&graf, initProdus(1, "Apa"));
	inserareListaPrincipala(&graf, initProdus(2, "Suc"));
	inserareListaPrincipala(&graf, initProdus(3, "Fructe"));
	inserareListaPrincipala(&graf, initProdus(4, "Legume"));
	inserareListaPrincipala(&graf, initProdus(5, "Cola"));
	inserareListaPrincipala(&graf, initProdus(6, "Guma"));

	inserareMuchie(1, 3, graf);
	inserareMuchie(1, 4, graf);
	inserareMuchie(1, 5, graf);
	inserareMuchie(2, 4, graf);
	inserareMuchie(2, 5, graf);
	inserareMuchie(3, 4, graf);
	inserareMuchie(3, 6, graf);
	inserareMuchie(4, 6, graf);

	parcurgere(graf);

	printf("\nAfisare in latime: ");
	parcurgereInLatime(graf, 1);
}