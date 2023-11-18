//
// Created by lolikion on 02.11.23.
//

#include "../big_int/big_int.h"
#include "rsa_cli.h"
#include "../rsa/rsa.h"
#include "string.h"
#include "stdlib.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/time.h>

#define MAX_BINARY_LENGTH 400000


void add_key(char *name, unsigned int len) {
    FILE *f_r = fopen("rsa_cli/public_keys.txt", "r");
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

    FILE *f_public = fopen("rsa_cli/public_keys.txt", "a");//a or a+??? pos to start of file fseek()
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


    FILE *f_secret = fopen("rsa_cli/secret_keys.txt", "a");//a or a+??? pos to start of file fseek()
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
    FILE *f_s = fopen("rsa_cli/secret_keys.txt", "r");
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
    FILE *f_p = fopen("rsa_cli/public_keys.txt", "r");
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

void hlp_f() {
    printf("description of the app\n");
}

void c2_func(char *name,big_int *secret_key,rsa_key *public_key){
    // new/add file function
    char *pth0 = "rsa_cli/encrypted/";
    char *pth1 = "rsa_cli/decrypted/";
    char *pth = (char *) calloc(strlen(pth0) + strlen(name) + 4, sizeof(char));
    strncpy(pth, pth0, strlen(pth0));
    strncpy(pth + strlen(pth0), name, strlen(name));
    strncpy(pth + strlen(pth0) + strlen(name), ".txt", 4);
    FILE *f_in = fopen(pth, "r");
    strncpy(pth, pth1, strlen(pth1));
    FILE *f_out = fopen(pth, "w+");
    char *str = (char *) calloc(MAX_BINARY_LENGTH, sizeof(char));
    while (fgets(str, MAX_BINARY_LENGTH, f_in) != NULL) {
        char *msg = (char *) calloc(strlen(str) - 1, sizeof(char));
        strncpy(msg, str, strlen(str) - 1);
        big_int *msg2 = big_int_get(msg);
        RSA_dec(msg2, secret_key, public_key);
        for (int i = 0; i < msg2->length; i++) {
            fprintf(f_out, "%c", msg2->number[i]);
        }
        fprintf(f_out, "\n");
    }
    fclose(f_out);
    fclose(f_in);
}

void c1_func(char* name,big_int *msg){
    char *pth0 = "rsa_cli/encrypted/";
    char *pth = (char *) calloc(strlen(pth0) + strlen(name) + 4, sizeof(char));
    strncpy(pth, pth0, strlen(pth0));
    strncpy(pth + strlen(pth0), name, strlen(name));
    strncpy(pth + strlen(pth0) + strlen(name), ".txt", 4);
    FILE *f_out = fopen(pth, "a");
    //write to file
    for (int i = msg->length - 1; i > -1; i--) {
        int x = msg->number[i];
        for (int bit = 0x80; bit; bit >>= 1)
            fprintf(f_out, "%i", (x & bit) != 0);
    }
    fprintf(f_out, "\n");
    fclose(f_out);
    big_int_free(&msg);
    free(pth);
}


//enum + switch_case
void console_app() {
    typedef enum cli_state {encode, decode, exit, add__key, help, invalid_command} cli_state;

    while (1 == 1) {
        int exit_flag=0;
        cli_state curr = invalid_command;
        printf(">>>");
        char *cmd = (char *) calloc(4000, sizeof(char));//with \n on the end!!!
        char *t = fgets(cmd, 4000, stdin);

        if(strstr(cmd,"encode")==cmd){curr=encode;}
        if(strstr(cmd,"decode")==cmd){curr=decode;}
        if(strstr(cmd,"exit")==cmd){curr=exit;}
        if(strstr(cmd,"add_key")==cmd){curr=add__key;}
        if(strstr(cmd,"help")==cmd){curr=help;}



        switch (curr) {
            case invalid_command:{

                if (cmd[0] == '\n') { printf("\n"); }
                if (cmd[0] != '\n') { printf("invalid command\n"); }
                break;
            }
            case encode:{
                int i1=-1, i2=-1, i3=-1, j=0;
                for (char *p = cmd; *p != '\0'; p++) {
                    if ((*p == ' ') && (i1 == -1)) {i1 = j; continue;}
                    if ((*p == ' ') && (i1 != -1) && (i2 == -1)) { i2 = j; }
                    if (*p == '\n') {
                        i3 = j;
                        break;
                    }
                    j++;
                }

                char *name = (char *) calloc(i2 - i1, sizeof(char));
                strncpy(name, cmd + 7, i2 - i1);
                char *msg = (char *) calloc(i3 - i2-1, sizeof(char));
                strncpy(msg, cmd + i2 + 2, i3 - i2-1);

                rsa_key *key = RSA_key_get(15);
                big_int_free(&(key->mod));
                key->mod = get_public_key(name);
                if (key->mod != NULL) {
                    key->length = key->mod->length;
                    big_int *msg2 = char_to_big_int(msg);
                    RSA_enc2(msg2, key);
                    c1_func(name,msg2);
                }
                free(name);
                free(msg);
                RSA_key_free(key);
                break;
            }

            case decode:{
                int i1 = -1, i2 = -1;
                for (int j = 0; j < strlen(cmd); j++) {
                    if ((cmd[j] == ' ') && (i1 == -1)) {
                        i1 = j;
                        continue;
                    }
                    if (cmd[j] == '\n') {
                        i2 = j;
                        break;
                    }
                }
                char *name = (char *) calloc(i2 - i1 - 1, sizeof(char));
                strncpy(name, cmd + 7, i2 - i1 - 1);

                big_int *secret_key = get_secret_key(name);
                rsa_key *public_key = RSA_key_get(15);
                big_int_free(&(public_key->mod));
                public_key->mod = get_public_key(name);

                if ((secret_key != NULL) && (public_key->mod != NULL)) {
                    public_key->length = public_key->mod->length;
                    c2_func(name,secret_key,public_key);
                }
                break;
            }

            case exit:{
                exit_flag=1;
                break;}

            case add__key:{
                int i1 = -1, i2 = -1;
                for (int j = 0; j < strlen(cmd); j++) {
                    if ((cmd[j] == ' ') && (i1 == -1)) { i1 = j; }
                    if (cmd[j] == '\n') {
                        i2 = j;
                        break;
                    }
                }
                char *name = (char *) calloc(i1, sizeof(char));
                strncpy(name, cmd + 8, i2 - i1 - 1);
                printf("len:");
                unsigned int len;
                int t;
                t = scanf("%ui", &len);
                add_key(name, len);
                free(name);
                break;
            }

            case help:{
                hlp_f();
                break;
            }

        }
        if(exit_flag){break;}
        free(cmd);
    }
}
