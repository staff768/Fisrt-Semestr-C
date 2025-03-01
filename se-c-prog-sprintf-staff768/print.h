//
// Created by user on 02.12.2024.
//
#ifndef LAPA_PO_OP_2_PRINT_H
#define LAPA_PO_OP_2_PRINT_H
#include "transforming.h"

#include <stdio.h>
void print(char *out_buf, const char *format, const char *number)
{
	FormatSpec fmt_info = parsing_argv1((char *)format);
	long long value = parsing_argv2(number);

	if (value == -1)
	{
		char error_message[] = "Error: Invalid number format\n";
		int i = 0;
		while (error_message[i] != '\0')
		{
			out_buf[i] = error_message[i];
			i++;
		}
		out_buf[i] = '\0';

		puts(out_buf);
		return;
	}

	apply_formatting(out_buf, value, &fmt_info);

	puts(out_buf);
}
#endif	  // LAPA_PO_OP_2_PRINT_H
