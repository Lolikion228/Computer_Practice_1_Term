//
// Created by lolikion on 16.11.23.
//
#include "../stack/stack.h"
#include "sccs.h"
#ifndef TITLED1_GRAPHS_H
#define TITLED1_GRAPHS_H

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

void del_arc(graph* g, int a, int b);

void graph_print(graph* g);//

void graph_free(graph* g);//

void node_free(node* nd);//

void save_graph_to_file(graph *g);//

void visualize_graph(graph *g);//

void DFS(int start_point, int *V, Stack *stack, graph *g,int* nodes_status);

int DFS2(int start_point, int* nodes_status, graph* g);

int *topsort(graph *g);

sccs_list *FindSccs(graph *g);


#endif //TITLED1_GRAPHS_H
