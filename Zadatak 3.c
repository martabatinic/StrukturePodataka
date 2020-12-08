#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

/*.Prethodnom zadatku dodati funkcije:
a) dinamički dodaje novi element iza određenog elementa,
b) dinamički dodaje novi element ispred određenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) čita listu iz datoteke.*/

typedef struct _osoba {
	char ime[MAX];
	char prezime[MAX];
	int godinaRodenja;
	Osoba *next;
}Osoba;

Osoba *UnosPodataka(void);
int UnosPocetak(Osoba *El, Osoba *Head);
int IspisListe(Osoba *Head);
int UnosKraj(Osoba *El, Osoba *Head);
Osoba *TraziElement(char *prezime, Osoba *Head);
int BrisiElement(Osoba *El, Osoba *Head);
int DodajElementIza(Osoba *El, Osoba * noviEl);
int DodajElementIspred(Osoba *Head, Osoba *El);
int SortirajPoPrezimenu(Osoba *Head);
int SpremiUDatoteku(Osoba *Head, char *filename);
int UcitajIzDatoteke(Osoba *Head, char *filename);
Osoba *PronadiZadnjiElement(Osoba *Head);
int ZamijeniPozicije(Osoba *Head, Osoba *x, Osoba *y);
Osoba *PronadiPrethodniElement(Osoba *Head, Osoba *El);

int main(void)
{
	Osoba *Head;
	Head = (Osoba*)malloc(sizeof(Osoba));
	Head->next = NULL;

	int a;
	Osoba *El = NULL;
	char prezime[MAX] = { 0 };
	char filename[MAX] = { 0 };

	printf("Odaberite zeljenu opciju: \n");
	printf("1. Dodati novi element na pocetak liste\n");
	printf("2. Ispisati listu\n");
	printf("3. Dodati novi element na kraj liste\n");
	printf("4. Pronaci element u listi (po prezimenu)\n");
	printf("5. Brisati odredeni element\n");
	printf("6. Dodati element iza nekog elementa\n");
	printf("7. Dodati element ispred nekog elementa\n");
	printf("8. Sortirati listu\n");
	printf("9. Spremiti listu u datoteku\n");
	printf("10. Ucitati listu iz datoteke\n");
	scanf("%d", &a);

	switch (a) {
	case(1):
		UnosPocetak(UnosPodataka(), Head);
		break;
	case(2):
		IspisListe(Head);
		break;
	case(3):
		UnosKraj(UnosPodataka(), Head);
		break;
	case(4):
		printf("Unesite prezime:\t");
		scanf("%s", prezime);
		El = TraziElement(prezime, Head);
		printf("%s %s %d", El->ime, El->prezime, El->godinaRodenja);
		break;
	case(5):
		printf("Unesite prezime:\t");
		scanf("%s", prezime);
		BrisiElement(TraziElement(prezime, Head), Head);
		break;
	case (6):
		printf("Unesi prezime: ");
		scanf(" %s", prezime);
		El = PronadiElement(Head, prezime);
		DodajElementIza(El, unosPodataka());
		break;
	case (7):
		printf("Unesi prezime: ");
		scanf(" %s", prezime);
		El = pronadiElement(Head, prezime);
		DodajElementIspred(Head, El);
		break;
	case (8):
		SortirajPoPrezimenu(Head);
		IspisListe(Head);
		break;
	case (9):
		printf("Unesi ime datoteke: ");
		scanf(" %s", filename);
		SpremiUDatoteku(Head, filename);
		break;
	case (10):
		printf("Unesi ime datoteke: ");
		scanf(" %s", filename);
		UcitajIzDatoteke(Head, filename);
		break;
	default:
		printf("Krivi unos");
	}
	return 0;
}
Osoba *UnosPodataka(void)
{
	Osoba *P = (Osoba*)malloc(sizeof(Osoba));

	printf("Unesite ime, prezime i godinu rodenja: \n");
	scanf("%s %s %d", P->ime, P->prezime, P->godinaRodenja);

	return P;
}
int UnosPocetak(Osoba *El, Osoba *Head)
{
	El->next = Head->next;
	Head->next = El;

	return 0;
}
int IspisListe(Osoba *Head)
{
	Osoba *P = Head->next;
	while (P != NULL) {
		printf("%s %s %d", P->ime, P->prezime, P->godinaRodenja);
		P = P->next;
	}
}
int UnosKraj(Osoba *El, Osoba *Head)
{
	Osoba *P = Head;

	while (P != NULL)
		P = P->next;

	El->next = NULL;
	P->next = El;

	return 0;
}
Osoba *TraziElement(char *prezime, Osoba *Head)
{
	Osoba *P = Head->next;

	while (P != NULL && P->prezime != prezime)
		P = P->next;

	return P;
}
int BrisiElement(Osoba *El, Osoba *Head)
{
	Osoba *P = Head;

	while (P != NULL && P->next != El)
		P = P->next;

	P->next = P->next->next;
	free(El);

	return 0;
}
int DodajElementIza(Osoba *El, Osoba *noviEl)
{
	noviEl->next = El->next;
	El->next = noviEl;

	return 0;
}

int DodajElementIspred(Osoba *Head, Osoba *El)
{
	Osoba *P = Head;
	Osoba *noviEl = (Osoba*)malloc(sizeof(Osoba));

	while (P != NULL && P->next != El)
		P = P->next;

	if (P == NULL) {
		free(noviEl);
		return -1;
	}

	DodajElementIza(P, unosPodataka());

	return 0;
}
int SpremiUDatoteku(Osoba *Head, char *filename)
{
	Osoba *P = Head->next;
	FILE *fp = NULL;
	fp = fopen(filename, "w");

	if (fp == NULL)
		return -1;

	while (P != NULL) {
		fprintf(fp, "%s %s %d\n", P->ime, P->prezime, P->godinaRodenja);
		P = P->next;
	}

	fclose(fp);

	return 0;
}
int UcitajIzDatoteke(Osoba *Head, char *filename)
{

}
