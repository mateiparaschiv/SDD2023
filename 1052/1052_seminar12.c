#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Heap Heap;
typedef struct Calculator Calculator;

struct Calculator
{
	int prioritate;
	char* model;
	float pret;
};

struct Heap
{
	Calculator* vectorCalc;
	int dimensVect;
	int dimensMax;
};

Calculator initializareaCalc(int prioritate, char* model, float pret)
{
	Calculator c;
	c.prioritate = prioritate;
	c.model = (char*)malloc(sizeof(char) * (strlen(model) + 1));
	strcpy(c.model, model);
	c.pret = pret;
	return c;
}

void afisareCalc(Calculator c)
{
	printf("\nCalculatorul %s are prioritatea %d si costa %f lei", c.model, c.prioritate, c.pret);
}

void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.dimensVect; i++) {
		afisareCalc(heap.vectorCalc[i]);
	}
}

void afisareHeapMax(Heap heap) {
	for (int i = 0; i < heap.dimensMax; i++) {
		afisareCalc(heap.vectorCalc[i]);
	}
}

void filtrare(Heap h, int index) {
	if (h.dimensVect) {
		int pozSt = 2 * index + 1;
		int pozDr = 2 * index + 2;
		int pozMax = index;

		if (h.dimensVect > pozSt && h.vectorCalc[pozMax].prioritate < h.vectorCalc[pozSt].prioritate) {
			pozMax = pozSt;
		}
		if (h.dimensVect > pozDr && h.vectorCalc[pozMax].prioritate < h.vectorCalc[pozDr].prioritate) {
			pozMax = pozDr;
		}
		if (pozMax != index) {
			Calculator aux = h.vectorCalc[index];
			h.vectorCalc[index] = h.vectorCalc[pozMax];
			h.vectorCalc[pozMax] = aux;
			if (pozMax <= h.dimensVect / 2-1) {
				filtrare(h, pozMax);
			}
		}
	}
}

void extragere(Heap* heap, Calculator* c) {
	*c=initializareaCalc(heap->vectorCalc[0].prioritate, heap->vectorCalc[0].model, heap->vectorCalc[0].pret);
	Calculator aux = heap->vectorCalc[0];
	heap->vectorCalc[0] = heap->vectorCalc[heap->dimensVect-1] ;
	heap->vectorCalc[heap->dimensVect - 1] = aux;
	heap->dimensVect--;
	filtrare(*heap, 0);
}

int main() {
	Heap heap;
	heap.dimensVect = heap.dimensMax = 5;
	heap.vectorCalc = (Calculator*)malloc(sizeof(Calculator) * heap.dimensVect);
	heap.vectorCalc[0] = initializareaCalc(19, "DELL", 3000);
	heap.vectorCalc[1] = initializareaCalc(11, "ACER", 4500);
	heap.vectorCalc[2] = initializareaCalc(15, "SAMSUNG", 6000);
	heap.vectorCalc[3] = initializareaCalc(21, "LENOVO", 4000);
	heap.vectorCalc[4] = initializareaCalc(14, "DELL", 3000);
	afisareHeap(heap);

	for (int i = heap.dimensVect / 2 - 1; i >= 0; i--) {
		filtrare(heap, i);
	}

	printf("\n\n");
	afisareHeap(heap);

	printf("\n\n");
	Calculator calc;
	while (heap.dimensVect != 0) {
		extragere(&heap, &calc);
		afisareCalc(calc);
		free(calc.model);
	}

	printf("\n\n");
	afisareHeapMax(heap);
}