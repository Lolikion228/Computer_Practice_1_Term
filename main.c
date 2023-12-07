#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
//#include "rsa/rsa.h"
#include "rsa_cli/rsa_cli.h"
#include "graphs/graphs.h"
#include "big_int/big_int.h"
#include "stack/stack.h"
#include "sat/two_sat.h"
#include "graphs/sccs.h"
#define MAX_BINARY_LENGTH 40000

/*
 * topsort indexes +-
 * sccs struct +-
 * in dfs_scc move extraction of scc to FindSccs !!!!!!!
 * rename in many files  +-
 * remove dfs2 +-
 * return in dfs instead of printf +-
*/




int main() {
    srand(time(NULL));

//    graph *g= graph_init(7);
//    graph_add_arc(g, 0, 1);
//    graph_add_arc(g, 1, 0);
//    graph_add_arc(g, 2, 0);
//    graph_add_arc(g, 2, 1);
//    graph_add_arc(g, 2, 3);
//    graph_add_arc(g, 3, 2);
//    graph_add_arc(g, 4, 1);
//    graph_add_arc(g, 4, 3);
//    graph_add_arc(g, 4, 5);
//    graph_add_arc(g, 5, 3);
//    graph_add_arc(g, 5, 6);
//    graph_add_arc(g, 6, 4);
//    scc_list *res = scc(g);
//    scc_list_print(res);


    graph *g= graph_init(7);
    graph_add_arc(g, 5, 3);
    graph_add_arc(g, 3, 1);
    graph_add_arc(g, 1, 5);
    graph_add_arc(g, 4, 6);
    graph_add_arc(g, 6, 2);
    graph_add_arc(g, 2, 4);
    graph_add_arc(g, 2, 0);
    scc_list *res = scc(g);
    scc_list_print(res);


//
//
//
//    CNF2 *cnf= CNF2_get("(!x1||!x2)&&(x1||x2)&&(!x1||x2)&&(x1||!x2)&(x2||x3)");
////    CNF2 *cnf= CNF2_get("(x1||x3)&&(x1||!x4)&&(x2||!x4) && (x2||!x5) && (x3||!x5)&&(x1||!x6)&&(x2||!x6)&&(x3||!x6) &&(x4||x7)&&(x5||x7)&&(x6||x7)");
//    for(int i=0;i<cnf->clauses;i++){
//        printf("[%d %d] ",cnf->arr[i][0],cnf->arr[i][1]);
//    }
//    printf("\n");
//    CNF2_print(cnf);
//    int *x=TWO_SAT(cnf);
//    if(x==NULL){printf("unSAT\n");}
//    else{
//        printf("SAT\n[ ");
//        for(int i=1;i<1+cnf->max;i++){printf("%d ",x[i]);}
//        printf("]\n");
//        printf("test=%d\n", test_two_sat(cnf,x));
//    }
//    CNF2_free(cnf);
//    free(x);
//



//    graph *g= graph_init(7);
//    graph_add_arc(g, 0, 1);
//    graph_add_arc(g, 1, 0);
//    graph_add_arc(g, 2, 0);
//    graph_add_arc(g, 2, 1);
//    graph_add_arc(g, 2, 3);
//    graph_add_arc(g, 3, 2);
//    graph_add_arc(g, 4, 1);
//    graph_add_arc(g, 4, 3);
//    graph_add_arc(g, 4, 5);
//    graph_add_arc(g, 5, 3);
//    graph_add_arc(g, 5, 6);
//    graph_add_arc(g, 6, 4);
//
//
//    graph_print(g);
////    int* ord= topsort(g1);
////    printf("isNULL=%d\n",ord==NULL);
////    printf("ordering = [ ");
////    for(int i=0;i<g1->count;i++){
////        printf("%d ",ord[i]);
////    }
////    printf("]\n");
////
//
//    scc_list *sccs= FindSccs(g);
//    scc_list_print(sccs);
//
//////
//    graph_visualize(g);
//
//
//
////    free(ord);
////
//    free(sccs);
//    graph_free(g);
    return 0;

}
//python3 chck.py




