#include <stdio.h>
#include <string.h>
#include <math.h>
#include "lib/lib.h"
#include "big_int/big_int.h"
#include <time.h>
#include <stdlib.h>
extern long con;
int main() {
//    tst();
//    clock_t start_time, end_time;
//    double total_time;
//    start_time = clock();

    big_int *n1= big_int_rnd(1000);
    big_int_print(n1);

//    big_int *n2= big_int_rnd(10000);
//    big_int *n3= big_int_mult(n1,n2);
//    end_time = clock();
//    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
//    printf("const=%ld Время выполнения: %f секунд\n",con,total_time);
////    big_int_print(n1);
    big_int_free(n1);
//    big_int_free(n2);
//    big_int_free(n3);
//    big_int *n1= big_int_get("0010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111111111111111111111111111111111111111111111111111100000000000000000000000000000000000000000000000");
//    big_int *n2= big_int_get("10000000000000000000001111111111111111111111111111111111111111111111111100000000000000000000000");
//    big_int *n3= big_int_get("1000000000000000000000000111111111111111111111111111111111111111111111111111111111111111111111100000000001");
//    big_int *n4= big_int_rl_mod_pow(n1,n2,n3);
//    big_int_free(n1);
//    big_int_free(n2);
//    big_int_free(n3);
//    big_int_free(n4);
    return 0;


}