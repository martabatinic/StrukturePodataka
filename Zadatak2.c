#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
a) dinamički dodaje novi element na početak liste,
b) ispisuje listu,
c) dinamički dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

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

int main(void)
{
	Osoba *Head= (Osoba*)malloc(sizeof(Osoba));
	Head->next = NULL;

	int a = 0;
	char prezime[MAX];
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
