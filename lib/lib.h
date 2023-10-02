//
// Created by lolikion on 01.10.23.
//

#ifndef UNTITLED2_LIB_H
#define UNTITLED2_LIB_H
int euclid(int a, int b);
int mul_inverse(int e, int m);
int euclid_recursive(int a, int b);
int linear_diophantine(int *a, int *result,int n, int c);
long long rl_mod_pow(int x, long long n, int m);
int euclid_extended(int a, int b, int* x, int* y);
int euclid_binary(int x,int y);
int lr_mod_pow(int x, long long n, int p);
int chinese_remainder(const int *a, const int *m, int k);
int chinese_remainder_iterative(const int *a, const int *m, int k);
#endif //UNTITLED2_LIB_H
