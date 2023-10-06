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


    big_int *n1 = big_int_get("111000");
    big_int *n2 = big_int_get("110000");
    big_int_print(n1);
    big_int_print(n2);

//    printf("%d",big_int_leq(n1,n2));
    big_int_euclid_binary(n2,n1);
////    big_int_add2(n1,n2);
//    //big_int_print(n3);
//    big_int_free(n1);
//    big_int_free(n2);
////    big_int_free(n3);

    return 0;
}

