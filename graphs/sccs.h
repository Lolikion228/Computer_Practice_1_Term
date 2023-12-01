//
// Created by lolikion on 28.11.23.
//

#ifndef TITLED1_SCCS_H
#define TITLED1_SCCS_H

#include "../stack/stack.h"
#include "graphs.h"

typedef struct scc_list{
    struct list* array;
    int len;
}scc_list;

scc_list *scc_list_init();

void scc_list_print(scc_list *list);

void scc_list_append(struct list scc,scc_list *list0);

void scc_list_free (scc_list *sccs);
//
void scc_list_transform(scc_list *sccs,int n);
//
int scc_search_for_matches(scc_list *sccs);

#endif //TITLED1_SCCS_H
