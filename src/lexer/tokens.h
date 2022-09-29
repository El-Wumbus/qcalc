#pragma once

enum TokenType
{
	ILLIGALCHAR = -1,
	NUM = 0,
	ADD = 1,
	SUB = 2,
	MUL = 3,
	DIV = 4,
	LPAREN = 5,
	RPAREN = 6,
};

typedef struct
{
	short int Type;
	long double Value;
} Token;