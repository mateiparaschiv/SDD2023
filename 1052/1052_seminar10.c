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
			if (id<radacina->info.id) {
				p=cautareProdus(radacina->stanga, id);
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

int main()
{
	Nod* radacina = NULL;
	inserareInArbore(&radacina, initializareProdus(5, "prod1"));
	inserareInArbore(&radacina, initializareProdus(3, "prod2"));
	inserareInArbore(&radacina, initializareProdus(7, "prod3"));
	inserareInArbore(&radacina, initializareProdus(2, "prod4"));
	inserareInArbore(&radacina, initializareProdus(4, "prod5"));
	inserareInArbore(&radacina, initializareProdus(6, "prod6"));
	inserareInArbore(&radacina, initializareProdus(8, "prod7"));

	parcurgereInOrdine(radacina);
	printf("\n Parcurgere preordine: ");
	parcurgerePreOrdine(radacina);
	printf("\n Cautare Produs id=4 ");
	Produs p = cautareProdus(radacina, 4);
	afisareProdus(p);
	
	int hArbore = inaltimeArbore(radacina);
	printf("\n Inaltimea arborelui este: %d", hArbore);

	dezalocare(&radacina);
}

