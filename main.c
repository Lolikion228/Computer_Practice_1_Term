#include <stdio.h>
#include <math.h>
#include "lib/lib.h"
#include "big_int/big_int.h"

void swap(int *x, int *y) {
    int k = *x;
    *x = *y;
    *y = k;
}

int main() {

    printf("\n");
    big_int *n1 = big_int_get("-10000000");
    big_int_print(n1);
    big_int *n2 = big_int_get("+11000000");
    big_int_print(n2);
    big_int_print(big_int_sub(n1,n2));
    printf("\n");


//    big_int *n1 = big_int_get("+111111111110000000");
//    big_int_print(n1);
//    big_int_bin_shft_rl(n1);
//    big_int_print(n1);

    return 0;
}
