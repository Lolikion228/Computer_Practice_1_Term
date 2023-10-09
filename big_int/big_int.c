//
// Created by lolikion on 02.10.23.
//
#include <string.h>
#include "big_int.h"
#include <stdlib.h>
#include "stdio.h"
#include <math.h>


#define MAX_BINARY_LENGTH 32

//ok
big_int *big_int_get(const char *bin_number) {//'-'=45 '+'=43
    big_int *n1 = (big_int *) malloc(sizeof(big_int));
    int len1 = strlen(bin_number), t = 0;
    if (bin_number[0] == '-') {
        t = 1;
        n1->sign = '-';
    } else n1->sign = '+';
    n1->length = (len1 + 7 - t) >> 3;
    n1->number = (unsigned char *) calloc(n1->length, sizeof(n1->number));
    int i;
    for (i = 0; i < len1 - t; i++) {
        n1->number[i / 8] += (bin_number[len1 - i - 1] - '0') << (i % 8);
    }
    big_int_dlz(n1);
    return n1;
}


//ok
void big_int_print(const big_int *n) {
    putchar(n->sign);
    for (int i = n->length - 1; i > -1; i--) {
        int x = n->number[i];
        int bit = 128;
        for (int j = 7; j > -1; j--) {
            printf("%i", (x & bit) != 0);
            bit >>= 1;
        }
        if (i)printf(" ");
    }
    printf("\n");

}


//ok
void big_int_bin_shft_r(big_int *n) {
    for (int i = 0; i < n->length; i++) {
        n->number[i] >>= 1;
        if (i != ((n->length) - 1)) n->number[i] += (((n->number[i + 1])) & 1) << 7;
    }
    big_int_dlz(n);
}


//ok
void big_int_bin_shft_l(big_int *n) {
    int t = (n->number[(n->length) - 1]) & 128;
    if (t) {
        n->length++;
        n->number = (unsigned char *) realloc(n->number, n->length * sizeof(n->number));
        memset(n->number + (n->length) - 1, 0, 1);
    }
    for (int i = n->length - 1; i > -1; i--) {
        n->number[i] <<= 1;
        if (i) n->number[i] += (n->number[i - 1] & 128) != 0;
    }
    //big_int_dlz(n);
}

////??? shift n bits to the right, e.g. n = 27 00000000 00000000 00000000 000
//ok?????
void big_int_bin_shft_l2(big_int *n, int cnt) {
    for (int i = 0; i < cnt % 8; i++) big_int_bin_shft_l(n);
    unsigned int x = cnt / 8;
    n->length += x;
    n->number = (unsigned char *) realloc(n->number, (n->length) * sizeof(n->number));
    memmove(n->number + x, n->number, sizeof(n->number) * x);
    for (int i = 0; i < x; i++) n->number[i] = 0;
}


//ok
void big_int_bin_shft_r2(big_int *n, int cnt) {
    for (int i = 0; i < cnt % 8; i++) big_int_bin_shft_r(n);
    unsigned int x = cnt / 8;
    if (x >= n->length) {
        big_int_free(n);
        n = big_int_get("0");
    } else {
        if (x) {
            n->number = (unsigned char *) realloc(n->number, (n->length) * sizeof(n->number));
            memmove(n->number, n->number + x, sizeof(n->number) * (n->length - x));
        }
    }
    big_int_dlz(n);
}

//ok
big_int *big_int_disj(big_int *n1, big_int *n2) {
    int mx = (int) fmax(n1->length, n2->length);
    big_int *n3 = (big_int *) malloc(sizeof(big_int));
    n3->length = mx;
    n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number));
    for (int i = 0; i < mx; i++) { n3->number[i] = (n2->number[i]) | (n1->number[i]); }
    n3->sign = '+';
    big_int_dlz(n3);
    return n3;
}


