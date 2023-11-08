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

#define MAX_BINARY_LENGTH 40000

rsa_key *RSA_key_get(unsigned int len){

    rsa_key *key = (rsa_key *) malloc(sizeof(rsa_key));
    key->exp= big_int_get("10000000000000001");//e=65537
    key->length=len;
    key->mod= big_int_get("0");
    return key;
}

big_int* char_to_big_int(const char* str){
    big_int *res = (big_int *) malloc(sizeof(big_int));
    res->length = strlen(str);
    res->number = (unsigned char *) calloc(res->length, sizeof(res->number[0]));
    for(int i=0;i<strlen(str);i++){
        res->number[i]=str[i];
    }
    return res;
}

void big_int_txt_print(big_int *x){


    for(int i=0;i<x->length;i++){
        printf("%c",x->number[i]);
    }

    printf("\n");
}


big_int *RSA_enc(big_int *message, rsa_key *key){
    big_int *p = big_int_get_prime((key->length)/2,10);
//    printf("after prime1\n");
    big_int *q = big_int_get_prime((key->length)/2,10);
//    printf("after prime2\n");
    big_int *one = big_int_get("1");
    big_int_free(&(key->mod));
    key->mod = big_int_karatsuba_mult2(p,q);

    big_int_sub2(p,one);
    big_int_sub2(q,one);

    big_int *eu_func=big_int_karatsuba_mult2(p,q);



    big_int *inv_e = big_int_mul_inverse(key->exp,eu_func);

    big_int *res= big_int_lr_mod_pow2(message,key->exp,key->mod);
    big_int_swap(res,message);
    big_int_free2(5,&p,&q,&res,&one,&eu_func);

    return inv_e;
}

void RSA_enc2(big_int *message, rsa_key *key){


    big_int *res= big_int_lr_mod_pow2(message,key->exp,key->mod);
    big_int_swap(res,message);
    big_int_free2(1,&res);

    return;
}

big_int *RSA_gen(rsa_key *key){
    big_int *p = big_int_get_prime((key->length)/2,10);
//    printf("after prime1\n");
    big_int *q = big_int_get_prime((key->length)/2,10);
//    printf("after prime2\n");
    big_int *one = big_int_get("1");
    big_int_free(&(key->mod));
    key->mod = big_int_karatsuba_mult2(p,q);

    big_int_sub2(p,one);
    big_int_sub2(q,one);

    big_int *eu_func=big_int_karatsuba_mult2(p,q);

    big_int *inv_e = big_int_mul_inverse(key->exp,eu_func);

    big_int_free2(4,&p,&q,&one,&eu_func);

    return inv_e;
}


void RSA_dec(big_int *message,big_int *secret_key, rsa_key *public_key){

    big_int *res= big_int_lr_mod_pow2(message,secret_key,public_key->mod);
    big_int_swap(message,res);
    big_int_free2(1,&res);
}

void RSA_key_free(rsa_key* public_key){
    big_int_free2(2,&(public_key->mod),&(public_key->exp));
    free(public_key);
}

void read_file(char* target,char** mod) {
    FILE *file = fopen("rsa/public_keys.txt", "r");
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int t;
    long i1 = -1, i2 = -1;

    while(fgets(buffer, MAX_BINARY_LENGTH + 1, file)!=NULL) {

        t = 1;
        i1 = -1, i2 = -1;
        for (int j = 0; j < strlen(target); j++) {
            if (buffer[j] != target[j]) {
                t = 0;
                break;
            }
        }
        if(buffer[strlen(target)]!=' '){t=0;}

        if (t) {

            for (long j = 0; j < MAX_BINARY_LENGTH; j++) {
                if ((buffer[j] == ' ') && (i1 == -1)) { i1 = j; continue;}
                if ( buffer[j] == '\n')  { i2 = j;break;}
                if ( (buffer[j] == ' ')&&(i1!=-1) )  { i2 = j;break; }
            }
            break;
        }
    }

    if(!t){
        printf("There is no name: %s\n",target);
        return;
    }
    *mod = malloc(i2 - i1 - 1);
    strncpy(*mod, buffer + i1 + 1, i2 - i1 - 1);
    free(buffer);
    fclose(file);
}

