#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>
#include<string.h>

typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;
typedef struct Masina Masina;

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

struct Masina {
	int id;
	char* marca;
};

struct NodPrincipal {
	Masina info;
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

Masina initMasina(int id, const char* marca)
{
	Masina masina;
	masina.id = id;
	masina.marca = (char*)malloc(strlen(marca) + 1);
	strcpy(masina.marca, marca);

	return masina;
}

void inserareListaPrincipala(NodPrincipal** cap, Masina masina) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = masina;
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

void afisareMasina(Masina m) {
	printf("\nMasina %s are id-ul %d.", m.marca, m.id);
}

void parcurgereLista(NodPrincipal* np) {
	while (np) {
		afisareMasina(np->info);
		NodSecundar* aux = np->vecini;
		printf("\nVecini: ");
		while (aux) {
			afisareMasina(aux->info->info);
			aux = aux->next;
		}
		printf("\n");
		np = np->next;
	}
}

NodPrincipal* cautareNod(NodPrincipal* nod, int id)
{
	while (nod && nod->info.id != id)
	{
		nod = nod->next;
	}
	return nod;
}

void inserareVecini(NodPrincipal* nod, int id1, int id2)
{
	NodPrincipal* nod1 = cautareNod(nod, id1);
	NodPrincipal* nod2 = cautareNod(nod, id2);
	if (nod1 != NULL && nod2 != NULL)
	{
		inserareListaSecundara(&nod1->vecini, nod2);
		inserareListaSecundara(&nod2->vecini, nod1);
	}
}

int getNumarNoduri(NodPrincipal* graf) {
	int nr = 0;
	while (graf) {
		nr++;
		graf = graf->next;
	}
	return nr;
}

void parcurgereInAdancime(NodPrincipal* graf, int id)
{
	int nr_noduri = getNumarNoduri(graf);
	int* vizitate = (int*)malloc(sizeof(int) * nr_noduri);
	for (int i = 0; i < nr_noduri; i++)
	{
		vizitate[i] = 0;
	}
	ListaDubla stiva;
	stiva.first = NULL;
	stiva.last = NULL;
	push(&stiva, id);
	vizitate[id - 1] = 1;
	while (stiva.first)
	{
		int id_scos = pop(&stiva);
		NodPrincipal* nod_curent = cautareNod(graf, id_scos);
		afisareMasina(nod_curent->info);
		NodSecundar* vecini = nod_curent->vecini;
		while (vecini)
		{
			if (vizitate[vecini->info->info.id - 1] == 0)
			{
				push(&stiva, vecini->info->info.id);
				vizitate[vecini->info->info.id - 1] = 1;
			}
			vecini = vecini->next;
		}
	}
}

void main() {
	NodPrincipal* graf = NULL;
	inserareListaPrincipala(&graf, initMasina(1, "Dacia"));
	inserareListaPrincipala(&graf, initMasina(2, "Audi"));
	inserareListaPrincipala(&graf, initMasina(3, "Golf"));
	inserareListaPrincipala(&graf, initMasina(4, "Renault"));
	inserareListaPrincipala(&graf, initMasina(5, "Mercedes"));

	inserareVecini(graf, 1, 4);
	inserareVecini(graf, 2, 4);
	inserareVecini(graf, 2, 5);
	inserareVecini(graf, 3, 5);

	parcurgereLista(graf);

	printf("\n Parcurgere in adancime:");
	parcurgereInAdancime(graf, 1);
}