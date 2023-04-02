#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Cutie Cutie;
struct Cutie {
	long id;
	char* forma;
	float pret;

};

typedef struct Nod Nod;
struct Nod {
	Nod	* next;
	Cutie info;
};

Cutie initializare(long id, char* forma, float pret)
{
	Cutie c;
	c.id = id;
	c.pret = pret;
	c.forma = (char*)malloc(sizeof(char) * (strlen(forma)+1));
	strcpy(c.forma, forma);

	return c;
}

void push(Cutie c, Nod** varf)
{
	Nod* n;
	n = (Nod*)malloc(sizeof(Nod) * 1);
	n->info = c;

	n->next = *varf;
	*varf = n;
}

void put(Cutie c, Nod** prim)
{
	Nod* n;
	n = (Nod*)malloc(sizeof(Nod) * 1);
	n->info = c;
	n->next = NULL;

	Nod* aux;
	aux = *prim;

	if (aux != NULL)
	{
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = n;
	}
	else
	{
		*prim = n;
	}
}

Cutie pop(Nod** varf)
{
	Cutie c;
	c.id = -1;
	c.forma = NULL;
	c.pret = -1;
	if (*varf)
	{
		c = (*varf)->info;
		Nod* aux=(*varf);
		(*varf) = (*varf)->next;
		free(aux);
	}
	return c;
}

void afis(Cutie c)
{
	printf("Id- ul este %ld , forma este  %s, pretul este %f \n", c.id, c.forma, c.pret);
}

Cutie CautareCutie(long id, Nod** varf)
{
	Cutie c;
	c.id = -1;
	c.forma = NULL;
	c.pret = -1;

	Nod* aux=NULL;
	while ((*varf) != NULL && id != (*varf)->info.id)
	{
		push(pop(varf), &aux);

	}
	if (*varf != NULL)
	{
		c = pop(varf);
	}
	while (aux)
	{
		push(pop(&aux), varf);
	}
	return c;
}

int main()
{
	Nod* varf = NULL;
	Cutie c;
	push(initializare(1001, "patrat", 7.2), &varf);
	push(initializare(1002, "rotund", 5.2), &varf);
	push(initializare(1003, "dreptunghi", 3.4), &varf);
	push(initializare(1004, "romb", 2.9), &varf);

	Cutie CutieCautata = CautareCutie(1001, &varf);
	printf("Afisare Cutie Cautata\n");
	afis(CutieCautata);
	free(CutieCautata.forma);
	
	printf("Afisare Cutie din stiva\n");

	while (varf != NULL)
	{
		c = pop(&varf);
		afis(c);
		free(c.forma);
	}
	
	Nod* coada = NULL;
	put(initializare(101, "patrat", 7.2), &coada);
	put(initializare(102, "rotund", 5.2), &coada);
	put(initializare(103, "dreptunghi", 3.4), &coada);
	put(initializare(104, "romb", 2.9), &coada);

	printf("Afisare coada \n");
	while (coada != NULL)
	{
		c = pop(&coada);
		afis(c);
		free(c.forma);
	}
}
