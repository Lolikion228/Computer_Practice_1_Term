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



    console_app();

//    graph *g1= graph_init(7);
//
//    graph_add_arc(g1,0,1);
//    graph_add_arc(g1,1,2);
//    graph_add_arc(g1,1,4);
//    graph_add_arc(g1,1,6);
//    graph_add_arc(g1,2,3);
//    graph_add_arc(g1,3,2);
//    graph_add_arc(g1,3,4);
//    graph_add_arc(g1,3,5);
//    graph_add_arc(g1,4,5);
//    graph_add_arc(g1,5,4);
//    graph_add_arc(g1,6,0);
//    graph_add_arc(g1,6,2);
////
////
////    graph_print(g1);
////
////    int* ord= topsort(g1);
////
////    printf("ordering = [ ");
////    for(int i=0;i<g1->count;i++){
////        printf("%d ",ord[i]);
////    }
////    printf("]\n");
////
//    int *sccs= FindSccs(g1);
////
//    visualize_graph(g1);
//    graph_free(g1);
////    free(ord);
//
//    free(sccs);
    return 0;

}
//python3 chck.py




