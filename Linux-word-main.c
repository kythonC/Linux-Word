#include "Linux-word.h"

int main(void) {
	List list = LIST(FILE_);
	char PutString[MAX_LEN];

	while(1){
		fgets(PutString,MAX_LEN,stdin);
		Discrimination(list, PutString);
	}
	return 0;
}
