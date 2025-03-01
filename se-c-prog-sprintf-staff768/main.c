#include "parsing.h"
#include "print.h"
#include "transforming.h"

#include <stdio.h>
int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: <format> <number>");
		return 1;
	}

	const char *format = argv[1];
	const char *number = argv[2];

	FormatSpec spec = parsing_argv1(format);
	if (spec.specifier == '\0')
	{
		fprintf(stderr, "Error: Unsupported format");
		return 1;
	}

	unsigned long long value = parsing_argv2(number);
	if (value == -1)
	{
		fprintf(stderr, "Error: Invalid number format");
		return 1;
	}
	char out_buf[256];

	print(out_buf, format, number);

	return 0;
}
