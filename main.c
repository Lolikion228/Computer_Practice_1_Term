#include <stdio.h>
#include <string.h>
#include "big_int/big_int.h"
#include "tests.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "rsa/rsa.h"
#include  "lib/lib.h"
#define MAX_BINARY_LENGTH 40000
/////// mult: x*=y;





int main() {
    srand(time(NULL));

//    tst();

//    console_app();
//    >>>encode fin lolikion 228
//enc_f
//name=fin
//msg=lolikion 228
//msg=001110000011001000110010001000000110111001101111011010010110101101101001011011000110111101101100
//msg enc=+001011111010001100011101001101111101001001111001100010100001101001000011011110110001100011000100100100100100011011010111101101001110010001010001000011100000110001100101111101011111100011111101010100101101111011001110101100011110001110110010
//>>>encode fin lolikion pro 666
//enc_f
//name=fin
//msg=lolikion pro 666
//msg=00110110001101100011011000100000011011110111001001110000001000000110111001101111011010010110101101101001011011000110111101101100
//msg enc=+001001110101110111001001111001110111001000111110111010011110111001101000001100011001000110101110100000100101011000001011011000011111001100101101011001100010010000010101100111100011010101111010100001001111110100110001100111100000111110110101
//>>>
    big_int *n=get_secret_key("test5");
    big_int *n2= get_public_key("test5");
    if( (n!=NULL)&&(n2!=NULL) ){
//    big_int_print(n);
//    big_int_print(n2);
        rsa_key *key= RSA_key_get(15);
        big_int_free(&(key->mod));
        key->mod=n2;
        key->length=key->mod->length;
//        big_int *msg= char_to_big_int("lolikion 288 pro");
//    printf("msg=");
//    big_int_print(msg);
//        RSA_enc2(msg,key);
//    printf("enc msg=");
//    big_int_print(msg);
    big_int *msg= big_int_get("00001011000111001110100100110010110001111101000011001100100101101110111100010101");
        RSA_dec(msg,n,key);
        big_int_txt_print(msg);
//
    }


//    add_key("test2283",4);
//    add_key("test2",3);
//    add_key("test3",3);
//    add_key("test0007",20);
//    add_key("test0008",21);
//    add_key("test0009",22);


//    rsa_key *key= RSA_key_get(15);
//    big_int_free(&(key->mod));
//    key->mod=big_int_get("0100000101000110000000111110100010001111001001110010001010010111101111011010010111111000111101001010010010101001");
//    key->length=key->mod->length;
//    big_int *secret_key=big_int_get("0000010001101011010011100001011001101111101000101011000110010110010101010010010001111110011001101111010001100101");
//    big_int *msg= char_to_big_int("lolikion228");
////    printf("msg=");
////    big_int_print(msg);
//    RSA_enc2(msg,key);
////    printf("enc msg=");
////    big_int_print(msg);
////    big_int *msg= big_int_get("0010011110111110111011011111010010101011000111010111101100000000000010111000000000111111011101101011001011111111");
//    RSA_dec(msg,secret_key,key);
//    big_int_txt_print(msg);




    return 0;

}
//python3 chck.py




