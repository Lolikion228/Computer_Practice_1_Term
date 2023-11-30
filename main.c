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

/*
 * sccs struct
 * topsort indexes
 * in dfs_scc move extraction of scc to FindSccs +-
 * rename in many files +-
 * remove dfs2 +-
 * return in dfs instead of printf +-
*/




int main() {
    srand(time(NULL));



//    CNF2 *cnf= CNF2_get("(x1||x2)&&(!x1||!x2)&&(x1||!x2)&&(!x1||!x2)&&(x3||x1)&&(!x3||x2)");
//    for(int i=0;i<cnf->clauses;i++){
//        printf("[%d %d] ",cnf->arr[i][0],cnf->arr[i][1]);
//    }
//    printf("\n");
//    CNF2_print(cnf);
//    int *x=TWO_SAT(cnf);
//    if(x==NULL){printf("not SAT\n");}
//    else{
//        printf("SAT\n[ ");
//        for(int i=1;i<1+cnf->max;i++){printf("%d ",x[i]);}
//        printf("]\n");
//        printf("test=%d\n", test_two_sat(cnf,x));
//    }
//    CNF2_free(cnf);
//    free(x);




    graph *g1= graph_init(10);
    graph_add_arc(g1,0,1);
    graph_add_arc(g1,1,2);
    graph_add_arc(g1,0,1);
    graph_add_arc(g1,4,5);
    graph_add_arc(g1,6,7);
    graph_add_arc(g1,7,3);
    graph_add_arc(g1,0,5);
    graph_add_arc(g1,4,1);
    graph_add_arc(g1,3,5);
    graph_add_arc(g1,5,9);
    graph_add_arc(g1,9,1);


    graph_print(g1);
    int* ord= topsort(g1);

    printf("ordering = [ ");
    for(int i=0;i<g1->count;i++){
        printf("%d ",ord[i]);
    }
    printf("]\n");
//
//    int *sccs= FindSccs(g1);
////
//    visualize_graph(g1);
    graph_free(g1);
    free(ord);
//
//    free(sccs);
    return 0;

}
//python3 chck.py




