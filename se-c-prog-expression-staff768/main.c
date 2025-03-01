#include "help_function.h"
#include "parsing.h"
#include "struct.h"
int math(char *postfix)
{
	intStack stack;
	initStack(&stack);

	for (int i = 0; postfix[i] != '\0'; ++i)
	{
		if (postfix[i] == ' ')
		{
			continue;
		}
		if (postfix[i] >= '0' && postfix[i] <= '9')
		{
			int number = 0;
			while (postfix[i] >= '0' && postfix[i] <= '9')
			{
				number = number * 10 + (postfix[i] - '0');
				i++;
			}
			int_push(&stack, number);
			i--;
		}
		else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' ||
				 postfix[i] == '%' || postfix[i] == '&' || postfix[i] == '|' || postfix[i] == '^' ||
				 postfix[i] == '<' || postfix[i] == '>' || postfix[i] == '#')
		{
			if (isEmpty_int(&stack))
			{
				return 3;
			}
			int oper2 = int_pop(&stack);

			int oper1 = int_pop(&stack);

			int result = 0;
			switch (postfix[i])
			{
			case '+':
				result = oper1 + oper2;
				break;
			case '-':
				result = oper1 - oper2;
				break;
			case '*':
				result = oper1 * oper2;
				break;
			case '/':
				if (oper2 != 0)
				{
					result = oper1 / oper2;
				}
				else
				{
					fprintf(stderr, "You can't divide by 0\n");
					freeIntStack(&stack);
					return 2;
				}
				break;
			case '%':
				if (oper2 != 0)
				{
					result = oper1 % oper2;
				}
				else
				{
					fprintf(stderr, "You can't divide by 0\n");
					freeIntStack(&stack);
					return 2;
				}
				break;
			case '&':
				result = oper1 & oper2;
				break;
			case '^':
				result = oper1 ^ oper2;
				break;
			case '|':
				result = oper1 | oper2;
				break;
			case '<':
				if (oper2 >= 32)
				{
					fprintf(stderr, "You can't shift more than 32\n");
					freeIntStack(&stack);
					return 2;
				}
				else
				{
					result = oper1 << oper2;
				}
				break;
			case '>':
				if (oper2 >= 32)
				{
					fprintf(stderr, "You can't shift more than 32\n");
					freeIntStack(&stack);
					return 2;
				}
				else
				{
					result = oper1 >> oper2;
				}
				break;
			case '#':
				if (oper2 < 0)
				{
					fprintf(stderr, "The exponent should be positive\n");
					freeIntStack(&stack);
					return 2;
				}
				result = power(oper1, oper2);
				break;
			default:
				freeIntStack(&stack);
				return 1;
			}
			int_push(&stack, result);
		}
		else if (postfix[i] == '~')
		{
			if (!isEmpty_int(&stack))
			{
				int oper3 = int_pop(&stack);
				int result = ~oper3;
				int_push(&stack, result);
			}
		}
		else if (postfix[i] == '$')
		{
			if (!isEmpty_int(&stack))
			{
				int oper3 = int_pop(&stack);
				int result = -oper3;
				int_push(&stack, result);
			}
			else
			{
				fprintf(stderr, "Error: Unary operator without operand\n");
				freeIntStack(&stack);
				return 4;
			}
		}

		else
		{
			fprintf(stderr, "It's not a operator\n");
			freeIntStack(&stack);
			return 4;
		}
	}
	if (isEmpty_int(&stack))
	{
		freeIntStack(&stack);
		return 3;
	}

	int final_result = int_pop(&stack);
	freeIntStack(&stack);
	return final_result;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Invalid number of arguments. Usage: %s <expression>\n", argv[0]);
		return 4;
	}

	char *primer = argv[1];
	char postfix[1000] = { 0 };

	int parse_result = parsing_primer(primer, postfix);
	if (parse_result != 0)
	{
		return parse_result;
	}
	int final_otvet = math(postfix);
	printf("%d\n", final_otvet);

	return 0;
}
