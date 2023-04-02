#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Student Student;
typedef struct Nod Nod;

struct Student {
	long id;
	char* nume;
	int varsta;
};

struct Nod {
	Nod* next;
	Student inf;
};

Student initializareStudent(long id, char* nume, int varsta) {
	Student s;
	s.id = id;
	s.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(s.nume, nume);
	s.varsta = varsta;
	return s;
}

void afisareStudent(Student s) {
	printf("\nStudentul are id-ul %ld, numele %s si varsta %d", s.id, s.nume, s.varsta);
}

Nod* push(Nod* varf, Student student) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	//nou->inf = initializareStudent(student.id, student.....); //deep copy
	nou->inf = student;
	nou->next = varf;
	//varf = nou;
	return nou;
}

Student pop(Nod** varf) {
	Student student;
	if (*varf != NULL) {
		student =(*varf)->inf;
		Nod* aux = *varf;
		*varf = (*varf)->next;
		free(aux);
	}
	else {
		student.id = -1;
		student.nume = NULL;
		student.varsta = 0;
	}

	return student;
}

void put(Nod** prim, Student student) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = student;
	nou->next = NULL;

	Nod* aux = (*prim);
	if (aux) {
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		(*prim) = nou;
	}
}

Student cautaStudent(long id, Nod** varf) {
	Student s;
	s.id = -1;
	s.nume = NULL;
	s.varsta = 0;

	Nod* stivaAux = NULL;
	while (*varf != NULL && (*varf)->inf.id != id) {
		stivaAux = push(stivaAux, pop(varf));
	}

	if (*varf != NULL) {
		s = pop(varf);
	}

	while (stivaAux != NULL) {
		*varf = push(*varf, pop(&stivaAux));
	}
	return s;
}

void main() {
	Nod* varf = NULL;
	Nod* coada = NULL;
	varf = push(varf, initializareStudent(1, "Ghita", 20));
	varf = push(varf, initializareStudent(2, "Ion", 21));
	varf = push(varf, initializareStudent(3, "Vasile", 50));

	printf("Cautare student cu id 1\n");
	afisareStudent(cautaStudent(1, &varf));

	printf("Afisare stiva\n");
	Student student;
	while (varf) {
		student = pop(&varf);
		afisareStudent(student);
		free(student.nume);
	}

	put(&coada, initializareStudent(4, "Ghita", 20));
	put(&coada, initializareStudent(5, "Ion", 21));
	put(&coada, initializareStudent(6, "Vasile", 50));

	printf("\n\nCOADA: ");
	while (coada) {
		student = pop(&coada);
		afisareStudent(student);
		free(student.nume);
	}
}