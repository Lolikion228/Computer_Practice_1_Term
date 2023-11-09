//
// Created by lolikion on 02.11.23.
//

#ifndef UNTITLED_RSA_H
#define UNTITLED_RSA_H

typedef struct {
    unsigned int length;

    big_int *exp;
    big_int *mod;
} rsa_key;

rsa_key *RSA_key_get(unsigned int len);

big_int *RSA_enc(big_int *message, rsa_key *key);

void RSA_dec(big_int *message,big_int *secret_key, rsa_key *public_key);

void RSA_key_free(rsa_key* public_key);

big_int* char_to_big_int(const char* str);
void big_int_txt_print(big_int *x);

void console_app();

big_int *get_secret_key(char *target);
big_int *get_public_key(char *target);

void add_key(char *name,unsigned int len);

void RSA_enc2(big_int *message, rsa_key *key);

#endif //UNTITLED_RSA_H
