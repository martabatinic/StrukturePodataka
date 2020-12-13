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
	Element *next;
}Element;

int Random(void);
int Push(Element *Head, int broj);
int PopStog(Element *HeadStog);
int PopRed(Element *HeadRed);
void Ispis(Element *Head);

int main()
{
	Element *HeadStog = (Element*)malloc(sizeof(Element));
	Element *HeadRed = (Element*)malloc(sizeof(Element));

	HeadStog->next = NULL;
	HeadRed->next = NULL;

	int a = 0, b = 0;

	printf("Odaberite zeljenu opciju:\n");
	printf("1. Dodati broj u stog\n");
	printf("2. Dodati broj u red\n");
	printf("3. Izbaciti broj iz stoga\n");
	printf("4. Izbaciti broj iz reda\n");
	scanf("%d", &a);

	switch (a)
	{
	case(1):
		b = Random();
		Push(HeadStog, b);
		printf("Dodani broj u stog: %d\n", b);
		Ispis(HeadStog);
		break;
	case(2):
		b = Random();
		Push(HeadRed, b);
		printf("Dodani broj u red: %d\n", b);
		Ispis(HeadRed);
		break;
	case(3):
		b = PopStog(HeadStog);
		printf("Izbaceni broj u stogu: %d\n", b);
		Ispis(HeadStog);
		break;
	case(4):
		b = PopRed(HeadRed);
		printf("Izbaceni broj u redu: %d\n", b);
		Ispis(HeadRed);
		break;
	default:
		printf("Krivi unos");
	}

	return 0;
}
int Random(void)
{
	int b = 0;
	b = (rand() % 90) + 10;

	return b;
}
int Push(Element *Head, int broj)
{
	Element *noviEl = (Element*)malloc(sizeof(Element));

	noviEl->next = Head->next;
	Head->next = noviEl;
	noviEl = broj;

	return 0;
}
int PopStog(Element *HeadStog)
{
	Element *P = HeadStog;
	Element *temp;
	int b = 0;

	b = P->next->broj;
	temp = P->next;
	P->next = P->next->next;
	free(temp);

	return b;
}
int PopRed(Element *HeadRed)
{
	Element *P = HeadRed;
	Element *temp;
	int b = 0;

	while (P->next->next != NULL)
		P = P->next;

	b = P->next->broj;
	temp = P->next;
	P->next = NULL;
	free(temp);

	return b;
}
void Ispis(Element *Head)
{
	Element *P = Head->next;
	while (P != NULL) {
		printf("%d \t", P->broj);
		P = P->next;
	}
	return 0;
}
