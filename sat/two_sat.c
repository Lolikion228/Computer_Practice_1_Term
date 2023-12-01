//
// Created by lolikion on 27.11.23.
//

#include "two_sat.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "math.h"
#include "../graphs/graphs.h"

CNF2 *CNF2_init(int n) {
    CNF2 *cnf = (CNF2 *) malloc(sizeof(struct CNF2));
    cnf->clauses = n;
    cnf->arr = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        cnf->arr[i] = (int *) malloc(2 * sizeof(int));
    }
    return cnf;
}


CNF2 *CNF2_get(char *str) {
    int cnt = 0, mx = 0, j, curr, flag = 0, ord;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '(') { ++cnt; }
    }

    CNF2 *cnf = CNF2_init(cnt);

    for (int i = strlen(str) - 1; i >= 0; i--) {
        if (str[i] == ')') {
            --cnt;
            flag = 1;
        }
        if ((str[i] == ')') || ((str[i] == '|') && (str[i + 1] == '|'))) {
            j = i - 1;
            curr = 0;
            ord = 0;
            while (str[j] != 'x') {
                curr += (str[j] - 48) * (int) pow(10, ord);
                j--;
                ord++;
            }
            mx = mx >= curr ? mx : curr;
            cnf->max = mx;

            cnf->arr[cnt][flag % 2] = ((str[j - 1] == '!') ? -1 : 1) * curr;
            ++flag;
        }
    }
    return cnf;
}


void CNF2_print(CNF2 *cnf) {
    for (int i = 0; i < cnf->clauses; i++) {
        printf("(");
        if (cnf->arr[i][0] >= 0) { printf("x%d||", cnf->arr[i][0]); }
        else { printf("!x%d||", (-1) * (cnf->arr[i][0])); }
        if (cnf->arr[i][1] >= 0) { printf("x%d)", cnf->arr[i][1]); }
        else { printf("!x%d)", (-1) * (cnf->arr[i][1])); }
        if (i != (cnf->clauses) - 1) { printf("&&"); }
    }
    printf("\n");
}


void CNF2_free(CNF2 *cnf) {
    for (int i = 0; i < cnf->clauses; i++) {
        free(cnf->arr[i]);
    }
    free(cnf->arr);
    free(cnf);
}


graph *get_implication_graph(CNF2 *cnf) {
    int M = cnf->clauses, N = cnf->max;
    graph *g = graph_init(1 + 2 * N);

    for (int i = 0; i < M; i++) {

        int x1 = cnf->arr[i][0], x2 = cnf->arr[i][1];

        if (x1 < 0) { x1 = abs(x1) + N; }
        if (x2 < 0) { x2 = abs(x2) + N; }

        graph_add_arc(g, x1 + (x1 <= N ? N : -(1) * N), x2);
        graph_add_arc(g, x2 + (x2 <= N ? N : -(1) * N), x1);

    }

    return g;
}



void get_vals(scc_list *sccs, int *res, int cnt) {
    int flag;
    for (int i = 0; i < sccs->len; i++) {
        node *curr=sccs->array[i].head;
        while (curr) {
            if (res[abs(curr->val)] == -1) {
                res[abs(curr->val)] = curr->val >= 0 ? 1 : 0;
            }
            flag = 1;
            for (int k = 1; k < cnt; k++) {
                if (res[k] == -1) {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1) { return; }
            curr=curr->next;
        }
    }

}


int *TWO_SAT(CNF2 *cnf) {
    graph *g = get_implication_graph(cnf);
    graph_print(g);
    scc_list *sccs = FindSccs(g);
//    graph_visualize(g);
    scc_list_print(sccs);

    scc_list_transform(sccs, cnf->max);
    scc_list_print(sccs);
    graph_free(g);
    int matches = scc_search_for_matches(sccs);
    printf("matches=%d\n", matches);
    if (matches) { return NULL; }
    int *res = (int *) malloc((1 + cnf->max) * sizeof(int));
    for (int i = 0; i < 1 + cnf->max; i++) { res[i] = -1; }
    get_vals(sccs, res, 1 + cnf->max);
    scc_list_free(sccs);
    return res;
}


int test_two_sat(CNF2 *cnf, int *vals) {
    int curr, x1, x2;
    for (int i = 0; i < cnf->clauses; i++) {
        curr = 0;
        x1 = cnf->arr[i][0];
        x2 = cnf->arr[i][1];
        if (x1 > 0) { curr += vals[x1]; }
        if (x1 < 0) { curr += vals[abs(x1)] == 1 ? 0 : 1; }
        if (x2 > 0) { curr += vals[x2]; }
        if (x2 < 0) { curr += vals[abs(x2)] == 1 ? 0 : 1; }
        if (curr == 0) { return 0; }
    }
    return 1;
}

