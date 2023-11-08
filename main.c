#include <stdio.h>
#include <string.h>
#include "big_int/big_int.h"
#include "tests.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include "rsa/rsa.h"
#include  "lib/lib.h"
#define MAX_BINARY_LENGTH 40000
/////// mult: x*=y;





int main() {
    srand(time(NULL));
//    tst();
//    char*text="klopi is bad";
//    big_int *res=char_to_big_int(text);
//    big_int_print(res);
//    big_int_txt_print(res);

//    char*target1="name2";
//    char*mod;
//    char*exp;
//    read_file(target1,&mod,&exp);
//    big_int* mod1= big_int_get(mod);
//    big_int* exp1= big_int_get(exp);
//    big_int_print(mod1);
//    big_int_print(exp1);

//    console_app();

    add_key("lol1",2);
    add_key("lol2",3);
    add_key("lol31",4);
    add_key("prikol3",5);
//    char*mod=NULL;
//    char*secret=NULL;
//    read_file("lol4",&mod);
//    read_file2("lol4",&secret);
//    if( (mod!=NULL) && (secret!=NULL) ) {
//        printf("%s", mod);
//        printf("%s",secret);
//    }

//    big_int *msg=char_to_big_int("prikol123 12409 prikol");
//    rsa_key *public_key= RSA_key_get(24);
//    big_int *secret_key= RSA_enc(msg,public_key);
//    RSA_dec(msg,secret_key,public_key);
//    big_int_txt_print(msg);
//    console_app();




//    big_int *n1= big_int_get("-111");//-7
//    big_int *mod= big_int_get("101");//5
//    big_int *n3= big_int_mul_inverse(n1,mod);
//    big_int *n3= big_int_get("0");
//    big_int_div3(n1,mod,n3);
//    big_int_print(n3);



    return 0;

}
//python3 chck.py