//ok
void big_int_dlz(big_int *n) {
    int i = n->length - 1;
    while ((i > 0) * (n->number[i] == 0)) {
        i--;
    }
    n->length = i + 1;

    n->number = (unsigned char *) realloc(n->number, (n->length) * sizeof(n->number));
}


//ok
void big_int_free(big_int *n) {
    free(n->number);
    n->number = NULL;
    free(n);
    n = NULL;
}


//ok
void big_int_swap(big_int *n1, big_int *n2) {
    char sgn = n1->sign;
    unsigned int len = n1->length;
    unsigned char *num = (unsigned char *) calloc(n1->length, sizeof(n1->number));
    memcpy(num, n1->number, n1->length);
    n1->sign = n2->sign;
    n1->length = n2->length;
    memcpy(n1->number, n2->number, n2->length);
    n2->sign = sgn;
    n2->length = len;
    memcpy(n2->number, num, len);
    //*(n2->number)=*num;
    free(num);
}


//ok
int big_int_geq(big_int *n1, big_int *n2)//n1<=n2
{
    if (n1->sign != n2->sign) return (n1->sign == '+') ? 0 : 1;
    else {
        if (n1->length < n2->length) return 1 * (n1->sign == '+');
        if (n1->length > n2->length) return 0 + (n1->sign != '+');
        for (int i = n1->length; i > -1; i--) {
            if (n1->number[i] < n2->number[i]) return 1 * (n1->sign == '+');
            if (n1->number[i] > n2->number[i]) return 0 + (n1->sign != '+');
        }
        return 1;
    }
}


//ok?
big_int *big_int_add(big_int *n1, big_int *n2) {
    if (n1->sign != n2->sign) {
        int t = n1->sign == '+';
        if (t) {
            n2->sign = '+';
            big_int *n4 = (big_int_sub(n1, n2));
            n2->sign = '-';
            big_int_dlz(n4);
            return n4;
        } else {
            n1->sign = '+';
            big_int *n4 = (big_int_sub(n2, n1));
            n1->sign = '-';
            big_int_dlz(n4);
            return n4;
        }
    }
    int mx = (int) fmax(n1->length, n2->length), carry = 0, x;
    big_int *n3 = (big_int *) malloc(sizeof(big_int));
    n3->length = mx + 1;
    n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number));
    int t = n1->length <= n2->length;
    if (t) big_int_swap(n1, n2);
    for (int i = 0; i < mx; i++) {
        if (i < n2->length) x = n1->number[i] + n2->number[i] + carry;//sizeof(unsigned char)=1 sizeof(int)=4
        else x = n1->number[i] + carry;
        n3->number[i] = x & 0xFF; // 0xFF 1111 1111
        carry = x >> 8;
    }
    n3->number[mx] = carry;
    n3->sign = n1->sign;
    big_int_dlz(n3);
    return n3;
}


//ok
int big_int_leq(big_int *n1, big_int *n2) //n1<=n2
{
    if (n1->length < n2->length) return 1;
    if (n1->length > n2->length) return 0;
    for (int i = n1->length - 1; i > -1; i--) {
        if (n1->number[i] < n2->number[i]) return 1;
        if (n1->number[i] > n2->number[i]) return 0;
    }
    return 1;
}


