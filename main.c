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
#define MAX_BINARY_LENGTH 40000






int main() {
    srand(time(NULL));


    graph *g1= graph_init(6);

    graph_add_arc(g1,1,2);
//    graph_add_arc(g1,0,1);
    graph_add_arc(g1,2,0);
    graph_add_arc(g1,2,3);
    graph_add_arc(g1,4,3);
    graph_add_arc(g1,5,4);
    graph_add_arc(g1,3,1);
//    for(int i=0;i<g1->count;i++){
//        for(int j=i+1;j<g1->count;j++)
//        graph_add_arc(g1,i,j);
//    }

//
//    for(int i=0;i<4+2*g1->count;i++){
//        graph_add_arc(g1,rand()%(g1->count),rand()%(g1->count));
//    }


//    graph_add_arc(g1,0,0);
//    del_arc(g1,0,1);
//    printf("------------\n");





    graph_print(g1);

    int* ord= topsort(g1);
//
    printf("ordering = [ ");
    for(int i=0;i<g1->count;i++){
        printf("%d ",ord[i]);
    }
    printf("]\n");
//    for(int i=0;i<g1->count;i++){
//        int* visited=calloc((g1->count),sizeof(int));
//        int* V=calloc((g1->count),sizeof(int));
//        DFS(i,V,visited,g1);
//        printf("i=%d  {",i);
//        for(int j=0;j<g1->count;j++){printf("%d ",visited[j]);}
//        printf("}\n");
//        printf("{");
//        for(int j=0;j<g1->count;j++){printf("%d ",V[j]);}
//        printf("}\n");
//        free(visited);
//    }
//    tst();

//    console_app();
    visualize_graph(g1);
    graph_free(g1);
    return 0;

}
//python3 chck.py




