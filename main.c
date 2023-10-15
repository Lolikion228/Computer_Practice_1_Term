#include <stdio.h>
#include <string.h>
#include <math.h>
#include "lib/lib.h"
#include "big_int/big_int.h"
#include <time.h>
#include <stdlib.h>
extern long con;

int check(long n){
    for(long i=2;i<n;i++){
        if(n%i==0) return 0;
    }
    return 1;
}
int main() {
    srand(time(NULL));
//    tst();

    big_int *n1= big_int_get_prime(3,100);
    long x=n1->number[0]+((n1->number[1])<<8)+((n1->number[2])<<16);
    printf("%li\n",x);
    printf("really prime = %d\n", check(x));
    big_int_free(n1);
    return 0;


}