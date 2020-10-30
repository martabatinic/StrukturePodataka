#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

/*2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
a) dinamički dodaje novi element na početak liste,
b) ispisuje listu,
c) dinamički dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

typedef struct _osoba {
	char ime[MAX];
	char prezime[MAX];
	int godinaRodenja;
	struct _osoba *next;
}Osoba;

Osoba *UnosPodataka(void);
int UnosPocetak(Osoba *El, Osoba *Head);
int IspisListe(Osoba *Head);
int UnosKraj(Osoba *El, Osoba *Head);
Osoba *TraziElement(char *prezime, Osoba *Head);
int BrisiElement(Osoba *El, Osoba *Head);

int main(void)
{
	Osoba *Head;
	Head = (Osoba*)malloc(sizeof(Osoba));
	if (!Head)
		return -1;
	Head->next = NULL;

	int status = 0;
	do {
		int opcija = 0;
		Osoba *El = NULL;
		char prezime[MAX] = { 0 };

		printf("Odaberite zeljenu opciju: \n");
		printf("1. Dodati novi element na pocetak liste\n");
		printf("2. Ispisati listu\n");
		printf("3. Dodati novi element na kraj liste\n");
		printf("4. Pronaci element u listi (po prezimenu)\n");
		printf("5. Brisati odredeni element\n");
		printf("0. ZATVORI PROGRAM\n");
		scanf("%d", &opcija);

		switch (opcija)
		{
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
		case(0):
			return 1;
		}


	} while (!status);

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

	while (P != NULL && strcmp(P->prezime, prezime))
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