//ok?
big_int *big_int_sub(big_int *n1, big_int *n2) {
    if (n1->sign != n2->sign) {
        if (n1->sign == '+') {
            n2->sign = '+';
            big_int *n4 = (big_int_add(n1, n2));
            big_int_dlz(n4);
            n2->sign = '-';
            return n4;
        } else {
            n2->sign = '-';
            big_int *n4 = (big_int_add(n2, n1));
            big_int_dlz(n4);
            n2->sign = '+';
            return n4;
        }
    }
    int mx = (int) fmax(n1->length, n2->length), carry = 0;
    big_int *n3 = (big_int *) malloc(sizeof(big_int));
    n3->length = mx;
    n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number));
    int t = big_int_leq(n1, n2);//n1<=n2
    if (t)big_int_swap(n1, n2);

    for (int i = 0; i < mx; i++) {//n2<=n1
        if (carry) if ((n1->number[i] == 0) || (n1->number[i] == n2->number[i])) n3->number[i] += 0xFF;

        if (i < n2->length) {
            if (n1->number[i] >= n2->number[i]) {
                n3->number[i] += n1->number[i] - n2->number[i] - carry;
                carry = 0;
            }
            if (n1->number[i] < n2->number[i]) {
                if(!carry){
                n3->number[i] = 0x100 + n1->number[i] - n2->number[i];
                carry = 1;}
                else{
                    n3->number[i]+=n1->number[i] - n2->number[i];
                }
            }
        } else {
            n3->number[i] = n1->number[i] - carry;
            if (n1->number[i]) carry = 0;
        }
    }
    if (t) big_int_swap(n1, n2);
    if (n1->sign == '+') {
        if (t)n3->sign = '-';
        else n3->sign = '+';
    } else {
        if (t)n3->sign = '+';
        else n3->sign = '-';
    }
    big_int_dlz(n3);
    return n3;
}


//ok
void big_int_add2(big_int *n1, big_int *n2) {
    if (n1->sign != n2->sign) {
        int t = n1->sign == '+';
        if (t) {
            n2->sign = '+';
            big_int *n4 = (big_int_sub(n1, n2));
            n2->sign = '-';
            n1->sign = n4->sign;
            n1->length = n4->length;
            memcpy(n1->number, n4->number, n4->length);
            big_int_free(n4);
            big_int_dlz(n1);
        } else {
            n1->sign = '+';
            big_int *n4 = (big_int_sub(n2, n1));
            n1->sign = '-';
            n1->sign = n4->sign;
            n1->length = n4->length;
            memcpy(n1->number, n4->number, n4->length);
            big_int_free(n4);
            big_int_dlz(n1);
        }
    } else {
//        printf("//////////////start of add2//////////////////\n");

        int mx = (int) fmax(n1->length, n2->length), carry = 0, x;
        big_int *n3 = (big_int *) malloc(sizeof(big_int));
        n3->length = mx + 1;
//        printf("len n1=%d\n",n1->length);
//        printf("len n2=%d\n",n2->length);
//        printf("n1=");
//        big_int_print(n1);
//        printf("n2=");
//        big_int_print(n2);
        n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number));
//        printf("cycle for\n");
        int t = n1->length <= n2->length;
//        printf("n1=");
//        big_int_print(n1);
//        printf("n2=");
//        big_int_print(n2);
        if (t) big_int_swap(n1, n2);
//        printf("n1=");
//        big_int_print(n1);
//        printf("n2=");
//        big_int_print(n2);
//        printf("----------------\n");
        for (int i = 0; i < mx; i++) {
//            printf("carry0[%d]=%d\n",i,carry);
//            printf("n1=");
//            big_int_print(n1);
//            printf("n2=");
//            big_int_print(n2);
//            printf("n3_0[%d]=",i);
//            big_int_print(n3);
//            printf("n1[%d]=%d\n",i,n1->number[i]);
//            printf("n2[%d]=%d\n",i,n2->number[i]);
            if (i < n2->length) x = n1->number[i] + n2->number[i] + carry;//sizeof(unsigned char)=1 sizeof(int)=4
            else x = n1->number[i] + carry;
//            printf("n3_1[%d]=",i);
//            big_int_print(n3);
            n3->number[i] = x & 0xFF; // 0xFF 1111 1111
//            printf("byte[%d] = %d = %d\n",i,x&0xFF,n3->number[i]);
            carry = x >> 8;
//            printf("n3_2[%d]=",i);
//            big_int_print(n3);
//            printf("carry1[%d]=%d\n",i,carry);
//            printf("----------------\n");
        }
        if (t) big_int_swap(n1, n2);

