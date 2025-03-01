
#ifndef LAPA_PO_OP_2_PARSING_H
#define LAPA_PO_OP_2_PARSING_H

typedef struct
{
	int width;
	int flag_plus;
	int flag_space;
	int flag_minus;
	int flag_hash;
	int flag_zero;
	char specifier;
} FormatSpec;

unsigned long long parsing_argv2(const char *number);
FormatSpec parsing_argv1(char *format);

#endif	  // LAPA_PO_OP_2_PARSING_H
