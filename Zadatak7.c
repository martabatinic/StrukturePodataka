#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*7. Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
rezultat. Stog je potrebno realizirati preko vezane liste.*/

#define MAX 1024

typedef struct _element{
	float broj;
	struct Element *next;
} Element;

int Push(Element *Head, float broj);
float Pop(Element *Head);
int IzracunajPostfix(Element *Head, char *filename);
int IzracunajOperaciju(Element *Head, char operator);

int main()
{
	Element *Head = (Element*)malloc(sizeof(Element));

	if (!Head)
		return -1;

	Head->next = NULL;
	char filename[MAX];

	printf("Unesi ime datoteke s postfix izrazom: ");
	scanf("%s", filename);

	IzracunajPostfix(Head, filename);

	if (!Head->next)
		return -1;

	printf("%.3f\n", Head->next->broj);

	return 0;
}

int Push(Element *Head, float broj)
{
	Element *noviEl = (Element*)malloc(sizeof(Element));

	if (!noviEl)
		return -1;

	noviEl->next = Head->next;
	Head->next = noviEl;
	noviEl->broj = broj;

	return 0;
}

float Pop(Element *Head)
{
	float broj = Head->next->broj;
	Element *temp = Head->next;
	Head->next = Head->next->next;

	free(temp);
	return broj;
}

int IzracunajPostfix(Element *Head, char *filename)
{
	FILE *fp = NULL;
	char buffer[MAX];
	char *pBuffer = buffer;
	float operand1 = 0;
	float operand2 = 0;

	fp = fopen(filename, "r");

	if (!fp)
		return -1;

	fgets(buffer, MAX, fp);

	fclose(fp);

	while (strlen(pBuffer) > 0)
	{
		char operator= 0;
		int offset = 0;
		float broj = 0;
		if (sscanf(pBuffer, " %f%n", &broj, &offset) == 1)
		{
			pushStack(Head, broj);
			pBuffer += offset;
		}
		else
		{
			sscanf(pBuffer, " %c%n", &operator, &offset);
			izracunajOperaciju(Head, operator);
			pBuffer += offset;
		}
	}

	return 0;
}

int IzracunajOperaciju(Element* Head, char operator)
{
	float operand1 = 0;
	float operand2 = 0;

	switch (operator)
	{
	case ('*'):
		operand1 = Pop(Head);
		operand2 = Pop(Head);
		Push(Head, operand1 * operand2);
		break;
	case ('/'):
		operand1 = Pop(Head);
		operand2 = Pop(Head);
		Push(Head, operand2 / operand1);
		break;
	case ('+'):
		operand1 = Pop(Head);
		operand2 = Pop(Head);
		Push(Head, operand1 + operand2);
		break;
	case ('-'):
		operand1 = Pop(Head);
		operand2 = Pop(Head);
		Push(Head, operand2 - operand1);
		break;
	}

	return 0;
}
