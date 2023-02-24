#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>

void schimbare(int* a, int* b) {
	//dereferentiere
	int aux = *a;
	*a = *b;
	*b = aux;
}

void citire(int** vector, int* dimensiune)
{
	printf("dimensiune: ");
	scanf("%i", dimensiune);

	*vector = (int*)malloc(sizeof(int) * (*dimensiune));
	for (int i = 0; i < (*dimensiune); i++)
	{
		printf("v[%i] = ", i);
		scanf("%i", &(*vector)[i]);
	}
}

void afisare_vector(int* vector, int dimensiune)
{
	for (int i = 0; i < dimensiune; i++) {
		printf("v[%i] = %i\n", i, vector[i]);
	}
}

//ASA NU
//!!!DE VERIFICAT cat este intotdeauna sizeof(vector)
//void afisare_fara_dim(int* vector)
//{
//	int dim = sizeof(vector) / sizeof(int);
//	for (int i = 0; i < dim; i++)
//	{
//		printf("v[%i] = %i\n", i, vector[i]);
//	}
//}

void main() {
	int a = 5;
	float b = 2.3;
	char c = 'a';
	printf("%i\n", a);
	printf("%.2f\n", b);
	printf("%c\n", c);
	c++;
	printf("%c\n", c);
	printf("%d\n", c);

	char sir[5] = "abcd";
	printf("%s\n", sir);

	char* al = (char*)malloc(sizeof(char) * 5);
	for (int i = 0; i < 4; i++) {
		al[i] = 'g';
	}
	al[4] = '\0';
	printf("%s\n", al);

	int x = 5, y = 6;
	schimbare(&x, &y);
	printf("%d\n", x);
	printf("%d\n", y);

	int* vector;
	int dimensiune;

	citire(&vector, &dimensiune);
	afisare_vector(vector, dimensiune);
	//afisare_fara_dim(vector);
	//sizeof(pointer)=4/8, in functie de compilator
	printf("%d", sizeof(vector));
}