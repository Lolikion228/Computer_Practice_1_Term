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
//    tst_add();
    big_int *n1= big_int_get("100");
    big_int *n2= big_int_get("101");
    big_int_free(n1);
    big_int_copy(n1);
    return 0;


}