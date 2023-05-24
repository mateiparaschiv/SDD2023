#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>
#include<string.h>

typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;
typedef struct Cofetarie Cofetarie;

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

struct Cofetarie {
	int id;
	char* nume;
};

struct NodPrincipal {
	Cofetarie info;
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

Cofetarie initCofetarie(int id, const char* nume)
{
	Cofetarie cofetarie;
	cofetarie.id = id;
	cofetarie.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(cofetarie.nume, nume);

	return cofetarie;
}

void inserareListaPrincipala(NodPrincipal** cap, Cofetarie cofetarie) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = cofetarie;
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

void afisareCofetarie(Cofetarie c) {
	printf("\nCofetaria %s are id-ul %d.", c.nume, c.id);
}

void parcurgereLista(NodPrincipal* np) {
	while (np) {
		afisareCofetarie(np->info);
		NodSecundar* aux = np->vecini;
		printf("\nVecini: ");
		while (aux) {
			afisareCofetarie(aux->info->info);
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

void main() {

}