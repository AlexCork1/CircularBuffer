/*
 * CircularBuffer.h
 *
 *      Author: AlexCork
 *		
 *		Implementation of circular buffer in C
 */

#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

#include <stdint.h>

#define CIRC_BUFF_SIZE 3
#define CUSTOM_TYPE char

typedef struct
{
	//array to store data
	volatile CUSTOM_TYPE buffer[CIRC_BUFF_SIZE];  // default = {'\0'}
	
	//variable that "points to" where the last character was stored
	volatile int32_t head; // default = -1

	//variable that "points to" where the oldest character in the buffer is stored
	volatile int32_t tail; // default = -1
} CircularBuffer;

typedef enum
{
	OK = 1,
	NO_DATA_TO_RETURN = -1,
	BUFFER_OVERFLOW = -2
} ResponseStatus;

ResponseStatus get_char(CircularBuffer* circ_buffer, CUSTOM_TYPE* returned_char);
ResponseStatus insert_char(CircularBuffer* circ_buffer, CUSTOM_TYPE char_to_write);

#endif /* CIRCULARBUFFER_H_ */
