
#include <string.h>
#include "big_int/big_int.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "tests.h"

int main() {
    clock_t start_time, end_time;
    double total_time;
    start_time = clock();
    srand(time(NULL));
//    tst();
//    big_int *n1= big_int_get("1111");
//    big_int *n2= big_int_get("11111");
//    big_int *n;
//    n=big_int_add(n1,n2);
//    big_int_print(n);
//
//    big_int_free(n);
//    n=big_int_get("1111111111111111111111111111111111110");
//    big_int_print(n);
//    big_int_free(n);
//    n=big_int_get("11000000000000000000000000000000000");
//    big_int_print(n);
//
//
//    big_int_free(n);
//    big_int_free(n2);
//    big_int_free(n1);
//    //ВОЗВОДИТЬ В СТЕПЕНЬ ОСТАТОК!!!!!!!!!!!!!!!!!!!!!!!!!!!
    big_int *n1= big_int_get_prime(100,100);
    big_int_print(n1);
    big_int_free(n1);
    end_time = clock();
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Время выполнения : %f секунд\n", total_time);
    return 0;

}