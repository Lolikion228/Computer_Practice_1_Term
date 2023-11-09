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


void add_key(char *name, unsigned int len) {
    FILE *f_r = fopen("rsa/public_keys.txt", "r");
    char *str = (char *) calloc(MAX_BINARY_LENGTH, sizeof(char));
    while (fgets(str, MAX_BINARY_LENGTH, f_r) != NULL) {
        int exists = 1;
        int i1 = -1, i2 = -1;
        for (int j = 0; j < strlen(str); j++) {
            if ((str[j] == ' ') && (i1 == -1)) { i1 = j; }
            if (str[j] == '\n') {
                i2 = j;
                break;
            }
        }

        char *name2 = (char *) calloc(i1, sizeof(char));
        strncpy(name2, str, i1);
        exists = 0;
        if (strlen(name2) == strlen(name)) {
            exists = 1;
            for (int j = 0; j < strlen(name); j++) {
                if (name[j] != name2[j]) { exists = 0; }
            }
        }
        if (exists == 1) {
            printf("key with this name already exists\n");
            free(str);
            free(name2);
            fclose(f_r);
            return;
        }
    }


    fclose(f_r);


    big_int *msg = big_int_get("1111000011110000");
    rsa_key *public_key = RSA_key_get(len);
    big_int *secret_key = RSA_enc(msg, public_key);
//    printf("mod=");
//    big_int_print(public_key->mod);
//    printf("secret=");
//    big_int_print(secret_key);

    FILE *f_public = fopen("rsa/public_keys.txt", "a");//a or a+??? pos to start of file fseek()
    fprintf(f_public, "%s ", name);
    for (int i = public_key->mod->length - 1; i > -1; i--) {
        int x = public_key->mod->number[i];
        int bit = 128;
        for (int j = 7; j > -1; j--) {
            fprintf(f_public, "%i", (x & bit) != 0);
            bit >>= 1;
        }
    }
    fprintf(f_public, "\n");
    fclose(f_public);


    FILE *f_secret = fopen("rsa/secret_keys.txt", "a");//a or a+??? pos to start of file fseek()
    fprintf(f_secret, "%s ", name);
    for (int i = secret_key->length - 1; i > -1; i--) {
        int x = secret_key->number[i];
        int bit = 128;
        for (int j = 7; j > -1; j--) {
            fprintf(f_secret, "%i", (x & bit) != 0);
            bit >>= 1;
        }
    }
    fprintf(f_secret, "\n");
    fclose(f_secret);


    big_int_free2(2, &msg, &secret_key);
    RSA_key_free(public_key);


}

big_int *get_secret_key(char *target) {
    FILE *f_s = fopen("rsa/secret_keys.txt", "r");
    char *str = (char *) calloc(MAX_BINARY_LENGTH, sizeof(char));

    int equal = 1;
    while (fgets(str, MAX_BINARY_LENGTH, f_s) != NULL) {
//        printf("%s",str);
        equal = 1;
        int i1 = -1, i2 = -1;
        for (int j = 0; j < strlen(str); j++) {
            if ((str[j] == ' ') && (i1 == -1)) { i1 = j; }
            if (str[j] == '\n') {
                i2 = j;
                break;
            }
        }

        char *name = (char *) calloc(i1, sizeof(char));
        strncpy(name, str, i1);
        equal = 0;
        if (strlen(name) == strlen(target)) {
            equal = 1;

            for (int i = 0; i < strlen(name); i++) {
                if (name[i] != target[i]) {
                    equal = 0;
                    break;
                }
            }
        }
        if (equal == 1) {

//            printf("%d %d\n",i1,i2);
            char *s_key = (char *) calloc(i2 - i1 - 1, sizeof(char));

            strncpy(s_key, str + i1 + 1, i2 - i1 - 1);
            big_int *s_key2 = big_int_get(s_key);
//            printf("name=%s\n",name);
//            printf("key=%s\n",s_key);
//            printf("key2=");
//            big_int_print(s_key2);
//            printf("%lu %lu\n",strlen(name),strlen(s_key));
            fclose(f_s);
            free(str);
            free(name);
            free(s_key);
            return s_key2;
            break;
        }
//        printf("-------------------\n");
        free(name);
    }
    printf("there is no key with name:%s\n", target);
    free(str);

    fclose(f_s);
    return NULL;
}

