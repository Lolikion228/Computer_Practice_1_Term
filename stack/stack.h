//
// Created by lolikion on 23.11.23.
//

#ifndef TITLED1_STACK_H
#define TITLED1_STACK_H

typedef struct Stack{
    int top;
    int elements;
    int max;
    int *item;
}Stack;

Stack *stack_init(int m);

int is_empty_S(Stack S);

int is_full_S(Stack S);

void push_S(int x, Stack *S);

int pop_S(Stack *S);

int top_S(Stack S);

void destroy_S(Stack *S);

#endif //TITLED1_STACK_H
