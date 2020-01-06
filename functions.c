#include "Linux-word.h"

void Discrimination(List list, char PutString[MAX_LEN]) {
	int count = 0;
	char UseFunction[][MAX_LEN] = { "append\n","delete\n","view\n","quit\n" };

	for (count = 0; count <= 4; count++)
		if (!strcmp(PutString, UseFunction[count]))
			break;

	switch (count) {
	case 0:
		list.append(list);
		break;
	case 1:
		list.deletes(list);
		break;
	case 2:
		list.view(list);
		break;
	case 3:
		list.quit(list);
		break;
	default:
		list.search(list, PutString);
	}
}

List LIST(char file_name[]) {
	List list;

	list.head = (Language*)malloc(sizeof(Language));
	list.head->next = NULL;

	list.isFile = fopen(file_name, "r");

	if (NULL == list.isFile) {
		printf("%s not found\n",list.isFile);
		exit(-1);
	}
	sprintf(list.name,"%s",file_name);
	while (1) {
		Language* NewLanguage = (Language*)malloc(sizeof(Language));

		if(NULL == fgets(NewLanguage->word, MAX_LEN, list.isFile)
			|| NULL == fgets(NewLanguage->meaning, MAX_LEN, list.isFile))
			break;

		NewLanguage->next = list.head->next;
		list.head->next = NewLanguage;
	}
	fclose(list.isFile);

	list.append=Append;
	list.deletes=Deletes;
	list.view=View;
	list.quit=Quit;
	list.search=Search;
	return list;
}

void Append(List list) {
	Language* NewLanguage = (Language*)malloc(sizeof(Language));
	printf("WORD INPUT:"), fgets(NewLanguage->word, MAX_LEN, stdin);
	printf("meaning INPUT:"), fgets(NewLanguage->meaning, MAX_LEN, stdin);

	NewLanguage->next = list.head->next;
	list.head->next = NewLanguage;
}

int Deletes(List list) {
	Language* NewLanguage = list.cur;
	char string[MAX_LEN];
	int Result = 1;
	printf("Delete word: "), fgets(string, MAX_LEN, stdin);

	if (list.head->next == NULL)
		return 0;

	list.before = list.head;
	list.cur = list.head->next;

	Result = strcmp(string, list.cur->word);

	while (Result) {
		if (list.cur->next == NULL)
			return 0;

		list.before = list.cur;
		list.cur = list.cur->next;
		Result = strcmp(string, list.cur->word);

		if (!Result)
			break;
	}

	list.before->next = list.cur->next;
	free(NewLanguage);
	return 1;
}

int View(List list) {
	if (list.head->next == NULL)
		return 0;

	list.cur = list.head->next;

	printf("%s%s", list.cur->word, list.cur->meaning);

	while (1) {
		if (list.cur->next == NULL)
			return 1;

		list.cur = list.cur->next;
		printf("%s%s", list.cur->word, list.cur->meaning);
	}
}

void Quit(List list) {
	list.isFile = fopen(list.name, "w");
	if (NULL == list.isFile) {
		printf("%s not found\n",list.isFile);
		exit(-1);
	}

	list.cur = list.head->next;

	fputs(list.cur->word, list.isFile);
	fputs(list.cur->meaning, list.isFile);

	while (1) {
		if (list.cur->next == NULL) {
			fclose(list.isFile);
			exit(-1);
		}

		list.cur = list.cur->next;
		fputs(list.cur->word, list.isFile);
		fputs(list.cur->meaning, list.isFile);
	}
	free(list.head);
}

void Search(List list, char PutString[MAX_LEN]) {
	int TrueORFalse = 1;

	list.cur = list.head->next;
	TrueORFalse = !strcmp(PutString,list.cur->word);
	while (TrueORFalse != 1) {
		if (list.cur->next == NULL){
			TrueORFalse = 0;
			break;
		}

		list.cur = list.cur->next;
		TrueORFalse = !strcmp(PutString,list.cur->word);
}

	if (TrueORFalse == 1)
		printf("%s%s", list.cur->word, list.cur->meaning);
	else
		printf("Not Found %s", PutString);
}
