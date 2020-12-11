#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<malloc.h>

#define MAX 1000

/*7. Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
rezultat.Stog je potrebno realizirati preko vezane liste.*/

typedef struct _element{
	float broj;
	Element *next;
}Element;

int PostfixIzraz(Element *Head, char *filename);

int main()
{
	Element *Head = (Element*)malloc(sizeof(Element));
	Head->next = NULL;

	char filename[MAX];
	printf("Unesite ime datoteke: ");
	scanf("%s", filename);

	PostfixIzraz(Head, filename);

	printf("%f\n", Head->next->broj);

	return 0;
}
int PostfixIzraz(Element *Head, char *filename)
{
	FILE *fp = NULL;
	char buffer[MAX];
	fp = fopen(filename, "r");

	fgets(buffer, MAX, fp);  //reads a line from the specified stream and stores it into the string pointed
	fclose(fp);

	while () {
		
	}
	return 0;
}
