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


void DFS(int start_point, int *V, Stack *stack, graph *g,int* nodes_status) {
    if(nodes_status[start_point] == EXPLORING) {printf("Cyclic2\n"); }
    V[start_point] = 1;
    nodes_status[start_point] = EXPLORING;
    node *curr = g->adj_list[start_point].head;
    while (curr != NULL) {
        if(nodes_status[curr->val]==EXPLORING){printf("Cyclic2\n");}
        if (V[curr->val] == 0) { DFS(curr->val, V,stack, g,nodes_status); }
        curr = curr->next;
    }
    push_S(start_point,stack);
    nodes_status[start_point] = VISITED;
}


int *topsort(graph *g) {
    if(!isAcyclic(g)){printf("Cyclic!!!\n");}
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
            DFS(at,V,stack1,g,nodes_status);
            int i0=(i-=1+stack1->top);
            for(;1+stack1->top!=0;i++)
                ordering[i] = pop_S(stack1);
            i=i0;
            destroy_S(stack1);
            free(nodes_status);
        }
    }
    free(V);
    return ordering;
}


void dfs_scc(int at,Stack *stack,int *onStack,int *ids,int *low,int *id,graph *g,int *cnt,sccs_list *res) {
    push_S(at, stack);
    onStack[at] = 1;
    ids[at] = low[at] = (*id)++;//?????

    node *curr = g->adj_list[at].head;
    while (curr != NULL) {
        if (ids[curr->val] == unvisited) { dfs_scc(curr->val, stack, onStack, ids, low, id, g, cnt,res); }
        if (onStack[curr->val]) { low[at] = (low[at] > low[curr->val]) ? low[curr->val] : low[at]; }
        curr = curr->next;
    }

    if (ids[at] == low[at]) {
        int j=stack->top;
        int j0=j;

        printf("[ ");
        for (int node = pop_S(stack);; node = pop_S(stack)) {
            j--;
            onStack[node] = 0;
            low[node] = ids[at];
            printf("%d ", node);
            if (node == at) { break; }
        }
        printf("] ");


        int *scc=(int *)malloc((j0-j) * sizeof(int));
        int ind=0;
        for(int i=j0;i>j;i--,ind++){
            scc[ind]=stack->item[i];
        }
        sccs_list_append(scc,res,j0-j);

    }
}

sccs_list *FindSccs(graph *g){


    int n=g->count;

    sccs_list *res=sccs_list_init();

    int id=0;
    int sccCount=0;

    int *ids=(int *)calloc(n,sizeof(int));
    int *low=(int *)calloc(n,sizeof(int));
    int *onStack=(int *)calloc(n,sizeof(int));
    Stack *stack= stack_init(n);

    for(int i=0; i<n ;i++){
        ids[i]=unvisited;
    }

    printf("sccs: { ");
    for(int i=0; i<n;i++){
        if(ids[i]==unvisited){
            dfs_scc(i,stack,onStack,ids,low,&id,g,&sccCount,res);

        }
    }
    printf("}\n");
    printf("count of Sccs = %d\n",sccCount);

    free(ids);
    free(onStack);
    destroy_S(stack);

    return res;

}

