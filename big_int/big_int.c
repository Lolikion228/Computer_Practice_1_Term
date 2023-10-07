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
    int len1 = strlen(bin_number), t = 0;
    if (bin_number[0] == '-') {
        t = 1;
        n1->sign = '-';
    } else n1->sign = '+';
    n1->length = (len1 + 7 - t) >> 3;
    n1->number = (unsigned int *) calloc(n1->length, sizeof(n1->number));
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
        n->number = (unsigned int *) realloc(n->number, n->length * sizeof(n->number));
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
    n->number = (unsigned int *) realloc(n->number, (n->length) * sizeof(n->number));
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
            n->number = (unsigned int *) realloc(n->number, (n->length) * sizeof(n->number));
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
    n3->number = (unsigned int *) calloc(n3->length, sizeof(n3->number));
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

    n->number = (unsigned int *) realloc(n->number, (n->length) * sizeof(n->number));
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
    n3->sign = n1->sign;
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


//ok
void big_int_add2(big_int *n1, big_int *n2) {
    if (n1->sign != n2->sign) {
        int t = n1->sign == '+';
        if (t) {
            n2->sign = '+';
            big_int *n4 = (big_int_sub(n1, n2));
            n2->sign = '-';
            *n1 = *n4;
            big_int_dlz(n1);
        } else {
            n1->sign = '+';
            big_int *n4 = (big_int_sub(n2, n1));
            n1->sign = '-';
            *n1 = *n4;
            big_int_dlz(n1);
        }
    } else {
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
        n3->sign = n1->sign;
        //big_int_dlz(n3);
        *n1 = *n3;
        big_int_dlz(n1);
    }
}


//ok
void big_int_sub2(big_int *n1, big_int *n2) {
    if (n1->sign != n2->sign) {
        if (n1->sign == '+') {
            n2->sign = '+';
            big_int *n4 = (big_int_add(n1, n2));
            n2->sign = '-';
            *n1 = *n4;
            big_int_dlz(n1);
        } else {
            n2->sign = '-';
            big_int *n4 = (big_int_add(n2, n1));
            n2->sign = '+';
            *n1 = *n4;
            big_int_dlz(n1);
        }
    } else {

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
        *n1 = *n3;

    }
}


big_int *big_int_euclid_binary(big_int *x, big_int *y) {

    big_int *zero = big_int_get("0");
//    if( (*x->number==*zero->number) || (*y->number==*zero->number)) return one;
    int k, n = 0;
    char c1 = x->sign, c2 = y->sign;
    x->sign = '+';
    y->sign = '+';
//
    big_int *a = big_int_disj(x, y);//a = x | y;
    while ((a->number[0] & 1) != 1) {
        big_int_bin_shft_r(a);
        big_int_bin_shft_r(x);
        big_int_bin_shft_r(y);
        n++;
    }
    //printf("n=%d\n",n);
//    printf("x0=");
//    big_int_print(x);
//    printf("y0=");
//    big_int_print(y);
//    printf("---------\n");
    big_int_dlz(x);
    big_int_dlz(y);
    while ((!big_int_leq(x, zero)) && (!big_int_leq(y, zero))) {
        if ((x->number[0] & 1) == 1) {
            while ((y->number[0] & 1) == 0) big_int_bin_shft_r(y);
        } else {
            while ((x->number[0] & 1) == 0) big_int_bin_shft_r(x);
        }
//        printf("x1=");big_int_print(x);
//        printf("y1=");big_int_print(y);
//        printf("sub:\n");
////        scanf("%d",&k);
//        printf("x2=");big_int_print(x);
//        printf("y2=");big_int_print(y);
        big_int_dlz(x);
        big_int_dlz(y);
        if (big_int_leq(y, x)) {
            //printf("case y<=x\n");
            big_int_sub2(x, y);
        } else {
            //printf("case x<y\n");
            big_int_sub2(y, x);
        }
//        printf("x3=");big_int_print(x);
//        printf("y3=");big_int_print(y);
//        printf("---------\n");
//        scanf("%d",&k);
    }
    x->sign = '+';
    y->sign = '+';
    //printf("x=");big_int_print(x);
    //printf("y=");big_int_print(y);
    //printf("x+y=");
    big_int_dlz(x);
    big_int_dlz(y);
    big_int *n3 = big_int_add(x, y);
    //big_int_print(n3);
    big_int_bin_shft_l2(n3, n);
    //printf("after shft=");big_int_print(n3);
    x->sign = c1;
    y->sign = c2;
    return n3;
}


big_int *big_int_copy(big_int*x){

    big_int *n3 = (big_int *) malloc(sizeof(big_int));
    n3->sign=x->sign;
    n3->length=x->length;
    n3->number = (unsigned int *) calloc(n3->length, sizeof(x->number));
    memccpy(n3->number,x->number,'z',(sizeof(unsigned int))*(x->length));
    return n3;
}

big_int *big_int_mult(big_int *x, big_int *y) {

    int mx = (int) fmax(x->length, y->length),k;
    big_int *zero = big_int_get("0");
    big_int *n3 = (big_int *) malloc(sizeof(big_int));
    n3->length = mx + 1;
    n3->sign='+';
    big_int *x0= big_int_copy(x);
    big_int *y0= big_int_copy(y);
//    big_int_print(y0);
//    big_int_print(x0);
    n3->number = (unsigned int *) calloc(n3->length, sizeof(n3->number));
    if (x->length >= y->length) {
//        printf("case1 lenx>=leny\n");
        while(!big_int_leq(y,zero)){
//            printf("n3_0=");big_int_print(n3);
//            printf("x0="); big_int_print(x);
//            printf("y0="); big_int_print(y);
            if(y->number[0]&1) big_int_add2(n3,x);
            big_int_bin_shft_r(y);
            big_int_bin_shft_l(x);
//            printf("in if1\n");big_int_print(y0);
//            big_int_print(x0);
//            printf("n3=");big_int_print(n3);
//            printf("x="); big_int_print(x);
//            printf("y="); big_int_print(y);
//            scanf("%d",&k);
//            printf("---------------\n");
        }
    }
    else{
//        printf("case2 lenx<leny\n");
        while(!big_int_leq(x,zero)){
//            printf("n3_0=");big_int_print(n3);
//            printf("x0="); big_int_print(x);
//            printf("y0="); big_int_print(y);
            if(x->number[0]&1) big_int_add2(n3,y);
            big_int_bin_shft_r(x);
            big_int_bin_shft_l(y);
//            printf("in if2\n");big_int_print(y0);
//            big_int_print(x0);
//            printf("n3=");big_int_print(n3);
//            printf("x="); big_int_print(x);
//            printf("y="); big_int_print(y);
//            scanf("%d",&k);
//            printf("---------------\n");
        }
    }
//    printf("in end\n");
//    big_int_print(y0);
//    big_int_print(x0);
    big_int_swap(y,x0);
    big_int_swap(x,y0);
    big_int_swap(x,y);
    big_int_free(x0);
    big_int_free(y0);
    n3->sign=(x->sign==y->sign)? '+' : '-';
    return n3;
}

