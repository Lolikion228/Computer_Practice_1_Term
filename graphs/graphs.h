//
// Created by lolikion on 16.11.23.
//

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


graph* graph_init(int n);

void add_arc(graph* g, int a, int b);

void del_arc(graph* g, int a, int b);

void graph_print(graph* g);

void graph_free(graph* g);

#endif //TITLED1_GRAPHS_H
