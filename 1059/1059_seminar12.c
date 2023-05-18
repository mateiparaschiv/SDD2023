#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Pantof Pantof;
typedef struct Heap Heap;

struct Pantof {
	int prioritate;
	char* denumire;
	int marime;
	int pret;
};

struct Heap {
	Pantof* vect;
	int nrElem;
	int nrElemMaxim;
};

Pantof initializarePantof(int prioritate,char* den,int marime, int pret) {
	Pantof p;
	p.prioritate = prioritate;
	p.denumire = (char*)malloc(sizeof(char) * (strlen(den) + 1));
	strcpy(p.denumire, den);
	p.marime = marime;
	p.pret = pret;
	return p;
}

void afisarePantof(Pantof p) {
	printf("\n Pantof: %s, Important: %d, Marime: %d, pret: %d", p.denumire, p.prioritate, p.marime, p.pret);
}

void afisareHeapMax(Heap heap) {
	for (int i = 0; i < heap.nrElemMaxim; i++) {
		afisarePantof(heap.vect[i]);
	}
}

void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.nrElem; i++) {
		afisarePantof(heap.vect[i]);
	}
}

void filtrareHeap(Heap heap, int i)
{
	if (heap.nrElem)
	{
		int copilst = 2 * i + 1;
		int copildr = 2 * i + 2;
		int maxim = i;
		
		if (heap.nrElem > copilst && heap.vect[maxim].prioritate < heap.vect[copilst].prioritate)
		{
			maxim = copilst;
		}
		if (heap.nrElem > copildr && heap.vect[maxim].prioritate < heap.vect[copildr].prioritate )
		{
			maxim = copildr;
		}

		if (maxim != i)
		{
			Pantof p;
			p=heap.vect[i];
			heap.vect[i] = heap.vect[maxim];
			heap.vect[maxim] = p;
			if (maxim < heap.nrElem / 2 - 1)
			{
				filtrareHeap(heap, maxim);
			}
		}
	}
}

void extragereHeap(Heap* heap,Pantof* inf)
{
	*inf = initializarePantof((*heap).vect[0].prioritate, (*heap).vect[0].denumire, (*heap).vect[0].marime,
		(*heap).vect[0].pret);
	Pantof aux;
	aux = (*heap).vect[0];
	(*heap).vect[0] = (*heap).vect[(*heap).nrElem - 1];
	(*heap).vect[(*heap).nrElem - 1] = aux;
	
	(*heap).nrElem--;

	filtrareHeap(*heap, 0);
}

int main() {
	Heap heap;
	heap.nrElem = heap.nrElemMaxim = 5;
	heap.vect = (Pantof*)malloc(sizeof(Pantof)*heap.nrElemMaxim);
	heap.vect[0] = initializarePantof(17, "Balerini", 37, 79);
	heap.vect[1] = initializarePantof(15, "Cu toc", 38, 99);
	heap.vect[2] = initializarePantof(27, "Adidasi", 44, 88);
	heap.vect[3] = initializarePantof(20, "Papuci", 41, 99);
	heap.vect[4] = initializarePantof(19, "Slapi", 40, 99);
	afisareHeap(heap);
	printf("\n");
	for (int i = heap.nrElem / 2 - 1; i >= 0; i--)
	{
		filtrareHeap(heap, i);
	}

	afisareHeap(heap);
	Pantof p;
	printf("\n\nExtragere HEAP");
	while (heap.nrElem != 0)
	{
		extragereHeap(&heap, &p);
		afisarePantof(p);
		free(p.denumire);
	}

	printf("\nAfisare crescator\n");
	afisareHeapMax(heap);
}