/*
 * Seven_Segment.cpp
 *
 *  Created on: 20 Aug 2014
 *      Author: Peter
 */

#include <Arduino.h>
#include "Seven_Segment.h"

void SevenSegment::begin(){
	  DDRA |= 0b11111111;
	  DDRD |= 0b01111000;
}

void SevenSegment::numtochar(int32_t number, char* text, uint32_t digits){
    memset(text,'\0',digits+1);
    snprintf(text,digits+1,"%4d",number);
}

void SevenSegment::activateDigit(uint32_t dignum){
	uint8_t mask = 0x00;
	switch(dignum){
	case 0: mask = 0b00001000; break;
	case 1: mask = 0b00010000; break;
	case 2: mask = 0b00100000; break;
	case 3: mask = 0b01000000; break;
	}
	PORTD = mask;
}

void SevenSegment::printChar(char c){
	uint8_t mask=0x00;
	switch(c){
	case '0': mask = 0b00111111; break;
	case '1': mask = 0b00000110; break;
	case '2': mask = 0b01011011; break;
	case '3': mask = 0b01001111; break;
	case '4': mask = 0b01100110; break;
	case '5': mask = 0b01101101; break;
	case '6': mask = 0b01111101; break;
	case '7': mask = 0b00000111; break;
	case '8': mask = 0b01111111; break;
	case '9': mask = 0b01101111; break;
	case '-': mask = 0b01000000; break;
	case 'a':
	case 'A': mask = 0b01110111; break;

	}
	PORTA = mask;
}

void SevenSegment::printText(char text[]){

	uint8_t i;
	for(i=0;i<4;i++){
		activateDigit(i);
		printChar(text[i]);
		delay(4);
	}
	printChar(' ');
}

void SevenSegment::printNum(int32_t num){
	char text[5];
	numtochar(num,text,4);
	printText(text);
}



