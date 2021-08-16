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
	struct _polinom *next;
} Polinom;

int UcitajIzDatoteke(Polinom *Head1, Polinom *Head2, char *fileName);
int ProcitajRed(Polinom *Head, char *line);
int UmetniElementSortirano(Polinom *Head, int koef, int eksp);
int Ispis(Polinom *Head);
int ZbrojiPolinome(Polinom *Head1, Polinom *Head2, Polinom *HeadSuma);
int PomnoziPolinome(Polinom *Head1, Polinom *Head2, Polinom *HeadProdukt);
int Ocisti(Polinom *Head);

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

	printf("Prvi polinom: \n");
	Ispis(Head1);

	printf("\nDrugi polinom: \n");
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
int ProcitajRed(Polinom *Head, char *line) {
	line[strlen(line)] = 0;
	int koeficijent = 0;
	int eksponent = 0;
	char *pRed = line;

	do {
		int n = 0;

		sscanf(pRed, " %d %d%n", &koeficijent, &eksponent, &n);
		pRed += n;

		UmetniElementSortirano(Head, koeficijent, eksponent);

	} while (strlen(pRed) > 1);

	return 0;
}
int UmetniElementSortirano(Polinom *Head, int koef, int eksp) {
	Polinom *P = Head;

	while (P->next != NULL && P->next->eksponent > eksp)
		P = P->next;

	if (P->next != NULL && P->next->eksponent == eksp)
		P->next->koeficijent += koef;

	else {
		Polinom *noviEl = (Polinom*)malloc(sizeof(Polinom));

		if (!noviEl)
			return -1;

		noviEl->next = P->next;
		P->next = noviEl;

		noviEl->koeficijent = koef;
		noviEl->eksponent = eksp;
	}

	return 0;
}
int Ispis(Polinom *Head) {
	Polinom *P = Head->next;

	while (P != NULL) {
		printf("%d x^ %d\n", P->koeficijent, P->eksponent);
		if (P->next != NULL)
			printf("+");
		P = P->next;
	}

	return 0;
}
int ZbrojiPolinome(Polinom *Head1, Polinom *Head2, Polinom *HeadSuma) {
	Polinom *pHead1 = Head1->next;
	Polinom *pHead2 = Head2->next;

	while (pHead1 != NULL) {
		UmetniElementSortirano(HeadSuma, pHead1->koeficijent, pHead1->eksponent);
		Head1 = Head1->next;
	}
	while (pHead2 != NULL) {
		UmetniElementSortirano(HeadSuma, pHead2->koeficijent, pHead2->eksponent);
		Head1 = Head1->next;
	}

	Ocisti(HeadSuma);

	return 0;
}
int PomnoziPolinome(Polinom *Head1, Polinom *Head2, Polinom *HeadProdukt) {
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

	Ocisti(HeadProdukt);

	return 0;
}
int Ocisti(Polinom *Head){
	Polinom *P = Head;
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
