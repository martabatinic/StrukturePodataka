#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

/*4. Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani. */

typedef struct _polinom {
	int koeficijent;
	int eksponent;
	Polinom *next;
}Polinom;

int Ucitaj(Polinom *Head);
int Ispis(Polinom *Head);
int ZbrojiPolinome(Polinom *Head1, Polinom *Head2, Polinom *HeadZbroj);
int UnosZbroja(Polinom *HeadZbroj, int koef, int eks);
int PomnoziPolinome(Polinom *Head1, Polinom *Head2, Polinom *HeadUmnozak);
int SortirajUmnozak(Polinom *HeadUmnozak);

int main()
{
	Polinom *Head1 = (Polinom*)malloc(sizeof(Polinom));
	Polinom *Head2 = (Polinom*)malloc(sizeof(Polinom));
	Polinom *HeadZbroj = (Polinom*)malloc(sizeof(Polinom));
	Polinom *HeadUmnozak = (Polinom*)malloc(sizeof(Polinom));

	Head1->next = NULL;
	Head2->next = NULL;
	HeadZbroj->next = NULL;
	HeadUmnozak->next = NULL;

	Ucitaj(Head1);
	printf("Prvi polinom:\n");
	Ispis(Head1);

	Ucitaj(Head2);
	printf("Drugi polinom:\n");
	Ispis(Head2);

	ZbrojiPolinome(Head1, Head2, HeadZbroj);
	printf("Zbroj polinoma:\n");
	Ispis(HeadZbroj);

	PomnoziPolinome(Head1, Head2, HeadUmnozak);
	SortirajUmnozak(HeadUmnozak);
	printf("UmnozakPolinoma:\n");
	Ispis(HeadUmnozak);

	return 0;
}
int Ucitaj(Polinom *P)
{
	Polinom *q;
	Polinom *temp = NULL;
	q = (Polinom*)malloc(sizeof(Polinom));
	temp = P;
	char* filename;

	FILE* fp = NULL;
	fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("Greska u otvaranju datoteke!\n");
	}

	while (!feof(fp)) {

		q = Stvori(q);

		fscanf(fp, " %d %d", &q->koeficijent, &q->eksponent);

		while (temp->next != NULL && temp->next->eksponent > q->eksponent)
			temp = temp->next;
		if (temp->next != NULL && temp->next->eksponent == q->eksponent) {
			temp->next->koeficijent += q->koeficijent;

			if (temp->next->koeficijent == 0) {
				q = temp->next;
				temp->next = q->next;
			}
		}
		else {
			q->next = temp->next;
			temp->next = q;
		}
	}

	fclose(fp);

	return 0;
}
int Ispis(Polinom *Head)
{
	Polinom *P = Head->next;
	while (P != NULL) {
		printf("%d x^ %d +", P->koeficijent, P->eksponent);
		P = P->next;
	}
}
int ZbrojiPolinome(Polinom *Head1, Polinom *Head2, Polinom *HeadZbroj)
{
	Head1 = Head1->next;
	Head2 = Head2->next;

	while (Head1 != NULL && Head2 != NULL) {
		if (Head1->eksponent == Head2->eksponent) {
			UnosZbroja(HeadZbroj, Head1->koeficijent + Head2->koeficijent, Head1->eksponent);
			Head1 = Head1->next;
			Head2 = Head2->next;
		}
		else if (Head1->eksponent > Head2->eksponent) {
			UnosZbroja(HeadZbroj, Head1->koeficijent, Head1->eksponent);
			Head1 = Head1->next;
		}
		else {
			UnosZboja(HeadZbroj, Head2->koeficijent, Head2->eksponent);
			Head2 = Head2->next;
		}	
	}
	return 0;
}
int UnosZbroja(Polinom *HeadZbroj, int koef, int eks)
{
	Polinom *q;
	q = (Polinom*)malloc(sizeof(Polinom));

	while (HeadZbroj != NULL && HeadZbroj->next->eksponent > eks)
		HeadZbroj = HeadZbroj->next;

	q->koeficijent = koef;
	q->eksponent = eks;
	q->next = HeadZbroj->next;
	HeadZbroj->next = q;

	return 0;
}
int PomnoziPolinome(Polinom *Head1, Polinom *Head2, Polinom *HeadUmnozak)
{
	Head1 = Head1->next;
	Head2 = Head2->next;

	while (Head1 != NULL) {
		while (Head2 != NULL) {
			UnosZbroja(HeadUmnozak, Head1->koeficijent * Head2->koeficijent, Head1->eksponent + Head2->eksponent);
			Head2 = Head2->next;
		}
		Head1 = Head1->next;
	}
	return 0;
}
int SortirajUmnozak(Polinom *HeadUmnozak)
{
	Polinom *temp;
	temp = (Polinom*)malloc(sizeof(Polinom));

	HeadUmnozak = HeadUmnozak->next;
	temp = HeadUmnozak->next;

	while (HeadUmnozak != NULL && temp != NULL) {
		if (HeadUmnozak->eksponent == temp->eksponent) {
			HeadUmnozak->koeficijent = HeadUmnozak->koeficijent + temp->koeficijent;
			HeadUmnozak->next = temp->next;
			free(temp);
			temp = HeadUmnozak->next;
		}
		else {
			HeadUmnozak = HeadUmnozak->next;
			temp = temp->next;
		}
	}
	return 0;
}
