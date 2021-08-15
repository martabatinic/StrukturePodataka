#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*3. Prethodnom zadatku dodati funkcije:
a) dinamički dodaje novi element iza određenog elementa,
b) dinamički dodaje novi element ispred određenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) čita listu iz datoteke.*/


#define MAX 1024

typedef struct _osoba {
	char ime[MAX];
	char prezime[MAX];
	int godinaRodenja;
	struct _osoba *next;
} Osoba;

Osoba *UnosPodataka(void);
int DodatiElementNaPocetak(Osoba *El, Osoba *Head);
int IspisElemenata(Osoba *Head);
int DodatiElementNaKraj(Osoba *El, Osoba *Head);
Osoba *PronadiElementPoPrezimenu(Osoba *Head, char *prezime);
int IzbrisiElement(Osoba *El, Osoba *Head);
int DodajElementIza(Osoba *noviEl, Osoba *El);
int DodajElementIspred(Osoba *Head, Osoba *El);
int SortirajListu(Osoba *Head);
int ZamijeniPozicije(Osoba *Head, Osoba *El1, Osoba *El2);
Osoba *PronadiPrethodniElement(Osoba *Head, Osoba *El);
Osoba *PronadiZadnjiElement(Osoba *Head);
int SpremiListuUDatoteku(Osoba *Head, char *datoteka);
int UcitajListuIzDatoteke(Osoba *Head, char *datoteka);

int main(void)
{
	Osoba *Head = (Osoba*)malloc(sizeof(Osoba));
	Head->next = NULL;

	int a = 0;
	char prezime[MAX];
	char datoteka[MAX];
	Osoba *El = (Osoba*)malloc(sizeof(Osoba));

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
		DodatiElementNaPocetak(UnosPodataka(), Head);
		break;
	case(2):
		IspisElemenata(Head);
		break;
	case(3):
		DodatiElementNaKraj(UnosPodataka(), Head);
		break;
	case(4):
		printf("Upisite prezime elementa kojeg zelite pronaci: ");
		scanf("%s", prezime);
		El = PronadiElementPoPrezimenu(Head, prezime);
		break;
	case(5):
		printf("Upisite prezime elementa kojeg zelite izbrisati: ");
		scanf("%s", prezime);
		IzbrisiElement(PronadiElementPoPrezimenu(Head, prezime), Head);
		break;
	case(6):
		printf("Upisite prezime elementa iza kojeg zelite dodati novi element: ");
		scanf("%s", prezime);
		DodajElementIza(UnosPodataka(), PronadiElementPoPrezimenu(Head,prezime));
		break;
	case(7):
		printf("Upisite prezime elementa ispred kojeg zelite dodati novi element: ");
		scanf("%s", prezime);
		DodajElementIspred(Head, PronadiElementPoPrezimenu(Head, prezime));
		break;
	case(8):
		SortirajListu(Head);
		break;
	case(9):
		printf("Upisite ime datoteke: ");
		scanf("%s", datoteka);
		SpremiListuUDatoteku(Head, datoteka);
		break;
	case(10):
		printf("Upisite ime datoteke: ");
		scanf("%s", datoteka);
		UcitajListuIzDatoteke(Head, datoteka);
		break;
	default:
		printf("Krivi unos");
	}

	return 0;
}
Osoba *UnosPodataka(void) {
	Osoba *El = (Osoba*)malloc(sizeof(Osoba));

	printf("Unesite ime, prezime i godinu rodenja: \n");
	scanf("%s %s %d", El->ime, El->prezime, &(El->godinaRodenja));

	return El;
}
int DodatiElementNaPocetak(Osoba *El, Osoba *Head) {

	El->next = Head->next;
	Head->next = El;

	return 0;
}
int IspisElemenata(Osoba *Head) {
	Osoba *P = Head->next;

	while (P != NULL) {
		printf("%s %s %d", P->ime, P->prezime, P->godinaRodenja);
		P = P->next;
	}

	return 0;
}
int DodatiElementNaKraj(Osoba *El, Osoba *Head) {
	Osoba *P = Head->next;

	while (P != NULL)
		P = P->next;

	P->next = El;
	El->next = NULL;

	return 0;
}
Osoba *PronadiElementPoPrezimenu(Osoba *Head, char *prezime) {
	Osoba *P = Head->next;

	while (P != NULL && P->prezime != prezime)
		P = P->next;

	return P;
}
int IzbrisiElement(Osoba *El, Osoba *Head) {
	Osoba *P = Head->next;

	while (P != NULL && P->next != El)
		P = P->next;

	P->next = El->next;
	free(El);

	return 0;
}
int DodajElementIza(Osoba *noviEl, Osoba *El) {

	noviEl->next = El->next;
	El->next = noviEl;

	return 0;
}
int DodajElementIspred(Osoba *Head, Osoba *El) {
	
	Osoba *noviEl = (Osoba*)malloc(sizeof(Osoba));
	Osoba *P = Head;

	while (P != NULL && P->next != El)
		P = P->next;

	DodajElementIza(UnosPodataka(), P);

	return 0;
}
int SortirajListu(Osoba *Head) {
	Osoba *X = Head->next;
	Osoba *Y = NULL;

	while (Head->next != Y) {
		while (X->next != Y) {
			if (strcmp(X->prezime, X->next->prezime) > 0) {
				ZamijeniPozicije(Head, X, X->next);
			}
			else
				X = X->next;
		}
	}
	Y = PronadiPrethodniElement(Head, Y);
	X = Head->next;

	return 0;
}
int ZamijeniPozicije(Osoba *Head, Osoba *El1, Osoba *El2) {
	Osoba *prethodniEl = PronadiPrethodniElement(Head, El1);
	Osoba *temp = El2->next;;

	prethodniEl->next = El2;
	El2->next = El1;
	El1->next = temp;

	return 0;
}
Osoba *PronadiPrethodniElement(Osoba *Head, Osoba *El) {
	Osoba *P = Head;

	while (P != NULL && P->next != El)
		P = P->next;

	return P;
}
Osoba *PronadiZadnjiElement(Osoba *Head) {
	return PronadiPrethodniElement(Head, NULL);
}
int SpremiListuUDatoteku(Osoba *Head, char *datoteka) {
	FILE *fp = NULL;
	Osoba *P = Head->next;

	fp = fopen(datoteka, "w");
	if (fp == NULL)
		return -1;

	while (P != NULL) {
		printf(fp, "%s %s %d", P->ime, P->prezime, P->godinaRodenja);
		P = P->next;
	}

	fclose(fp);

	return 0;
}
int UcitajListuIzDatoteke(Osoba *Head, char *datoteka) {
	FILE *fp = NULL;
	int brojOsoba = 0;
	char buffer[MAX];
	Osoba *noviEl = (Osoba*)malloc(sizeof(Osoba));
	Osoba *P = PronadiZadnjiElement(Head);
	
	while (fgets(buffer, MAX, fp))
		brojOsoba++;

	fp = fopen(datoteka, "r");
	if (fp == NULL)
		return -1;

	for (int i = 0; i < brojOsoba; i++) {
		P->next = noviEl;
		noviEl->next = NULL;
		P = P->next;

		scanf(fp, "%s %s %d", noviEl->ime, noviEl->prezime, &(noviEl->godinaRodenja));
	}
	fclose(fp);

	return 0;
}
