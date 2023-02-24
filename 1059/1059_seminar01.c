#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

void interschimbare(int* a, int* b)
{
	int aux;
	//dereferentiere
	aux = *a;
	*a = *b;
	*b = aux;
}

void citesteVector(int** vector, int* nrElemente) {
	printf("\nDimensiune vector:");
	scanf("%d", nrElemente);
	*vector = (int*)malloc((*nrElemente) * sizeof(int));
	for (int i = 0; i < *nrElemente; ++i) {
		printf("v[%d] = ", i);
		//scanf("%d", (*vector)+i);
		scanf("%d", &((*vector)[i]));
	}
}

void main()
{
	int a = 1;
	float b = 10.5;
	char c = 'a';

	printf("%c\n", c);
	printf_s("%c\n", c);

	c = c + 1;
	printf_s("%c\n", c);
	printf_s("%d\n", c);

	printf_s("%d\n", a);
	printf_s("%0.2f\n", b);

	char d[4] = "abc";
	printf_s("%s\n", d);

	char* e = (char*)malloc(4 * sizeof(char));
	e[0] = 97;
	e[1] = 98;
	e[2] = 99;
	e[3] = 0;
	printf_s("%s\n", e);

	int aa = 5;
	int bb = 12;
	interschimbare(&aa, &bb);
	printf_s("%d\n", aa);
	printf_s("%d\n", bb);

	int* vector;
	int nrElemente;
	citesteVector(&vector, &nrElemente);

	for (int i = 0; i < nrElemente; i++)
	{
		printf_s("\t%d\n", vector[i]);
	}
}