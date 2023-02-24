#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

void schimb(int* a, int* b)
{
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void citire(int** v, int* dim)//I * tipul de data,II* adresa
{
	printf("Dim:");
	scanf("%d", dim);//dim in interiorul functiei citire este o adresa
	(*v) = (int*)malloc(sizeof(int) * (*dim));//(*dim)dereferentiem dim

	for (int i = 0; i < (*dim); i++)
	{
		printf("v[%i]=", i);
		scanf("%d", &(*v)[i]);
		//scanf("v[%i]: %d \n ",((*v)+i);
	}
}

void afisare(int* v, int dim)
{
	for (int i = 0; i < dim; i++)
	{
		printf("\nv[%i]= %d", i, v[i]);
	}
}

int main()
{
	int nr;
	char nume;
	float medie;
	nr = 10;
	nume = 'C';
	medie = 9.3f;
	printf("Numar %d \n", nr);
	printf("Nume %d \n", nume);
	printf("Nume %c \n", nume);
	printf("Medie %.2f \n", medie);

	//char c[10]="hhhhhhhhh";
	char c[10];
	for (int i = 0; i < 9; i++)
	{
		c[i] = 'h';
	}
	c[9] = '\0';
	printf("%s \n", c);

	char* d;
	d = (char*)malloc(sizeof(char) * 10);
	for (int i = 0; i < 9; i++)
	{
		d[i] = 97 + i;//a,b,c...
	}
	d[9] = '\0';
	printf("%s \n", d);

	int a = 7, b = 5;
	schimb(&a, &b);
	printf("a: %d\nb: %d\n", a, b);

	int* v;
	int dim;
	citire(&v, &dim);
	afisare(v, dim);

	return 0;
}