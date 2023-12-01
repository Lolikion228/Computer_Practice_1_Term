//
// Created by lolikion on 23.11.23.
//

#include "stack.h"
#include "stdlib.h"
#include "stdio.h"

Stack *stack_init(int m) {
    Stack *S = (Stack *)malloc(sizeof(struct Stack));
    S->max = m;
    S->top = -1;
    S->item = (int *)malloc(m * sizeof(int));
    for(int j=0;j<m;j++){
        S->item[j]=-1;
    }
    return S;
}

int stack_is_empty_S(Stack *S) {
    return (S->top == -1);
}

int stack_size(Stack *S){
    return 1+S->top;
}

int stack_is_full_S(Stack *S) {
    return (S->top == S->max - 1);
}

void stack_push_S(int x, Stack *S) {
    if (stack_is_full_S(S)) {
        printf("Stack full!\n");
        abort();
    }
    S->top++;
    S->item[S->top] = x;
}

int stack_pop_S(Stack *S) {
    if (stack_is_empty_S(S)) {
        printf("Stack empty!\n");
        abort();
    }
    int x = S->item[S->top];
    S->top--;
    return x;
}



int stack_top_S(Stack *S) {
    if (stack_is_empty_S(S)) {
        printf("Stack empty!\n");
        abort();
    }
    return S->item[S->top];
}

void stack_destroy_S(Stack *S) {
    free(S->item);
    free(S);
    S = NULL;
}
