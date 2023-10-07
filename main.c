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


int main() {

    printf("\n");

    big_int*n1=big_int_get("1111111111111");
    big_int*n2=big_int_get("1001111");

    big_int_print(n1);
    big_int_print(n2);

    big_int *n3 = big_int_mult(n1,n2);

    printf("res=");
    big_int_print(n3);
    big_int_print(n1);
    big_int_print(n2);

    big_int_free(n1);
    big_int_free(n2);
    big_int_free(n3);

    return 0;
}

