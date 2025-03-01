//
// Created by user on 09.12.2024.
//
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef LABA3_STRUCT_H
#define LABA3_STRUCT_H
typedef struct Node
{
	char value;
	struct Node* next;
} Node;

typedef struct Stack
{
	Node* head;
} Stack;

Node* creation_node(char new_value)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->value = new_value;
	new_node->next = NULL;
	return new_node;
}

void init(Stack* stack)
{
	stack->head = NULL;
}

void push(Stack* stack, char new_value)
{
	Node* new_node = creation_node(new_value);
	new_node->next = stack->head;
	stack->head = new_node;
}

int isEmpty(Stack* stack)
{
	return stack->head == NULL;
}

char pop(Stack* stack)
{
	if (!isEmpty(stack))
	{
		Node* temp = stack->head;
		char value = temp->value;
		stack->head = stack->head->next;
		free(temp);
		return value;
	}
	return '\0';
}

char peek(Stack* stack)
{
	if (!isEmpty(stack))
		return stack->head->value;
	else
		return '\0';
}

typedef struct intNode
{
	int data;
	struct intNode* next;
} intNode;

typedef struct intStack
{
	intNode* head;
} intStack;

intNode* createIntNode(int new_data)
{
	intNode* new_node = (intNode*)malloc(sizeof(intNode));
	new_node->data = new_data;
	new_node->next = NULL;
	return new_node;
}

void initStack(intStack* stack)
{
	stack->head = NULL;
}

int isEmpty_int(intStack* stack)
{
	return stack->head == NULL;
}

void int_push(intStack* stack, int new_data)
{
	intNode* new_node = createIntNode(new_data);
	new_node->next = stack->head;
	stack->head = new_node;
}

int int_pop(intStack* stack)
{
	if (!isEmpty_int(stack))
	{
		intNode* temp = stack->head;
		int value = temp->data;
		stack->head = stack->head->next;
		free(temp);
		return value;
	}
	return 0;
}

int peek_int(intStack* stack)
{
	if (!isEmpty_int(stack))
		return stack->head->data;
	else
	{
		printf("Stack is empty\n");
		return '\0';
	}
}
void freeStack(Stack* stack)
{
	while (!isEmpty(stack))
	{
		pop(stack);
	}
}
void freeIntStack(intStack* stack)
{
	while (!isEmpty_int(stack))
	{
		int_pop(stack);
	}
}
int count_bit(intStack* stack)
{
	intNode* temp = stack->head;
	int count = 0;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return count;
}

#endif	  // LABA3_STRUCT_H
