#include <stdio.h>
#include "../CircularBuffer.h"

int main(int argv, char** args) {

	//EXAMPLE OF USE
	CircularBuffer buffer = {.head = -1, .tail = -1 };

	ResponseStatus response_insert = insert_char(&buffer, 'A');
	if (response_insert != OK) {
		printf("ERROR after %s\n", "ResponseStatus insert_char(CircularBuffer* circ_buffer, CUSTOM_TYPE char_to_write)");
		return -1;
	}
	else
		printf("%s successful\n", "ResponseStatus insert_char(CircularBuffer* circ_buffer, CUSTOM_TYPE char_to_write)");

	char returned_char;
	ResponseStatus response_get = get_char(&buffer, &returned_char);
	if (response_get != OK) {
		printf("ERROR after %s\n", "ResponseStatus get_char(CircularBuffer* circ_buffer, CUSTOM_TYPE* returned_char)");
		return -1;
	}
	else
		printf("%s successful\n", "ResponseStatus get_char(CircularBuffer* circ_buffer, CUSTOM_TYPE* returned_char)");
	return 0;
}