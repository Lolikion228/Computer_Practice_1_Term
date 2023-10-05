//
// Created by lolikion on 02.10.23.
//
#include <string.h>
#include "big_int.h"
#include <stdlib.h>
#include "stdio.h"
#include <math.h>


//ok
big_int *big_int_get(const char *bin_number) {//'-'=45 '+'=43
    big_int *n1 = (big_int *) malloc(sizeof(big_int));
    int len1 = strlen(bin_number);
    n1->length = (len1 + 6) >> 3;
    n1->number = (unsigned int *) calloc(n1->length, sizeof(n1->number));
    n1->sign = bin_number[0];
    for (int i = 0; i < len1 - 1; i++)
        n1->number[i >> 3] += (bin_number[len1 - i - 1] - '0') << (i & 7);
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


//???
void big_int_bin_shft_lr(big_int *n) {
    for (int i = 0; i < n->length; i++) {
        n->number[i] >>= 1;
        if (i != ((n->length) - 1)) n->number[i] += (((n->number[i + 1])) & 1) << 7;
    }
    big_int_dlz(n);
}


//???
void big_int_bin_shft_rl(big_int *n) {
    int t = (n->number[(n->length) - 1]) & 128;
    if (t) {
        n->length++;
        n->number = (unsigned int *) realloc(n->number, n->length * sizeof(n->number));
    }
    for (int i = n->length - 1; i > -1; i--) {
        n->number[i] <<= 1;
        if (i) n->number[i] += (n->number[i - 1] & 128) != 0;
    }
    big_int_dlz(n);
}


big_int* big_int_disj(big_int *n1,big_int *n2){
    int mx = (int) fmax(n1->length, n2->length);
    big_int *n3 = (big_int *) malloc(sizeof(big_int));
    n3->length = mx;
    n3->number = (unsigned int *) calloc(n3->length, sizeof(n3->number));
    for (int i = 0; i < mx; i++) {n3->number[i]=(n2->number[i])|(n1->number[i]);}
    n3->sign='+';
    return n3;
}


//ok
void big_int_dlz(big_int *n) {
    int i = n->length - 1;
    while ((i > 0) * (n->number[i] == 0)) {
        i--;
    }
    n->number = (unsigned int *) realloc(n->number, (n->length - i) * sizeof(n->number));
    n->length = i + 1;
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
    big_int k = *n2;
    *n2 = *n1;
    *n1 = k;
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
        if (t) { n2->sign = '+'; big_int*n4 = (big_int_sub(n1, n2)); n2->sign='-'; return n4;}
        else { n1->sign = '+'; big_int*n4 = (big_int_sub(n2, n1)); n1->sign='-'; return n4;}
    }
    int mx = (int) fmax(n1->length, n2->length), carry = 0;
    big_int *n3 = (big_int *) malloc(sizeof(big_int));
    n3->length = mx + 1;
    n3->number = (unsigned int *) calloc(n3->length, sizeof(n3->number));
    for (int i = 0; i < mx; i++) {
        int x = n1->number[i] + n2->number[i] + carry;//sizeof(unsigned char)=1 sizeof(int)=4
        n3->number[i] = x & 0xFF; // 0xFF 1111 1111
        carry = x >> 8;
    }
    n3->number[mx] = carry;
    n3->sign=n1->sign;
    big_int_dlz(n3);
    return n3;
}


//ok
int big_int_leq(big_int *n1, big_int *n2) //n1<=n2
{
    if (n1->length < n2->length) return 1;
    if (n1->length > n2->length) return 0;
    for (int i = n1->length; i > -1; i--) {
        if (n1->number[i] < n2->number[i]) return 1;
        if (n1->number[i] > n2->number[i]) return 0;
    }
    return 1;
}


//ok?
big_int *big_int_sub(big_int *n1, big_int *n2) {
    if (n1->sign != n2->sign){
        if(n1->sign == '+'){
            n2->sign='+';
            big_int*n4=(big_int_add(n1, n2));
            n2->sign='-';
            return n4;
        }
        else{
            n2->sign='-';
            big_int*n4=(big_int_add(n2, n1));
            n2->sign='+';
            return n4;
        }
    }
    int mx = (int) fmax(n1->length, n2->length), carry = 0;
    big_int *n3 = (big_int *) malloc(sizeof(big_int));
    n3->length = mx;
    n3->number = (unsigned int *) calloc(n3->length, sizeof(n3->number));
    int t = big_int_leq(n1, n2);//n1<=n2
    if (t)big_int_swap(n1, n2);

    for (int i = 0; i < mx; i++) {//n2<=n1
        if (carry) if ((n1->number[i] == 0) || (n1->number[i] == n2->number[i])) n3->number[i] += 0xFF;
        if (i < n2->length) {
            if (n1->number[i] > n2->number[i]) {
                n3->number[i] += n1->number[i] - n2->number[i] - carry;
                carry = 0;
            }
            if (n1->number[i] < n2->number[i]) {
                n3->number[i] = 0x100 + n1->number[i] - n2->number[i];
                carry = 1;
            }
        } else {
            n3->number[i] = n1->number[i] - carry;
            carry = 0;
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


/*
void big_int_sub2(big_int *n1, big_int *n2) {
    int mx = (int) fmax(n1->length, n2->length), carry = 0;


    int t = big_int_leq(n1, n2);//n1<=n2
    if (t)big_int_swap(n1, n2);

    for (int i = 0; i < mx; i++) {//n2<=n1
        if (carry) if ((n1->number[i] == 0) || (n1->number[i] == n2->number[i])) n1->number[i] += 255;
        if (i < n2->length) {
            if (n1->number[i] > n2->number[i]) {
                n1->number[i] = n1->number[i] - n2->number[i] - carry;
                carry = 0;

            }
            if (n1->number[i] < n2->number[i]) {
                n1->number[i] = 256 + n1->number[i] - n2->number[i];
                carry = 1;
            }
        } else {
            n1->number[i] = n1->number[i] - carry;
            carry = 0;
        }
    }
    if (t) big_int_swap(n1, n2);


}
*/

/*
void big_int_add2(big_int *n1, big_int *n2) {
    int mx = (int) fmax(n1->length, n2->length), carry = 0;
    n1->length=mx+1;
    n1->number = (unsigned int *) realloc(n1->number, (n1->length) * sizeof(n1->number));
    if (n1->sign != n2->sign) {
        if (n1->sign == '+') {
            big_int *n3 = big_int_sub(n1, n2, 1);
            big_int_free(n1);
            *n1 = *n3;
            n1=n3;
            free(n3);
        } else {
            big_int *n3 = big_int_sub(n2, n1, 1);
            big_int_free(n1);
            *n1 = *n3;
            n1=n3;
            free(n3);
        }
    } else {

        for (int i = 0; i < mx; i++) {
            int x = n1->number[i] + n2->number[i] + carry;
            n1->number[i] = x % 256;
            carry = x >> 8;
        }
        if(carry) n1->number[n1->length-1]+=1;
    }
    big_int_dlz(n1);
}
*/

