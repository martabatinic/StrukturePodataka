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
	struct _student *next;
}Student;

Student **HashTable(int size);
Student *getElement(void);
int UcitajIzDatoteke(Student **Table, char *datoteka);
int PronadiKljuc(char *prezime, int size);
int UnosHash(Student **Table, char *ime, char *prezime, int matBroj, int kljuc);
int IspisHash(Student **Table, int size);
int IspisiListu(Student *Head, int kljuc);
int PronadiMaticniBroj(Student *El);
Student *PronadiEl(Student **Table, char *ime, char *prezime);

int main(void)
{
	Student **Table;

	char ime[MAX];
	char prezime[MAX];
	char datoteka[MAX] = "dat.txt";

	Table = HashTable(SIZE);

	UcitajIzDatoteke(Table, datoteka);

	IspisHash(Table, SIZE);

	printf("Unesite ime i prezime za ispis Maticnog broja [IME PREZIME]: ");
	scanf(" %s %s", ime, prezime);

	PronadiMaticniBroj(PronadiEl(Table, ime, prezime));

	return 0;
}
Student **HashTable(int size) {
	Student **Table = malloc(size * sizeof(Table));

	for (int i = 0; i < size; i++) {
		Table[i] = getElement();
	}

	return Table;
}
Student *getElement(void) {
	Student *noviEl = (Student*)malloc(sizeof(Student));

	memset(noviEl->ime, 0, MAX);
	memset(noviEl->prezime, 0, MAX);
	noviEl->maticniBroj = 0;
	noviEl->next = NULL;

	return noviEl;
}
int UcitajIzDatoteke(Student **Table, char *datoteka) {
	FILE *fp = NULL;

	char ime[MAX];
	char prezime[MAX];
	int matBroj = 0;
	int kljuc = 0;

	fp = fopen(datoteka, "r");

	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", ime, prezime, &matBroj);
		kljuc = PronadiKljuc(prezime, SIZE);
		UnosHash(Table, ime, prezime, matBroj, kljuc);
	}

	fclose(fp);

	return 0;
}
int PronadiKljuc(char *prezime, int size) {
	int suma = 0, kljuc = 0;

	for (int i = 0; i < 5; i++) {
		suma += (int)prezime[i];
	}

	kljuc = suma % SIZE;

	return kljuc;
}
int UnosHash(Student **Table, char *ime, char *prezime, int matBroj, int kljuc) {
	Student *El = (Student*)malloc(sizeof(Student));

	strcpy(El->ime, ime);
	strcpy(El->prezime, prezime);
	El->maticniBroj = matBroj;

	Student *P = Table[kljuc];

	while (P->next != NULL && (strcmp(prezime, P->next->prezime) > 0) && (strcmp(ime, P->next->ime) > 0))
		P = P->next;

	El->next = P->next;
	P->next = El;

	return 0;
}
int IspisHash(Student **Table, int size) {
	for (int i = 0; i < size; i++) {
		IspisiListu(Table[i], i + 1);
	}

	return 0;
}
int IspisiListu(Student *Head, int kljuc) {

	if (Head->next) {
		Student *P = Head;
		while (P->next != NULL) {
			printf("Kljuc: %d \n", kljuc);
			printf("%s %s %d", P->ime, P->prezime, P->maticniBroj);
			printf("\n");
		}
	}

	else if (Head->next == NULL)
		printf("(%d)---\n", kljuc);
	
	
	return 0;
}
int PronadiMaticniBroj(Student *El) {
	if (El == NULL)
		printf("Unesen nepostojeci maticni broj!");
	else
		printf("Maticni broj: %d", El->maticniBroj);

	return 0;
}
Student *PronadiEl(Student **Table, char *ime, char *prezime) {
	int kljuc = PronadiKljuc(prezime, SIZE);

	Student *El = Table[kljuc];

	while (El->next != NULL && El->next->prezime != prezime && El->next->ime != ime)
		El = El->next;

	return El;
}
