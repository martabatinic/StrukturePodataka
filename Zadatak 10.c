#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX 1024
#define ELEMENT 21

/*10. Napisati program koji iz datoteke čita postfiks izraz i zatim stvara stablo proračuna.Iz
gotovog stabla proračuna upisati u datoteku infiks izraz.*/

typedef struct _node{
	char element[ELEMENT];
	Node *lijevo;
	Node *desno;
} Node;

typedef struct _stack{
	char element[ELEMENT];
	Stack *next;
} Stack;

int PostfixToStack(Stack *StackRoot, char *buffer);
int ProcitajIzDatoteke(Stack *StackRoot, char *filename);
int Operand(char element);
int PushStack(Stack *Head, char *znak);
char *PopStack(Stack *Head);
Node *StackToTree(Stack *Head, Node *Root);
Node *Alociranje(void);
int InorderIspis(Node *Root);

int main(void)
{
	char filename[MAX];
	Stack *Head = (Stack*)malloc(sizeof(Stack));

	Node *Root = Alociranje();
	Head->next = NULL;
	memset(Head->element, 0, ELEMENT);

	printf("Unesite ime datoteke: ");
	scanf(" %s", filename);

	ProcitajIzDatoteke(Head, filename);

	Root = StackToTree(Head, Root);

	InorderIspis(Root);

	return 0;
}

int ProcitajIzDatoteke(Stack *StackRoot, char *filename)
{
	FILE *fp = NULL;
	char buffer[MAX] = { 0 };
	fp = fopen(filename, "r");

	if (!fp)
	{
		printf("Datoteka nije otvorena.\n");
		return -1;
	}

	fgets(buffer, MAX, fp);
	PostfixToStack(StackRoot, buffer);

	return 0;
}

int PostfixToStack(Stack *StackRoot, char *buffer)
{
	int offset = 0;
	char znak[ELEMENT] = { 0 };

	while (sscanf(buffer, " %s %n", znak, &offset) == 1)
	{
		PushStack(StackRoot, znak);
		buffer += offset;
		offset = 0;
	}

	return 0;
}

int Operand(char element)
{
	switch (element)
	{
	case '+':
	case '-':
	case '*':
	case '/':
		return 1;
	}
	return 0;
}

int PushStack(Stack *Head, char *znak)
{
	Stack *noviEl = (Stack*)malloc(sizeof(Stack));

	if (!noviEl)
		return -1;

	noviEl->next = Head->next;
	Head->next = noviEl;
	strcpy(noviEl->element, znak);

	return 0;
}

char *PopStack(Stack *Head)
{
	char *tempStr = malloc(sizeof(char));

	if (!Head->next)
		return NULL;

	Stack *temp = Head->next;
	strcpy(tempStr, temp->element);

	Head->next = Head->next->next;
	free(temp);

	return tempStr;
}

Node *StackToTree(Stack *Head, Node *Root)
{
	char *element = PopStack(Head);

	Root = Alociranje();

	if (!element)
		return NULL;

	strcpy(Root->element, element);

	if (Operand(Root->element[0])) {
		Root->desno = StackToTree(Head, Root->desno);
		Root->lijevo = StackToTree(Head, Root->lijevo);
	}

	return Root;
}

Node *Alociranje(void)
{
	Node *noviNode = (Node*)malloc(sizeof(Node));
	noviNode->lijevo = NULL;
	noviNode->desno = NULL;

	return noviNode;
}

int InorderIspis(Node *Root)
{
	if (!Root)
		return 0;

	printf("(");
	InorderIspis(Root->lijevo);
	printf("%s", Root->element);
	InorderIspis(Root->desno);
	printf(")");

	return 0;
}
