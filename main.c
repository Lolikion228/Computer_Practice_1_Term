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
 n1=-00001011 10111000
n2=+00000000
ans n1+n2=-00001011 10111000
my func n1+n2=-00100110
len
IMPOSTER i=3000


 */
int main() {
//    big_int *n1= big_int_get("-0000101110111000");
//    big_int *n2= big_int_get("00000000");
//    printf("n1=");
//    big_int_print(n1);
//    printf("n2=");
//    big_int_print(n2);
//    big_int_add2(n1,n2);
//    printf("n1=");
//    big_int_print(n1);

    tst_add();

//    big_int *n1=big_int_get("0000101110111000");
//    big_int *n2=big_int_get("0000101011111111");
//    big_int_print(n1);
//    big_int_print(n2);
//
//    big_int_print(n1);
//    big_int_print(n2);
    return 0;
}