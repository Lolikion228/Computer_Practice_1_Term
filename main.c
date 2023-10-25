
#include <string.h>
#include "big_int/big_int.h"
#include "lib/lib.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "tests.h"
#include <stdarg.h>

int main() {
    clock_t start_time, end_time;
    double total_time;
    start_time = clock();
    srand(time(NULL));
//    tst();

    big_int *message= big_int_rnd(40);
    big_int *msg0= big_int_copy(message);
    printf("message = \n");
    big_int_print(message);
    rsa_key *public_key=RSA_key_get(100);
    big_int *secret_key = RSA_enc(message,public_key);
    printf("secret key = ");
    big_int_print(secret_key);
    printf("public mod = ");
    big_int_print(public_key->mod);
    printf("message_encrypted = \n");
    big_int_print(message);

    RSA_dec(message,secret_key,public_key);

    printf("message0 = \n");
    big_int_print(msg0);
//
    printf("message_decrypted = \n");
    big_int_print(message);

    if(!big_int_equal(msg0,message)){
        printf("/////////////////////////////////////IMPOSTER/////////////////////////////////\n");
    }

//    printf("%d\n",big_int_primality_test(big_int_get("1111"),10));
//    while(1==1){
//    big_int *n1= big_int_get_prime(100,10);
//    big_int_print(n1);}
    big_int_free2(3,&msg0,&message,&secret_key);

    RSA_key_free(public_key);
//    end_time = clock();
//    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
//    printf("Время выполнения : %f секунд\n", total_time);
//

//    big_int *enc_msg= big_int_get("10010100010110000110111000010110011001111101000100011000001010110101110000101010001110000110101011101011110011001001111001001000100110111111100110100101000101001111110110001000101101111110111100111101010000000000101110100111010101000010111010010001111101000111100110110010000100010000110111101100110100101011001100011001111000001100001101001011110000000111001001000011100010001100111100011101010000");
//
//    big_int *secret_key=big_int_get("11111111011101010110000100000000101001100000101011111111111010000011000100010111000111011001000100111001010100001000101001101110001111111111000100011001010001101111100110010111100000111101000110011110100010100110100101000111000101110010110111011010100110111110111001101111011100101110001000100000101000001101111111100011111100001000110000110011010110000000111001010111011100011111010010001101101001");
//    rsa_key *public_key= RSA_key_get(10);
//    public_key->mod= big_int_get("101001110010110011111111001000011000010100111100101001010000111110101110110001010010111111100011110101100101100011111010010110001111100101110010111111010011100101011101011010000100001101110111110011000000000000110111000110111111100000110101110110101100001010010110101000101101111000000011001001010100111000110100001101011100011110111001010110110100100011110100100000111000100101001110011111110001111");
//
//    RSA_dec(enc_msg,secret_key,public_key);
//    big_int_print(enc_msg);
    return 0;

}
//python3 chck.py



