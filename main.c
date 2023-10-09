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
ans=+00000001 00000000 00001110
m=+00101011
ans1=+00000001 00010010
right=00010010
 */

int main() {
//65550/43=1524
//    printf("n1=");
//    big_int *n1= big_int_get("000000010000000000001110");
//    big_int_print(n1);
//    big_int *n2= big_int_get("00101011");
//    printf("n2=");
//    big_int_print(n2);
//    big_int *n3= big_int_get("101011");
////    big_int *n4= big_int_get("0");
//    big_int_div(n1,n2,n3,n3);
//    printf("n1%%n2=");big_int_print(n3);
//47**2%11=9
    tst_add();
//    big_int_print(big_int_rl_mod_pow(n1,n2,n3));
//    big_int_div(n1,n3,n2,n4);
//    big_int_print(n2);
//    big_int_print(n4);
//    big_int_free(n4);
//    printf("%lli", rl_mod_pow(8,2,3));
    return 0;
}