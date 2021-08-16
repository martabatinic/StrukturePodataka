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
	struct _lista *next;
}Lista;

int Unos(Lista *Head);
int Sortiraj(Lista *Head, int El);
int Ispis(Lista *Head);
int Unija(Lista *Head1, Lista *Head2, Lista *HeadUnija);
int Presjek(Lista *Head1, Lista *Head2, Lista *HeadPresjek);

int main(void)
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

	Unija(Head1, Head2, HeadUnija);
	Ispis(HeadUnija);

	Presjek(Head1, Head2, HeadPresjek);
	Ispis(HeadPresjek);

	return 0;
}
int Unos(Lista *Head) {
	int a = 0, El = 0;

	printf("Unesite broj elemenata liste: \n");
	scanf("%d", &a);

	for (int i = 0; i < a; i++) {
		printf("Unesite %d. element liste:\t", i+1);
		scanf("%d", &El);
		Sortiraj(Head, El);
	}

	return 0;
}
int Sortiraj(Lista *Head, int El) {
	Lista *P = Head->next;
	Lista *noviEl = (Lista*)malloc(sizeof(Lista));

	while (P != NULL && P->element < El)
		P = P->next;

	noviEl->next = P->next;
	P->next = noviEl;
	noviEl = El;

	return 0;
}
int Ispis(Lista *Head) {
	Lista *P = Head->next;

	while (P != NULL) {
		printf("%d \t", P->element);
		P = P->next;
	}

	return 0;
}
int Unija(Lista *Head1, Lista *Head2, Lista *HeadUnija) {
	Lista *pHead1 = Head1->next;
	Lista *pHead2 = Head2->next;

	while (pHead1 != NULL && pHead2 != NULL) {
		if (pHead1->element > pHead2->element) {
			Sortiraj(HeadUnija, pHead2->element);
			pHead2 = pHead2->next;
		}
		else if(pHead1->element < pHead2->element) {
			Sortiraj(HeadUnija, pHead1->element);
			pHead1 = pHead2->next;
		}
		else {
			Sortiraj(HeadUnija, pHead1->element);
			pHead1 = pHead2->next;
			pHead2 = pHead2->next;
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
int Presjek(Lista *Head1, Lista *Head2, Lista *HeadPresjek){
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
