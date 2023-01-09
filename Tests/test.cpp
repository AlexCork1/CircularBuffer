#include <gtest/gtest.h>
#include <queue>

using namespace std;


extern "C" {
#include "../CircularBuffer.h"
}

TEST(CircularBuffer_test, EmptyBufferGetCharOnce) {
	CircularBuffer round_robin{ {'\0'}, -1, -1};
	char returned_char;
	ResponseStatus response = get_char(&round_robin, &returned_char);
	EXPECT_EQ(response, NO_DATA_TO_RETURN);
}
TEST(CircularBuffer_test, EmptyBufferGetCharTwice) {
	CircularBuffer round_robin{ {'\0'}, -1, -1 };
	char returned_char, returned_char2;
	ResponseStatus response1 = get_char(&round_robin, &returned_char);
	ResponseStatus response2 = get_char(&round_robin, &returned_char2);
	EXPECT_EQ(response1, NO_DATA_TO_RETURN);
	EXPECT_EQ(response2, NO_DATA_TO_RETURN);
}
TEST(CircularBuffer_test, InsertOneChar) {
	CircularBuffer round_robin{ {'\0'}, -1, -1 };
	ResponseStatus response = insert_char(&round_robin, 'z');
	EXPECT_EQ(response, OK);
	EXPECT_EQ(round_robin.head, 0);
	EXPECT_EQ(round_robin.tail, 0);
	EXPECT_EQ(round_robin.buffer[0], 'z');
}

TEST(CircularBuffer_test, InsertOneChars){
	CircularBuffer round_robin{ {'\0'}, -1, -1 };
	ResponseStatus response1 = insert_char(&round_robin, 'z');
	ResponseStatus response2 = insert_char(&round_robin, 'A');
	EXPECT_EQ(response1, OK);
	EXPECT_EQ(response2, OK);
	EXPECT_EQ(round_robin.head, 1);
	EXPECT_EQ(round_robin.tail, 0);
	EXPECT_EQ(round_robin.buffer[0], 'z');
	EXPECT_EQ(round_robin.buffer[1], 'A');
}
TEST(CircularBuffer_test, InsertBuffSizeChars) {
	CircularBuffer round_robin{ {'\0'}, -1, -1 };
	for (int i = 0; i < CIRC_BUFF_SIZE; i++)
	{
		ResponseStatus responseI = insert_char(&round_robin, 'A'+i);
		EXPECT_EQ(responseI, OK);
	}
	
	EXPECT_EQ(round_robin.head, CIRC_BUFF_SIZE - 1);
	EXPECT_EQ(round_robin.tail, 0);
	EXPECT_EQ(round_robin.buffer[0], 'A');
	EXPECT_EQ(round_robin.buffer[1], 'B');
	EXPECT_EQ(round_robin.buffer[2], 'C');
}
TEST(CircularBuffer_test, InsertBuffSizePlus1Chars) {
	CircularBuffer round_robin{ {'\0'}, -1, -1 };
	for (int i = 0; i < CIRC_BUFF_SIZE; i++)
	{
		ResponseStatus responseI = insert_char(&round_robin, 'A' + i);
		EXPECT_EQ(responseI, OK);
	}
	ResponseStatus responseOverflow = insert_char(&round_robin, 'D');
	EXPECT_EQ(responseOverflow, BUFFER_OVERFLOW);

	EXPECT_EQ(round_robin.head, 0);
	EXPECT_EQ(round_robin.tail, 1);
	EXPECT_EQ(round_robin.buffer[0], 'D');
	EXPECT_EQ(round_robin.buffer[1], 'B');
	EXPECT_EQ(round_robin.buffer[2], 'C');
}