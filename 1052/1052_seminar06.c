#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct Nod Nod;
typedef struct Carte Carte;

struct Carte {
	char* denumire_carte;
	long id;
	float pret;
};

struct Nod {
	Carte info;
	Nod* next;
};

Carte initializareCarte(char* denumire, long id, float pret) {
	Carte c;
	c.id = id;
	c.pret = pret;
	c.denumire_carte = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy_s(c.denumire_carte, strlen(denumire)+1, denumire);

	return c;
}

void afisareCarte(Carte c) {
	printf("\n Cartea cu denumirea %s, id-ul %ld si pretul %.2f", c.denumire_carte, c.id, c.pret);
}

void push(Carte c, Nod** varf) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = *varf;

	*varf = nou;

}

void put(Carte c, Nod** prim)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	Nod* aux = (*prim);
	if (aux)
	{
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
	else
	{
		(*prim) = nou;

	}
}
Carte pop(Nod** varf) {
	Carte c;
	c.id = -1;
	c.denumire_carte = NULL;
	c.pret = 0;

	if (*varf) {
		c = (*varf)->info;
		Nod* aux = *varf;
		*varf = (*varf)->next;
		free(aux);
	}
	return c;
}

Carte findById(Nod** varf, long id) {
	Carte c;
	c.id = -1;
	c.denumire_carte = NULL;
	c.pret = -1;

	Nod* stivaAux = NULL;

	while ((*varf) && (*varf)->info.id != id) {
		push(pop(varf), &stivaAux);
	}

	if ((*varf) != NULL) {
		c = pop((varf));
	}

	while (stivaAux != NULL) {
		push(pop(&stivaAux), varf);
	}

	return c;
}

int main() {
	Nod* stiva = NULL;

	push(initializareCarte("Fram", 10001, 25.5), &stiva);
	push(initializareCarte("Rand", 10002, 30.2), &stiva);
	push(initializareCarte("C3", 10222, 42.3), &stiva);

	Carte c;
	
	Carte cautata;
	cautata = findById(&stiva, 10001);
	printf("\nAfisare Carte cu ID : 10001 \n");
	afisareCarte(cautata);
	free(cautata.denumire_carte);
	
	printf("\nAfisare Stiva :  \n");
	while (stiva) {
		c=pop(&stiva);
		afisareCarte(c);
		free(c.denumire_carte);
	}

	Nod* coada = NULL;
	put(initializareCarte("Tomas", 10006, 25.1), &coada);
	put(initializareCarte("Aventura", 10009, 37.2), &coada);
	put(initializareCarte("Bucuresti", 10222, 42.9), &coada);
	printf("\nAfisare Coada\n");
	while (coada) {
		c = pop(&coada);
		afisareCarte(c);
		free(c.denumire_carte);
	}

	return 0;
}