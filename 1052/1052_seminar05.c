#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Masina Masina;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Masina {
	char* marca;
	int pret;
};

struct Nod {
	Nod* prev;
	Masina info;
	Nod* next;
};

struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};

Masina initializareMasina(char* marca, int pret) {
	Masina m;
	m.marca = (char*)malloc(sizeof(char) * (strlen(marca) + 1));
	strcpy(m.marca, marca);

	m.pret = pret;

	return m;
}

void afisareMasina(Masina m) {
	printf("Marca: %s, pret: %d \n", m.marca, m.pret);
}

void inserareLaInceput(Masina m, ListaDubla* ld) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->prev = NULL;
	nou->next = ld->prim;
	nou->info = m;
	if (ld->prim != NULL) {
		ld->prim->prev = nou;
		ld->prim = nou;
	}
	else {
		ld->prim = nou;
		ld->ultim = nou;
	}
}

void inserareLaSfarsit(Masina m, ListaDubla* ld) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->prev = ld->ultim;
	nou->next = NULL;
	nou->info = m;
	if (ld->ultim != NULL) {
		ld->ultim->next = nou;
		ld->ultim = nou;
	}
	else {
		ld->prim = nou;
		ld->ultim = nou;
	}
}

void afisareInceputFinal(ListaDubla ld) {
	while (ld.prim) {
		afisareMasina(ld.prim->info);
		ld.prim = ld.prim->next;
	}
}

void afisareListaCirculara(ListaDubla lista)
{
	Nod* temp = lista.prim;
	do
	{
		afisareMasina(lista.prim->info);
		lista.prim = lista.prim->next;
	} while (lista.prim != temp);
}

void dezalocacareLista(ListaDubla* ld) {
	while (ld->ultim != NULL) {
		free(ld->ultim->info.marca);
		ld->ultim = ld->ultim->prev;
		if (ld->ultim != NULL) {
			free(ld->ultim->next);
		}
	}
	free(ld->prim);
	ld->prim = NULL;
	ld->ultim = NULL;
}

void stergereLaFinal(Nod** ultim)
{
	if (ultim != NULL)
	{
		free((*ultim)->info.marca);
		*ultim =(*ultim)->prev;
		if (*ultim != NULL) {
			free((*ultim)->next);
		}
	}
}

void dezalocare2(ListaDubla* ld)
{
	while (ld->ultim != NULL)
	{
		stergereLaFinal(&ld->ultim);
	}
	free(ld->prim);
	ld->prim = NULL;
	ld->ultim = NULL;
}

void conversieListaInVector(ListaDubla lista, Masina** vector, int* nrMasini)
{
	while (lista.prim)
	{
		(*vector)[(*nrMasini)] = lista.prim->info;
		lista.prim = lista.prim->next;
		(*nrMasini)++;
	}
}

void main() {
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	inserareLaInceput(initializareMasina("BMW", 50000), &lista);
	inserareLaInceput(initializareMasina("Mercedes", 30000), &lista);
	inserareLaInceput(initializareMasina("Dacia", 10000), &lista);
	inserareLaInceput(initializareMasina("WV", 20000), &lista);
	inserareLaSfarsit(initializareMasina("Tesla", 60000), &lista);
	inserareLaSfarsit(initializareMasina("Maybach", 70000), &lista);
	inserareLaSfarsit(initializareMasina("Opel", 80000), &lista);

	afisareInceputFinal(lista);

	Masina* vector = (Masina*)malloc(sizeof(Masina) * 7);
	int nrMasini = 0;
	conversieListaInVector(lista, &vector, &nrMasini);
	printf("\n Afisare vector: ");

	for (int i = 0; i < nrMasini; i++)
	{
		afisareMasina(vector[i]);
	}
	//dezalocacareLista(&lista);

	dezalocare2(&lista);
	afisareInceputFinal(lista);

	/*lista.prim->prev = lista.ultim;
	lista.ultim->next = lista.prim;
	printf("\n Afisare lista circulara: ");
	afisareListaCirculara(lista);*/

}