#include <stdio.h>
#include "transforming.h"
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