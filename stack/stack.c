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
    S->elements=0;
    S->item = (int *)malloc(m * sizeof(int));
    for(int j=0;j<m;j++){
        S->item[j]=-1;
    }
    return S;
}

int is_empty_S(Stack S) {
    return (S.top == -1);
}

int is_full_S(Stack S) {
    return (S.top == S.max - 1);
}

void push_S(int x, Stack *S) {
    if (is_full_S(*S)) {
        printf("Stack full!\n");
        abort();
    }
    S->top++;
    S->item[S->top] = x;
    S->elements++;
}

int pop_S(Stack *S) {
    if (is_empty_S(*S)) {
        printf("Stack empty!\n");
        abort();
    }
    int x = S->item[S->top];
    S->top--;
    S->elements--;
    return x;
}



int top_S(Stack S) {
    if (is_empty_S(S)) {
        printf("Stack empty!\n");
        abort();
    }
    return S.item[S.top];
}

void destroy_S(Stack *S) {
    free(S->item);
    free(S);
    S = NULL;
}