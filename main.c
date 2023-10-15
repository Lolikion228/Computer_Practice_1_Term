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
//    srand(time(NULL));
    tst();
//    clock_t start_time, end_time;
//    double total_time;
//    start_time = clock();
//
//    big_int *n1= big_int_get_prime(60,100);
//    big_int_print(n1);
//    big_int_free(n1);
//    end_time = clock();
//    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
//    printf("Время выполнения big_int_get_prime: %f секунд\n", total_time);
    return 0;

}