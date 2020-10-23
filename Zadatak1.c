/*Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata zapisanih u datoteci. 
Nakon toga potrebno je dinamički alocirati prostor za niz struktura studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. 
Na ekran ispisati ime, prezime,apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct student {
	char ime[MAX];
	char prezime[MAX];
	int bodovi;
}Student;

int BrojiStudente(char *datoteka);
void UnesiStudente(char *datoteka, Student *studenti, int broj_studenata);
void IspisiStudente(Student *studenti, int broj_studenata, int max_bodovi);

int main(void)
{
	int broj_studenata = 0;
	int max_bodovi = 0;
	char datoteka[] = "studenti.txt";
	Student *studenti;

	broj_studenata = BrojiStudente(datoteka);
	studenti = (Student*)malloc(broj_studenata*sizeof(Student));

	UnesiStudente(datoteka, studenti, broj_studenata);

	printf("Unesite max broj bodova: ");
	scanf("%d", &max_bodovi);

	IspisiStudente(studenti, broj_studenata, max_bodovi);

  getchar();
  getchar();
	return 0;
}
int BrojiStudente(char *datoteka)
{
	FILE *fp = NULL;
	int br_studenata = 0;
	char buffer[MAX];

	fp = fopen(datoteka, "r");
	if (fp == NULL)
		return -1;

	while (fgets(buffer, MAX, fp)) //reads a line from the specified stream and stores it into the string pointed to
		br_studenata++;

	fclose(fp);

	return br_studenata;
}
void UnesiStudente(char *datoteka, Student *studenti, int broj_studenata)
{
	FILE *fp = NULL;

	fp = fopen(datoteka, "r");
	if (fp == NULL)
		return -1;

	for (int i = 0; i < broj_studenata; i++)
		fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);

	fclose(fp);

	return 0;
}
void IspisiStudente(Student *studenti, int broj_studenata, int max_bodovi)
{
	for (int i = 0; i < broj_studenata; i++) {
		double rel = ((double)studenti[i].bodovi / max_bodovi) * 100;
		printf("Ime: %s\t", studenti[i].ime);
		printf("Prezime: %s\t", studenti[i].prezime);
		printf("Bodovi: %d\t", studenti[i].bodovi);
		printf("Relativni bodovi: %lf\n", rel);
	}
  
	return 0;
}
