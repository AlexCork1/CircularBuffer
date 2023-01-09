#include <stdio.h>
#include "../CircularBuffer.h"

int main(int argv, char** args) {

	//EXAMPLE OF USE

	CircularBuffer buffer{{'\0'}, -1, -1};

	ResponseStatus response_insert = insert_char(&buffer, 'A');
	if (response_insert != OK) {
		printf("ERROR after insert\n");
		return -1;
	}
	char returned_char;
	ResponseStatus response_get = get_char(&buffer, &returned_char);
	if (response_get != OK) {
		printf("ERROR after get\n");
		return -1;
	}
	return 0;
}