#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

/*. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
a) dinamički dodaje novi element na početak liste,
b) ispisuje listu,
c) dinamički dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

struct _osoba;
typedef struct _osoba *Pozicija;
typedef struct _osoba {
	char ime[MAX];
	char prezime[MAX];
	int godinaRodenja;
	Pozicija *next;
}Osoba;

Pozicija StvoriOsobu(char *ime, char *prezime, int *godinaRodenja);
int UnosNaPocetak(Osoba *element, Pozicija P);
int IspisListe(Pozicija P);
int UnosNaKraj(Osoba *element, Pozicija P);
int TraziEelement(char *element, Pozicija P);

int main(void)
{
	Osoba *Head;
	Head = (Osoba*)malloc(sizeof(Osoba));
	if (!Head)
		return -1;
	Head->next = NULL;
	Pozicija *what;
	Osoba *element = NULL;

	int opcija = 0;
	int n = 0;
	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };
	int godinaRodenja = 0;

	printf("Koliko osoba zelite unijeti?\n");
	scanf("%d", &n);

	for(int i=0;i<n;i++){
		printf("Unesite ime: \n");
		scanf("%s", ime);
		printf("Unesite prezime: \n");
		scanf("%s", prezime);
		printf("Unesite godinu rodenja: \n");
		scanf("%d", &godinaRodenja);

		what = StvoriOsobu(ime, prezime, godinaRodenja);
	} 

	printf("Odaberite opciju: \n");
	printf("1. Dodavanje elementa na pocetak liste \n");
	printf("2. Ispis liste \n");
	printf("3. Dodavanje elementa na kraj liste \n");
	printf("4. Trazi element u listi (po prezimenu \n");
	printf("5. Brisanje elementa iz liste \n");

	scanf("%d", &opcija);

	switch (opcija)
	{
		case(1):
			UnosNaPocetak(what, Head);
			break;
		case(2):
			IspisListe(Head);
			break;
		case(3):
			UnosNaKraj(what, Head);
			break;
		case(4):
			printf("Unesi prezime:\n");
			scanf("%s", prezime);
			element= TraziElement(prezime, Head);
			printf("%s %s %d", element->ime, element->prezime, element->godinaRodenja);
			break;
		case(5):
			printf("Unesi prezime: ");
			scanf(" %s", prezime);
			BrisiElement(TraziElement(prezime, Head), Head);
			break;
	}

	return 0;
}
Pozicija StvoriOsobu(char *ime, char *prezime, int *godinaRodenja)
{
	Pozicija osoba = NULL;
	osoba = (Pozicija)malloc(sizeof(Osoba));

	if (!osoba) {
		printf("Greska!");
		return NULL;
	}

	strcpy(osoba->ime, ime);
	strcpy(osoba->prezime, prezime);
	strcpy(osoba->godinaRodenja, godinaRodenja);
	osoba->next = NULL;

	return osoba;
}
int UnosNaPocetak(Osoba *element, Pozicija P)
{
	element->next = P->next;
	P->next = element;

	return 0;
}
int IspisListe(Pozicija P)
{
	while (P != NULL) {
		printf("%s %s %d", P->ime, P->prezime, P->godinaRodenja);
		P = P->next;
	}
	return 0;
}
int UnosNaKraj(Osoba *element, Pozicija P)
{
	while (P->next != NULL)
		P = P->next;

	element->next = NULL;
	P->next = element;

	return 0;
}
int TraziEelement(char *prezime, Pozicija P)
{
	while (P != NULL && strcmp(P->prezime, prezime))
		P = P->next;
	return P;
}
int BrisiElement(Osoba *element, Pozicija P)
{
	
	while (P != NULL && P->next != element)
		P = P->next;
	if (P == NULL)
		printf("Element ne postoji.\n");
	else {
		P->next = P->next->next;
		free(element);
	}
	return 0;
}
