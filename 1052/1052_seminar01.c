#pragma warning(disable:4996)
#include <stdio.h>
#include <malloc.h>

void interschimbare(int* a, int* b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

void citireVector(int* n, int** vector)
{
	printf("\nDimensiune vector: ");
	scanf("%d", n);// adresa lui n 
	*vector = (int*)malloc((*n) * sizeof(int));
	for (int i = 0; i < *n; i++)
	{
		printf("v[%d]=", i);
		//scanf("%d", &((*vector)[i]));
		scanf("%d", (*vector) + i);
	}
}

void afisareVector(int* vector, int n)
{
	for (int i = 0; i < n; i++) {
		printf("\nv[%d]=%d", i, vector[i]);
	}
}

//ASA NU
//SE AFISEAZA VALORI REZIDUALE
//void afisareVectorSmechera(int* vector)
//{
//	int i = 0;
//	do
//	{
//		printf("\nv[%d]=%d", i, vector[i]);
//		++i;
//	} while (vector[i]);
//}

//ASA NU
//!!! DE VERIFICAT cat ocupa intotdeauna sizeof(vector)
//void afisareVectorCorespunzatoare(int* vector)
//{
//	int dimensiune = sizeof(vector) / sizeof(int);
//	for (int i = 0; i < dimensiune; i++) {
//		printf("\nv[%d]=%d", i, vector[i]);
//
//	}
//}

int main()
{
	int a = 1;
	float b = 1.5;
	char c = 'c';
	printf("%d\n", a);
	printf("%.2f\n", b);
	printf("%c\n", c);

	c = c + 1;
	printf("%c\n", c);
	printf("%d\n", c);

	char sir[5] = "semi";
	printf("%s\n", sir);

	char* sir2;
	sir2 = (char*)malloc(5 * sizeof(char));
	sir2[0] = 97;
	sir2[1] = 'b';
	sir2[2] = 'c';
	sir2[3] = 'd';
	sir2[4] = 0;
	printf("%s\n", sir2);

	int val1 = 5;
	int val2 = 6;
	interschimbare(&val1, &val2);
	printf("%d %d", val1, val2);

	int n, * vector;
	citireVector(&n, &vector);

	afisareVector(vector, n);
	//afisareVectorSmechera(vector);
	//afisareVectorCorespunzatoare(vector);
}

