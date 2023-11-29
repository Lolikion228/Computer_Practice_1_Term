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
#include "sat/two_sat.h"
#define MAX_BINARY_LENGTH 40000






int main() {
    srand(time(NULL));

//    console_app();
//    Stack **arr= malloc(3*sizeof(Stack *));


    CNF2 *cnf= CNF2_get("(x1||x2)&&(!x2||x3)&&(!x1||!x2)&&(x3||x4)&&(!x3||x5)&&(!x4||!x5)&&(!x3||x4)&&(!x2||x6)&&(!x6||!x1)&&(!x6||!x3)");
    for(int i=0;i<cnf->clauses;i++){
        printf("[%d %d] ",cnf->arr[i][0],cnf->arr[i][1]);
    }
    printf("\n");
    CNF2_print(cnf);
    int *x=TWO_SAT(cnf);
    if(x==NULL){printf("not SAT\n");}
    else{
        printf("SAT\n[ ");
        for(int i=1;i<1+cnf->max;i++){printf("%d ",x[i]);}
        printf("]\n");
        printf("test=%d\n", test_two_sat(cnf,x));
    }
    CNF2_free(cnf);
    free(x);




//    graph *g1= graph_init(14);
//
//    graph_add_arc(g1,0,1);
//    graph_add_arc(g1,0,5);
//    graph_add_arc(g1,1,0);
//    graph_add_arc(g1,1,12);
//    graph_add_arc(g1,1,13);
//    graph_add_arc(g1,12,13);
//    graph_add_arc(g1,2,3);
//    graph_add_arc(g1,13,2);
//    graph_add_arc(g1,3,4);
//    graph_add_arc(g1,4,2);
//    graph_add_arc(g1,7,3);
//
//    graph_add_arc(g1,5,6);
//    graph_add_arc(g1,6,5);
//    graph_add_arc(g1,6,7);
//    graph_add_arc(g1,7,8);
//    graph_add_arc(g1,8,9);
//    graph_add_arc(g1,9,7);
//    graph_add_arc(g1,10,11);
//    graph_add_arc(g1,11,10);
//    graph_add_arc(g1,5,10);
//    graph_add_arc(g1,8,11);

////
////
//    graph_print(g1);
//
//    int* ord= topsort(g1);
//
//    printf("ordering = [ ");
//    for(int i=0;i<g1->count;i++){
//        printf("%d ",ord[i]);
//    }
//    printf("]\n");
//

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




