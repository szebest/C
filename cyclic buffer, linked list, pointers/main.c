#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define numberAmount 10
#define charLength 20

void generateRomanNumber(char ** dest)
{
	int losowa = rand() % 4000;
	char* number = malloc(charLength);
	int i = 0;
	while (losowa)
	{
		if (losowa >= 1000)
		{
			number[i] = 'M';
			losowa -= 1000;
		}

		else if (losowa >= 900)
		{
			number[i] = 'C';
			i++;
			number[i] = 'M';
			losowa -= 900;
		}

		else if (losowa >= 500)
		{
			number[i] = 'D';
			losowa -= 500;
		}

		else if (losowa >= 400)
		{
			number[i] = 'C';
			i++;
			number[i] = 'D';
			losowa -= 400;
		}

		else if (losowa >= 100)
		{
			number[i] = 'C';
			losowa -= 100;
		}

		else if (losowa >= 90)
		{
			number[i] = 'X';
			i++;
			number[i] = 'C';
			losowa -= 90;
		}

		else if (losowa >= 50)
		{
			number[i] = 'L';
			losowa -= 50;
		}

		else if (losowa >= 40)
		{
			number[i] = 'X';
			i++;
			number[i] = 'L';
			losowa -= 40;
		}

		else if (losowa >= 10)
		{
			number[i] = 'X';
			losowa -= 10;
		}

		else if (losowa >= 9)
		{
			number[i] = 'I';
			i++;
			number[i] = 'X';
			losowa -= 9;
		}

		else if (losowa >= 5)
		{
			number[i] = 'V';
			losowa -= 5;
		}

		else if (losowa >= 4)
		{
			number[i] = 'I';
			i++;
			number[i] = 'V';
			losowa -= 4;
		}

		else if (losowa >= 1)
		{
			number[i] = 'I';
			losowa -= 1;
		}
		i++;
	}
	number[i] = '\0';
	*dest = malloc(strlen(number) + 1);
	strcpy(*dest, number);
	free(number);
}

int wartosc(char c)
{
	switch (c)
	{
		case 'M':
			return 1000;
		break;
		case 'D':
			return 500;
		break;
		case 'C':
			return 100;
		break;
		case 'L':
			return 50;
		break;
		case 'X':
			return 10;
		break;
		case 'V':
			return 5;
		break;
		case 'I':
			return 1;
		break;
		default:
			return -1;
		break;
	}
}

int toDecimal(char* number)
{
	int liczba = 0;
	for (int i = 0; i < strlen(number); i++)
	{
		int liczba1 = wartosc(number[i]);
		if (i + 1 < strlen(number))
		{
			int liczba2 = wartosc(number[i + 1]);
			if (liczba1 < liczba2)
				liczba -= liczba1;
			else
				liczba += liczba1;
		}
		else
			liczba += liczba1;
	}

	return liczba;
}

typedef struct c_buffer
{
	char* start;
	char** liczbaHead;
	char** liczbaTail;
	int count;
	int maxSize;
}c_buffer;

typedef struct lista
{
	char* number;
	struct lista* next;
	struct lista* prev;
}lista;

void dodajNaPoczatekDoListyDwukierunkowej(lista** pToListaHead, lista** pToListaTail, char* liczba)
{
	if ((*pToListaHead) == NULL)
	{
		(*pToListaTail) = (*pToListaHead) = malloc(sizeof(struct lista));
		(*pToListaHead)->next = NULL;
		(*pToListaHead)->prev = NULL;
		(*pToListaHead)->number = malloc(strlen(liczba) + 1);
		strcpy((*pToListaHead)->number, liczba);
	}
	else
	{
		lista* pNowy = malloc(sizeof(struct lista));
		pNowy->next = (*pToListaHead);
		pNowy->prev = NULL;
		pNowy->number = malloc(strlen(liczba) + 1);
		strcpy(pNowy->number, liczba);
		pNowy->next->prev = pNowy;
		(*pToListaHead) = pNowy;
	}
}

