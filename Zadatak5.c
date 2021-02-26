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
kojem su sortirane.*/

typedef struct _lista {
	int element;
	Lista *next;
}Lista;

int Unos(Lista *Head);
int Sortiraj(Lista *Head, int El);
int Ispis(Lista *Head);
int IzracunajUniju(Lista *Head1, Lista *Head2, Lista *HeadUnija);
int IzracunajPresjek(Lista *Head1, Lista *Head2, Lista *HeadPresjek);

int main()
{
	Lista *Head1 = (Lista*)malloc(sizeof(Lista));
	Lista *Head2 = (Lista*)malloc(sizeof(Lista));
	Lista *HeadUnija = (Lista*)malloc(sizeof(Lista));
	Lista *HeadPresjek = (Lista*)malloc(sizeof(Lista));

	Head1->next = NULL;
	Head2->next = NULL;
	HeadUnija->next = NULL;
	HeadPresjek->next = NULL;

	Unos(Head1);
	Ispis(Head1);
	Unos(Head2);
	Ispis(Head2); 

	IzracunajUniju(Head1, Head2, HeadUnija);
	printf("Unija listi:\n");
	Ispis(HeadUnija);

	IzracunajPresjek(Head1, Head2, HeadPresjek);
	printf("Presjek listi:\n");
	Ispis(HeadPresjek);

	return 0;
}
int Unos(Lista *Head)
{
	int n = 0, El = 0;

	printf("Unesite broj elemenata liste:\n");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("Unesi: [%d.] \t", i + 1);
		scanf("%d", &El);
		Sortiraj(Head, El);
	}
	return 0;
}
int Sortiraj(Lista *Head, int El)
{
	Lista *P = Head;
	Lista *noviEl = (Lista*)malloc(sizeof(Lista));

	while (P->next != NULL && P->next->element < El)
		P = P->next;

	noviEl->next = P->next;
	P->next = noviEl;
	noviEl = El;

	return 0;
}
int Ispis(Lista *Head)
{
	Lista *P = Head->next;
	while (P != NULL) {
		printf("%d ", P->element);
		P = P->next;
	}
	printf("\n");

	return 0;
}
int IzracunajUniju(Lista *Head1, Lista *Head2, Lista *HeadUnija)
{
	Head1 = Head1->next;
	Head2 = Head2->next;

	while (Head1 != NULL && Head2 != NULL) {
		if (Head1->element > Head2->element) {
			HeadUnija = Sortiraj(HeadUnija, Head2->element);
			Head2=Head2->next;
		}
		else if (Head1->element < Head2->element) {
			HeadUnija = Sortiraj(HeadUnija, Head1->element);
			Head1 = Head1->next;
		}
		else {
			HeadUnija = Sortiraj(HeadUnija, Head1->element);
			Head1 = Head1->next;
			Head2 = Head2->next;
		}
	}
	if (Head1 == NULL) {
		while (Head2 != NULL) {
			HeadUnija = Sortiraj(HeadUnija, Head2->element);
			Head2 = Head2->next;
		}
	}
	if (Head2 == NULL) {
		while (Head1 != NULL) {
			HeadUnija = Sortiraj(HeadUnija, Head1->element);
			Head1 = Head1->next;
		}
	}

	return 0;
}
int IzracunajPresjek(Lista *Head1, Lista *Head2, Lista *HeadPresjek)
{
	Head1 = Head1->next;
	Head2 = Head2->next;

	while (Head1 != NULL && Head2 != NULL) {
		if (Head1->element > Head2->element)
			Head2 = Head2->next;
		else if (Head1->element < Head2->element)
			Head1 = Head1->next;
		else {
			HeadPresjek = Sortiraj(HeadPresjek, Head1->element);
			Head1 = Head1->next;
			Head2 = Head2->next;
		}
	}

	return 0;
}
