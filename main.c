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
    tst();
    clock_t start_time, end_time;
    double total_time;
    start_time = clock();
    //ВОЗВОДИТЬ В СТЕПЕНЬ ОСТАТОК!!!!!!!!!!!!!!!!!!!!!!!!!!!
//    big_int *n1= big_int_get_prime(200,100);
//    big_int *n1= big_int_get("100100000011000110000000011110110100001100100000011000110000000011110110100001001010111100001111111011111001000101001010100110100001111011010001111101101111000001000101000111000110011111100111001000000110001100000000111101101000010010101111000011111110111110010001010010101001101000011110110100011111011011110000010001010001110001100111111001110010000001100011000000001111011010000100101011110000111111101111100100010100101010011010000111101101000111110110111100000100010100011100011001111110011100100000011000110000000011110110100001001010111100001111111011111001000101001010100110100001111011010001111101101111000001000101000111000110011111100111001000000110001100000000111101101000010010101111000011111110111110010001010010101001101000011110110100011111011011110000010001010001110001100111111001110010000001100011000000001111011010000100101011110000111111101111100100010100101010011010000111101101000111110110111100000100010100011100011001111110011001010111100100100000011000110000000011110110100001001010111100001111111011111001000101001010100110100001111011010001111101101111000001000101000111000110011111100111001000000110001100000000111101101000010010101111000011111110111110010001010010101001101000011110110100011111011011110000010001010001110001100111111001110010000001100011000000001111011010000100101011110000111111101111100100010100101010011010000111101101000111110110111100000100010100011100011001111110011100100000011000110000000011110110100001001010111100001111111011111001000101001010100110100001111011010001111101101111000001000101000111000110011111100110011111110111110010001010010101001101000011110110100011111011011110000010001010001110001100111111001110010000001100011000000001111011010000100101011110000111111101111100100010100101010011010000111101101000111110110111100000100010100011100011001111110011010000100000010000000111011100101111011111010010000001000001101001000011100101011100011111110001000101011110111100101000111100110100101110001111111000101010101010111001");
//    big_int *n1= big_int_rnd(200);
//    big_int *n2= big_int_rnd(230);
//    big_int *n3= big_int_rnd(230);
//    big_int *n4= big_int_karatsuba_mult(n1,n2);
//    big_int_div2_for_pow(n1,n2,n3);// (n3=n1%n2)
//    big_int *n4=big_int_lr_mod_pow2(n1,n2,n3);
////    printf("%d", big_int_primality_test(n1,100));
//    big_int_print(n1);
//    big_int_free(n1);
//    big_int_free(n2);
//    big_int_free(n3);
//    big_int_free(n4);
    end_time = clock();
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
//    printf("Время выполнения : %f секунд\n", total_time);
    return 0;

}