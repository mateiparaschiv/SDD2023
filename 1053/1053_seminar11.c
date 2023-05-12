#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina {
	int id;
	char* marca;
};

struct Nod {
	Masina info;
	Nod* stanga;
	Nod* dreapta;
};

Masina initializareMasina(int id, const char* marca) {
	Masina m;
	m.id = id;
	m.marca = (char*)malloc(sizeof(char) * (strlen(marca) + 1));
	strcpy(m.marca, marca);
	return m;
}

void afisare(Masina m) {
	printf("\n Masina cu id-ul %d este de marca %s", m.id, m.marca);
}

void inserare(Nod** radacina, Masina m)
{
	if (*radacina == NULL)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = m;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		*radacina = nou;
	}
	else
	{
		if ((*radacina)->info.id > m.id)
			inserare(&(*radacina)->stanga, m);
		else
			inserare(&(*radacina)->dreapta, m);
	}
}

void parcurgereInordine(Nod* radacina) {
	if (radacina) {
		parcurgereInordine(radacina->stanga);
		afisare(radacina->info);
		parcurgereInordine(radacina->dreapta);
	}
}

void parcurgerePreordine(Nod* radacina) {
	if (radacina) {
		afisare(radacina->info);
		parcurgerePreordine(radacina->stanga);
		parcurgerePreordine(radacina->dreapta);
	}
}

Masina search(Nod* radacina, int idMasina) {
	if (!radacina) {
		return initializareMasina(-1, "N/A");
	}
	else {
		if (radacina->info.id == idMasina) {
			return initializareMasina(radacina->info.id, radacina->info.marca);
		}
		else {
			if (idMasina < radacina->info.id) {
				return search(radacina->stanga, idMasina);
			}
			else {
				return search(radacina->dreapta, idMasina);
			}
		}
	}
}

void dezalocare(Nod** radacina) {
	if (*radacina != NULL)
	{
		dezalocare(&(*radacina)->stanga);
		dezalocare(&(*radacina)->dreapta);
		free((*radacina)->info.marca);
		free(*radacina);
	}
	*radacina = NULL;
}

int calculInaltime(Nod* radacina) {
	if (radacina) {
		int inaltimeStanga = calculInaltime(radacina->stanga);
		int inaltimeDreapta = calculInaltime(radacina->dreapta);
		if (inaltimeStanga > inaltimeDreapta)
			return inaltimeStanga + 1;
		else
			return inaltimeDreapta + 1;
	}
	else {
		return 0;
	}
}

void rotireStanga(Nod** radacina)
{
	Nod* aux = (*radacina)->dreapta;
	(*radacina)->dreapta = aux->stanga;
	aux->stanga = (*radacina);
	*radacina = aux;
}

void rotireDreapta(Nod** radacina)
{
	Nod* aux = (*radacina)->stanga;
	(*radacina)->stanga = aux->dreapta;
	aux->dreapta = (*radacina);
	*radacina = aux;
}

int diferentaInaltime(Nod* radacina)
{
	if (radacina)
	{
		return calculInaltime(radacina->stanga) - calculInaltime(radacina->dreapta);
	}
	else
		return 0;
}

void inserareInAVL(Nod** radacina, Masina m)
{
	if (*radacina == NULL)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = m;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		*radacina = nou;
	}
	else
	{
		if ((*radacina)->info.id > m.id)
			inserare(&(*radacina)->stanga, m);
		else
			inserare(&(*radacina)->dreapta, m);
	}
	int dif = diferentaInaltime(*radacina);
	if (dif == -2) {
		//dezechilibru pe partea dreapta
		if (diferentaInaltime((*radacina)->dreapta) == 1) {
			rotireDreapta(&(*radacina)->dreapta);
		}
		rotireStanga(radacina);
	}
	if (dif == 2) {
		//dezechilibru pe partea stanga
		if (diferentaInaltime((*radacina)->stanga) == -1) {
			rotireStanga(&(*radacina)->stanga);
		}
		rotireDreapta(radacina);
	}
}

void main() {
	Nod* radacina = NULL;
	inserareInAVL(&radacina, initializareMasina(10, "BMW"));
	inserareInAVL(&radacina, initializareMasina(7, "BMW"));
	inserareInAVL(&radacina, initializareMasina(12, "BMW"));
	inserareInAVL(&radacina, initializareMasina(5, "BMW"));
	inserareInAVL(&radacina, initializareMasina(2, "BMW"));

	parcurgereInordine(radacina);

}