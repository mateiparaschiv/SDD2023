#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Autostrada Autostrada;
typedef struct Nod Nod;

struct Autostrada{
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

void main() {
	Nod* radacina = NULL;
	//cautareDupaId(radacina, 10);
	inserareInArbore(&radacina, initAutostrada(5, "A5", 100));
	inserareInArbore(&radacina, initAutostrada(8, "A8", 101));
	inserareInArbore(&radacina, initAutostrada(3, "A3", 102));
	inserareInArbore(&radacina, initAutostrada(10, "A10", 103));
	inserareInArbore(&radacina, initAutostrada(6, "A6", 104));
	inserareInArbore(&radacina, initAutostrada(4, "A4", 105));
	inserareInArbore(&radacina, initAutostrada(1, "A1", 106));
	inserareInArbore(&radacina, initAutostrada(11, "A11", 106));

	printf("\n Parcurgere inordine:");
	parcurgereInordine(radacina);

	printf("\n Cautare a10:");
	Autostrada a10 = cautareDupaId(radacina, 10);
	afisareAutostrada(a10);

	printf("\n Inaltime arbore: %d", inaltimeArbore(radacina));

	dezalocareArbore(&radacina);
	free(a10.denumire);
	parcurgereInordine(radacina);

}