void read_file2(char* target,char** secret) {

    FILE *file = fopen("rsa/secret_keys.txt", "r");
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int t;

    long i1 = -1, i2 = -1;

    while(fgets(buffer, MAX_BINARY_LENGTH + 1, file)!=NULL) {
        t = 1;
        i1 = -1, i2 = -1;
        for (int j = 0; j < strlen(target); j++) {
            if (buffer[j] != target[j]) {
                t = 0;
                break;
            }
        }
        if(buffer[strlen(target)]!=' '){t=0;}
        if (t) {
            for (long j = 0; j < MAX_BINARY_LENGTH; j++) {
                if ((buffer[j] == ' ') && (i1 == -1)) { i1 = j;
                    continue; }
                if (buffer[j] == '\n') { i2 = j; break;}
                if ( (buffer[j] == ' ') && (i1!=-1) ) { i2 = j; break;}
            }
            break;
        }
    }

    if(!t){
        printf("There is no name: %s\n",target);
        return;
    }
    *secret = (char*)calloc(i2 - i1 - 1, sizeof(char));

    strncpy(*secret, buffer + i1 + 1, i2 - i1 - 1);

    free(buffer);
    fclose(file);
}

void help_func(){
    printf("description of the app\n");
}


//FIX
void add_key(char*name,int len){
    FILE *file0=fopen("rsa/secret_keys.txt", "r");
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    long i1 = -1, i2 = -1,flag=1;
    long cnt=0;
    while(fgets(buffer, MAX_BINARY_LENGTH + 1, file0)!=NULL) {
        flag=1;
        cnt++;
        for(int i=0;i< strlen(name);i++){
            if(buffer[i]!=name[i]){flag=0;}
        }
        if(flag==1){break;}
    }
    if((flag==1)&&(cnt!=0)){
        printf("Key with this name already exists\n");
        fclose(file0);
        free(buffer);
        return;
    }

    fclose(file0);


    FILE *file=fopen("rsa/secret_keys.txt", "a");

    big_int *msg=big_int_get("10101");
    rsa_key *key= RSA_key_get(len);
    big_int *secret_key= RSA_enc(msg,key);


    fprintf(file,"%s ",name);
    for (int i = secret_key->length - 1; i > -1; i--) {
        int x = secret_key->number[i];
        int bit = 128;
        for (int j = 7; j > -1; j--) {
            fprintf(file,"%i", (x & bit) != 0);
            bit >>= 1;
        }
    }
    fprintf(file,"\n");
    fclose(file);

    FILE *file2=fopen("rsa/public_keys.txt", "a");
    fprintf(file2,"%s ",name);
    for (int i =key->mod->length - 1; i > -1; i--) {
        int x = key->mod->number[i];
        int bit = 128;
        for (int j = 7; j > -1; j--) {
            fprintf(file2,"%i", (x & bit) != 0);
            bit >>= 1;
        }
    }
    fprintf(file2,"\n");
    fclose(file2);
}
long get_time(){
    struct timeval tv1;
    struct timezone tz;
    gettimeofday(&tv1, &tz);
    return tv1.tv_sec;
}
//make big free
void console_app(){
    printf("///////////////console_app////////////////\n");
    char*help_cmd="help";
    char*encode_cmd="encode";
    char*decode_cmd="decode";
    char*exit_cmd="exit";
    char *command = (char*)malloc(400);

    while(1==1){
        printf(">>>");
        char* trash=fgets(command,400,stdin);

        int c1=1,c2=1,c3=1,c4=1;

        for(int j=0;j< strlen(command);j++){
            if( (j<4) && (command[j]!=help_cmd[j]) ){c1=0;}
            if( (j<4) && (command[j]!=exit_cmd[j]) ){c4=0;}
            if( j<6 ){
                if(command[j]!=encode_cmd[j]) {c2=0;}
                if(command[j]!=decode_cmd[j]) {c3=0;}
            }
            if(c1+c2+c3+c4<=1){
                break;
            }
        }
        if(strlen(command)>5){
            c1=0; c4=0;
        }
        if(c1){help_func();}
        if(c2){


            int i1=-1,i2=-1;
            for (long j = 7; j < strlen(command); j++) {
                if ((command[j] == ' ') && (i1 == -1)) { i1 = j; }
                if (command[j] == '\n') { i2 = j; }
            }
            char*target=(char*)calloc(i1-6-1,sizeof(char));
//            printf("name = %s\n",target);
//            printf("len=%li %d\n", strlen(target),i1-6-1);
            char*msg=(char*)calloc(i2-i1-1,sizeof (char));
            strncpy(target,command+7,i1-6-1);
            strncpy(msg,command+1+i1,i2-i1-1);
//            printf("name = %s\n",target);
//            printf("len=%li\n", strlen(target));
//            printf("msg = %s\n",msg);
            char*mod=NULL;

            //encode name1 101010

            read_file(target,&mod);

//            printf("name = %s\n",target);
//            printf("len=%li\n", strlen(target));


            if( (mod!=NULL)  ){
                big_int* mod1= big_int_get(mod);

                rsa_key*key1= RSA_key_get(30);
                key1->mod=mod1;
//                printf("mod = ");
//                big_int_print(key1->mod);

                big_int *int_msg= char_to_big_int(msg);//last \n????
//                printf("msg = ");
//                big_int_print(int_msg);
                RSA_enc2(int_msg,key1);


//                printf("mod2=");
//                big_int_print(key1->mod);
                char*secret=NULL;
                read_file2(target,&secret);


                char*z1="rsa/encrypted/";
                char*path=(char*)calloc(strlen(target)+strlen(z1)+4,sizeof(char));
                strncpy(path,z1,strlen(z1));

                strncpy(path+strlen(z1),target,strlen(target));
                strncpy(path+strlen(z1)+strlen(target),".txt",4);
//                printf("path=%s\n",path);
                FILE *out= fopen(path,"a");

                for (int i = int_msg->length - 1; i > -1; i--) {
                    int x = int_msg->number[i];
                    int bit = 128;
                    for (int j = 7; j > -1; j--) {
                        fprintf(out,"%i", (x & bit) != 0);
                        bit >>= 1;
                    }
                }

                fprintf(out,"\n");
                fclose(out);

                free(path);
                free(target);

//                RSA_dec(int_msg,secret_key,key1);
//                printf("decrypted msg = ");
//                big_int_print(int_msg);
            }
            free(mod);
        }
        if(c3){

            int i1=-1,i2=-1;
            for (long j = 0; j < strlen(command); j++) {
                if ((command[j] == ' ') && (i1 == -1)) { i1 = j; }
                if (command[j] == '\n') { i2 = j; }
            }

            char*target=(char*)calloc(i2-i1-1,sizeof(char));
            strncpy(target,command+7,i2-i1-1);

            char*mod=NULL;
            char*secret=NULL;
//            printf("target=%s\n",target);
            read_file(target,&mod);
            read_file2(target,&secret);



            if( (mod!=NULL) && (secret!=NULL) ){
                big_int *public_key1= big_int_get(mod);
                big_int *secret_key= big_int_get(secret);
//                printf("public=");
//                big_int_print(public_key1);
//                printf("secret=");
//                big_int_print(secret_key);
                rsa_key *key= RSA_key_get(20);
                key->mod=public_key1;
                key->length=public_key1->length;
                char*z1="rsa/encrypted/";
                char*path=(char*)calloc(strlen(target)+strlen(z1)+4,sizeof(char));
                strncpy(path,z1,strlen(z1));
                strncpy(path+strlen(z1),target,strlen(target));
                strncpy(path+strlen(z1)+strlen(target),".txt",4);
                FILE *in= fopen(path,"r");
                char *buffer = malloc(MAX_BINARY_LENGTH + 1);
                while(fgets(buffer, MAX_BINARY_LENGTH + 1, in)!=NULL){
//                    printf("input=%s",buffer);
                    char*str= calloc(strlen(buffer)-1, sizeof(char ));
                    strncpy(str,buffer,strlen(buffer)-1);
                    big_int*msg= big_int_get(str);
//                    printf("ln=%li\n", strlen(str));
                    RSA_dec(msg,secret_key,key);
//                    printf("decoded=");
//                    big_int_print(msg);
                    big_int_txt_print(msg);
                }
                fclose(in);
            }
        }
        if(c4){break;}
        if(c1+c2+c3+c4==0){printf("incorrect command\n");}
//        printf("-----------------------------------------------------------\n");

    }
    free(command);

}