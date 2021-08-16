#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*7. Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
rezultat. Stog je potrebno realizirati preko vezane liste.*/

#define MAX 1024

typedef struct _element {
	float broj;
	struct _element *next;
} Element;

int Push(Element *Head, float broj);
float Pop(Element *Head);
int IzracunajPostfix(Element *Head, char *datoteka);
int IzracunajOperaciju(Element *Head, char operator);


int main()
{
	Element *Head = (Element*)malloc(sizeof(Element));
	Head->next = NULL;

	char datoteka[MAX];

	printf("Unesi ime datoteke s postfix izrazom: ");
	scanf("%s", datoteka);

	IzracunajPostfix(Head, datoteka);

	if (!Head->next)
		return -1;

	printf("%.3f\n", Head->next->broj);

	return 0;
}
int IzracunajPostfix(Element *Head, char *filename){
	FILE *fp = NULL;
	char buffer[MAX];
	char *pbuffer = buffer;

	fp = fopen(filename, "r");

	if (!fp)
		return -1;

	fgets(buffer, MAX, fp);

	fclose(fp);

	while (strlen(pbuffer) > 0)
	{
		char operator= 0;
		int offset = 0;
		float broj = 0;
		if (sscanf(pbuffer, " %f%n", &broj, &offset) == 1)
		{
			Push(Head, broj);
			pbuffer += offset;
		}
		else
		{
			sscanf(pbuffer, " %c%n", &operator, &offset);
			IzracunajOperaciju(Head, operator);
			pbuffer += offset;
		}
	}

	return 0;
}
int Push(Element *Head, float broj) {
	Element *P = Head;
	Element *noviEl = (Element*)malloc(sizeof(Element));

	noviEl->next = P->next;
	P->next = noviEl;
	noviEl->broj = broj;

	return 0;
}
float Pop(Element *HeadStog) {
	float b = 0;
	Element *P = HeadStog;
	Element *temp = (Element*)malloc(sizeof(Element));

	b = P->next->broj;

	temp = P->next;
	P->next = P->next->next;
	free(temp);

	return b;

}
int IzracunajOperaciju(Element* Head, char operator){
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
