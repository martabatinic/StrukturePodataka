#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<ctype.h>

#define MAX 1024

/*9. Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
omogućiti unošenje novog elementa u stablo, ispis elemenata, brisanje i pronalaženje
nekog elementa.*/

typedef struct _stablo {
	int broj;
	struct _stablo *lijevo;
	struct _stablo *desno;
}Stablo;

int getNumber(void);
Stablo *Unesi(Stablo *Root, int broj);
Stablo *AlocirajNovoStablo(int broj);
int Ispis(Stablo *Root, int razmak);
Stablo *IzbrisiElement(Stablo *Root, Stablo *El);
Stablo *TraziElement(Stablo *Root, int broj);
Stablo *PronadiMin(Stablo *Node);

int main(void)
{
	Stablo *Root = NULL;

	do {
		int a = 0;

		printf("Odaberite: \n");
		printf("1. - Unesi novi cvor\n");
		printf("2. - Ispisi elemente stabla\n");
		printf("3. - Izbrisi element stabla\n");
		printf("4. - Pronadi element stabla\n");
		printf("0. - Zatvori program\n");
		scanf("%d", &a);

		switch (a){
			case (1):
				Root = Unesi(Root, getNumber());
				break;
			case(2):
				Ispis(Root, 10);
				break;
			case(3):
				Root = IzbrisiElement(Root, TraziElement(Root, getNumber()));
				break;
			case(4):
				Root = TraziElement(Root, getNumber());
				break;
			default:
					printf("Krivi unos!\n");
				
			
		}

	} while (Root);

	return 0;
}
int getNumber(void){
	int n;

	printf("Unesite broj: \n");
	scanf("%d", &n);

	return n;
}
Stablo *Unesi(Stablo *Root, int broj) {
	if (!Root)
		Root = AlocirajNovoStablo(broj);
	else if (broj < Root->broj)
		Root->lijevo = Unesi(Root->lijevo, broj);
	else if (broj > Root->broj)
		Root->desno = Unesi(Root->desno, broj);

	return Root;
}
Stablo *AlocirajNovoStablo(int broj){
	Stablo *noviRoot = malloc(sizeof(Stablo));

	noviRoot->broj = broj;
	noviRoot->lijevo = NULL;
	noviRoot->desno = NULL;

	return noviRoot;
}
int Ispis(Stablo *Root, int razmak) {
	Stablo *Node = (Stablo*)Root;

	Ispis(Node->desno, razmak + 10);

	for (int i = 0; i < razmak + 10; i++)
		printf(" ");

	printf("%d\n", Node->broj);
	Ispis(Node->lijevo, razmak + 10);

	return 0;
}
Stablo *IzbrisiElement(Stablo *Root, Stablo *El) {
	Stablo *Node = (Stablo *)Root;
	Stablo *temp = NULL;

	if (!Node)
		return NULL;
	else if (El->broj < Node->broj)
		Node->lijevo = IzbrisiElement(Node->lijevo, El);
	else if (El->broj > Node->broj)
		Node->desno = IzbrisiElement(Node->desno, El);
	else if (Node->lijevo && Node->desno){
		temp = PronadiMin(Node->desno); 
		Node->broj = temp->broj;
		Node->desno = IzbrisiElement(Node->desno, Node);
	}
	else{
		temp = Node;
		if (!Node->lijevo)
			Node = Node->desno;
		else
			Node = Node->lijevo;
		free(temp);
	}

	return Node;
}
Stablo *TraziElement(Stablo *Root, int broj) {
	Stablo *Node = (Stablo*)Root;
	
	if (!Node)
		return NULL;
	else if (broj < Node->broj)
		Node = TraziElement(Node->lijevo, broj);
	else if (broj > Node->broj)
		Node = TraziElement(Node->desno, broj);

	return Node;
}
Stablo *PronadiMin(Stablo *Node){
	if (!Node)
		return NULL;
	else if (!Node->lijevo)
		return Node;

	return PronadiMin(Node->lijevo);
}
