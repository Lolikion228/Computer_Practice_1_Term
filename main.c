#include <stdio.h>
#include <string.h>
#include <math.h>
#include "lib/lib.h"
#include "big_int/big_int.h"

int main() {

//    printf("\n");
//    big_int *n1 = big_int_get("-10");
//    big_int_print(n1);
//    big_int *n2 = big_int_get("0");
//    big_int_print(n2);
//    big_int_print(big_int_sub(n2,n1));
//    printf("\n");


    big_int *n1 = big_int_get("1101000000000000");
    big_int_print(n1);
    big_int_bin_shft_r2(n1,15);
    big_int_print(n1);

    return 0;
}

