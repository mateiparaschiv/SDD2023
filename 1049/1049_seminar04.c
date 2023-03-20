#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Facultate Facultate;
typedef struct Nod Nod;

struct Facultate {
	char* denumire;
	int nrStud;
};

struct Nod {
	Facultate info;
	Nod* next;
};

Facultate initFacultate(char* denumire, int nrStud) {
	Facultate facultate;
	facultate.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(facultate.denumire, denumire);
	facultate.nrStud = nrStud;

	return facultate;
}

void afisFacultate(Facultate facultate) {
	printf("\n%s %d", facultate.denumire, facultate.nrStud);
}

void inserareLaInceput(Nod **cap, Facultate f) //transmitem prin adresa cap-ul
{
	Nod* n = (Nod*)malloc(sizeof(Nod) * 1);
	n->info = f; //accesam elementul prin "->"  pt ca e o adresa
	//shallow-copy

	n->next = *cap; //am fc legatura intre cele doua noduri+deref pt cap
	*cap = n; 
}

void inserareLaSfarsit(Nod** cap, Facultate f)
{
	Nod* n = (Nod*)malloc(sizeof(Nod));
	n->info = f;
	n->next = NULL;
	Nod* aux = *cap;
	if (*cap)
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = n;
	}
	else
		*cap = n;
}

void afisareLista(Nod* cap) {
	while (cap != NULL) {
		afisFacultate(cap->info);
		cap = cap->next;
	}
}

void dezalocare(Nod** cap) {
	while (*cap != NULL) {
		free((*cap)->info.denumire);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
	printf("\n S-a dezalocat complet");
}

int main(){
	Nod* cap = NULL;
	inserareLaInceput(&cap, initFacultate("CSIE", 100));
	inserareLaInceput(&cap, initFacultate("CIG", 120));
	inserareLaInceput(&cap, initFacultate("Marketing", 150));
	afisareLista(cap);
	inserareLaSfarsit(&cap, initFacultate("FABIZ", 175));
	inserareLaSfarsit(&cap, initFacultate("Agro", 200));
	afisareLista(cap);
	dezalocare(&cap);
}