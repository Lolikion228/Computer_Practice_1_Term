//
// Created by lolikion on 16.10.23.
//
#include <string.h>
#include "big_int/big_int.h"
#include <stdlib.h>
#include "stdio.h"
#include <time.h>

#define MAX_BINARY_LENGTH 200000
#define const1 100


int tst_add() {
    FILE *file = fopen("add.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int err = 0;
    for (long i = 0; i < 1000; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n1 = big_int_get(binary);
        big_int *n12 = big_int_copy(n1);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n2 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans = big_int_get(binary);
        big_int *n3 = big_int_add(n1, n2);
        big_int_add2(n12, n2);
        if ((!big_int_equal(ans, n3)) || (!big_int_equal(ans, n12))) {
            printf("////////////////////////IMPOSTER IN ADD i=%li//////////////\n", i);

            err = 1;
            break;
        }
        big_int_free(&n1);
        big_int_free(&n2);
        big_int_free(&ans);
        big_int_free(&n12);
        big_int_free(&n3);

    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    return err;
}


int tst_sub() {
    FILE *file = fopen("sub.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int err = 0;
    for (long i = 0; i < 1000; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n1 = big_int_get(binary);
        big_int *n12 = big_int_copy(n1);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n2 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans = big_int_get(binary);
        big_int *n3 = big_int_sub(n1, n2);
        big_int_sub2(n12, n2);
        big_int_dlz(n3);
        big_int_dlz(n12);
        big_int_swap2(n1, n12);
        big_int_swap(n1, n12);
        big_int_dlz(n3);
        big_int_dlz(n12);
        big_int_swap2(n1, n12);
        big_int_swap2(n1, n12);
        big_int_dlz(n3);
        big_int_dlz(n12);
        if ((!big_int_equal(ans, n3)) || (!big_int_equal(ans, n12))) {
            printf("////////////////////////IMPOSTER IN SUBi=%li//////////////\n", i);
            err = 1;
            break;
        }
        big_int_free(&n1);
        big_int_free(&n2);
        big_int_free(&ans);
        big_int_free(&n12);
        big_int_free(&n3);
    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    return err;
}


int tst_eu() {
    FILE *file = fopen("eu.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int err = 0;
    for (long i = 0; i < 1000; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n1 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n2 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans = big_int_get(binary);
        big_int *n3 = big_int_euclid_binary(n1, n2);
        big_int_swap(n1, n3);
        big_int_swap(n1, n3);
        if ((!big_int_equal(ans, n3))) {
            printf("////////////////////////IMPOSTER IN EU i=%li//////////////\n", i);
            err = 1;
            break;
        }
        big_int_free(&n1);
        big_int_free(&n2);
        big_int_free(&ans);
        big_int_free(&n3);
    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    return err;
}


int tst_pow() {
    clock_t start_time, end_time;
    double total_time;
    start_time = clock();
    FILE *file = fopen("pow.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int err = 0;
    for (long i = 0; i < 375; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n1 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n2 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *mod = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans = big_int_get(binary);
        big_int *n3 = big_int_lr_mod_pow(n1, n2, mod);
        big_int *n4 = big_int_rl_mod_pow(n1, n2, mod);
        if ((!big_int_equal(ans, n3)) ||  (!big_int_equal(ans, n4))) {
            printf("////////////////////////IMPOSTER IN POWi=%li//////////////\n", i);
            err = 1;
            break;
        }
        big_int_free(&n1);
        big_int_free(&n2);
        big_int_free(&mod);
        big_int_free(&ans);
        big_int_free(&n3);
        big_int_free(&n4);
    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    end_time = clock();
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Время выполнения pow: %f секунд\n", total_time);
    return err;
}


int tst_pow2() {
    clock_t start_time, end_time;
    double total_time;
    start_time = clock();
    FILE *file = fopen("pow.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int err = 0;
    for (long i = 0; i < 375; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n1 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n2 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *mod = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans = big_int_get(binary);
        big_int *n3 = big_int_lr_mod_pow2(n1, n2, mod);
        big_int *n4 = big_int_rl_mod_pow2(n1, n2, mod);
        if ((!big_int_equal(ans, n3)) || (!big_int_equal(ans, n4))) {
            printf("////////////////////////IMPOSTER IN POW2 i=%li//////////////\n", i);
            err = 1;
            break;
        }
        big_int_free(&n1);
        big_int_free(&n2);
        big_int_free(&mod);
        big_int_free(&ans);
        big_int_free(&n3);
        big_int_free(&n4);
    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    end_time = clock();
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Время выполнения pow2: %f секунд\n", total_time);
    return err;
}


int tst_div() {
    FILE *file = fopen("div.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int err = 0;
    for (long i = 0; i < 300; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n1 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n2 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans1 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans2 = big_int_get(binary);
        big_int *my1 = big_int_get("0");
        big_int *my2 = big_int_get("0");
        big_int_div2(n1, n2, my1, my2);
        if ((!big_int_equal(ans1, my1)) || (!big_int_equal(ans2, my2))) {
            printf("////////////////////////IMPOSTER IN DIV i=%li//////////////\n", i);
            err = 1;
            break;
        }
        big_int_free(&n1);
        big_int_free(&n2);
        big_int_free(&ans1);
        big_int_free(&ans2);
        big_int_free(&my1);
        big_int_free(&my2);
    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    return err;
}


int tst_shft1() {
    FILE *file = fopen("shft1.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int err = 0;
    for (long i = 0; i < 300; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n1 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans1 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans2 = big_int_get(binary);
        big_int *my1 = big_int_copy(n1);
        big_int *my2 = big_int_copy(n1);
        big_int_bin_shft_l(my1);
        big_int_bin_shft_r(my2);
        if ((!big_int_equal(ans1, my1)) || (!big_int_equal(ans2, my2))) {
            printf("////////////////////////IMPOSTER IN shft1 i=%li//////////////\n", i);
            err = 1;
            break;
        }
        big_int_free(&n1);
        big_int_free(&ans1);
        big_int_free(&ans2);
        big_int_free(&my1);
        big_int_free(&my2);
    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    return err;
}


int tst_shft2() {
    FILE *file = fopen("shft2.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int err = 0;
    for (long i = 0; i < 300; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n1 = big_int_get(binary);
        buffer= fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n2 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans1 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans2 = big_int_get(binary);
        big_int *my1 = big_int_copy(n1);
        big_int *my2 = big_int_copy(n1);
        big_int_bin_shft_l2(my1, n2->number[0]);
        big_int_bin_shft_r2(my2, n2->number[0]);
        if ((!big_int_equal(ans1, my1)) || (!big_int_equal(ans2, my2))) {
            printf("////////////////////////IMPOSTER IN shft2 i=%li//////////////\n", i);
            printf("n1 = ");
            big_int_print(n1);
            printf("cnt = ");
            printf("%d\n",n2->number[0]);
            printf("ans1 = ");
            big_int_print(ans1);
            printf("ans2 = ");
            big_int_print(ans2);
            printf("my1 = ");
            big_int_print(my1);
            printf("my2 = ");
            big_int_print(my2);
            err = 1;
            break;
        }
        big_int_free(&n1);
        big_int_free(&n2);
        big_int_free(&ans1);
        big_int_free(&ans2);
        big_int_free(&my1);
        big_int_free(&my2);
    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    return err;
}

int tst_shft3() {
    FILE *file = fopen("shift_right.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int err = 0;
    for (long i = 0; i < 300; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n1 = big_int_get(binary);
        buffer= fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n2 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans1 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *my1 = big_int_copy(n1);
        big_int_bin_shft_r2(my1, n2->number[0]);
        if ((!big_int_equal(ans1, my1)) ) {
            printf("////////////////////////IMPOSTER IN shft2 i=%li//////////////\n", i);
            err = 1;
            break;
        }
        big_int_free(&n1);
        big_int_free(&n2);
        big_int_free(&ans1);
        big_int_free(&my1);
    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    return err;
}


int tst_swap() {
    FILE *file = fopen("swap.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int err = 0;
    for (long i = 0; i < 1000; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n1 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n2 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans1 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans2 = big_int_get(binary);
        big_int_swap2(n1,n2);
        big_int_swap(n1,n2);
        big_int_swap2(n1,n2);
        big_int_swap(n1,n2);
        if ((!big_int_equal(ans1, n2)) || (!big_int_equal(ans2, n1))) {
            printf("////////////////////////IMPOSTER IN swap i=%li//////////////\n", i);
            err = 1;
            break;
        }
        big_int_free(&n1);
        big_int_free(&n2);
        big_int_free(&ans1);
        big_int_free(&ans2);
    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    return err;
}


int tst_set_bit() {
    FILE *file = fopen("set_bit.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int err = 0;
    for (long i = 0; i < 200; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n1 = big_int_get(binary);
        big_int *n0 = big_int_copy(n1);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *num = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *bit = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans = big_int_get(binary);
        big_int_set_bit(n1, num->number[0], bit->number[0]);
        big_int_dlz(n1);
        big_int_swap2(n1, ans);
        big_int_swap2(n1, ans);
        big_int_dlz(ans);
        big_int_swap2(n1, ans);
        big_int_swap2(n1, ans);
        big_int_dlz(n1);
        big_int_dlz(ans);
        if ((!big_int_equal(ans, n1))) {
            printf("////////////////////////IMPOSTER IN set_bit i=%li//////////////\n", i);
            err = 1;
            break;
        }
        big_int_free(&n1);
        big_int_free(&n0);
        big_int_free(&num);
        big_int_free(&bit);
        big_int_free(&ans);
    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    return err;
}


int tst_copy() {
    FILE *file = fopen("copy.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int err = 0;
    for (long i = 0; i < 300; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *src = big_int_get(binary);
        big_int *n1 = big_int_copy(src);
        big_int *n2 = big_int_copy(n1);
        big_int *n3 = big_int_copy(n2);
        big_int *n4 = big_int_copy(src);
        big_int_dlz(n1);
        big_int_swap2(n1, n3);
        big_int_dlz(n2);
        big_int_swap2(n1, n2);
        big_int_dlz(n2);
        big_int_swap2(n4, n3);
        big_int_swap2(n2, src);
        big_int_dlz(n1);
        big_int_dlz(n3);
        if ((big_int_equal(src, n1) * big_int_equal(src, n2) * big_int_equal(src, n3) * big_int_equal(src, n4)) != 1) {
            printf("////////////////////////IMPOSTER IN copy i=%li//////////////\n", i);
            err = 1;
            break;
        }
        big_int_free(&n1);
        big_int_free(&n2);
        big_int_free(&n3);
        big_int_free(&n4);
        big_int_free(&src);
    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    return err;
}


int tst_mult() {
    clock_t start_time, end_time;
    double total_time;
    start_time = clock();
    FILE *file = fopen("mult.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int err = 0;
    for (long i = 0; i < 300; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n1 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n2 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans = big_int_get(binary);
        big_int *n4 = big_int_mul(n1, n2);
        if ( (!big_int_equal(ans, n4))) {
            printf("////////////////////////IMPOSTER IN mult i=%li//////////////\n", i);
            err = 1;
            break;
        }
        big_int_free(&n1);
        big_int_free(&n2);
        big_int_free(&n4);
        big_int_free(&ans);
    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    end_time = clock();
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Время выполнения mult: %f секунд\n", total_time);
    return err;
}


int tst_mult2() {
    clock_t start_time, end_time;
    double total_time;
    start_time = clock();
    FILE *file = fopen("mult.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int err = 0;
    for (long i = 0; i < 300; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n1 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n2 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans = big_int_get(binary);
        big_int *n3 = big_int_karatsuba_mult2(n1, n2);
        if ((!big_int_equal(ans, n3))) {
            printf("////////////////////////IMPOSTER IN karatsuba i=%li//////////////\n", i);
            err = 1;
            break;
        }
        big_int_free(&n1);
        big_int_free(&n2);
        big_int_free(&n3);
        big_int_free(&ans);
    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    end_time = clock();
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Время выполнения big_int_karatsuba_mult: %f секунд\n", total_time);
    return err;
}

int tst_prime() {
    clock_t start_time, end_time;
    double total_time;
    start_time = clock();
    FILE *file = fopen("prime.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int err = 0;
    for (long i = 0; i < 1000; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n1 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans = big_int_get(binary);
        int my= big_int_primality_test(n1,10);
//        if(my){ big_int_print(n1);}
        if ((ans->number[0])!=my) {
            printf("////////////////////////IMPOSTER IN prime i=%li//////////////\n", i);
            err = 1;
            break;
        }
        big_int_free(&n1);
        big_int_free(&ans);
    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    end_time = clock();
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Время выполнения big_int_test_prime: %f секунд\n", total_time);
    return err;
}

int tst_inv() {
    clock_t start_time, end_time;
    double total_time;
    start_time = clock();
    FILE *file = fopen("inv.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
    int err = 0;
    for (long i = 0; i < 100; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n1 = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *mod = big_int_get(binary);
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans = big_int_get(binary);
//        printf("b\n");
        big_int *n3 = big_int_mul_inverse(n1, mod);
//        printf("a\n");
        if ((!big_int_equal(ans, n3))) {
            printf("////////////////////////IMPOSTER IN inverse i=%li//////////////\n", i);
            err = 1;
            break;
        }
        big_int_free2(4,&n1,&mod,&ans,&n3);
    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    end_time = clock();
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Время выполнения big_int_mul_inverse: %f секунд\n", total_time);
    return err;
}


void tst() {
    printf("start of the test\n");
    printf("-----------------\n");
    if(tst_swap()){return;}//ok
    else{printf("swap is ok\n");}
    if(tst_add()){return;}//ok
    else{printf("add is ok\n");}
    if(tst_sub()){return;}//ok
    else{printf("sub is ok\n");}
    if(tst_eu()){return;}//ok
    else{printf("eu is ok\n");}
//    if(tst_shft1()){return;}//Ok
//    else{printf("shft1 is ok\n");}
//    if(tst_shft2()){return;}//ok
//    else{printf("shft2 is ok\n");}
//
//    if(tst_div()){return;}//ok
//    else{printf("div is ok\n");}
//    if(tst_set_bit()){return;}//ok
//    else{printf("set_bit is ok\n");}
//    if(tst_copy()){return;}//ok
//    else{printf("copy is ok\n");}
//    if(tst_mult()){return;}//ok
//    else{printf("mult is ok\n");}
//    if(tst_mult2()){return;}//ok
//    else{printf("karatsuba_mult is ok\n");}
//    if(tst_pow()){return;}//ok
//    else{printf("pow is ok\n");}
//    if(tst_pow2()){return;}//ok
//    else{printf("pow2 is ok\n");}
//    if(tst_prime()){return;}//ok
//    else{printf("prime is ok\n");}
//    if(tst_inv()){return;}//ok
//    else{printf("inverse is ok\n");}
    printf("-----------------\n");
    printf("end of the test\n");
}