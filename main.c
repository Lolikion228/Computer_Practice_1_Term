#include <stdio.h>
#include <string.h>
#include "big_int/big_int.h"
#include "tests.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
//#include "rsa/rsa.h"
#include "rsa_cli/rsa_cli.h"
#include  "lib/lib.h"
#include "graphs/graphs.h"
#include "stack/stack.h"
#define MAX_BINARY_LENGTH 40000






int main() {
    srand(time(NULL));


//    if(is_empty_S(*stack1)){printf("empty\n");}
//    push_S(116,stack1);
//    push_S(116,stack1);
//    push_S(322,stack1);
//    push_S(322,stack1);
//    push_S(116,stack1);
//    printf("top=%d\n", top_S(*stack1));
//    if(is_empty_S(*stack1)){printf("empty\n");}




    graph *g1= graph_init(12);
//
    graph_add_arc(g1,1,2);
    graph_add_arc(g1,4,11);
    graph_add_arc(g1,5,10);
    graph_add_arc(g1,11,7);
    graph_add_arc(g1,9,10);
    graph_add_arc(g1,0,1);
    graph_add_arc(g1,2,5);
    graph_add_arc(g1,3,5);
    graph_add_arc(g1,6,1);
    graph_add_arc(g1,7,9);
    graph_add_arc(g1,9,3);
    graph_add_arc(g1,7,3);
    graph_add_arc(g1,8,5);
    graph_add_arc(g1,1,8);
    graph_add_arc(g1,9,1);
    graph_add_arc(g1,4,3);

//    for(int i=0;i<g1->count;i++){
//        for(int j=i+1;j<g1->count;j++)
//        graph_add_arc(g1,i,j);
//    }

//
//    for(int i=0;i<4+2*g1->count;i++){
//        graph_add_arc(g1,rand()%(g1->count),rand()%(g1->count));
//    }


    graph_print(g1);
//    Stack *stack1= stack_init(g1->count);
//    int *V = (int*)calloc(g1->count, sizeof(int));
//    DFS_new(7,V,stack1,g1);
//    while(!is_empty_S(*stack1)){
//        printf("%d ", pop_S(stack1));
//    }
//    printf("\n");

////
    int* ord= topsort(g1);
//
    printf("ordering = [ ");
    for(int i=0;i<g1->count;i++){
        printf("%d ",ord[i]);
    }
    printf("]\n");
//


//    visualize_graph(g1);
    graph_free(g1);
    free(ord);


    return 0;

}
//python3 chck.py




