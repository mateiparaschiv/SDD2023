#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Cofetarie Cofetarie;
typedef struct Nod Nod;

struct Cofetarie {
	int id;
	char* nume;
};

struct Nod {
	Cofetarie info;
	Nod* stanga;
	Nod* dreapta;
};

Cofetarie initializareCofetarie(int id, char* nume) {
	Cofetarie c;
	c.id = id;
	c.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(c.nume, nume);
	return c;
}

void afisareCofetarie(Cofetarie c) {
	printf("\n Cofetaria %s are id-ul %d", c.nume, c.id);
}

void inserareArbore(Cofetarie c, Nod** radacina)
{
	if (*radacina == NULL)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = c;
		nou->dreapta = NULL;
		nou->stanga = NULL;
		*radacina = nou;
	}
	else
	{
		if (c.id > (*radacina)->info.id)
			inserareArbore(c, &(*radacina)->dreapta);
		else
			inserareArbore(c, &(*radacina)->stanga);
	}
}

void afisareInOrdine(Nod* radacina)
{
	//afisare In ordine : Stanga,Radacina,Dreapta
	if (radacina != NULL)
	{
		afisareInOrdine(radacina->stanga);
		afisareCofetarie(radacina->info);
		afisareInOrdine(radacina->dreapta);
	}

}
void afisarePreOrdine(Nod* radacina)
{
	//Afisare preordine : Radacina,Stanga,Dreapta
	if (radacina != NULL)
	{
		afisareCofetarie(radacina->info);
		afisarePreOrdine(radacina->stanga);
		afisarePreOrdine(radacina->dreapta);
	}
}

void dezalocareArbore(Nod** radacina)
{
	if (*radacina)
	{
		dezalocareArbore(&(*radacina)->stanga);
		dezalocareArbore(&(*radacina)->dreapta);
		free((*radacina)->info.nume);
		free(*radacina);
	}
	*radacina = NULL;
}

void cautareDupaId(Cofetarie* c, Nod* radacina,int idCautat) {
	
	if (radacina) {
		if (radacina->info.id == idCautat)
			*c = initializareCofetarie(idCautat, radacina->info.nume);
		else {
			if (idCautat < radacina->info.id) {
				cautareDupaId(c, radacina->stanga, idCautat);
			}
			else {
				cautareDupaId(c, radacina->dreapta, idCautat);
			}
		}
	}
	else *c = initializareCofetarie(-1, "");
}

int calculInaltime(Nod* radacina)
{
	if (radacina)
	{
		int inaltimeS=calculInaltime(radacina->stanga);
		int inaltimeD=calculInaltime(radacina->dreapta);
		if (inaltimeD > inaltimeS)
			return inaltimeD + 1;
		else
			return inaltimeS + 1;
	}
	else
	{
		return 0;
	}
}

void main() {
	Nod* radacina = NULL;
	Cofetarie c;
	inserareArbore(initializareCofetarie(7, "Cof1"), &radacina);
	inserareArbore(initializareCofetarie(5, "Cof2"), &radacina);
	inserareArbore(initializareCofetarie(9, "Cof3"), &radacina);
	inserareArbore(initializareCofetarie(6, "Cof4"), &radacina);
	inserareArbore(initializareCofetarie(3, "Cof5"), &radacina);
	inserareArbore(initializareCofetarie(8, "Cof6"), &radacina);
	inserareArbore(initializareCofetarie(11, "Cof7"), &radacina);
	printf("\n Inordine : ");
	afisareInOrdine(radacina);
	printf("\n Preordine : ");
	afisarePreOrdine(radacina);
	printf("\n Cautare nod cu id 3 : ");
	cautareDupaId(&c, radacina, 3);
	afisareCofetarie(c);

	
	int inaltime= calculInaltime(radacina);
	printf("\n inaltime arbore:%d",inaltime);

	dezalocareArbore(&radacina);
	
}