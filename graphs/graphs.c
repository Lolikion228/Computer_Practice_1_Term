//
// Created by lolikion on 16.11.23.
//
#include <stdlib.h>
#include "graphs.h"

node *node_init(int val) {
    node* nd= (node *) malloc(sizeof(node*));
    nd->val = val;
    nd->next=NULL;
    return nd;
}

graph* graph_init(int n){
    graph* res = (graph *)calloc(1,sizeof(graph*));
    res->count=n;
    res->adj_list=(list*)calloc(n,sizeof(list));
    for(int i = 0; i < n; i++)
        res->adj_list[i].head = NULL;
    return res;
}

void graph_add_arc(graph *g, int a, int b) {
    node *curr = g->adj_list[a].head;
    if(curr) {
        for(; curr->next; curr = curr->next)
            if(curr->val == b) break;
        curr->next = node_init(b);
    }
    else g->adj_list[a].head = node_init(b);
}