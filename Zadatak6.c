#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define MAX 1000

/*6. Napisati program koji pomoću vezanih listi simulira rad:
a) stoga,
b) reda.
Napomena: Funkcija "push" sprema cijeli broj, slučajno generirani u opsegu od 10 -100.*/

typedef struct _element {
	int broj;
	struct _element *next;
}Element;

int Random(void);
int Push(Element *Head, int broj);
int PopStog(Element *HeadStog);
int PopRed(Element *HeadRed);
int Ispis(Element *Head);

int main(void)
{
	Element *HeadStog = (Element*)malloc(sizeof(Element));
	Element *HeadRed = (Element*)malloc(sizeof(Element));

	HeadStog->next = NULL;
	HeadRed->next = NULL;

	int a = 0;
	int b = 0;

	printf("Odaberite zeljenu opciju:\n");
	printf("1. Dodati broj u stog\n");
	printf("2. Dodati broj u red\n");
	printf("3. Izbaciti broj iz stoga\n");
	printf("4. Izbaciti broj iz reda\n");
	scanf("%d", &a);

	switch(a){
		case(1):
			b = Random();
			Push(HeadStog, b);
			printf("Dodali ste %d broj u stog.\n", b);
			Ispis(HeadStog);
			break;
		case(2):
			b = Random();
			Push(HeadRed, b);
			printf("Dodali ste %d broj u red.\n", b);
			Ispis(HeadRed);
			break;
		case(3):
			b = PopStog(HeadStog);
			printf("Izbacili ste %d broj iz stog.\n", b);
			Ispis(HeadStog);
			break;
		case(4):
			b = PopRed(HeadRed);
			printf("Izbacili ste %d broj iz reda.\n", b);
			Ispis(HeadRed);
			break;
		default:
			printf("Krivi unos");

	}

	return 0;
}
int Random(void) {
	int b = 0;

	b = (rand() % 90) + 10;

	return b;
}
int Push(Element *Head, int broj) {
	Element *P = Head;
	Element *noviEl = (Element*)malloc(sizeof(Element));

	noviEl->next = P->next;
	P->next = noviEl;
	noviEl = broj;
	
	return 0;
}
int PopStog(Element *HeadStog) {
	int b = 0;
	Element *P = HeadStog;
	Element *temp = (Element*)malloc(sizeof(Element));

	b = P->next->broj;
	
	temp = P->next;
	P->next = P->next->next;
	free(temp);

	return b;
}
int PopRed(Element *HeadRed) {
	int b = 0;
	Element *P = HeadRed;
	Element *temp = (Element*)malloc(sizeof(Element));

	while (P->next != NULL)
		P = P->next;

	b = P->next->broj;

	temp = P->next;
	P->next = NULL;
	free(temp);

	return b;
}
int Ispis(Element *Head) {
	Element *P = Head->next;

	while (P != NULL) {
		printf("%d\t", P->broj);
		P = P->next;
	}

	return 0;
}
