#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Persoana Persoana;
typedef struct LinkedList LinkedList;

struct Persoana
{
	char* nume;
	int varsta;

};

struct LinkedList {
	Persoana info;
	LinkedList* next;
};

Persoana initializare(char* nume, int varsta) {
	Persoana p;
	p.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(p.nume, nume);
	p.varsta = varsta;
	return p;
}

void afisarePers(Persoana p) {
	printf("\nPersoana %s are varsta de %d ani.", p.nume, p.varsta);
}

void inserareLaIncput(Persoana p, LinkedList** cap)
{
	LinkedList* nou = (LinkedList*)malloc(sizeof(LinkedList));
	nou->info = p;
	nou->next = *cap;
	*cap = nou;
}

void afisareLista(LinkedList* cap)
{
	while (cap)
	{
		afisarePers(cap->info);
		cap = cap->next;
	}
}

void inserareFinal(Persoana p, LinkedList** head) {
	LinkedList* nodNou = (LinkedList*)malloc(sizeof(LinkedList));
	nodNou->info = p;
	nodNou->next = NULL;

	if (!(*head)) {
		*head = nodNou;
	}
	else {
		LinkedList* aux = *head;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nodNou;
	}
}

void dezalocare(LinkedList** cap)
{
	while (*cap != NULL)
	{
		free((*cap)->info.nume);
		LinkedList* aux = *cap;
		(*cap) = (*cap)->next;
		free(aux);
	}
}

float calculMedie(LinkedList* cap) {
	float suma = 0;
	int k = 0;
	while (cap) {
		k++;
		suma += cap->info.varsta;
		cap = cap->next;
	}
	if(k)	return suma / k;
}

int main() {
	LinkedList* capLista = NULL;

	inserareLaIncput(initializare("Mihai", 18), &capLista);
	inserareLaIncput(initializare("Laurentiu", 23), &capLista);
	inserareLaIncput(initializare("Lorena", 15), &capLista);
	inserareFinal(initializare("George", 45), &capLista);
	inserareFinal(initializare("Ion", 35), &capLista);
	afisareLista(capLista);
	float medie = calculMedie(capLista);
	printf("\n%.2f", medie);

	dezalocare(&capLista);
	afisareLista(capLista);
	

}
