#include "help_function.h"
#include "struct.h"
int parsing_primer(char* primer, char* postfix)
{
	Stack stack;
	init(&stack);

	postfix[0] = '\0';
	int str_len = 0;

	int counter_open_bracket = 0;
	int counter_close_bracket = 0;
	int flag = 1;

	char* temp = primer;

	while (*temp != '\0')
	{
		if (*temp == ' ')
		{
			temp++;
			continue;
		}

		if (*temp >= '0' && *temp <= '9')
		{
			while (*temp >= '0' && *temp <= '9')
			{
				postfix[str_len++] = *temp++;
			}
			postfix[str_len++] = ' ';
			flag = 0;
			continue;
		}

		if (*temp == '+' && flag == 1)
		{
			temp++;
			continue;
		}
		if (*temp == '-' && (flag == 1 || *(temp - 1) == '(' || *(temp - 1) == ' '))
		{
			push(&stack, '$');
			temp++;
			continue;
		}

		if (*temp == '(')
		{
			counter_open_bracket++;
			push(&stack, *temp);
		}

		else if (*temp == ')')
		{
			counter_close_bracket++;
			while (!isEmpty(&stack) && peek(&stack) != '(')
			{
				postfix[str_len++] = peek(&stack);
				postfix[str_len++] = ' ';
				pop(&stack);
			}
			pop(&stack);
		}

		else if (*temp == '*' && *(temp + 1) == '*')
		{
			temp++;
			while (!isEmpty(&stack) && operator_precedence(peek(&stack)) >= operator_precedence('#'))
			{
				postfix[str_len++] = peek(&stack);
				postfix[str_len++] = ' ';
				pop(&stack);
				flag = 1;
			}
			push(&stack, '#');
		}

		else if (*temp == '<' && *(temp + 1) == '<')
		{
			temp++;
			while (!isEmpty(&stack) && operator_precedence(peek(&stack)) >= operator_precedence('<'))
			{
				postfix[str_len++] = peek(&stack);
				postfix[str_len++] = ' ';
				pop(&stack);
				flag = 1;
			}
			push(&stack, '<');
		}

		else if (*temp == '>' && *(temp + 1) == '>')
		{
			temp++;
			while (!isEmpty(&stack) && operator_precedence(peek(&stack)) >= operator_precedence('>'))
			{
				postfix[str_len++] = peek(&stack);
				postfix[str_len++] = ' ';
				pop(&stack);
				flag = 1;
			}
			push(&stack, '>');
		}

		else
		{
			while (!isEmpty(&stack) && operator_precedence(peek(&stack)) >= operator_precedence(*temp))
			{
				postfix[str_len++] = peek(&stack);
				postfix[str_len++] = ' ';
				pop(&stack);
				flag = 1;
			}
			push(&stack, *temp);
		}
		temp++;
	}
	if (counter_open_bracket != counter_close_bracket)
	{
		fprintf(stderr, "Can't parse example\n");
		return 3;
	}

	while (!isEmpty(&stack))
	{
		postfix[str_len++] = peek(&stack);
		postfix[str_len++] = ' ';
		pop(&stack);
	}
	freeStack(&stack);
	postfix[str_len] = '\0';
	return 0;
}