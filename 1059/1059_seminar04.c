#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Avion Avion;
typedef struct Nod Nod;

struct Avion {
	char* denumire;
	int capacitate;
};

struct Nod {
	Avion info;
	Nod* next;
};

Avion creareAvion(const char* denumire, int capacitate) {
	Avion a;
	a.capacitate = capacitate;
	a.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(a.denumire, denumire);
	return a;
}

void inserareInceput(Nod** cap, Avion _avion) {
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));
	nou->info = _avion; // shallow copy util, salvam o copie a lui avion
	nou->next = *cap;
	*cap = nou;
}

void afisare(Avion a) {
	printf("%d, %s", a.capacitate, a.denumire);
}

void afisareLista(Nod* cap) {
	if (cap == NULL) {
		printf("Nu exista elemente in lista");
	}
	else {
		while (cap != NULL) {
			afisare(cap->info);
			cap = cap->next;
			printf("\n");
		}
	}
}

void inserareFinal(Nod** cap, Avion a) {
	Nod* aux = *cap;
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->info = a;
	if (*cap) {
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*cap = nou;
	}
}

void dezalocareLista(Nod** cap) {
	while (*cap != NULL) {
		Nod* auxiliar = *cap;

		free((*cap)->info.denumire);
		*cap = (*cap)->next;
		free(auxiliar);
	}
}

void afisareSimplaLista(Nod* cap) {
	while (cap != NULL) {
		afisare(cap->info);
		cap = cap->next;
		printf("\n");
	}
}

void main() {
	Nod* cap = NULL;
	inserareInceput(&cap, creareAvion("numeAvion", 100));
	inserareInceput(&cap, creareAvion("avionulMeu", 20));
	inserareInceput(&cap, creareAvion("altAvion", 150));

	afisareLista(cap);

	inserareFinal(&cap, creareAvion("avion1", 25));
	inserareFinal(&cap, creareAvion("avion2", 75));
	inserareFinal(&cap, creareAvion("avion3", 130));

	afisareLista(cap);

	dezalocareLista(&cap);

	afisareLista(cap);
	afisareSimplaLista(cap);
}