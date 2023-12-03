#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
//#include "rsa/rsa.h"
#include "graphs/graphs.h"
#include "stack/stack.h"
#include "sat/two_sat.h"
#include "graphs/sccs.h"
#define MAX_BINARY_LENGTH 40000

/*
 * sccs struct +-
 * topsort indexes +-
 * in dfs_scc move extraction of scc to FindSccs <-bad
 * rename in many files  +-
 * remove dfs2 +-
 * return in dfs instead of printf +-
*/




int main() {
    srand(time(NULL));




//
//    scc_list *lst=scc_list_init();
//
//    node *scc1= node_init(7);
//    scc1->next=node_init(3);
//    list sc;
//    sc.head=scc1;
//    scc_list_append(sc,lst);
//
//    node *scc2= node_init(9);
//    scc2->next=node_init(4);
//    scc2->next->next=node_init(5);
//    list sc2;
//    sc2.head=scc2;
//
//    scc_list_append(sc2,lst);
//    scc_list_print(lst);
//    scc_list_free(lst);


//    CNF2 *cnf= CNF2_get("(!x1||!x2)&&(x1||x2)&&(!x1||x2)&&(x1||x3)&&(x3||!x1)");
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
    graph_add_arc(g1,3,5);
    graph_add_arc(g1,3,4);
    graph_add_arc(g1,5,6);
    graph_add_arc(g1,6,1);
    graph_add_arc(g1,2,7);
    graph_add_arc(g1,7,4);
    graph_add_arc(g1,9,1);
    graph_add_arc(g1,8,2);


    graph_print(g1);
    int* ord= topsort(g1);
    printf("isNULL=%d\n",ord==NULL);
    printf("ordering = [ ");
    for(int i=0;i<g1->count;i++){
        printf("%d ",ord[i]);
    }
    printf("]\n");
//

//    scc_list *sccs= FindSccs(g1);
//    scc_list_print(sccs);

////
//    graph_visualize(g1);



    free(ord);
//
//    free(sccs);
    graph_free(g1);
    return 0;

}
//python3 chck.py




