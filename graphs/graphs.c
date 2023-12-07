//
// Created by lolikion on 16.11.23.
//
#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"
#include <string.h>
#include "../stack/stack.h"
#include "sccs.h"
#define unvisited -1
node *node_init(int val) {
    node *nd = (node *)malloc(sizeof(node));//not sizeof(node*)
    nd->val = val;
    nd->next = NULL;
    return nd;
}

graph *graph_init(int n) {
    graph *res = (graph *)malloc(sizeof(graph));;//not sizeof(graph*)
    res->count = n;
    res->adj_list = (list *)malloc(n * sizeof(list));
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

void graph_del_arc(graph *g, int a, int b) {
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

void graph_visualize(graph *g) {
    graph_save_to_file(g);
    int t = system("python3 /home/lolikion/CLionProjects/Titled1/graphs/gr.py > /dev/null 2>&1");
}

void graph_save_to_file(graph *g) {
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

enum {NOT_VISITED, VISITED, EXPLORING};

int DFS(int start_point, int *V, Stack *stack, graph *g,int* nodes_status) {

    if(nodes_status[start_point] == EXPLORING) {return EXIT_FAILURE; }
    V[start_point] = 1;
    nodes_status[start_point] = EXPLORING;
    node *curr = g->adj_list[start_point].head;

    while (curr != NULL) {
        if(nodes_status[curr->val]==EXPLORING){return EXIT_FAILURE;}
        if (V[curr->val] == 0) { if(DFS(curr->val, V,stack, g,nodes_status)==EXIT_FAILURE){return EXIT_FAILURE;} }
        curr = curr->next;
    }

    stack_push_S(start_point,stack);
    nodes_status[start_point] = VISITED;
    return EXIT_SUCCESS;
}


int *topsort(graph *g) {
    int N = g->count;
    int *V = (int*)calloc(N, sizeof(int));
    int *ordering = (int*)calloc(N, sizeof(int));
    for(int j=0;j<N;j++){ordering[j]=-1;}
    int i=N;
    Stack *stack1;
    int *nodes_status;
    for (int at = 0; at < N; at++) {
        if(V[at]==0){
            stack1= stack_init(N);
            nodes_status = (int*)calloc(N, sizeof(int));
            if(DFS(at,V,stack1,g,nodes_status)==EXIT_FAILURE) {
                free(V);
                free(ordering);
                free(nodes_status);
                stack_destroy_S(stack1);
                return NULL;
            }
            i-= stack_size(stack1);
            for(int j=0;!stack_is_empty_S(stack1);j++){
                ordering[j+i] = stack_pop_S(stack1);
            }

            stack_destroy_S(stack1);
            free(nodes_status);
        }
    }
    free(V);
    return ordering;
}


void dfs_scc(int at,Stack *stack,int *onStack,int *ids,int *low,int *id,graph *g) {
    stack_push_S(at, stack);
    onStack[at] = 1;
    ids[at] = low[at] = (*id)++;

    node *curr = g->adj_list[at].head;
    while (curr != NULL) {
        if (ids[curr->val] == unvisited) { dfs_scc(curr->val, stack, onStack, ids, low, id, g); }
        if (onStack[curr->val]) { low[at] = (low[at] > low[curr->val]) ? low[curr->val] : low[at]; }
        curr = curr->next;
    }

    if (ids[at] == low[at]) {
        while (!stack_is_empty_S(stack)) {
            int node = stack_pop_S(stack);
            onStack[node] = 0;
            low[node] = ids[at];
            if (node == at) { break; }
        }
    }


}

scc_list *scc(graph *g){

    int n=g->count;

    scc_list *res=scc_list_init();

    int id=0;

    int *ids=(int *)calloc(n,sizeof(int));
    int *low=(int *)calloc(n,sizeof(int));
    int *onStack=(int *)calloc(n,sizeof(int));
    Stack *stack= stack_init(n);

    for(int i=0; i<n ;i++){
        ids[i]=unvisited;
    }

    for(int i=0; i<n;i++){
        if(ids[i]==unvisited){
            dfs_scc(i,stack,onStack,ids,low,&id,g);
        }
    }
    // transfor low into a pretty output

    for(int i=0;i<n;++i){
        if(i==low[i]){
            node *root= node_init(i);
            node *curr=root;
            for(int j=0;j<n;++j){
                if( (low[j]==i) && (j!=i) ){
                    curr->next= node_init(j);
                    curr=curr->next;
                }
            }
            list scc0;
            scc0.head=root;
            scc_list_append(scc0,res);
            }
        }


    free(ids);
    free(onStack);
    stack_destroy_S(stack);
    for(int i = 0; i < g->count; i++) printf("%d -> comp# %d\n", i, low[i]);
    free(low);
    return res;

}

