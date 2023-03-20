#include <stdio.h>
#include <malloc.h>
typedef struct Auto Auto;
typedef struct Nod Nod;

struct Auto {
	char* marca;
	int nrUsi;
};

struct Nod {
	Auto info;
	Nod* next;//urmatorul nod

};

Auto initializare(char* marca, int nrUsi)
{
	Auto automobil;
	automobil.marca = (char*)malloc(sizeof(char)*(strlen(marca)+1));
	strcpy(automobil.marca, marca);
	automobil.nrUsi = nrUsi;
	return automobil;
}

void afisare(Auto a)
{
	printf("%d \n %s", a.nrUsi, a.marca);
}

//Nod* este same cu void si ca parametri avem nod**
Nod* inserareinceput(Nod* cap, Auto info)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod) * 1);
	nou->info = info;
	nou->next = cap;
	//return nou; sau continuam:
	cap = nou;
	return cap;
}

void afisareLista(Nod* cap)
{
	while (cap != NULL)
	{
		afisare(cap->info);
		printf("\n");
		cap = cap->next;
	}

}

void inserareNodLaFinal(Nod** cap, Auto a)
{
	Nod* aux = *cap;
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));
	nou->info = a;
	nou->next = NULL;
	if (*cap == NULL)
	*cap = nou;
	else
	{
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
}

void main()
{
	Nod* cap = NULL;
	cap=inserareinceput(cap,initializare("masina1",4));
	cap = inserareinceput(cap, initializare("masina2", 3));
	cap = inserareinceput(cap, initializare("masina3", 1));
	cap = inserareinceput(cap, initializare("masina4", 6));
	inserareNodLaFinal(&cap, initializare("BMW",2));

	afisareLista(cap);
	
	//tema dezalocare lista
}