/*
 * seven_segment.h
 *
 *  Created on: 19 Aug 2014
 *      Author: Peter
 */

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

#include<inttypes.h>

class SevenSegment{
public:
	static void begin();
	static void printText(char text[]);
	static void printNum(int32_t num);
private:
	static void numtochar(int32_t number, char* text, uint32_t digits);
	static void activateDigit(uint32_t dignum);
	static void printChar(char c);
};

#endif /* SEVEN_SEGMENT_H_ */
