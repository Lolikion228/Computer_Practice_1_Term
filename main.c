
#include <string.h>
#include "big_int/big_int.h"
#include "lib/lib.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "tests.h"
#include <stdarg.h>

int main() {
    clock_t start_time, end_time;
    double total_time;
    start_time = clock();
    srand(time(NULL));
//    big_int *n1= big_int_get_prime(200,50);
//    big_int_print(n1);
//    big_int_get_prime(256,50);
//    big_int *n1=big_int_rnd(100);
//    big_int_primality_test(n1,100);
//    big_int_free(n1);

    big_int *n1=big_int_rnd(55556);
//    big_int_bin_shft_r2(n1,1000);
    big_int *n2=big_int_rnd(55556);
//    big_int *n3=big_int_rnd(256);
//    big_int_lr_mod_pow2(n1,n2,n3);
//    big_int_div2_for_pow(n1,n2,n2);
//    big_int_karatsuba_mult2(n1,n2);
//      tst();
//    while(1){//0017
//    big_int *n2= big_int_rnd(300);
//    big_int_div2_for_pow(n1,n2,n1);
//    big_int *n3= big_int_rnd(200);
//    big_int_lr_mod_pow2(n1,n2,n3);


//    big_int *n1 = big_int_get("1111111111111111111111111111111111111");
//    big_int *n2 = big_int_get("111111111111111111111111");

//    big_int_primality_test(n1,50);


//    big_int_test_loop(100,big_int_mul);
//    big_int_test_loop(100,big_int_mult);

    big_int_test_loop(1,big_int_karatsuba_mult2);


//    big_int_free2(3,n1,n2,n3);


//    printf("%d\n", big_int_primality_test(n1,50));

    end_time = clock();
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
//    printf("Время выполнения : %f секунд\n", total_time);
    return 0;

}
//python3 chck.py



