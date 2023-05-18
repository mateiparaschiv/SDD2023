#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Scoala Scoala;
typedef struct Heap Heap;

struct Scoala
{
	int prioritate;
	char* denumire;
	int nrCopii;
};

struct Heap
{
	Scoala* vectScoli;
	int dimVector;
	int dimMaxima;
};

Scoala initScoala(int prioritate, char* denumire, int nrCopii)
{
	Scoala s;
	s.prioritate = prioritate;
	s.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(s.denumire, denumire);
	s.nrCopii = nrCopii;
	return s;
}

void afisareScoala(Scoala s)
{
	printf("Scoala cu prioritatea %d are denumirea: %s si %d elevi \n", s.prioritate, s.denumire, s.nrCopii);
}

void afisareHeap(Heap h) {
	for (int i = 0; i < h.dimVector; i++)
	{
		afisareScoala(h.vectScoli[i]);
	}
}

void afisareHeapMax(Heap h) {
	for (int i = 0; i < h.dimMaxima; i++)
	{
		afisareScoala(h.vectScoli[i]);
	}
}

void filtrare(Heap h, int index) {
	if (h.dimVector) {
		int copilStanga = 2 * index+ 1;
		int copilDreapta = 2 * index + 2;
		int pozMax = index;
		if ( h.dimVector > copilStanga && h.vectScoli[pozMax].prioritate < h.vectScoli[copilStanga].prioritate) {
			pozMax = copilStanga;
		}
		if (h.dimVector > copilDreapta && h.vectScoli[pozMax].prioritate < h.vectScoli[copilDreapta].prioritate) {
			pozMax = copilDreapta;
		}

		if (pozMax != index) {
			Scoala aux;
			aux = h.vectScoli[pozMax];
			h.vectScoli[pozMax] = h.vectScoli[index];
			h.vectScoli[index] = aux;
			if (pozMax <= h.dimVector / 2 - 1) {
				filtrare(h, pozMax);
			}
		}
	}
}

void Extragere(Heap* h, Scoala* s)
{
	*s = initScoala(h->vectScoli[0].prioritate, 
		h->vectScoli[0].denumire, h->vectScoli[0].nrCopii); //deep copy
	
	Scoala aux;
	aux = h->vectScoli[0];
	h->vectScoli[0] = h->vectScoli[h->dimVector - 1];
	h->vectScoli[h->dimVector - 1] = aux;

	(*h).dimVector--;
	filtrare(*h, 0);
}

int main()
{
	Heap h;
	h.dimMaxima = h.dimVector=6;
	
	h.vectScoli = (Scoala*)malloc(sizeof(Scoala) * h.dimMaxima);

	h.vectScoli[0] = initScoala(10,"Cuza",150);
	h.vectScoli[1] = initScoala(11,"Caragiale",200);
	h.vectScoli[2] = initScoala(15,"Ovidius",160);
	h.vectScoli[3] = initScoala(17,"Mircea",170);
	h.vectScoli[4] = initScoala(12,"Madgearu",210);
	h.vectScoli[5] = initScoala(20,"Blaga",180);

	afisareHeap(h);
	for (int i = (h.dimVector / 2) - 1; i >= 0; i--) {
		filtrare(h, i);
	}
	printf("\n\r");
	afisareHeap(h);

	printf("\n\n");
	Scoala s2;
	while (h.dimVector != 0)
	{
		Extragere(&h, &s2);
		afisareScoala(s2);
		free(s2.denumire);
	}
	printf("\n\n");
	afisareHeapMax(h);
		
	return 0;
}