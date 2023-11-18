//
// Created by lolikion on 02.11.23.
//

#include "../big_int/big_int.h"
#include "rsa.h"
#include "string.h"
#include "stdlib.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/time.h>

#define MAX_BINARY_LENGTH 400000

rsa_key *RSA_key_get(unsigned int len) {

    rsa_key *key = (rsa_key *) malloc(sizeof(rsa_key));
    key->exp = big_int_get("10000000000000001");//e=65537
    key->length = len;
    key->mod = big_int_get("0");
    return key;
}

big_int *char_to_big_int(const char *str) {
    big_int *res = (big_int *) malloc(sizeof(big_int));
    res->length = strlen(str);
    res->number = (unsigned char *) calloc(res->length, sizeof(res->number[0]));
    for (int i = 0; i < strlen(str); i++) {
        res->number[i] = str[i];
    }
    return res;
}

void big_int_txt_print(big_int *x) {


    for (int i = 0; i < x->length; i++) {
        printf("%c", x->number[i]);
    }

    printf("\n");
}


big_int *RSA_enc(big_int *message, rsa_key *key) {
    big_int *p = big_int_get_prime((key->length) / 2, 10);
//    printf("after prime1\n");
    big_int *q = big_int_get_prime((key->length) / 2, 10);
//    printf("after prime2\n");
    big_int *one = big_int_get("1");
    big_int_free(&(key->mod));
    key->mod = big_int_karatsuba_mult2(p, q);

    big_int_sub2(p, one);
    big_int_sub2(q, one);

    big_int *eu_func = big_int_karatsuba_mult2(p, q);


    big_int *inv_e = big_int_mul_inverse(key->exp, eu_func);

    big_int *res = big_int_lr_mod_pow2(message, key->exp, key->mod);
    big_int_swap(res, message);
    big_int_free2(5, &p, &q, &res, &one, &eu_func);

    return inv_e;
}

void RSA_enc2(big_int *message, rsa_key *key) {

    big_int *res = big_int_lr_mod_pow2(message, key->exp, key->mod);
    big_int_swap(res, message);
    big_int_free2(1, &res);

}


void RSA_dec(big_int *message, big_int *secret_key, rsa_key *public_key) {

    big_int *res = big_int_lr_mod_pow2(message, secret_key, public_key->mod);
    big_int_swap(message, res);
    big_int_free2(1, &res);
}

void RSA_key_free(rsa_key *public_key) {
    big_int_free2(2, &(public_key->mod), &(public_key->exp));
    free(public_key);
}
