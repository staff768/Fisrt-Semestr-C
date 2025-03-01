#include <stdio.h>
#include "help_function.h"
#include "struct.h"
int power(int base, int exponent)
{
	if (exponent < 0)
	{
		fprintf(stderr, "Exponent should be non-negative\n");
		return 2;
	}
	int result = 1;
	for (int i = 0; i < exponent; i++)
	{
		result *= base;
	}
	return result;
}
int operator_precedence(char operator)
{
	switch (operator)
	{
	case '#':
		return 17;
	case '$':
		return 16;
	case '*':
	case '/':
	case '%':
		return 14;
	case '+':
	case '-':
		return 13;
	case '<':
	case '>':
		return 12;
	case '&':
		return 11;
	case '^':
		return 10;
	case '|':
		return 9;
	case '(':
		return 0;
	default:
		return -1;
	}
}