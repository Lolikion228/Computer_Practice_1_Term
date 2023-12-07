//
// Created by lolikion on 23.11.23.
//

#ifndef TITLED1_STACK_H
#define TITLED1_STACK_H

typedef struct Stack{
    int top;
    int max;
    int *item;
}Stack;

Stack *stack_init(int m);

int stack_is_empty_S(Stack *S);

int stack_size(Stack *S);

int stack_is_full_S(Stack *S);

void stack_push_S(int x, Stack *S);

int stack_pop_S(Stack *S);

int stack_top_S(Stack *S);

void stack_destroy_S(Stack *S);

#endif //TITLED1_STACK_H