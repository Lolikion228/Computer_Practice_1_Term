#include <stdio.h>
#include <string.h>
#include "big_int/big_int.h"
#include "tests.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
//#include "rsa/rsa.h"
#include "rsa_cli/rsa_cli.h"
#include  "lib/lib.h"
#include "graphs/graphs.h"
#define MAX_BINARY_LENGTH 40000






int main() {
    srand(time(NULL));


//    graph *g1= graph_init(5);
//    for(int i=0;i<g1->count;i++){
//        g1->adj_list[i].head->val=i+1;
//    }


//    tst();

    console_app();
//    char* str1="test";
//    char* str2="kontest336";
//    printf("%s\n", strstr(str2,str1));
//    big_int *n=get_secret_key("fin");
//    big_int *n2= get_public_key("fin");
//    if( (n!=NULL)&&(n2!=NULL) ){
////    big_int_print(n);
////    big_int_print(n2);
//        rsa_key *key= RSA_key_get(15);
//        big_int_free(&(key->mod));
//        key->mod=n2;
//        key->length=key->mod->length;
////        big_int *msg= char_to_big_int("lolikion");
////    printf("msg=");
////    big_int_print(msg);
////        RSA_enc2(msg,key);
////    printf("enc msg=");
////    big_int_print(msg);
//    big_int *msg= big_int_get("000101100101111000111101010000111101100000001001011100000010111101001011001010011110110001111101000101100001000111101001011110101101111110111100001100101110010100010000100100111011101010101101000010100001001100010111111101000011001010111000");
//        RSA_dec(msg,n,key);
//        big_int_txt_print(msg);
////
//    }
//    add_key("test2283",4);
//    add_key("test2",3);
//    add_key("test3",3);
//    add_key("test0007",20);

    return 0;

}
//python3 chck.py




