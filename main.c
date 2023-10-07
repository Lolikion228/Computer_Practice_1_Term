#include <stdio.h>
#include <string.h>
#include <math.h>
#include "lib/lib.h"
#include "big_int/big_int.h"


int dec2bin(int num)
{
    if(num<0)num*=-1;
    int bin = 0, k = 1;

    while (num)
    {
        bin += (num % 2) * k;
        k *= 10;
        num /= 2;
    }

    return bin;
}

/*
 //////////////////start of add2/////////////
n0= +00000000
x0= +00011111 11111100
n1= +00000000 00100010 11111100
x1= +00011111 11111100
//////////////////end of add2//////////////
 */
int main() {

    printf("\n");

    big_int*n1=big_int_get("111111111");
    big_int*n2=big_int_get("10000000000000000");
    big_int_print(n1);
    big_int_print(n2);
    big_int*n3=big_int_mult(n1,n2);

    printf("res=\n");
    big_int_print(n3);
////    big_int_print(n1);
////    big_int_print(n2);
//
//    big_int_free(n1);
//    big_int_free(n2);
////    big_int_free(n3);

    return 0;
}

