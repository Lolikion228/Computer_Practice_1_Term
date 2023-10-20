
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

    tst();


//
//    big_int *n1= big_int_get("1");
//    big_int_free2(1,n1);
//    big_int_free2(1,n1);
//    big_int_free2(1,n1);

//    big_int_print(n1);

//    big_int_test_loop(10,big_int_primality_test);
//    big_int *n1=big_int_get("111111111111110000000000000000000000000000000000000011111");
//    big_int *n2=big_int_get("1011111111111111111111111110000000000011");
//    big_int *n3=big_int_mul_inverse(n1,n2);
//    big_int_print(big_int_mul_inverse(big_int_get("11"), big_int_get("1001")));
//    printf("%d\n", mul_inverse(4,5));
//    big_int_free2(3,n1,n2,n3);

    end_time = clock();
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
//    printf("Время выполнения : %f секунд\n", total_time);
    return 0;

}
//python3 chck.py



