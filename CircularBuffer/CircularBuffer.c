/*
 * CircularBuffer.c
 *      Author: AlexCork
 */

#include "CircularBuffer.h"

ResponseStatus get_char(CircularBuffer* circ_buffer, CUSTOM_TYPE* returned_char) {
	//buffer is empty
	if (circ_buffer->tail < 0 && circ_buffer->head < 0) {
		*returned_char = 0;
		return NO_DATA_TO_RETURN;
	}
	//something was in buffer but this is the last char to read
	//we can reset both "pointers" because there is no char left in the buffer
	//	which is the same as buffer being empty
	else if (circ_buffer->tail == circ_buffer->head) {
		*returned_char = circ_buffer->buffer[circ_buffer->tail];
		circ_buffer->tail = -1;
		circ_buffer->head = -1;
		return OK;
	}
	else {
		//there is character in buffer
		*returned_char = circ_buffer->buffer[circ_buffer->tail];

		//move tail to next location
		circ_buffer->tail++;

		//check for buffer overflow
		if (circ_buffer->tail >= CIRC_BUFF_SIZE)
			circ_buffer->tail = 0;

		return OK;
	}
}

ResponseStatus insert_char(CircularBuffer* circ_buffer, CUSTOM_TYPE char_to_write) {
	//buffer is empty - add element on position 0
	//	set tail and head to 0
	if (circ_buffer->tail < 0 && circ_buffer->head < 0) {
		circ_buffer->tail = 0;
		circ_buffer->head = 0;
		circ_buffer->buffer[circ_buffer->head] = char_to_write;
		return OK;
	}
	//buffer is full
	else if (((circ_buffer->head + 1) % CIRC_BUFF_SIZE) == circ_buffer->tail) {
		//move tail to next place
		circ_buffer->tail++;
		if (circ_buffer->tail == CIRC_BUFF_SIZE)
			circ_buffer->tail = 0;

		//increment head
		circ_buffer->head++;
		if (circ_buffer->head == CIRC_BUFF_SIZE)
			circ_buffer->head = 0;

		//store data to buffer
		circ_buffer->buffer[circ_buffer->head] = char_to_write;

		//an overflow occured so we let user know that
		return BUFFER_OVERFLOW;
	}
	//buffer is not empty nor full
	else {
		circ_buffer->head++;
		if (circ_buffer->head == CIRC_BUFF_SIZE)
			circ_buffer->head = 0;

		circ_buffer->buffer[circ_buffer->head] = char_to_write;
		return OK;
	}
}
