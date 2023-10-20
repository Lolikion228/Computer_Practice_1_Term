
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

//    tst();


//
//    big_int *n1= big_int_get_prime(200,10);
//    big_int_print(n1);

//    big_int_test_loop(10,big_int_primality_test);


//    printf("%d\n", mul_inverse(4,5));
    big_int_print(big_int_extended_eu(big_int_get("101"), big_int_get("1001")));


    end_time = clock();
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
//    printf("Время выполнения : %f секунд\n", total_time);
    return 0;

}
//python3 chck.py



