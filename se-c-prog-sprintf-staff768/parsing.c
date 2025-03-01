#include "parsing.h"
unsigned long long parsing_argv2(const char *number)
{
	unsigned long long result = 0;
	int base = 10;
	int sign = 1;

	while (*number == ' ' || *number == '\t')
	{
		number++;
	}
	if (*number == '-')
	{
		sign = -1;
		number++;
	}
	else if (*number == '+')
	{
		number++;
	}

	if (*number == '0')
	{
		number++;
		if (*number == 'x' || *number == 'X')
		{
			base = 16;
			number++;
		}
		else if (*number == 'b' || *number == 'B')
		{
			base = 2;
			number++;
		}
		else if (*number >= '0' && *number <= '7')
		{
			base = 8;
		}
		else if (*number == '\0')
		{
			return 0;
		}
	}
	while (*number != '\0')
	{
		int digit = -1;
		if (*number >= '0' && *number <= '9')
		{
			digit = *number - '0';
		}
		else if (*number >= 'a' && *number <= 'f')
		{
			digit = *number - 'a' + 10;
		}
		else if (*number >= 'A' && *number <= 'F')
		{
			digit = *number - 'A' + 10;
		}

		if (digit < 0 || digit >= base)
		{
			return -1;
		}

		result = result * base + digit;
		number++;
	}

	return result * sign;
}

FormatSpec parsing_argv1(char *format)
{
	FormatSpec spec = { 0, 0, 0, 0, 0, 0, '\0' };
	const char *temp = format;
	int i = 0;

	while (temp[i] != '\0')
	{
		if (temp[i] == '%')
		{
			i++;
			while (temp[i] == '-' || temp[i] == '+' || temp[i] == ' ' || temp[i] == '#' || temp[i] == '0')
			{
				switch (temp[i])
				{
				case '+':
					spec.flag_plus = 1;
					break;
				case ' ':
					spec.flag_space = 1;
					break;
				case '-':
					spec.flag_minus = 1;
					break;
				case '#':
					spec.flag_hash = 1;
					break;
				case '0':
					spec.flag_zero = 1;
					break;
				}
				i++;
			}
			while (temp[i] >= '0' && temp[i] <= '9')
			{
				spec.width = spec.width * 10 + (temp[i] - '0');
				i++;
			}
			if (temp[i] == 'd' || temp[i] == 'o' || temp[i] == 'b' || temp[i] == 'x' || temp[i] == 'X')
			{
				spec.specifier = temp[i];
				return spec;
			}
			else
			{
				spec.specifier = '\0';
				return spec;
			}
		}
		else
		{
			spec.specifier = '\0';
			return spec;
		}
	}
	return spec;
}