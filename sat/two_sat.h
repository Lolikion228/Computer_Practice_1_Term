//
// Created by lolikion on 27.11.23.
//

#ifndef TITLED1_2_SAT_H
#define TITLED1_2_SAT_H
#include "../stack/stack.h"
#include "../graphs/graphs.h"
typedef struct CNF2{
    int clauses;
    int **arr;
    int max;
}CNF2;


CNF2 *CNF2_get(char* str);

void CNF2_print(CNF2 *cnf);

void CNF2_free(CNF2 *cnf);

graph *get_implication_graph(CNF2 *cnf);

int *TWO_SAT(CNF2 *cnf);

int test_two_sat(CNF2 *cnf,int *vals);

#endif //TITLED1_2_SAT_H
