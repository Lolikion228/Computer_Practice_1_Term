//
// Created by lolikion on 16.11.23.
//

#ifndef TITLED1_GRAPHS_H
#define TITLED1_GRAPHS_H

#include "../stack/stack.h"
#include "sccs.h"

typedef struct node {
    int val;
    struct node* next;
} node;

typedef struct list{
    node* head;
} list;

typedef struct graph{
    int count;
    list* adj_list;
} graph;

graph* graph_init(int n);//

void graph_add_arc(graph *g, int a, int b);//

void graph_del_arc(graph* g, int a, int b);

void graph_print(graph* g);//

void graph_free(graph* g);//

void node_free(node* nd);//
//
void graph_save_to_file(graph *g);//

void graph_visualize(graph *g);//

int DFS(int start_point, int *V, Stack *stack, graph *g,int* nodes_status);

int *topsort(graph *g);

struct scc_list *FindSccs(graph *g);

node *node_init(int val);
#endif //TITLED1_GRAPHS_H