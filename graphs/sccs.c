//
// Created by lolikion on 28.11.23.
//

#include "sccs.h"
#include "stdlib.h"
#include "stdio.h"
#include "graphs.h"

scc_list *scc_list_init(){
    scc_list *res=(scc_list*)malloc(sizeof(scc_list));
    res->len=0;
    res->array=NULL;
    return res;
}


void scc_list_print(scc_list *list){
    printf("sccs:{ ");
    for(int i=0;i<list->len;i++){
        printf("[ ");
        node *curr=list->array[i].head;
        while(curr){
            printf("%d ",curr->val);
            curr=curr->next;
        }
        printf("] ");
    }
    printf("}\n");
}


void scc_list_append(list scc,scc_list *list0){
    (list0->len)++;
    list0->array=(list *)realloc( list0->array,(list0->len) * sizeof(list));
    list0->array[(list0->len)-1]=scc;
}


void scc_list_free (scc_list *sccs){

    for(int i=0;i<sccs->len;i++){
        node_free(sccs->array[i].head);
    }
    free(sccs->array);
    free(sccs);
}


void scc_list_transform(scc_list *sccs,int n){
    for(int i=0;i<sccs->len;i++){
        node *curr = sccs->array[i].head;
        while(curr){
            if(curr->val>n){curr->val=n-curr->val;}
            curr=curr->next;
        }
    }
}


int scc_search_for_matches(scc_list *sccs){

    for(int i=0;i<sccs->len;i++){
        node *curr=sccs->array[i].head;
        while(curr){
            node *curr2=curr->next;
            while(curr2){
                if(abs(curr->val)==abs(curr2->val)){return 1;}
                curr2=curr2->next;
            }
            curr=curr->next;
        }
    }

    return 0;
}
