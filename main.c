
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

//    big_int *n1=big_int_rnd(55556);
//    big_int *n2=big_int_rnd(55556);





//    big_int_test_loop(1,big_int_karatsuba_mult2);



    end_time = clock();
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Время выполнения : %f секунд\n", total_time);
    return 0;

}
//python3 chck.py



