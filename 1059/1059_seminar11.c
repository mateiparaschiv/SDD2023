#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Autostrada Autostrada;
typedef struct Nod Nod;

struct Autostrada {
	int id;
	char* denumire;
	int nrKm;
};

struct Nod {
	Nod* stanga;
	Nod* dreapta;
	Autostrada info;
};

Autostrada initAutostrada(int id, const char* denumire, int nrKm) {
	Autostrada autostrada;
	autostrada.id = id;
	autostrada.nrKm = nrKm;
	autostrada.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(autostrada.denumire, denumire);

	return autostrada;
}

void afisareAutostrada(Autostrada autostrada) {
	printf("\n Autostrada %s are id-ul %d si %d kilometri", autostrada.denumire, autostrada.id, autostrada.nrKm);
}

void inserareInArbore(Nod** radacina, Autostrada autostrada) {
	if ((*radacina) == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = autostrada;
		nou->stanga = nou->dreapta = NULL;
		*radacina = nou;
	}
	else {
		if (autostrada.id > (*radacina)->info.id) {
			inserareInArbore(&(*radacina)->dreapta, autostrada);
		}
		else {
			inserareInArbore(&(*radacina)->stanga, autostrada);
		}
	}
}

//parcurgere inordine: SRD (crescator)
void parcurgereInordine(Nod* radacina) {
	if (radacina) {
		parcurgereInordine(radacina->stanga);
		afisareAutostrada(radacina->info);
		parcurgereInordine(radacina->dreapta);
	}
}
//Tema
//parcurgere preordine: RSD
//parcurgere postordine: SDR

Autostrada cautareDupaId(Nod* radacina, int id) {
	if (radacina) {
		if (id == radacina->info.id) {
			//return radacina->info; //shallow copy
			return initAutostrada(id, radacina->info.denumire, radacina->info.nrKm);
		}
		else {
			if (id < radacina->info.id) {
				return cautareDupaId(radacina->stanga, id);
			}
			else {
				return cautareDupaId(radacina->dreapta, id);
			}
		}
	}
	else {
		return initAutostrada(-1, "", -1);
	}
}

void dezalocareArbore(Nod** radacina) {
	if (*radacina != NULL) {
		dezalocareArbore(&(*radacina)->stanga);
		dezalocareArbore(&(*radacina)->dreapta);

		free((*radacina)->info.denumire);
		free(*radacina);
	}
	*radacina = NULL;
}

int inaltimeArbore(Nod* radacina) {
	if (radacina == NULL) {
		return 0;
	}
	else {
		int hstanga = inaltimeArbore(radacina->stanga);
		int hdreapta = inaltimeArbore(radacina->dreapta);
		if (hstanga > hdreapta) {
			return hstanga + 1;
		}
		else {
			return hdreapta + 1;
		}
	}
}

void rotireDreapta(Nod** radacina)
{
	Nod* aux = (*radacina)->stanga;
	(*radacina)->stanga = aux->dreapta;
	aux->dreapta = (*radacina);
	(*radacina) = aux;
}

void rotireStanga(Nod** radacina)
{
	Nod* aux = (*radacina)->dreapta;
	(*radacina)->dreapta = aux->stanga;
	aux->stanga = (*radacina);
	(*radacina) = aux;
}

int calculDiferenta(Nod*radacina)
{
	if (radacina)
	{
		int hstanga = inaltimeArbore(radacina->stanga);
		int hdreapta = inaltimeArbore(radacina->dreapta);
		return hstanga - hdreapta;
	}
	else return 0;
}

void inserareInAVL(Nod** radacina, Autostrada autostrada) {
	if ((*radacina) == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = autostrada;
		nou->stanga = nou->dreapta = NULL;
		*radacina = nou;
	}
	else {
		if (autostrada.id > (*radacina)->info.id) {
			inserareInArbore(&(*radacina)->dreapta, autostrada);

		}
		else {
			inserareInArbore(&(*radacina)->stanga, autostrada);
		}

	}
	int  dif = calculDiferenta(*radacina);

	if (dif == 2)
	{
		//dezechilibru pe partea stanga
		if (calculDiferenta((*radacina)->stanga) == -1)
		{
			rotireStanga(&(*radacina)->stanga);
		}
		rotireDreapta(radacina);
	}
	if (dif == -2)
	{
		//dezechilibru pe partea dreapta
		if (calculDiferenta((*radacina)->dreapta)==1)
		{
			rotireDreapta(&(*radacina)->dreapta);
		}
		rotireStanga(radacina);
	}
}

void main() {
	Nod* radacina = NULL;

	inserareInAVL(&radacina,initAutostrada(5,"A5",105));
	inserareInAVL(&radacina, initAutostrada(4, "A4", 104));
	inserareInAVL(&radacina, initAutostrada(8, "A8", 108));
	inserareInAVL(&radacina, initAutostrada(2, "A2", 102));
	inserareInAVL(&radacina, initAutostrada(1, "A1", 101));

	parcurgereInordine(radacina);
}