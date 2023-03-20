#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>
typedef struct Produs Produs;
typedef struct Nod Nod;

 struct Produs
{
	 char* denumire;
	 int codProdus;
	 float pret;
};

 struct Nod
 {
	 Produs info;
	 Nod* next;
 };

 void afisareProdus(Produs p)
 {
	 printf("\n Produsul %s are codul %d, cu pretul %f", p.denumire, p.codProdus, p.pret);
 }

Produs initializareProdus(const char* denumire, int codProdus, float pr )
{
	Produs p;
	p.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(p.denumire, denumire);
	p.codProdus = codProdus;
	p.pret = pr;
	return p;
}

void inserareLaInceput(Produs p, Nod** cap) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p; //shallow copy util!
	nou->next = *cap;
	*cap = nou;
}

void inserareLaFinal(Produs p, Nod** cap) 
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;
	nou->next = NULL;

	if (*cap)
	{
		Nod* temp = *cap;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = nou;
	}
	else
	{
		*cap = nou;
	}

}

void afisareLista(Nod* cap) {
	while (cap) {
		afisareProdus(cap->info);
		cap = cap->next;
	}
}

float calculPretMediu(Nod* cap) {
	float x = 0;
	int contor = 0;
	while (cap) {
		x += cap->info.pret;
		contor++;
		cap = cap->next;
	}
	return contor != 0 ? x / contor: 0;
}

void dezalocare(Nod** cap)
{
	while (*cap != NULL)
	{
		free((*cap)->info.denumire);
		Nod* temp = *cap;
		(*cap) = (*cap)->next;
		free(temp);
	}
}

void main() {
	Nod* cap=NULL;
	inserareLaInceput(initializareProdus("Carte", 234, 15.2),&cap);
	inserareLaInceput(initializareProdus("Creion", 244, 14),&cap);
	inserareLaInceput(initializareProdus("Caiet", 344, 20.2),&cap);
	inserareLaInceput(initializareProdus("Stilou", 644, 30.3),&cap);
	inserareLaFinal(initializareProdus("Produs1", 744, 40), &cap);
	inserareLaFinal(initializareProdus("Produs2", 844, 10.5), &cap);
	inserareLaFinal(initializareProdus("Produs3", 944, 45), &cap);
	afisareLista(cap);

	float mediu = calculPretMediu(cap);
	printf("\nPretul mediu este: %f", mediu);

	dezalocare(&cap);
	afisareLista(cap);
	
}