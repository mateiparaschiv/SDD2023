#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>
#include<string.h>

typedef struct Farfurie Farfurie;
typedef struct Nod Nod;

struct Farfurie {
	long id;
	char* culoare;
	float pret;
};

struct Nod {
	Farfurie info;
	Nod* next;
};

Farfurie initFarfurie(long id, const char* culoare, float pret) {
	Farfurie f;
	f.culoare = (char*)malloc(sizeof(char) * (strlen(culoare) + 1));
	strcpy(f.culoare, culoare);
	f.id = id;
	f.pret = pret;
	return f;
}

void afisareFarfurie(Farfurie f) {
	printf("Farfuria cu id-ul %ld si culoarea %s are pretul %.2f\n", f.id, f.culoare, f.pret);
}

void push(Nod** varf, Farfurie f) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = *varf;
	nou->info = f;
	*varf = nou;
}

Farfurie pop(Nod** varf) {
	Farfurie f; f.id = -1; f.culoare = NULL; f.pret = 0;
	if (*varf != NULL) {
		f = (*varf)->info;
		Nod* aux = *varf;
		*varf = (*varf)->next;
		free(aux);
	}

	return f;
}

void put(Nod** prim, Farfurie f) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->info = f;

	if (!(*prim)) {
		*prim = nou;
	}
	else {
		Nod* aux = *prim;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}

Farfurie cautareFarfurieById(long id, Nod** varf) {
	Farfurie f;
	Nod* aux = NULL;
	f.id = -1;
	f.culoare = NULL;
	f.pret = 0;
	while ((*varf) != NULL && (*varf)->info.id != id) {
		push(&aux, pop(varf));
	}
	if (*varf) {
		f = pop(varf);
	}
	while (aux) {
		push(varf, pop(&aux));
	}
	return f;
}

void main() {
	Nod* stiva = NULL;
	push(&stiva, initFarfurie(34, "alb", 78.5));
	push(&stiva, initFarfurie(37, "negru", 78.5));
	push(&stiva, initFarfurie(39, "gri", 78.5));
	push(&stiva, initFarfurie(40, "alb", 81));

	printf("\n Afisare farfurie cautata:\n");
	Farfurie farfurieCautata = cautareFarfurieById(37, &stiva);
	afisareFarfurie(farfurieCautata);
	free(farfurieCautata.culoare);

	Farfurie f;
	printf("\n Stiva:");
	while (stiva) {
		f = pop(&stiva);
		afisareFarfurie(f);
		free(f.culoare);
	}

	printf("\n------------\n");
	Nod* coada = NULL;
	put(&coada, initFarfurie(12, "Turcoaz", 50.6));
	put(&coada, initFarfurie(22, "Alb", 34.6));
	put(&coada, initFarfurie(24, "Roz", 12.6));
	put(&coada, initFarfurie(36, "Negru", 67.6));
	while (coada) {
		f = pop(&coada);
		afisareFarfurie(f);
		free(f.culoare);
	}

}