big_int *get_public_key(char *target) {
    FILE *f_p = fopen("rsa/public_keys.txt", "r");
    char *str = (char *) calloc(MAX_BINARY_LENGTH, sizeof(char));

    int equal = 1;
    while (fgets(str, MAX_BINARY_LENGTH, f_p) != NULL) {
//        printf("%s",str);
        equal = 1;
        int i1 = -1, i2 = -1;
        for (int j = 0; j < strlen(str); j++) {
            if ((str[j] == ' ') && (i1 == -1)) { i1 = j; }
            if (str[j] == '\n') {
                i2 = j;
                break;
            }
        }

        char *name = (char *) calloc(i1, sizeof(char));
        strncpy(name, str, i1);
        equal = 0;
        if (strlen(name) == strlen(target)) {
            equal = 1;

            for (int i = 0; i < strlen(name); i++) {
                if (name[i] != target[i]) {
                    equal = 0;
                    break;
                }
            }
        }
        if (equal == 1) {

//            printf("%d %d\n",i1,i2);
            char *p_key = (char *) calloc(i2 - i1 - 1, sizeof(char));

            strncpy(p_key, str + i1 + 1, i2 - i1 - 1);
            big_int *p_key2 = big_int_get(p_key);
//            printf("name=%s\n",name);
//            printf("key=%s\n",s_key);
//            printf("key2=");
//            big_int_print(s_key2);
//            printf("%lu %lu\n",strlen(name),strlen(s_key));
            fclose(f_p);
            free(str);
            free(name);
            free(p_key);
            return p_key2;
            break;
        }
//        printf("-------------------\n");
        free(name);
    }
    printf("there is no key with name:%s\n", target);
    free(str);

    fclose(f_p);
    return NULL;
}