//        printf("n3_1=");
//        big_int_print(n3);
        n3->number[mx] = carry;
        n3->sign = n1->sign;
        big_int_dlz(n3);
//        printf("n3_2=");
//        big_int_print(n3);
        n1->length = n3->length;
        memcpy(n1->number, n3->number, n3->length);
        big_int_free(n3);
//        printf("n3_3=");

//        big_int_print(n1);
//        printf("//////////////end of add2//////////////////\n");
    }
}


//ok
void big_int_sub2(big_int *n1, big_int *n2) {
    if (n1->sign != n2->sign) {
        if (n1->sign == '+') {
            n2->sign = '+';
            big_int *n4 = (big_int_add(n1, n2));
            n2->sign = '-';
            n1->sign = n4->sign;
            n1->length = n4->length;
            memcpy(n1->number, n4->number, n4->length);
            big_int_free(n4);
            big_int_dlz(n1);
        } else {
            n2->sign = '-';
            big_int *n4 = (big_int_add(n2, n1));
            n2->sign = '+';
            n1->sign = n4->sign;
            n1->length = n4->length;
            memcpy(n1->number, n4->number, n4->length);
            big_int_free(n4);
            big_int_dlz(n1);
        }
    } else {
//        printf("//////////start of sub2/////////////////\n");
        int mx = (int) fmax(n1->length, n2->length), carry = 0;
//        printf("n1_0=");
//        big_int_print(n1);
//        printf("n2_0=");
//        big_int_print(n2);
        big_int *n3 = (big_int *) malloc(sizeof(big_int));

        n3->length = mx;
        n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number));
        int t = big_int_leq(n1, n2);//n1<=n2

        if (t)big_int_swap(n1, n2);
//        printf("n1_1=");
//        big_int_print(n1);
//        printf("n2_1=");
//        big_int_print(n2);
//        printf("res0=");
//        big_int_print(n3);
        for (int i = 0; i < mx; i++) {//n2<=n1
//            printf("carry0[%d]=%d\n",i,carry);
            if (carry) if ((n1->number[i] == 0) || (n1->number[i] == n2->number[i])) n3->number[i] += 0xFF;
            if (i < n2->length) {
                if (n1->number[i] > n2->number[i]) {
                    n3->number[i] += n1->number[i] - n2->number[i] - carry;
//                    printf("res0[%d]=",i);big_int_print(n3);
                    carry = 0;
                }
                if (n1->number[i] < n2->number[i]) {
                    n3->number[i] = 0x100 + n1->number[i] - n2->number[i];
//                    printf("res1[%d]=",i);big_int_print(n3);
                    carry = 1;
                }
            } else {
                n3->number[i] = n1->number[i] - carry;
//                printf("res2[%d]=",i);big_int_print(n3);
                if (n1->number[i]) carry = 0;
            }
//            printf("carry1[%d]=%d\n",i,carry);
//            printf("res[%d]=",i);big_int_print(n3);
//            printf("----------------\n");
        }
//        printf("res1=");
//        big_int_print(n3);
//        printf("n1_2=");
//        big_int_print(n1);
//        printf("n2_2=");
//        big_int_print(n2);
        if (t) big_int_swap(n1, n2);
//        printf("n1_3=");
//        big_int_print(n1);
//        printf("n2_3=");
//        big_int_print(n2);
        if (n1->sign == '+') {
            if (t)n3->sign = '-';
            else n3->sign = '+';
        } else {
            if (t)n3->sign = '+';
            else n3->sign = '-';
        }
//        printf("n1_4=");
//        big_int_print(n1);
//        printf("n2_4=");
//        big_int_print(n2);
        big_int_dlz(n3);
        n1->sign = n3->sign;
        n1->length = n3->length;
        memcpy(n1->number, n3->number, n3->length);
        big_int_free(n3);

//        printf("n1_5=");
//        big_int_print(n1);
//        printf("n2_5=");
//        big_int_print(n2);
//        printf("//////////end of sub2/////////////////\n");
    }
}


