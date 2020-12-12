#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

/*5. Za dvije sortirane liste L1 i L2 (mogu se pročitati iz datoteke ili unijeti ručno, bitno je
samo da su sortirane), napisati program koji stvara novu vezanu listu tako da računa:
a) L1L2,
b) L1L2.
Liste osim pokazivača na slijedeću strukturu imaju i jedan cjelobrojni element, po
kojem su sortirane.
*/

typedef struct _lista {
	int broj;
	Lista *next;
}Lista;

int Ucitaj(Lista *Head);
Lista *Stvori(Lista *Head);
Lista *PronadiZadnji(Lista *Head);
int Ispis(Lista *Head);
int IzracunajUniju(Lista *Head1, Lista *Head2, Lista *Unija);
int IzracunajPresjek(Lista *Head1, Lista *Head2, Lista *Presjek);

int main()
{
	Lista *Head1 = (Lista*)malloc(sizeof(Lista));
	Lista *Head2 = (Lista*)malloc(sizeof(Lista));
	Lista *Unija = (Lista*)malloc(sizeof(Lista));
	Lista *Presjek = (Lista*)malloc(sizeof(Lista));

	Head1->next = NULL;
	Head2->next = NULL;
	Unija->next = NULL;
	Presjek->next = NULL;

	Ucitaj(Head1);
	printf("Prva lista:\n");
	Ispis(Head1);

	Ucitaj(Head2);
	printf("Druga lista:\n");
	Ispis(Head2);

	IzracunajUniju(Head1, Head2, Unija);
	printf("Unija listi:\n");
	Ispis(Unija);

	IzracunajPresjek(Head1, Head2, Presjek);
	printf("Presjek listi:\n");
	Ispis(Presjek);

	return 0;
}
int Ucitaj(Lista *Head)
{
	Lista *q = NULL;
	char *filename;

	FILE *fp = NULL;
	fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("Greska u otvaranju datoteke!\n");
	}

	while (!feof(fp)) {
		q = Stvori(Head);
		fscanf(fp, "%d", &q->broj);
	}

	fclose(fp);

	return 0;
}
Lista *Stvori(Lista *Head)
{
	Lista *q;
	Lista *p;
	q = (Lista*)malloc(sizeof(Lista));

	p = PronadiZadnji(Head);

	q->next = p->next;
	p->next = q;

	return q;
}
Lista *PronadiZadnji(Lista *Head)
{
	Lista *q;
	q = Head;

	while (q != NULL && q->next != NULL)
		q = q->next;

	return q;
}
int Ispis(Lista *Head)
{
	Lista *P = Head->next;
	while (P != NULL) {
		printf("%d", P->broj);
		P = P->next;
	}
}
int IzracunajUniju(Lista *Head1, Lista *Head2, Lista *Unija)
{
	Head1 = Head1->next;
	Head2 = Head2->next;

	while (Head1 != NULL && Head2 != NULL) {
		if (Head1->broj > Head2->broj) {
			Unija = Stvori(Unija);
			Unija->broj = Head2->broj;
			Head2 = Head2->next;
		}
		else if (Head1->broj < Head2->broj) {
			Unija = Stvori(Unija);
			Unija->broj = Head1->broj;
			Head1 = Head1->next;
		}
		else {
			Unija = Stvori(Unija);
			Unija->broj = Head1->broj;
			Head1 = Head1->next;
			Head2 = Head2->next;
		}
	}
	if (Head1 == NULL) {
		while (Head2 != NULL) {
			Unija = Stvori(Unija);
			Unija->broj = Head2->broj;
			Head2 = Head2->next;
		}
	}
	if (Head2 == NULL) {
		while (Head1 != NULL) {
			Unija = Stvori(Unija);
			Unija->broj = Head1->broj;
			Head1 = Head1->next;
		}
	}
	return 0;
}
int IzracunajPresjek(Lista *Head1, Lista *Head2, Lista *Presjek)
{
	Head1 = Head1->next;
	Head2 = Head2->next;

	while (Head1 != NULL && Head2 != NULL) {
		if (Head1->broj > Head2->broj)
			Head2 = Head2->next;
		else if (Head1->broj < Head2->broj)
			Head1 = Head1->next;
		else {
			Presjek = Stvori(Presjek);
			Presjek->broj = Head1->broj;
			Head1 = Head1->broj;
			Head2 = Head2->next;
		}
	}
	return 0;
}
