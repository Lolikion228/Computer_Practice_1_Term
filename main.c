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
 change cnf struct
smth like automata
 only lowlinks after dfs_scc???(по желанию)
*/




int main() {
    srand(time(NULL));

    // (2^x-1)*(2^y-1) == 2^{x+y}-2^{y}-2^x+1
//    big_int *n1= big_int_get("111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
//    big_int *n2= big_int_get("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
//    big_int *n3= big_int_karatsuba_mult2(n1,n2);
//    big_int_print(n3);

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


//    graph *g= graph_init(7);
//    graph_add_arc(g, 5, 3);
//    graph_add_arc(g, 3, 1);
//    graph_add_arc(g, 1, 5);
//    graph_add_arc(g, 4, 6);
//    graph_add_arc(g, 6, 2);
//    graph_add_arc(g, 2, 4);
//    graph_add_arc(g, 2, 0);
//    scc_list *res = scc(g);
//    scc_list_print(res);


//
//
//
//    CNF2_print(cnf);
//    graph *g= get_implication_graph(cnf);
//    graph_print(g);
//    graph_free(g);
//    CNF2_free(cnf);

//    CNF2 *cnf= CNF2_get("(!x1||!x2)&&(x1||x2)&&(!x1||x2)&&(x1||!x3)&&(x2||x3)");
    CNF2 *cnf= CNF2_get("(x1||x2)&&(!x2||x3)&&(!x1||!x2) && (x3||x4) && (!x3||x5)&&(!x4||!x5)&&(!x3||x4)");

    clause* curr=cnf->clauses;
    while (curr!=NULL){
        printf("[%d %d] ",curr->first,curr->second);
        curr=curr->next;
    }

    printf("\n");
    CNF2_print(cnf);
    int *x=TWO_SAT(cnf);
    if(x==NULL){printf("unSAT\n");}
    else{
        printf("SAT\n[ ");
        for(int i=1;i<1+cnf->max;i++){printf("%d ",x[i]);}
        printf("]\n");
        printf("test=%d\n", test_two_sat(cnf,x));
    }
    CNF2_free(cnf);
    free(x);
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




