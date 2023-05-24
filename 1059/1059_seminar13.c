#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>
#include<string.h>

typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;
typedef struct Autostrada Autostrada;

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

struct Autostrada {
	int id;
	char* denumire;
	int nrKm;
};

struct NodPrincipal {
	Autostrada info;
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

Autostrada initAutostrada(int id, const char* denumire, int nrKm)
{
	Autostrada autostrada;
	autostrada.id = id;
	autostrada.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(autostrada.denumire, denumire);
	autostrada.nrKm = nrKm;

	return autostrada;
}

void inserareListaPrincipala(NodPrincipal** cap, Autostrada autostrada) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = autostrada;
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

void afisareAutostrada(Autostrada a) {
	printf("\nAutostrada %s cu id-ul %d are %d km", a.denumire, a.id, a.nrKm);
}

NodPrincipal* cautareDupaID(NodPrincipal* graf, int id)
{
	while (graf != NULL && id != graf->info.id)
	{
		graf = graf->next;
	}
	return graf;
}

void inserareMuchie(int id1, int id2, NodPrincipal* graf)
{
	NodPrincipal* nod1 = cautareDupaID(graf, id1);
	NodPrincipal* nod2 = cautareDupaID(graf, id2);
	if (nod1 != NULL && nod2 != NULL)
	{
		inserareListaSecundara(&nod1->vecini, nod2);
		inserareListaSecundara(&nod2->vecini, nod1);
	}
}

void parcurgereListadeListe(NodPrincipal* graf) {
	while (graf) {
		afisareAutostrada(graf->info);
		printf("\nVecini:");
		NodSecundar* vecini = graf->vecini;
		while (vecini) {
			afisareAutostrada(vecini->info->info);
			vecini = vecini->next;
		}
		printf("\n");
		graf = graf->next;
	}
}

int calculNrNoduri(NodPrincipal* graf) {
	int nrNoduri = 0;
	while (graf != NULL) {
		nrNoduri++;
		graf = graf->next;
	}
	return nrNoduri;
}

void parcurgereInLatime(NodPrincipal* graf, int idStart) {
	int nrNoduri = calculNrNoduri(graf);
	int* vizitate=(int*)malloc(sizeof(int)*nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	ListaDubla coada;
	coada.first = NULL;
	coada.last = NULL;
	put(&coada, idStart);
	vizitate[idStart - 1] = 1;
	while (coada.first != NULL) {
		int id = pop(&coada);

		NodPrincipal* nodCurent = cautareDupaID(graf, id);
		afisareAutostrada(nodCurent->info);
		NodSecundar* vecini=nodCurent->vecini;
		while (vecini) {
			if (vizitate[vecini->info->info.id - 1] == 0) {
				put(&coada, vecini->info->info.id);
				vizitate[vecini->info->info.id-1] = 1;
			}
			vecini = vecini->next;
		}
	}
}

void main() {
	NodPrincipal *graf = NULL;
	
	inserareListaPrincipala(&graf, initAutostrada(1, "A3", 200));
	inserareListaPrincipala(&graf, initAutostrada(2, "A1", 250));
	inserareListaPrincipala(&graf, initAutostrada(3, "A2", 190));
	inserareListaPrincipala(&graf, initAutostrada(4, "A4", 100));
	inserareListaPrincipala(&graf, initAutostrada(5, "A5", 175));

	inserareMuchie(1, 2, graf);
	inserareMuchie(1, 3, graf);
	inserareMuchie(1, 5, graf);
	inserareMuchie(2, 3, graf);
	inserareMuchie(3, 4, graf);

	parcurgereListadeListe(graf);

	printf("\n");
	parcurgereInLatime(graf, 1);
}