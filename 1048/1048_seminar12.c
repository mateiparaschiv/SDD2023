#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

//Max-Heap
typedef struct Heap Heap;
typedef struct Echipa Echipa;

struct Echipa {
	int prioritate;
	char* denumire;
	int nrJucatori;
};

struct Heap {
	int dimensiune;
	Echipa* vector;
};

Echipa initEchipa(int prioritate, char* denumire, int nrJucatori) {
	Echipa echipa;
	echipa.prioritate = prioritate;
	echipa.nrJucatori = nrJucatori;
	echipa.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(echipa.denumire, denumire);
	return echipa;
}

void afisareEchipa(Echipa echipa) {
	printf("\n Echipa %s are %d jucatori. Prioritatea este %d",
		echipa.denumire, echipa.nrJucatori, echipa.prioritate);
}

void parcurgereHeap(Heap heap) {
	for (int i = 0; i < heap.dimensiune; i++) {
		afisareEchipa(heap.vector[i]);
	}
}

void filtrareHeap(Heap heap, int index) {
	if (heap.dimensiune > 0) {
		int pozS = 2 * index + 1;
		int pozD = 2 * index + 2;
		int pozMax = index;

		if (heap.dimensiune > pozS && heap.vector[pozMax].prioritate < heap.vector[pozS].prioritate) {
			pozMax = pozS;
		}

		if (heap.dimensiune > pozD && heap.vector[pozMax].prioritate < heap.vector[pozD].prioritate) {
			pozMax = pozD;
		}

		if (pozMax != index) {
			//interschimbare
			Echipa aux = heap.vector[pozMax];
			heap.vector[pozMax] = heap.vector[index];
			heap.vector[index] = aux;

			filtrareHeap(heap, pozMax);
		}
	}
}

void extragere(Heap* h, Echipa* echipa) {
	(*echipa) = h->vector[0];
	Echipa aux;
	aux = h->vector[0];
	h->vector[0] = h->vector[h->dimensiune - 1];
	h->vector[h->dimensiune - 1] = aux;
	h->dimensiune -= 1;
	filtrareHeap((*h), 0);
}

void main() {
	Heap heap;
	heap.dimensiune = 6;
	heap.vector = (Echipa*)malloc(sizeof(Echipa) * heap.dimensiune);
	heap.vector[0] = initEchipa(1, "Dinamo", 24);
	heap.vector[1] = initEchipa(2, "Steaua", 18);
	heap.vector[2] = initEchipa(5, "Rapid", 20);
	heap.vector[3] = initEchipa(4, "Cfr", 22);
	heap.vector[4] = initEchipa(8, "Petrolul", 19);
	heap.vector[5] = initEchipa(6, "Farul", 21);
	//prioritati initiale:1,2,5,4,8,6

	parcurgereHeap(heap);

	//filtrare
	for (int i = heap.dimensiune / 2 - 1; i >= 0; i--) {
		filtrareHeap(heap, i);
	}
	printf("\n\n Parcurgere dupa filtrare:");
	parcurgereHeap(heap);

	//extragem prima echipa din heap
	Echipa e;
	extragere(&heap, &e);

	printf("\n\n");
	afisareEchipa(e);

	printf("\n\n");
	parcurgereHeap(heap);
}