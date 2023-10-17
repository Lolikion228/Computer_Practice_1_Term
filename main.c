
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
//    big_int *n1=big_int_get_prime(256,100);
    big_int *n1= big_int_get("1000000011001100");
//    n1->number[0]=rand();
//    printf("n1 = ");
//    big_int_print(n1);
//    printf("%d\n", big_int_primality_test(n1,50));


    end_time = clock();
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Время выполнения : %f секунд\n", total_time);
    return 0;

}
//python3 chck.py