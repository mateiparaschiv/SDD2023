#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Avion Avion;
typedef struct Nod Nod;
typedef struct LD LD;

struct Avion {
	char* denumire;
	int capacitate;
};

struct Nod {
	Avion info;
	Nod* prev;
	Nod* next;
};

struct LD {
	Nod* prim;
	Nod* ultim;
};

Avion initializareAvion(char* denumire, int capacitate) {
	Avion a;
	a.capacitate = capacitate;
	a.denumire = (char*)malloc(sizeof(char) *
		(strlen(denumire) + 1));
	strcpy(a.denumire, denumire);
	return a;
}

void afisareAvion(Avion a) {
	printf("Avionul %s are capacitatea %d. \n", a.denumire, a.capacitate);
}

void inserareInceput(LD* lista, Avion a) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->prev = NULL;
	nou->next = lista->prim;
	nou->info = a;

	if (lista->prim) {
		lista->prim->prev = nou;
		lista->prim = nou;
	}
	else {
		lista->prim = nou;
		lista->ultim = nou;
	}
}

void inserareFinal(LD* lista, Avion a) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->prev = lista->ultim;
	nou->next = NULL;
	nou->info = a;

	if (lista->ultim) {
		lista->ultim->next = nou;
		lista->ultim = nou;
	}
	else {
		lista->ultim = nou;
		lista->prim = nou;
	}
}

void afisareStangaDreapta(LD lista) {
	//Nod* aux = lista.prim;
	while (lista.prim) {
		afisareAvion(lista.prim->info);
		lista.prim = lista.prim->next;
	}
}

void afisareListaCircularaSTG_DR(LD lista) {
	do {
		afisareAvion(lista.prim->info);
		lista.prim = lista.prim->next;
	} while (lista.prim != lista.ultim);
	afisareAvion(lista.prim->info);
}

void afisareListaCircularaSTG_DR2(LD lista) {
	while (lista.prim != lista.ultim){
		afisareAvion(lista.prim->info);
	lista.prim = lista.prim->next;
}
	afisareAvion(lista.prim->info);
}

void dezalocare(LD* lista) {
	Nod* aux;
	aux = lista->ultim;
	while(aux){
		free(aux->info.denumire);
		aux = aux->prev;
		if(aux){
			free(aux->next);
		}
	}
	free(lista->prim);
	lista->prim = NULL;
	lista->ultim = NULL;
}

void conversieListaInVector(Avion** vector, LD lista, int* poz) {
	while (lista.prim) {
		(*vector)[*poz] = initializareAvion(lista.prim->info.denumire, lista.prim->info.capacitate);
		(*poz)++;
		lista.prim = lista.prim->next;
	}
}

void main() {
	LD lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	inserareInceput(&lista, initializareAvion("Romatsa", 120));
	inserareInceput(&lista, initializareAvion("Lufthansa", 200));
	inserareInceput(&lista, initializareAvion("Tarom", 150));

	inserareFinal(&lista, initializareAvion("Mirakaluma", 100));
	inserareFinal(&lista, initializareAvion("Albasug", 150));

	afisareStangaDreapta(lista);
	//TEMA: afisare dreapta-stanga

	//Lista circulara
	/*lista.prim->prev = lista.ultim;
	lista.ultim->next = lista.prim;
	printf("\nAfisare lista circulara\n");
	afisareListaCircularaSTG_DR2(lista);*/

	int nr_avioane = 5;
	Avion* vector = (Avion*)malloc(sizeof(Avion) * nr_avioane);
	//TEMA: de calculat numarul de avioane din lista
	int poz = 0;
	conversieListaInVector(&vector,lista,&poz);
	printf("\nAfisare vector\n");
	for (int i = 0; i < poz; i++) {
		afisareAvion(vector[i]);
		free(vector[i].denumire);
	}
	free(vector);

	dezalocare(&lista);
}
