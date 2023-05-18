#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include<stdio.h>
#include<string.h>

typedef struct Calculator Calculator;
typedef struct Heap Heap;

struct Calculator {
	int prioritate;
	char* marca;
};

struct Heap {
	Calculator* vector;
	int dim;
	int dimmax;
};

Calculator initializareCalculator(int prioritate, char* marca)
{
	Calculator c;
	c.prioritate = prioritate;
	c.marca = (char*)malloc(sizeof(char) * (strlen(marca) + 1));
	strcpy(c.marca, marca);
	return c;
}

void afisareCalculator(Calculator c)
{
	printf("\n Calculatorul cu prioritatea %d are marca %s", c.prioritate, c.marca);
}

void parcurgereHeap(Heap h) {
	for (int i = 0; i < h.dim; i++) {
		afisareCalculator(h.vector[i]);
	}
}

void parcurgereHeapMax(Heap h) {
	for (int i = 0; i < h.dimmax; i++) {
		afisareCalculator(h.vector[i]);
	}
}

void filtrare(Heap h,int i) {
	if (h.dim) {
		int stanga = 2 * i + 1;
		int dreapta = 2 * i + 2;
		int pozMax = i;
		if (stanga < h.dim && h.vector[pozMax].prioritate < h.vector[stanga].prioritate)
			pozMax = stanga;
		if (dreapta < h.dim && h.vector[pozMax].prioritate < h.vector[dreapta].prioritate)
			pozMax = dreapta;
		if (i != pozMax) {
			Calculator aux = h.vector[i];
			h.vector[i] = h.vector[pozMax];
			h.vector[pozMax] = aux;
			filtrare(h, pozMax);
		}
	}
}

Calculator extragere(Heap* h)
{
	//Calculator c = initializareCalculator(h->vector[0].prioritate, h->vector[0].marca);
	Calculator aux = h->vector[0];
	h->vector[0] = h->vector[h->dim-1];
	h->vector[h->dim-1] = aux;
	h->dim--;
	filtrare(*h, 0);

	//return c;
	//return initializareCalculator(aux.prioritate, aux.marca);
	return initializareCalculator(h->vector[h->dim].prioritate, h->vector[h->dim].marca);
}

void main() {
	Heap heap;
	heap.dim = heap.dimmax = 6;
	heap.vector = (Calculator*)malloc(sizeof(Calculator) * (heap.dim));
	heap.vector[0] = initializareCalculator(7, "Calculator1");
	heap.vector[1] = initializareCalculator(9, "Calculator2");
	heap.vector[2] = initializareCalculator(8, "Calculator3");
	heap.vector[3] = initializareCalculator(13, "Calculator4");
	heap.vector[4] = initializareCalculator(15, "Calculator5");
	heap.vector[5] = initializareCalculator(10, "Calculator6");
	parcurgereHeap(heap);

	printf("\n\n");

	for (int i = heap.dim / 2 - 1; i >= 0; i--) {
		filtrare(heap, i);
	}
	parcurgereHeap(heap);

	printf("\n\n");

	while (heap.dim != 0) {
		Calculator c = extragere(&heap);
		afisareCalculator(c);
		free(c.marca);
	}

	parcurgereHeapMax(heap);
}



