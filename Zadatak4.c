#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 512

/*Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.*/

typedef struct _polinom {
	int koeficijent;
	int eksponent;
	Polinom *next;
} Polinom;

int UcitajIzDatoteke(Polinom *Head1, Polinom *Head2, char *fileName);
int UmetniElementSortirano(Polinom *Head, int koeficijent, int eksponent);
int ProcitajRed(Polinom *Head, char *red);
Polinom *PronadiPrethodniElement(Polinom *Head, Polinom *Pozicija);
int ZbrojiPolinome(Polinom *Head1, Polinom *Head2, Polinom *HeadSuma;
int PomnoziPolinome(Polinom *Head1, Polinom *Head2, Polinom *HeadProdukt);
int Ispis(Polinom *Head);
int OcistiNulaElemente(Polinom *Head);


int main(void)
{
	char fileName[] = "eksponenti.txt";

	Polinom *Head1 = (Polinom*)malloc(sizeof(Polinom));
	Polinom *Head2 = (Polinom*)malloc(sizeof(Polinom));
	Polinom *HeadSuma = (Polinom*)malloc(sizeof(Polinom));
	Polinom *HeadProdukt = (Polinom*)malloc(sizeof(Polinom));

	if (!Head1 || !Head2 || !HeadSuma || !HeadProdukt)
		return -1;

	Head1->next = NULL;
	Head2->next = NULL;
	HeadSuma->next = NULL;
	HeadProdukt->next = NULL;

	UcitajIzDatoteke(Head1, Head2, fileName);

	printf("Prvi polinom: \n\t");
	Ispis(Head1);
	printf("\nDrugi polinom: \n\t");
	Ispis(Head2);

	ZbrojiPolinome(Head1, Head2, HeadSuma);
	printf("\nSuma polinoma: \n\t");
	Ispis(HeadSuma);
	PomnoziPolinome(Head1, Head2, HeadProdukt);
	printf("\nUmnozak polinoma: \n\t");
	Ispis(HeadProdukt);
	printf("\n");

	return 0;
}

int UcitajIzDatoteke(Polinom *Head1, Polinom *Head2, char *fileName)
{
	FILE *fp = NULL;
	char line[MAX];
	fp = fopen(fileName, "r");

	fgets(line, MAX, fp);
	ProcitajRed(Head1, line);
	fgets(line, MAX, fp);
	ProcitajRed(Head2, line);

	fclose(fp);
	return 0;
}

int ProcitajRed(Polinom *Head, char *red)
{
	red[strlen(red)] = 0;
	int koeficijent = 0;
	int eksponent = 0;
	char *pRed = red;

	do {
		int n = 0;

		sscanf(pRed, " %d %d%n", &koeficijent, &eksponent, &n);
		pRed += n;

		UmetniElementSortirano(Head, koeficijent, eksponent);
	} while (strlen(pRed) > 1);

	return 0;
}

int UmetniElementSortirano(Polinom *Head, int koeficijent, int eksponent)
{
	Polinom *P = Head;

	while (P->next != NULL && P->next->eksponent > eksponent)
		P = P->next;

	if (P->next != NULL && P->next->eksponent == eksponent) {
		P->next->koeficijent += koeficijent;
	}
	else {
		Polinom *noviEl = (Polinom*)malloc(sizeof(Polinom));

		if (!noviEl)
			return -1;

		noviEl->next = P->next;
		P->next = noviEl;

		noviEl->koeficijent = koeficijent;
		noviEl->eksponent = eksponent;
	}

	return 0;
}


Polinom *PronadiPrethodniElement(Polinom *Head, Polinom *Pozicija)
{
	Polinom *P = Head;

	while (P != NULL && P->next != Pozicija)
		P = P->next;

	return P;
}

int Ispis(Polinom *Head)
{
	Polinom *P = Head->next;

	while (P != NULL) {
		printf("%dx^%d", P->koeficijent, P->eksponent);
		if (P->next != NULL)
			printf(" + ");
		P = P->next;
	}

	return 0;
}

int ZbrojiPolinome(Polinom *Head1, Polinom *Head2, Polinom *HeadSuma)
{
	Polinom *pHead1 = Head1->next;
	Polinom *pHead2 = Head2->next;

	while (pHead1 != NULL) {
		UmetniElementSortirano(HeadSuma, pHead1->koeficijent, pHead1->eksponent);
		pHead1 = pHead1->next;
	}

	while (pHead2 != NULL) {
		UmetniElementSortirano(HeadSuma, pHead2->koeficijent, pHead2->eksponent);
		pHead2 = pHead2->next;
	}

	OcistiNulaElemente(HeadSuma);

	return 0;
}

int PomnoziPolinome(Polinom *Head1, Polinom *Head2, Polinom *HeadProdukt)
{
	Polinom *pHead1 = Head1->next;
	Polinom *pHead2 = Head2->next;

	while (pHead1 != NULL) {
		pHead2 = Head2->next;
		while (pHead2 != NULL) {
			UmetniElementSortirano(HeadProdukt, pHead1->koeficijent * pHead2->koeficijent, pHead1->eksponent + pHead2->eksponent);
			pHead2 = pHead2->next;
		}
		pHead1 = pHead1->next;
	}

	OcistiNulaElemente(HeadProdukt);

	return 0;
}

int OcistiNulaElemente(Polinom *Head)
{
	Polinom *P= Head;
	Polinom *temp;

	while (P->next != NULL) {
		if (!P->next->koeficijent) {
			temp = P->next;
			P->next = P->next->next;
			free(temp);
		}
		P = P->next;
	}

	return 0;
}
