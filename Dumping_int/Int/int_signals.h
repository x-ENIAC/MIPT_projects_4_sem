#ifndef INT_SIGNALS_H
#define INT_SIGNALS_H

#include <string>

enum class Int_signal {
	MORE 				= 1,
	MORE_OR_EQUAL 		= 2,
	LESS 				= 3,
	LESS_OR_EQUAL 		= 4,
	EQUAL 				= 5,
	NOT_EQUAL 			= 6,
	ADD 				= 7,
	ADD_AND_ASSIGNMENT 	= 8,
	SUB 				= 9,
	SUB_AND_ASSIGNMENT 	= 10,
	MUL 				= 11,
	MUL_AND_ASSIGNMENT 	= 12,
	DIV 				= 13,
	DIV_AND_ASSIGNMENT 	= 14,
	ASSIGNMENT 			= 15
};

const int COUNT_OF_SIGNALS = 16;

extern const char* signals[];

#endif