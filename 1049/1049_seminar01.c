#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

void swap(int* a, int* b) {
	int aux = *a;
	*a = *b;
	*b = aux;

}

void citireDeLaTastatura(int* dim, int** v)
{
	printf("\nDimensiune: ");
	scanf("%d", dim);
	*v = (int*)(malloc((*dim) * sizeof(int)));
	for (int i = 0; i < *dim; i++)
	{
		printf("v[%d]=", i);
		//scanf("%d", &((*v)[i]));
		scanf("%d", (*v) + i);
	}
}

int main()
{
	int a = 5;
	float b = 3.5;
	char c = 'a';

	printf("%d\n", a);
	printf("%.2f\n", b);
	printf("%c\n", c);
	printf("%d\n", c);//afiseaza codul ascii
	printf("%c\n", c + 1);

	char s[5] = "mama";

	printf("%s\n", s);
	printf("%d\n", strlen(s));

	char* ss = malloc(sizeof(char) * 5);
	for (int i = 0; i < 4; i++)
	{
		ss[i] = 97 + i;
	}
	ss[4] = 0;
	printf("%s\n", ss);


	int x = 2, y = 3;
	swap(&x, &y);
	printf("x=%d, y=%d", x, y);

	int dim;
	int* v;
	citireDeLaTastatura(&dim, &v);

	for (int i = 0; i < dim; i++)
	{
		printf("\nv[%d]=%d",i, v[i]);
	}
}