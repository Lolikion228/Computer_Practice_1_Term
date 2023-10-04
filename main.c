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
    big_int *n1 = big_int_get("+11011");
    big_int_print(n1);
    big_int *n2 = big_int_get("-0");
    big_int_print(n2);
    big_int_add2(n1,n2);
    big_int_print(n1);
    putchar(n1->sign);


//    big_int*n2= big_int_get("+011100000");
//    big_int_print(n2);
//    big_int *n3=big_int_sub(n2,n1,0);
//    big_int_print(n3);

    /*
    big_int*n3=big_int_sub(n1,n2);
    big_int_print(n3);
    */
    /*
    int x=key,y=2;
    swap(&x,&y);
    printf("%d %d",x,y);
     */
    return 0;
}
