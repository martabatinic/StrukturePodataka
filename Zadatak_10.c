#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX 1024
#define ELEMENT 21

/*10. Napisati program koji iz datoteke čita postfiks izraz i zatim stvara stablo proračuna.Iz
gotovog stabla proračuna upisati u datoteku infiks izraz.*/

typedef struct _stablo {
	char element[MAX];
	struct _stablo *lijevo;
	struct _stablo *desno;
}Stablo;

typedef struct _stog {
	char element[MAX];
	struct _stog *next;
}Stog;

Stablo* StvoriStablo(void);
int UcitajDatoteku(Stog *Head);
int UcitajPostfixIzraz(Stog *Head, char *buffer);
int Push(Stog *Head, char *znak);
Stablo *Proracun(Stablo *Root, Stog *Head);
char *Pop(Stog* Head);
int ProvjeraZnaka(char znak);
int InorderIspis(Stablo *Root);

int main()
{
	Stog *Head = (Stog*)malloc(sizeof(Stog));
	Head->next = NULL;

	if (!Head)
		printf("Greska u alokaciji memorije <head stog>!\n");

	memset(Head->element, '0', MAX);     //The memset() function returns str, the pointer to the destination string. 

	Stablo *Root;
	Root = StvoriStablo();

	UcitajDatoteku(Head);

	Root = Proracun(Root, Head);

	InorderIspis(Root);

	return 0;
}
Stablo* StvoriStablo(void){
	Stablo *Root = (Stablo*)malloc(sizeof(Stablo));

	if (!Root)
		printf("Greska u alokaciji memorije <stablo novi>!\n");

	Root->lijevo = NULL;
	Root->desno= NULL;

	return Root;
}
int UcitajDatoteku(Stog *Head) {
	char datoteka[MAX];
	char buffer[MAX];

	memset(buffer, '0', MAX);

	printf("Kako se zove datoteka koju zelite procitati? ");
	scanf("%s", &datoteka);

	if (strchr(datoteka, '.') == NULL) //If '.' is found, a pointer to it is returned. If not, NULL is returned.
		strcat(datoteka, ".txt");

	FILE *fp = NULL;
	fp = fopen(datoteka, "r");

	if (fp == NULL)
		printf("Greska u otvaranju datoteke!\n");

	fgets(buffer, MAX, fp);

	UcitajPostfixIzraz(Head, buffer);

	return 0;
}
int UcitajPostfixIzraz(Stog *Head, char *buffer) {
	int pomak = 0;
	char znak[MAX];

	memset(znak, '0', MAX);

	while (sscanf(buffer, " %s %n", znak, &pomak) == 1) {
		Push(Head, znak);

		buffer += pomak;
		pomak = 0;
	}
	return 0;
}
int Push(Stog *Head, char *znak) {
	Stog *P = (Stog*)malloc(sizeof(Stog));

	P->next = Head->next;
	Head->next = P;
	strcpy(P->element, znak);

	return 0;
}
Stablo *Proracun(Stablo *Root, Stog *Head) {
	char *string = Pop(Head);

	Root = StvoriStablo();

	strcpy(Root->element, string);

	if (ProvjeraZnaka(Root->element[0])) {
		Root->desno = Proracun(Root->desno, Head);
		Root->lijevo = Proracun(Root->lijevo, Head);
	}

	return Root;
}
char *Pop(Stog* Head){
	char pomocni[MAX];

	if (Head->next == NULL) 
		printf("Greska, prazan stog!\n");

	Stog *temp;

	temp = Head->next;
	strcpy(pomocni, temp->element);
	Head->next = Head->next->next;
	free(temp);

	return pomocni;
}
int ProvjeraZnaka(char znak){
	if (znak == '+')
		return 1;
	else if (znak == '-')
		return 1;
	else if (znak == '*')
		return 1;
	else if (znak == '/')
		return 1;

	else
		return 0;
}
int InorderIspis(Stablo *Root) {
	InorderIspis(Root->desno);

	printf("%s", Root->element);

	InorderIspis(Root->lijevo);

	return 0;
}
