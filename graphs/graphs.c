//
// Created by lolikion on 16.11.23.
//
#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"
#include <string.h>
#include "../stack/stack.h"

node *node_init(int val) {
    node *nd = malloc(sizeof(node *));
    nd->val = val;
    nd->next = NULL;
    return nd;
}

graph *graph_init(int n) {
    graph *res = malloc(sizeof(graph *)) ;
    res->count = n;
    res->adj_list = malloc(n * sizeof(list));
    for (int i = 0; i < n; i++)
        res->adj_list[i].head = NULL;
    return res;
}

void graph_add_arc(graph *g, int a, int b) {
    node *curr = g->adj_list[a].head;
    if (curr != NULL) {
        while (curr->next != NULL) {
            if (curr->val == b) { return; }
            curr = curr->next;
        }
        if (curr->val == b) { return; }
        curr->next = node_init(b);
    } else g->adj_list[a].head = node_init(b);
}

void graph_print(graph *g) {
    node *curr = NULL;
    for (int i = 0; i < g->count; i++) {
        printf("g[%d]{ ", i);
        curr = g->adj_list[i].head;
        if (curr != NULL) {
            printf("%d; ", curr->val);
            while (curr->next != NULL) {
                curr = curr->next;
                printf("%d; ", curr->val);
            }
        }
        printf("}\n");
    }

}

void node_free(node *nd) {
    if (nd != NULL) {
        node *tmp = nd;
        if (nd->next == NULL) {
            free(nd);
            return;
        }
        while (nd->next != NULL) {
            tmp = nd;
            nd = nd->next;
            free(tmp);
        }
        free(nd);
    }
}

void graph_free(graph *g) {
    for (int i = 0; i < g->count; i++) {
        node_free(g->adj_list[i].head);
    }
    free(g->adj_list);
    free(g);
}

void del_arc(graph *g, int a, int b) {
    if(g) {
        node *curr = g->adj_list[a].head;
        node *tmp = NULL;
        if(curr)
            if (curr->val == b) {
                node * tmp2 = curr->next;
                free(curr);
                g->adj_list[a].head = tmp2;
                return;
            }
            for (; curr; curr = curr->next) {
                if (curr->val == b) {
                    tmp->next = curr->next;
                    free(curr);
                    return;
                }
                tmp = curr;
            }
    }
}

void visualize_graph(graph *g) {
    save_graph_to_file(g);
    int t = system("python3 /home/lolikion/CLionProjects/Titled1/graphs/gr.py > /dev/null 2>&1");
}

void save_graph_to_file(graph *g) {
    node *curr = NULL;
    FILE *f = fopen("graphs/gr.txt", "w");
    for (int i = 0; i < g->count; i++) {
        curr = g->adj_list[i].head;
        if (curr != NULL) {
            fprintf(f, "%d %d\n", i, curr->val);
            while (curr->next != NULL) {
                curr = curr->next;
                fprintf(f, "%d %d\n", i, curr->val);
            }
        }

    }
    fclose(f);
}








int isAcyclic(graph *g) {

    int N = g->count;
    int *nodes_status = (int*)calloc(N, sizeof(int));

    for(int at = 0; at < N; at++) {
        if (!DFS2(at, nodes_status, g)) {
            free(nodes_status);
            return 0;
        }
    }

    free(nodes_status);
    return 1;
}


enum {NOT_VISITED, VISITED, EXPLORING};
int DFS2(int start_point, int* nodes_status, graph* g) {
    if(nodes_status[start_point] == EXPLORING) return 0;
    if(nodes_status[start_point] == VISITED) return 1;

    nodes_status[start_point] = EXPLORING;

    node* curr = g->adj_list[start_point].head;
    while (curr != NULL) {
        if(DFS2(curr->val, nodes_status, g)==0) return 0;
        curr = curr->next;
    }

    nodes_status[start_point] = VISITED;

    return 1;
}


void DFS(int start_point, int *V, Stack *stack, graph *g) {
    V[start_point] = 1;

    node *curr = g->adj_list[start_point].head;
    while (curr != NULL) {
        if (V[curr->val] == 0) { DFS(curr->val, V,stack, g); }
        curr = curr->next;
    }
    push_S(start_point,stack);
}

int *topsort(graph *g) {
    if(!isAcyclic(g)){printf("Cyclic!!!\n");}
    int N = g->count;
    int *V = (int*)calloc(N, sizeof(int));
    int *ordering = (int*)calloc(N, sizeof(int));
    for(int j=0;j<N;j++){ordering[j]=-1;}
    int i=N;
    Stack *stack1;
    for (int at = 0; at < N; at++) {
        if(V[at]==0){
            stack1= stack_init(N);
            DFS(at,V,stack1,g);
            int i0=i-=stack1->elements;
            for(;stack1->elements!=0;i++)
                ordering[i] = pop_S(stack1);
            i=i0;
            destroy_S(stack1);
        }
    }
    free(V);
    return ordering;
}

//dfs=dfs+dfs2
//Stack struct