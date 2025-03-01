#include "parsing.h"
#include "print.h"
#include "transforming.h"
void apply_formatting(char *out_buf, long long value, const FormatSpec *format)
{
	char temp[256] = { 0 };
	char number_str[128] = { 0 };

	int base = 10;
	switch (format->specifier)
	{
	case 'b':
		base = 2;
		break;
	case 'o':
		base = 8;
		break;
	case 'd':
		base = 10;
		break;
	case 'x':
		base = 16;
		break;
	case 'X':
		base = 16;
		break;
	}

	int is_negative = (value < 0 && base == 10);
	if (is_negative)
	{
		value = -value;
	}

	int index = 0;
	do
	{
		int digit = value % base;
		if (digit < 10)
		{
			number_str[index++] = '0' + digit;
		}
		else
		{
			if (format->specifier == 'X')
			{
				number_str[index++] = 'A' + (digit - 10);
			}
			else
			{
				number_str[index++] = 'a' + (digit - 10);
			}
		}
		value /= base;
	} while (value > 0);

	if (is_negative)
	{
		number_str[index++] = '-';
	}

	for (int i = 0; i < index / 2; i++)
	{
		char tmp = number_str[i];
		number_str[i] = number_str[index - i - 1];
		number_str[index - i - 1] = tmp;
	}
	number_str[index] = '\0';

	int len = 0;
	while (number_str[len] != '\0')
	{
		len++;
	}

	int prefix_len = 0;
	char prefix[3] = { 0 };
	if (format->flag_hash && (format->specifier == 'x' || format->specifier == 'X' || format->specifier == 'o'))
	{
		if (format->specifier == 'o')
		{
			prefix[0] = '0';
			prefix_len = 1;
		}
		else if (format->specifier == 'x')
		{
			prefix[0] = '0';
			prefix[1] = 'x';
			prefix_len = 2;
		}
		else if (format->specifier == 'X')
		{
			prefix[0] = '0';
			prefix[1] = 'X';
			prefix_len = 2;
		}
	}

	char sign = '\0';
	if (!is_negative && base == 10)
	{
		if (format->flag_plus)
		{
			sign = '+';
		}
		else if (format->flag_space)
		{
			sign = ' ';
		}
	}

	if (sign != '\0')
	{
		prefix[prefix_len++] = sign;
	}

	int total_len = len + prefix_len;
	int padding = format->width > total_len ? format->width - total_len : 0;

	int temp_index = 0;

	if (!format->flag_minus && padding > 0)
	{
		char pad_char = format->flag_zero ? '0' : ' ';
		for (int i = 0; i < padding; i++)
		{
			temp[temp_index++] = pad_char;
		}
	}

	for (int i = 0; i < prefix_len; i++)
	{
		temp[temp_index++] = prefix[i];
	}

	for (int i = 0; i < len; i++)
	{
		temp[temp_index++] = number_str[i];
	}

	if (format->flag_minus && padding > 0)
	{
		for (int i = 0; i < padding; i++)
		{
			temp[temp_index++] = ' ';
		}
	}

	temp[temp_index] = '\0';

	int i = 0;
	while (temp[i] != '\0')
	{
		out_buf[i] = temp[i];
		i++;
	}
	out_buf[i] = '\0';
}