int wczytajIZwrocIleWiekszych(lista** pToListaHead, lista** pToListaTail, char** arr, int arrLenght, char* liczba)
{
	for (int i = 0; i < arrLenght; i++)
		dodajNaPoczatekDoListyDwukierunkowej(pToListaHead, pToListaTail, arr[i]);

	int licz = 0;
	lista* wskaznikTmp = (*pToListaHead);
	while (wskaznikTmp != NULL)
	{
		if (toDecimal(wskaznikTmp->number) > toDecimal(liczba))
			licz++;
		wskaznikTmp = wskaznikTmp->next;
	}

	return licz;
}

void usunListeDwukierunkowa(lista** pToListaHead, lista** pToListaTail)
{
	while ((*pToListaHead))
	{
		free((*pToListaHead)->number);
		lista* next = (*pToListaHead)->next;
		free((*pToListaHead));
		(*pToListaHead) = next;
	}
	(*pToListaHead) = (*pToListaTail) = NULL;
}

void initBuffer(c_buffer* pToBuffer, int mSize)
{
	pToBuffer->count = 0;
	pToBuffer->maxSize = mSize;
	pToBuffer->start = calloc(mSize, sizeof(char*));
	pToBuffer->liczbaHead = pToBuffer->start;
	pToBuffer->liczbaTail = pToBuffer->start;
}

void addNumber(c_buffer* pToBuffer, char* number)
{
	if (pToBuffer->count == pToBuffer->maxSize)
		printf("Buffer full\n");
	else
	{
		(*pToBuffer->liczbaHead) = malloc(strlen(number) + 1);
		strcpy((*pToBuffer->liczbaHead), number);
		pToBuffer->liczbaHead++;
		pToBuffer->count++;

		if (pToBuffer->liczbaHead - pToBuffer->maxSize >= pToBuffer->start)
			pToBuffer->liczbaHead = pToBuffer->start;
	}
}

void readNumber(c_buffer* pToBuffer, char** dest)
{
	if (pToBuffer->count == 0)
	{
		printf("Buffer empty\n");
		*dest = NULL;
	}
	else
	{
		free(*dest);
		*dest = malloc(strlen(*pToBuffer->liczbaTail)+1);
		strcpy(*dest, (*pToBuffer->liczbaTail));
		free((*pToBuffer->liczbaTail));
		(*pToBuffer->liczbaTail) = NULL;
		pToBuffer->liczbaTail++;
		pToBuffer->count--;

		if (pToBuffer->liczbaTail - pToBuffer->maxSize >= pToBuffer->start)
			pToBuffer->liczbaTail = pToBuffer->start;
	}
}

void freeBuffer(c_buffer* pToBuffer)
{
	while (pToBuffer->count > 0)
	{
		free((*pToBuffer->liczbaHead));
		pToBuffer->liczbaHead++;
		pToBuffer->count--;

		if (pToBuffer->liczbaTail - pToBuffer->maxSize >= pToBuffer->start)
			pToBuffer->liczbaTail = pToBuffer->start;
	}

	free(pToBuffer->start);
}

int main()
{
	srand(time(NULL));
	char* a = NULL;
	c_buffer buffer;
	initBuffer(&buffer, 5);

	char* arr[numberAmount] = { NULL };

	int index = 0;

	for (int i = 0; i < numberAmount; i++)
	{
		if (buffer.count < buffer.maxSize)
		{
			char* tmp = NULL;
			generateRomanNumber(&tmp);
			addNumber(&buffer, tmp);
			free(tmp);
		}
		else
		{
			readNumber(&buffer, &arr[index]);
			index++;
			i--;
		}
	}

	while (buffer.count > 0)
	{
		readNumber(&buffer, &arr[index]);
		index++;
	}

	lista* head = NULL;
	lista* tail = NULL;

	printf("%d\n", wczytajIZwrocIleWiekszych(&head, &tail, &arr, numberAmount, "MM"));

	usunListeDwukierunkowa(&head, &tail);
	freeBuffer(&buffer);
	return 0;
}