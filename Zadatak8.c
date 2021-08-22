#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*8. Napisati program koji pomoću vezanih listi (stabala) predstavlja strukturu direktorija.
Omogućiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Točnije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

#define MAX 50

typedef struct _stablo {
	char ime[MAX];
	struct _stablo *child;
	struct _stablo *sibling;
}Stablo;

typedef struct _stog {
	Stablo *directory;
	struct _stog *next;
	struct _stog *prev;
}Stog;

int Menu(Stablo *Root, Stog *Head);
int Linija(Stog *Head, Stablo *Root, Stablo *currentFile);
Stog *PronadiPosljednji(Stog *Head);
int MakeDir(Stablo *currentFile);
Stablo *cd(Stablo *currentFile, Stog *Head);
Stablo *Pronadi(char *name, Stablo *currentFile);
int PushStog(Stog *Head, Stablo *directory);
Stablo *Back(Stablo *currentFile, Stog *Head);
Stablo *PopStog(Stog *Head);
int Dir(Stablo *currentFile);

int main(void)
{
	Stablo *Root = (Stablo*)malloc(sizeof(Stablo));
	Root->child = NULL;
	Root->sibling = NULL;

	Stog *Head = (Stog*)malloc(sizeof(Stog));
	Head->next = NULL;
	Head->prev = NULL;

	int status = 0;

	do {
		status = Menu(Root, Head);
	} while (!status);

	return 0;
}
int Menu(Stablo *Root, Stog *Head) {
	Stablo *CurrentFile = Root;
	char command[MAX] = { 0 };

	printf("md <filename> - Dodaj novi direktorij\n");
	printf("cd <filename> - Otvori direktorij\n");
	printf("cd.. - Zatvoriti direktorij\n");
	printf("dir - Ispisi listu direktorija u trenutnome direktoriju\n");
	printf("refresh - Ponovo ispisi izbornik\n");
	printf("exit - Izlaz\n");

	while (1) {
		Linija(Head, Root, CurrentFile);
		scanf("%s", command);

		if (!strcmp(command, "md")) {
			MakeDir(CurrentFile);
		}
		else if (!strcmp(command, "cd")) {
			CurrentFile = cd(CurrentFile, Head);
		}
		else if (!strcmp(command, "cd..")) {
			CurrentFile = Back(CurrentFile, Head);
		}
		else if (!strcmp(command, "dir")) {
			Dir(CurrentFile);
		}
		else if (!strcmp(command, "exit")) {
			return 1;
		}
		else if (!strcmp(command, "refresh")) {
			return 0;
		}
		else
			printf("Naredba nije pronadena!\n");
	}

	return 0;
}
int Linija(Stog *Head, Stablo *Root, Stablo *currentFile){
	Stog* P;

	P = PronadiPosljednji(Head);

	if (Head->next == NULL) {
		printf("%s>", Root->ime);
		return 0;
	}

	while (P->prev != NULL) {
		printf("%s>", P->directory->ime);
		P = P->prev;
	}

	printf("%s>", currentFile->ime);

	return 0;
}
Stog *PronadiPosljednji(Stog *Head){
	Stog *P;;
	P = Head->next;

	if (P == NULL) {
		return NULL;
	}

	while (P->next != NULL) {
		P = P->next;
	}

	return P;
}
int MakeDir(Stablo *currentFile) {
	Stablo* directory = (Stablo*)malloc(sizeof(Stablo));

	if (currentFile->child != NULL) {
		currentFile = currentFile->child;
		while (currentFile->sibling != NULL) {
			currentFile = currentFile->sibling;
		}
		currentFile->sibling = directory;
	}
	else
		currentFile->child = directory;

	printf("Unesite ime direktorija: ");
	scanf(" %s", directory->ime);

	directory->sibling = NULL;
	directory->child = NULL;

	return 0;
}
Stablo *cd(Stablo *currentFile, Stog *Head){
	Stablo *SearchedFile;
	char imeDir[MAX];

	printf("Koji direktorij zelite otvoriti: ");
	scanf("%s", imeDir);

	if (currentFile->child == NULL) {
		printf("Nema direktorija koji mozete otvoriti!\n");
		return currentFile;
	}

	SearchedFile = Pronadi(imeDir, currentFile);
	if (SearchedFile == 0) {
		printf("Direktorij nije pronaden\n");
		return currentFile;
	}

	PushStog(Head, currentFile);

	return SearchedFile;
}
Stablo *Pronadi(char *name, Stablo *currentFile) {
	if (currentFile->child == NULL) {
		printf("Direktorij je prazan!");
		return 0;
	}

	currentFile = currentFile->child;

	while (strcmp(name, currentFile->ime) != 0 && currentFile->sibling != NULL) {
		currentFile = currentFile->sibling;
	}

	if (currentFile->sibling == NULL) {
		if (strcmp(name, currentFile->ime) != 0)
			return 0;
		else
			return currentFile;
	}

	else
		return currentFile;
}
int PushStog(Stog *Head, Stablo *directory) {
	Stog *q = (Stog*)malloc(sizeof(Stog));

	q->next = Head->next;
	q->prev = Head;
	if (Head->next != NULL) {
		Head->next->prev = q;
	}
	Head->next = q;
	q->directory = directory;

	return 0;
}
Stablo *Back(Stablo *currentFile, Stog *Head){
	Stablo* SearchedFile;

	SearchedFile = PopStog(Head);

	if (SearchedFile == NULL) {
		printf("Ne moze se izaci iz root direktorija!\n");
		SearchedFile = currentFile;
	}

	return SearchedFile;
}
Stablo *PopStog(Stog *Head) {
	Stog *q = (Stog*)malloc(sizeof(Stog));
	Stablo *p;

	if (Head->next == NULL)
		return NULL;

	q = Head->next;
	p = q->directory;
	Head->next = Head->next->next;
	if (Head->next != NULL)
		Head->next->prev = Head;
	free(q);

	return p;
}
int Dir(Stablo *currentFile) {
	if (currentFile->child == NULL) {
		printf("Prazan direktorij!\n");
		return 0;
	}

	currentFile = currentFile->child;

	printf("DIRECTORIES: \n");
	printf("\t- %s\n", currentFile->ime);

	while (currentFile->sibling != NULL) {
		printf("\t- %s\n", currentFile->sibling->ime);
		currentFile = currentFile->sibling;
	}

	return 0;
}
