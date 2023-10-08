#include <stdio.h>
#include <string.h>
#include <math.h>
#include "lib/lib.h"
#include "big_int/big_int.h"
#include <stdlib.h>

/*
n1=-00001011 10111000
n2=-00001010 11111111
ans n1+n2=-00010110 10110111
my func n1+n2=-00010101 10110111
 */

/*
IMPOSTER i=512633
n1=+00000001 00000000
n2=+00000001 01111010
ans n1/n2=+00000000
my func n1/n2=+00000001

 */

int main() {

//    big_int *n1= big_int_get("111");
//    big_int *n2= big_int_get("11");
//    printf("n1=");
//    big_int_print(n1);
//    printf("n2=");
//    big_int_print(n2);
//    big_int *n3=big_int_get("0");
//    big_int *n4=big_int_get("0");
//    big_int_div(n1,n2,n3,n4);
//    printf("n3=");
//    big_int_print(n3);
//    printf("n4=");
//    big_int_print(n4);


    tst_add();

//    big_int *n1=big_int_get("0000000101111010");
//    big_int_print(n1);
//    big_int *n2=big_int_copy(n1);
//    big_int_print(n1);
//    big_int_print(n2);
//    printf("%d",big_int_leq(n2,n1));
//    big_int_print(n1);
//    big_int_print(n2);
    return 0;
}