big_int *big_int_euclid_binary(big_int *x, big_int *y) {
    big_int *zero = big_int_get("0");
    int k, n = 0;
    char c1 = x->sign, c2 = y->sign;
    x->sign = '+';
    y->sign = '+';
    big_int *a = big_int_disj(x, y);//a = x | y;
    while ((a->number[0] & 1) != 1) {
        big_int_bin_shft_r(a);
        big_int_bin_shft_r(x);
        big_int_bin_shft_r(y);
        n++;
    }
    big_int_dlz(x);
    big_int_dlz(y);
    while ((!big_int_leq(x, zero)) && (!big_int_leq(y, zero))) {
        if ((x->number[0] & 1) == 1) {
            while ((y->number[0] & 1) == 0) big_int_bin_shft_r(y);
        } else {
            while ((x->number[0] & 1) == 0) big_int_bin_shft_r(x);
        }
        big_int_dlz(x);
        big_int_dlz(y);
        if (big_int_leq(y, x)) {
            big_int_sub2(x, y);
        } else {
            big_int_sub2(y, x);
        }
    }
    x->sign = '+';
    y->sign = '+';
    big_int_dlz(x);
    big_int_dlz(y);
    big_int *n3 = big_int_add(x, y);
    big_int_bin_shft_l2(n3, n);
    x->sign = c1;
    y->sign = c2;
    big_int_free(a);
    big_int_free(zero);
    return n3;
}


big_int *big_int_copy(big_int *x) {
    big_int *n3 = (big_int *) malloc(sizeof(big_int));
    n3->sign = x->sign;
    n3->length = x->length;
    n3->number = (unsigned char *) calloc(n3->length, sizeof(x->number));
    memcpy(n3->number, x->number, (x->length));
    return n3;
}

int check(big_int *n) {
    for (int i = 0; i < n->length; i++)
        if (n->number[i] != 240) return 1;
    return 0;
}

big_int *big_int_mult(big_int *x, big_int *y) {
    int mx = (int) fmax(x->length, y->length);
    big_int *zero = big_int_get("0");
    big_int *n3 = (big_int *) malloc(sizeof(big_int));
    n3->length = mx + 1;
    n3->sign = '+';
    big_int *x0 = big_int_copy(x);
    big_int *y0 = big_int_copy(y);
    n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number));
    if (x->length >= y->length) {
        while (!big_int_leq(y, zero)) {
            big_int_dlz(n3);
            if (y->number[0] & 1) big_int_add2(n3, x);
            big_int_bin_shft_r(y);
            big_int_bin_shft_l(x);
        }
    } else {
        while (!big_int_leq(x, zero)) {
            big_int_dlz(n3);
            if (x->number[0] & 1) big_int_add2(n3, y);
            big_int_bin_shft_r(x);
            big_int_bin_shft_l(y);
        }
    }
    big_int_swap(y, x0);
    big_int_swap(x, y0);
    big_int_swap(x, y);
    big_int_free(x0);
    big_int_free(y0);
    big_int_free(zero);
    n3->sign = (x->sign == y->sign) ? '+' : '-';
    big_int_dlz(n3);
    return n3;
}

void big_int_div(big_int *n1, big_int *n2, big_int *res1, big_int *rmdr) {
    big_int *one = big_int_get("1");
    int mx = (int) fmax(n1->length, n2->length), k;
    big_int *n3 = (big_int *) malloc(sizeof(big_int));
    n3->length = mx + 1;
    n3->sign = '+';
    big_int *x0 = big_int_copy(n1);
    big_int *y0 = big_int_copy(n2);
    x0->sign = '+';
    y0->sign = '+';
    n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number));
    while (big_int_leq(y0, x0)) {
        big_int_sub2(x0, y0);
        big_int_add2(n3, one);
    }
    big_int_free(one);
    big_int_free(x0);
    big_int_free(y0);
    n3->sign = (n1->sign == n2->sign) ? '+' : '-';
    big_int_dlz(n3);
    res1->sign = n3->sign;
    res1->length = n3->length;
    memcpy(res1->number, n3->number, n3->length);
    big_int_free(n3);
    big_int *n5 = big_int_mult(n2, res1);
    big_int *n4 = big_int_sub(n1, n5);
    big_int_free(n5);
    rmdr->sign = '+';
    rmdr->length = n4->length;
    memcpy(rmdr->number, n4->number, n4->length);
    big_int_free(n4);
}

