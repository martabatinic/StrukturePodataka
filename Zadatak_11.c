#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define MAX 256
#define SIZE 11

/*11. Napisati kod koji za zadane podatke studenata (matični broj, ime i prezime) pravi
hash tablicu sa zasebnim redovima. Tablica ima 11 mjesta, a funkcija za preslikavanje
ključ računa da se zbraja ASCII vrijednost prvih pet slova prezimena i zatim računa
ostatak cjelobrojnog dijeljenja te vrijednosti s veličinom tablice. Studenti s istim
ključem se pohranjuju u vezanu listu sortiranu po prezimenima i imenima.
Kada se tablica izgradi treba ispisati cijelu tablicu (naglasiti na kojem ključu se nalaze
koji podaci) te ponuditi mogućnost da se za određenog studenta (prezime i ime) ispiše
njegov matični broj.*/

typedef struct _student {
	int maticniBroj;
	char ime[MAX];
	char prezime[MAX];
	struct _student* next;
}Student;

Student** HashTable(int b);
Student *NoviElement(void);
int UcitajIzDatoteke(Student **Table, char *datoteka);
int Unos(Student **Table, char *ime, char *prezime, int br);
int IzracunTablice(char *prezime, int br);
Student *Sortirano(Student *Head, char *ime, char *prezime);
Student *Rewind(Student* Head, char* prezime);

int main(void)
{
	Student **Table;
	char ime[MAX];
	char prezime[MAX];
	char datoteka[MAX];

	Table = HashTable(SIZE);

	printf("Kako se zove datoteka iz koje citate podatke? ");
	scanf("%s", datoteka);
	if (strchr(datoteka, '.') == NULL)
		strcat(datoteka, ".txt");

	UcitajIzDatoteke(Table, datoteka);

	return 0;
}
Student** HashTable(int a){
	Student** Table = malloc(a*sizeof(Student*));

	for (int i = 0; i < a; i++)
		Table[i] = NoviElement();

	return Table;
}
Student *NoviElement(void){
	Student *Element = (Student*)malloc(sizeof(Student));

	memset(Element->ime, 0, MAX);
	memset(Element->prezime, 0, MAX);

	Element->maticniBroj = 0;
	Element->next = NULL;

	return Element;
}
int UcitajIzDatoteke(Student **Table, char *datoteka) {
	char ime[MAX];
	char prezime[MAX];
	int br;
	char buffer[MAX];

	FILE* fp = fopen(datoteka, "r");

	if (fp == NULL)
		printf("Neuspješno alociranje memorije!");

	while (!feof(fp)) {
		fgets(buffer, MAX, fp);
		sscanf(buffer, "%s %s %d", ime, prezime, &br);
		Unos(Table, ime, prezime, br);
	}

	fclose(fp);

	return 0;
}
int Unos(Student **Table, char *ime, char *prezime, int br){
	int pozicija = 0;
	Student *Element = NULL;
	Student *pom = NULL;

	pozicija = IzracunTablice(prezime, SIZE);
	Element = Sortirano(Table[pozicija], ime, prezime);


	strcpy(Element->ime, ime);
	strcpy(Element->prezime, prezime);
	Element->maticniBroj = br;

	return 0;
}
int IzracunTablice(char *prezime, int br){
	int suma = 0;
	
	for (int i = 0; i < 5; i++)
		suma += (int)prezime[i];

	return suma % br;
}
Student *Sortirano(Student *Head, char *ime, char *prezime){
	Student *P = Head;
	Student *pom = NULL;

	while (P->next && strcmp(prezime, P->next->prezime) > 0)
		P = P->next;

	if (P->next && !strcmp(prezime, P->next->prezime)) {
		P = Rewind(Head, prezime);
		while (P->next && !strcmp(prezime, P->next->prezime) && strcmp(ime, P->next->ime) > 0)
			P = P->next;
	}
	pom = P->next;
	P->next = NoviElement();
	P = P->next;
	P->next = pom;

	return P;
}
Student *Rewind(Student* Head, char* prezime)
{
	Student *Element = prezime;

	while (strcmp(Element->next->prezime, prezime))
		Element = Element->next;

	return Element;
}