void hlp_f(){
    printf("description of the app\n");
}
void console_app() {
    char *enc_c = "encode";
    char *dec_c = "decode";
    char *ext_c = "exit";
    char *add_c = "add_key";
    char *hlp_c = "help";
    int c1, c2, c3, c4, c5;
    while (1 == 1) {
        printf(">>>");
        c1 = 1;
        c2 = 1;
        c3 = 1;
        c4 = 1;
        c5 = 1;
        char *cmd = (char *) calloc(4000, sizeof(char));//with \n on the end!!!
        char *t = fgets(cmd, 4000, stdin);
        for (int j = 0; j < 7; j++) {
            if ((cmd[j] != enc_c[j]) && (j < 6)) { c1 = 0; }
            if ((cmd[j] != dec_c[j]) && (j < 6)) { c2 = 0; }
            if ((cmd[j] != ext_c[j]) && (j < 4)) { c3 = 0; }
            if ((cmd[j] != add_c[j]) && (j < 7)) { c4 = 0; }
            if ((cmd[j] != hlp_c[j]) && (j < 4)) { c5 = 0; }
        }
        if (c1 + c2 + c3 + c4 + c5 != 1) {
            printf("invalid command\n");
        }
        if (c1) {
//            printf("enc_f\n");
            int i1=-1,i2=-1,i3=-1;
            for (int j = 0; j < strlen(cmd); j++) {
                if ((cmd[j] == ' ') && (i1 == -1)) { i1 = j;continue; }
                if ((cmd[j] == ' ') && (i1 != -1) && (i2==-1) ) { i2 = j; }
                if (cmd[j] == '\n') {i3 = j;break;}
            }
            char*name=(char*)calloc(i2-i1-1, sizeof(char));
            strncpy(name,cmd+7,i2-i1-1);
            char*msg=(char*)calloc(i3-i2-1, sizeof(char));
            strncpy(msg,cmd+i2+1,i3-i2-1);
//            printf("name=%s\n",name);
//            printf("msg=%s\n",msg);

            rsa_key *key= RSA_key_get(15);
            big_int_free(&(key->mod));
            key->mod= get_public_key(name);
            if(key->mod!=NULL){
                key->length=key->mod->length;
                big_int *msg2= char_to_big_int(msg);
    //            printf("msg=");
    //            big_int_print(msg2);
                RSA_enc2(msg2,key);
    //            printf("msg enc=");
    //            big_int_print(msg2);
                char*pth0="rsa/encrypted/";
                char*pth=(char*)calloc(strlen(pth0)+ strlen(name)+4, sizeof(char));
                strncpy(pth,pth0,strlen(pth0));
                strncpy(pth+strlen(pth0),name,strlen(name));
                strncpy(pth+strlen(pth0)+strlen(name),".txt",4);
    //            printf("path=%s\n",pth);
                FILE *f_out= fopen(pth,"a");
                //write to file
                for (int i = msg2->length - 1; i > -1; i--) {
                    int x = msg2->number[i];
                    int bit = 128;
                    for (int j = 7; j > -1; j--) {
                        fprintf(f_out,"%i", (x & bit) != 0);
                        bit >>= 1;
                    }
                }
                fprintf(f_out,"\n");
                fclose(f_out);
                big_int_free(&msg2);
                free(pth);
            }
            free(name);
            free(msg);
            RSA_key_free(key);
        }
        if (c2) {
            int i1=-1,i2=-1;
            for (int j = 0; j < strlen(cmd); j++) {
                if ((cmd[j] == ' ') && (i1 == -1)) { i1 = j;continue; }
                if (cmd[j] == '\n') {i2 = j;break;}
            }
            char*name=(char*)calloc(i2-i1-1, sizeof(char));
            strncpy(name,cmd+7,i2-i1-1);


            big_int *secret_key= get_secret_key(name);

            rsa_key *public_key= RSA_key_get(15);
            big_int_free(&(public_key->mod));
            public_key->mod=get_public_key(name);
            public_key->length=public_key->mod->length;

            char*pth0="rsa/encrypted/";
            char*pth1="rsa/decrypted/";
            char*pth=(char*)calloc(strlen(pth0)+ strlen(name)+4, sizeof(char));
            strncpy(pth,pth0,strlen(pth0));
            strncpy(pth+strlen(pth0),name,strlen(name));
            strncpy(pth+strlen(pth0)+strlen(name),".txt",4);
            FILE *f_in=fopen(pth,"r");
            strncpy(pth,pth1,strlen(pth1));
            FILE *f_out=fopen(pth,"w+");
            char *str=(char*)calloc(MAX_BINARY_LENGTH,sizeof(char));
            while (fgets(str, MAX_BINARY_LENGTH, f_in) != NULL){

                char*msg=(char*)calloc(strlen(str)-1,sizeof(char));
                strncpy(msg,str,strlen(str)-1);
//                printf("%s\n",msg);
                big_int *msg2=big_int_get(msg);
                RSA_dec(msg2,secret_key,public_key);
//                big_int_txt_print(msg2);
                for (int i = 0; i < msg2->length; i++) {
                    fprintf(f_out,"%c", msg2->number[i]);
                }
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            fclose(f_in);
        }
        if (c3) {
            break;
        }
        if (c4) {
            int i1=-1,i2=-1;
            for (int j = 0; j < strlen(cmd); j++) {
                if ((cmd[j] == ' ') && (i1 == -1)) { i1 = j; }
                if (cmd[j] == '\n') {
                    i2 = j;
                    break;
                }
            }
            char*name=(char*)calloc(i1, sizeof(char));
            strncpy(name,cmd+8,i2-i1-1);
            printf("len:");
            unsigned int len;
            int t;
            t=scanf("%ui",&len);
            add_key(name,len);
            free(name);
        }
        if (c5) {
            hlp_f();
        }
    }
}