big_int *big_int_rl_mod_pow(big_int *x, big_int *n, big_int *m) {
    big_int *ans=big_int_get("1");//int ans=1
    big_int *zero=big_int_get("0");
    big_int *x0=big_int_copy(x);
    big_int *n0=big_int_copy(n);
    big_int *m0=big_int_copy(m);
    while(!big_int_leq(n0,zero)){//while(n)
        if((n0->number[0])&1){//if n&1
            big_int *xmodm=big_int_get("0");
            big_int *trash=big_int_get("0");
            big_int_div(x0,m0,trash,xmodm);
            big_int *n4=big_int_mult(ans,xmodm);
            big_int_swap(ans,n4);
            big_int_free(n4);
            big_int_free(xmodm);
            big_int_free(trash);
        }
        big_int *cp_x0= big_int_copy(x0);
        big_int *sq=big_int_mult(x0,cp_x0);
        big_int *sqmodm1=big_int_get("0");
        big_int *trash1=big_int_get("0");
        big_int_div(sq,m0,trash1,sqmodm1);
        big_int_swap(x0,sqmodm1);
        big_int_bin_shft_r(n0);//n>>=1
        big_int_free(cp_x0);
        big_int_free(sq);
        big_int_free(sqmodm1);
        big_int_free(trash1);
    }
    big_int *fin=big_int_get("0");
    big_int_div(ans,m0,zero,fin);
    big_int_free(zero);
    big_int_free(x0);
    big_int_free(m0);
    big_int_free(n0);
    big_int_free(ans);
    return fin;
}

int big_int_equal(big_int *n1, big_int *n2) {
    if (n1->length != n2->length) {
        return 0;
    }
    for (int i = 0; i < n1->length; i++)
        if ((n1->number[i]) != (n2->number[i])) return 0;
    return 1;
}

int tst_add() {
    FILE *file = fopen("numbers.txt", "r");

    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);


    for (long i = 0; i < 50*50*50; i++) {

        fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
//        printf("n1=");
        big_int *n1 = big_int_get(binary);
//        big_int_print(n1);

        fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
//        printf("n2=");
        big_int *n2 = big_int_get(binary);
//        big_int_print(n2);

        fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
//        printf("n3=");
        big_int *n3 = big_int_get(binary);
//        big_int_print(n3);

        fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans=big_int_get(binary);
//        printf("ans(n1**n2)%%n3=");
//        big_int_print(ans);


        big_int *n4 = big_int_rl_mod_pow(n1, n2,n3);
//        printf("my func n1+n2=");
//        big_int_print(n4);

//
        if ((!big_int_equal(ans, n4))) {//||(!big_int_equal(my_rm,rm_ans))
            printf("////////////////////////IMPOSTER i=%li//////////////\n", i);
            printf("n1=");
            big_int_print(n1);
            printf("n2=");
            big_int_print(n2);
            printf("n3=");
            big_int_print(n3);
            printf("ans(n1**n2)%%n3=");
            big_int_print(ans);
            printf("my ans(n1**n2)%%n3=");
            big_int_print(n4);
            break;
        }
        big_int_free(n1);
        big_int_free(n2);
        big_int_free(n3);
        big_int_free(n4);
        big_int_free(ans);
//        big_int_free(my_rm);
        if(i%10==0)printf("i=%li\n",i);
//        printf("---------------\n");
    }

    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    return 0;
}