#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Nod Nod;
typedef struct Produs Produs;

struct Produs {
	int id;
	char* denumire;
};

struct Nod {
	Nod* stanga;
	Nod* dreapta;
	Produs info;
};

Produs initializareProdus(int id, const char* denumire)
{
	Produs p;
	p.id = id;
	p.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(p.denumire, denumire);
	return p;
}

void afisareProdus(Produs p)
{
	printf("\nProdusul are id-ul %d si se numeste %s", p.id, p.denumire);
}

void inserareInArbore(Nod** radacina, Produs info) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = info;
		nou->stanga = nou->dreapta = NULL;
		*radacina = nou;
	}
	else {
		if (info.id < (*radacina)->info.id) {
			inserareInArbore(&(*radacina)->stanga, info);
		}
		else {
			inserareInArbore(&(*radacina)->dreapta, info);
		}
	}
}

void parcurgereInOrdine(Nod* radacina) {
	if (radacina != NULL) {
		parcurgereInOrdine(radacina->stanga);
		afisareProdus(radacina->info);
		parcurgereInOrdine(radacina->dreapta);
	}
}

void parcurgerePreOrdine(Nod* radacina) {
	if (radacina != NULL) {
		afisareProdus(radacina->info);
		parcurgerePreOrdine(radacina->stanga);
		parcurgerePreOrdine(radacina->dreapta);
	}
}

Produs cautareProdus(Nod* radacina, int id) {
	Produs p;
	if (radacina != NULL) {
		if (radacina->info.id == id) {
			p = initializareProdus(radacina->info.id, radacina->info.denumire);
			return p;
		}
		else
		{
			if (id < radacina->info.id) {
				p = cautareProdus(radacina->stanga, id);
			}
			else
			{
				p = cautareProdus(radacina->dreapta, id);
			}
			return p;
		}
	}
	else
	{
		p = initializareProdus(-1, "");
		return p;
	}
}

void dezalocare(Nod** rad) {
	if (*rad != NULL) {
		dezalocare(&(*rad)->stanga);
		dezalocare(&(*rad)->dreapta);
		free((*rad)->info.denumire);
		free((*rad));
	}
	*rad = NULL;
}

int inaltimeArbore(Nod* radacina) {
	if (radacina != NULL) {
		int inaltimeStanga = inaltimeArbore(radacina->stanga);
		int inaltimeDreapta = inaltimeArbore(radacina->dreapta);
		if (inaltimeStanga > inaltimeDreapta) {
			return inaltimeStanga + 1;
		}
		else {
			return inaltimeDreapta + 1;
		}
	}
	else {
		return 0;
	}
}

void rotireLaDreapta(Nod** rad) {
	Nod* aux = (*rad)->stanga;
	(*rad)->stanga = aux->dreapta;
	aux->dreapta = (*rad);
	*rad = aux;
}

void rotireLaStanga(Nod** rad) {
	Nod* aux = (*rad)->dreapta;
	(*rad)->dreapta = aux->stanga;
	aux->stanga = (*rad);
	*rad = aux;
}

int diferentaInaltime(Nod* rad) {
	if (rad != NULL) {
		return inaltimeArbore(rad->stanga) - inaltimeArbore(rad->dreapta);
	}
	else {
		return 0;
	}
}

void inserareInAVL(Nod** radacina, Produs info) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = info;
		nou->stanga = nou->dreapta = NULL;
		*radacina = nou;
	}
	else {
		if (info.id < (*radacina)->info.id) {
			inserareInArbore(&(*radacina)->stanga, info);
		}
		else {
			inserareInArbore(&(*radacina)->dreapta, info);
		}
	}
	int dif = diferentaInaltime(*radacina);
	if (dif == 2)
	{
		//dezechilibru pe partea stanga
		if (diferentaInaltime((*radacina)->stanga) == -1)
		{
			rotireLaStanga(&(*radacina)->stanga);
		}
		rotireLaDreapta(radacina);
	}
	else if (dif == -2)
	{
		//dezechilibru pe partea dreapta
		if (diferentaInaltime((*radacina)->dreapta) == 1)
		{
			rotireLaDreapta(&(*radacina)->dreapta);
		}
		rotireLaStanga(radacina);
	}
}

int main()
{
	Nod* radacina = NULL;
	inserareInAVL(&radacina, initializareProdus(13, "paine"));
	inserareInAVL(&radacina, initializareProdus(8, "unt"));
	inserareInAVL(&radacina, initializareProdus(15, "carte"));
	inserareInAVL(&radacina, initializareProdus(5, "lapte"));
	inserareInAVL(&radacina, initializareProdus(2, "stilou"));
	inserareInAVL(&radacina, initializareProdus(9, "haina"));
	
	parcurgereInOrdine(radacina);
}
