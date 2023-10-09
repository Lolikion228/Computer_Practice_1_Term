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
000000010000000000001110-1111111111111100=0000000100010010
 65550-65532=274????
 */

int main() {
// (3**29)%43
    printf("n1=");
    big_int *n1= big_int_get("111");
    big_int_print(n1);
    big_int *n2= big_int_get("1111111111111111111111111");
    printf("n2=");
    big_int_print(n2);
//    //65550/43=1524
//    //65550%43=274
//    //43*1524=65532
    big_int *n3= big_int_get("11101");
    printf("n3=");
    big_int_print(n3);
////    big_int *n4= big_int_get("0");
//    big_int_div(n1,n2,n3,n3);
//    printf("n1%%n2=");big_int_print(n3);
//47**2%11=9
//    tst_add();
    big_int_print(big_int_rl_mod_pow(n1,n2,n3));
//    big_int_div(n1,n3,n2,n4);
//    big_int_print(n2);
//    big_int_print(n4);
//    big_int_free(n4);
//    printf("%lli", rl_mod_pow(8,2,3));
    return 0;
}