#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<ctype.h>

#define MAX 1024
#define razmak 10

/*9. Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
omogućiti unošenje novog elementa u stablo, ispis elemenata, brisanje i pronalaženje
nekog elementa.*/

typedef struct _stablo {
	int element;
	Stablo *lijevo;
	Stablo *desno;
} Stablo;

int Menu();
Stablo *Operacija(Stablo *Root);
int getNumber();
Stablo *Unesi(Stablo *Root, int element);
void Ispisi(Stablo *Root, int x);
Stablo *Pronadi(Stablo *Root, int x);
Stablo *PronadiNajmanji(Stablo *Root);
Stablo *Izbrisi(const Stablo *Root, Stablo *R);

int main()
{
	Stablo *Root = NULL;
	
	do
	{
		Menu();
		Root = Operacija(Root);
	} while (Root);

	return 0;
}

int Menu() {
	printf("Odaberite:\n");
	printf("1. - Unesi novi cvor\n");
	printf("2. - Ispisi elemente stabla\n");
	printf("3. - Izbrisi element stabla\n");
	printf("4. - Ponovo ispisi izbornik\n");
	printf("0. - Zatvori program\n");
	
	return 0;
}

Stablo *Operacija(Stablo *Root) {
	int x = 0;
	Stablo* S;

	printf("Vas izbor -> ");
	scanf(" %d", &x);

	switch (x) {
	case 1:
		Root = Unesi(Root, getNumber());
		return Root;

	case 2:
		Ispisi(Root, 0);
		return Root;

	case 3:
		S = Pronadi(Root, getNumber());
		Izbrisi(Root, S);
		return Root;

	case 4:
		Menu();
		return Root;

	case 0:
		return NULL;

	default:
		printf("Krivi unos!\n");
	}
}

int getNumber()
{
	int n;
	printf("Unesite broj: ");
	scanf(" %d", &n);

	return n;
}

Stablo *Unesi(Stablo *Root, int element)
{
	if (Root == NULL) {
		Root = (Stablo*)malloc(sizeof(Stablo));

		Root->element = element;
		Root->lijevo = NULL;
		Root->desno= NULL;

		return Root;
	}
	else if (element > Root->element) {
		Root->desno = Unesi(Root->desno, element);
	}
	else if (element < Root->element) {
		Root->lijevo = Unesi(Root->lijevo, element);
	}

	return Root;
}

void Ispisi(Stablo *Root, int x) {

	int i = 0;

	if (Root == NULL)
		return -1;

	x += razmak;

	Ispisi(Root->desno, x);

	printf("\n");
	for (i = razmak; i < x; i++)
		printf(" ");
	printf("%d\n", Root->element);

	Ispisi(Root->lijevo, x);
}

Stablo *Pronadi(Stablo *Root, int x)
{
	

	if (Root == NULL)
		return NULL;

	else if (Root->element == x) {
		return Cvor;
	}

	else if (x > Root->element) {
		return Find(Root->desno, x);
	}

	else if (x < Root->element) {
		return Pronadi(Root->lijevo, x);
	}

	return Root;
}

Stablo *PronadiNajmanji(Stablo *Root)
{
	if (Root == NULL)
		return NULL;
	else if (Root->lijevo == NULL)
		return Root;

	return PronadiNajmanji(Root->lijevo);
}

Stablo *Izbrisi(const Stablo *Root, Stablo *R)
{
	Stablo *Pomocna = (Stablo*)Root;
	Stablo *temp = NULL;

	if (Pomocna == NULL)
		return NULL;

	else if (R->element < Pomocna->element)
		Pomocna->lijevo = Izbrisi(Pomocna->lijevo, R);

	else if (R->element > Pomocna->element)
		Pomocna->desno = Izbrisi(Pomocna->desno, R);

	else if (Pomocna->lijevo && Pomocna->desno) {
		temp = PronadiNajmanji(Pomocna->desno);
		Pomocna->element = temp->element;
		Pomocna->desno = Izbrisi(Pomocna->desno, Pomocna);
	}

	else {
		temp = Pomocna;

		if (Pomocna->lijevo == NULL)
			Pomocna = Pomocna->desno;
		else
			Pomocna = Pomocna->lijevo;

		free(temp);
	}

	return Pomocna;
}
