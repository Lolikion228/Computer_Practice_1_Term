//
// Created by lolikion on 02.10.23.
//

#include <math.h>

#ifndef UNTITLED_BIG_INT_H
#define UNTITLED_BIG_INT_H
typedef struct big_int {
    unsigned char *number;
    unsigned int length;
    char sign;
} big_int;

void big_int_set_bit(big_int *n,long long num,int x);

big_int *big_int_rl_mod_pow(big_int *x, big_int *n, big_int *m);

void big_int_swap(big_int *n1, big_int *n2);

big_int *big_int_sub(big_int *n1, big_int *n2);

big_int* big_int_disj(big_int *n1,big_int *n2);

void big_int_sub2(big_int *n1, big_int *n2);

big_int *big_int_add(big_int *n1, big_int *n2);

void big_int_add2(big_int *n1, big_int *n2);

void big_int_dlz(big_int *n);

int big_int_leq(big_int *n1, big_int *n2);

int big_int_geq(big_int *n1, big_int *n2);

void big_int_free(big_int *n);

void big_int_print(const big_int *n);

void big_int_bin_shft_lr(big_int *n);

void big_int_bin_shft_r(big_int *n);

void big_int_bin_shft_r2(big_int *n,int cnt);

void big_int_bin_shft_l(big_int *n);

void big_int_bin_shft_l2(big_int *n,int cnt);

big_int *big_int_get(const char *bin_number);

big_int *big_int_euclid_binary(big_int *x, big_int *y);

big_int *big_int_mult(big_int *x, big_int *y);

big_int *big_int_copy(big_int*x);

void big_int_div(big_int *n1, big_int *n2,big_int *res1,big_int*rmdr);

void big_int_div2(big_int *n1, big_int *n2, big_int *res1, big_int *rmdr);

int tst_add();

int big_int_equal(big_int *n1,big_int *n2);
#endif //UNTITLED_BIG_INT_H
