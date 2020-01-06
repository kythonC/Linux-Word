#ifndef __KYTHON_LINKED_LIST_LIB_H__
#define __KYTHON_LINKED_LIST_LIB_H__

#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#define MAX_LEN 100

typedef struct _LANGUAGE_WORD {
	char word[MAX_LEN];
	char meaning[MAX_LEN];
	struct _LANGUAGE_WORD* next;
}Language;

typedef struct _LINKED_LIST {
	FILE* isFile;
	char name[MAX_LEN];

	Language* head;
	Language* cur;
	Language* before;

	void (*append)(struct _LINKED_LIST);
	int (*deletes)(struct _LINKED_LIST);
	int (*view)(struct _LINKED_LIST);
	void (*quit)(struct _LINKED_LIST);
	void (*search)(struct _LINKED_LIST, char[]);
}List;

List LIST(char[]);
int View(List);
void Append(List);
int Deletes(List);
void Quit(List);
void Search(List, char[]);
void Discrimination(List list, char[]);
#endif
