//
// Created by lolikion on 02.10.23.
//
#include <string.h>
#include "big_int.h"
#include <stdlib.h>
#include "stdio.h"
#include <math.h>


#define MAX_BINARY_LENGTH 41000


big_int *big_int_get(const char *bin_number) {
    big_int *n1 = (big_int *) malloc(sizeof(big_int));
    int len1 = strlen(bin_number), t = 0;
    if (bin_number[0] == '-') {
        t = 1;
        n1->sign = '-';
    } else n1->sign = '+';
    n1->length = (len1 + 7 - t) >> 3;
    n1->number = (unsigned char *) calloc(n1->length, sizeof(n1->number[0]));
    if (n1->number == NULL) {
        printf("memory error in big_int_get\n");
        return NULL;
    }
    int i;
    for (i = 0; i < len1 - t; i++) {
        n1->number[i / 8] += (bin_number[len1 - i - 1] - '0') << (i % 8);
    }
    big_int_dlz(n1);
    return n1;
}


int big_int_equal_sgn(big_int *n1, big_int *n2) {
    if (n1->sign != n2->sign) {
        return 0;
    }
    if (n1->length != n2->length) {
        return 0;
    }
    for (int i = 0; i < n1->length; i++)
        if ((n1->number[i]) != (n2->number[i])) return 0;
    return 1;
}


int big_int_equal(big_int *n1, big_int *n2) {
    if (n1->length != n2->length) {
        return 0;
    }
    for (int i = 0; i < n1->length; i++)
        if ((n1->number[i]) != (n2->number[i])) return 0;
    return 1;
}


void big_int_dlz(big_int *n) {
    int i = (n->length) - 1;
    while (((i > 0) * (n->number[i] == 0)) != 0) {
        i--;
    }
    if ((n->length) != i + 1) {
        n->length = i + 1;
        n->number = (unsigned char *) realloc(n->number, n->length);
        if (n->number == NULL) {
            printf("memory error in big_int_dlz\n");
        }
    }
}


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


void big_int_free(big_int *n) {
//    if(n->number==NULL)printf("LOLIK\n");
//    if(n==NULL)printf("LOLIK2\n");
//    printf("here1\n");

    free(n->number);
    free(n);


//    printf("here2\n");

}


void big_int_swap(big_int *n1, big_int *n2) {
    char sgn = n1->sign;
    unsigned int len = n1->length;
    unsigned char *num = (unsigned char *) calloc(n1->length, sizeof(n1->number[0]));
    if (num == NULL) {
        printf("memory error in big_int_swap\n");
    }
    memmove(num, n1->number, n1->length);
    n1->sign = n2->sign;
    n1->length = n2->length;
    memmove(n1->number, n2->number, n2->length);
    n2->sign = sgn;
    n2->length = len;
    memmove(n2->number, num, len);
    free(num);
}


big_int *big_int_copy(big_int *x) {
    big_int *n3 = (big_int *) malloc(sizeof(big_int));
    n3->sign = x->sign;
    n3->length = x->length;
    n3->number = (unsigned char *) calloc(n3->length, sizeof(x->number[0]));
    if (n3->number == NULL) {
        printf("memory error in big_int_copy\n");
        return NULL;
    }
    memmove(n3->number, x->number, x->length * sizeof(x->number[0]));
    return n3;
}


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


big_int *big_int_disj(big_int *n1, big_int *n2) {
    int min = (int) fmin(n1->length, n2->length);
    big_int *n3 = (big_int *) malloc(sizeof(big_int));
    n3->length = min;
    n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number[0]));
    if (n3->number == NULL) {
        printf("memory error in big_int_disj\n");
        return NULL;
    }
    for (int i = 0; i < min; i++) {
        n3->number[i] = (n2->number[i]) | (n1->number[i]);
    }
    n3->sign = '+';
    big_int_dlz(n3);
    return n3;
}


void big_int_bin_shft_r(big_int *n) {
    for (int i = 0; i < n->length; i++) {
        n->number[i] >>= 1;
        if (i != ((n->length) - 1)) n->number[i] += (((n->number[i + 1])) & 1) << 7;
    }
    big_int_dlz(n);
}


void big_int_bin_shft_l(big_int *n) {
    int t = (n->number[(n->length) - 1]) & 128;
    if (t) {
        n->length++;
        n->number = (unsigned char *) realloc(n->number, n->length);
        if (n->number == NULL) printf("memory error in big_int_bin_shft_l\n");
        memset(n->number + (n->length) - 1, 0, 1);
    }
    for (int i = n->length - 1; i > -1; i--) {
        n->number[i] <<= 1;
        if (i) n->number[i] += (n->number[i - 1] & 128) != 0;
    }
}


void big_int_bin_shft_r2(big_int *n, int cnt) {
    for (int i = 0; i < cnt % 8; i++) big_int_bin_shft_r(n);
    unsigned int x = cnt / 8;
    if (x >= n->length) {
        big_int_free(n);
        n = big_int_get("0");
    } else {
        if (x) {
            n->length -= x;
            memmove(n->number, n->number + x, sizeof(n->number[0]) * (n->length));
            n->number = (unsigned char *) realloc(n->number, (n->length) * sizeof(n->number[0]));
            if (n->number == NULL) printf("memory error in big_int_bin_shft_r2\n");
        }
    }
    big_int_dlz(n);
}


void big_int_bin_shft_l2(big_int *n, int cnt) {
    for (int i = 0; i < cnt % 8; i++) big_int_bin_shft_l(n);
    unsigned int x = cnt / 8;
    n->length += x;
    n->number = (unsigned char *) realloc(n->number, (n->length) * sizeof(n->number[0]));
    if (n->number == NULL) printf("memory error in big_int_bin_shft_l2\n");
    memmove(n->number + x, n->number, n->length - x);
    for (int i = 0; i < x; i++) n->number[i] = 0;
}


void big_int_set_bit(big_int *n, long long num, int x) {
    if ((num / 8) >= (n->length)) {
        n->number = (unsigned char *) realloc(n->number, (num / 8 + 1) * sizeof(n->number[0]));
        if (n->number == NULL) printf("memory error in big_int_set_bit\n");
        memset((n->number) + (n->length), 0, (num / 8) - (n->length) + 1);
        n->length = num / 8 + 1;
    }
    if (x) { // set bit
        n->number[num / 8] |= 1 << (num % 8);
    } else { // clear bit
        n->number[num / 8] &= ~(1 << (num % 8));
    }
    big_int_dlz(n);
}

void big_int_set_bit2(big_int *n, long long num, int x) {
    if ((num / 8) >= (n->length)) {
        n->number = (unsigned char *) realloc(n->number, (num / 8 + 1) * sizeof(n->number[0]));
        if (n->number == NULL) {
            printf("memory error in big_int_set_bit\n");
            return;
        }
        memset((n->number) + (n->length), 0, (num / 8) - (n->length) + 1);
        n->length = num / 8 + 1;
    }
    if (x) { // set bit
        n->number[num / 8] |= 1 << (num % 8);
    } else { // clear bit
        n->number[num / 8] &= ~(1 << (num % 8));
    }
    big_int_dlz(n);
}

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
    n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number[0]));
    if (n3->number == NULL) { printf("memory error in big_int_add\n"); }
    int t = n1->length <= n2->length;
    if (t) big_int_swap(n1, n2);
    for (int i = 0; i < mx; i++) {
        if (i < n2->length) x = n1->number[i] + n2->number[i] + carry;
        else x = n1->number[i] + carry;
        n3->number[i] = x & 0xFF;
        carry = x >> 8;
    }
    if (t) big_int_swap(n1, n2);
    n3->number[mx] = carry;
    n3->sign = n1->sign;
    big_int_dlz(n3);
    return n3;
}


void big_int_add2(big_int *n1, big_int *n2) {
    if (n1->sign != n2->sign) {
        int t = n1->sign == '+';
        if (t) {
            n2->sign = '+';
            big_int *n4 = (big_int_sub(n1, n2));
            n2->sign = '-';
            n1->sign = n4->sign;
            n1->length = n4->length;
            memmove(n1->number, n4->number, n4->length);
            big_int_free(n4);
            big_int_dlz(n1);
        } else {
            n1->sign = '+';
            big_int *n4 = (big_int_sub(n2, n1));
            n1->sign = '-';
            n1->sign = n4->sign;
            n1->length = n4->length;
            memmove(n1->number, n4->number, n4->length);
            big_int_free(n4);
            big_int_dlz(n1);
        }
    } else {
        int mx = (int) fmax(n1->length, n2->length), carry = 0, x;
        big_int *n3 = (big_int *) malloc(sizeof(big_int));
        n3->length = mx + 1;
        n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number[0]));
        if (n3->number == NULL) { printf("memory error in big_int_add2\n"); }
        int t = n1->length <= n2->length;
        if (t) big_int_swap(n1, n2);
        for (int i = 0; i < mx; i++) {
            if (i < n2->length) x = n1->number[i] + n2->number[i] + carry;
            else x = n1->number[i] + carry;
            n3->number[i] = x & 0xFF;
            carry = x >> 8;
        }
        if (t) big_int_swap(n1,n2);
        n3->number[mx] = carry;
        n3->sign = n1->sign;
        big_int_dlz(n3);
        n1->length = n3->length;
        memmove(n1->number, n3->number, n3->length);
        big_int_free(n3);
    }
}


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
    n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number[0]));
    if (n3->number == NULL) { printf("memory error in big_int_sub\n"); }
    int t = big_int_leq(n1, n2);
    if (t)big_int_swap(n1, n2);
    for (int i = 0; i < mx; i++) {
        if (i < n2->length) {
            if (n1->number[i] > n2->number[i]) {
                n3->number[i] = n1->number[i] - n2->number[i] - carry;
                carry = 0;
            }
            if (n1->number[i] == n2->number[i]) {
                if (carry) {
                    n3->number[i] = 0xFF;
                } else {
                    n3->number[i] = 0;
                }
            }
            if (n1->number[i] < n2->number[i]) {
                if (carry) {
                    n3->number[i] = 0xFF + n1->number[i] - n2->number[i];
                } else {
                    n3->number[i] = 0x100 + n1->number[i] - n2->number[i];
                    carry = 1;
                }
            }
        } else {
            if (carry) {
                if (n1->number[i]) {
                    n3->number[i] = n1->number[i] - 1;
                    carry = 0;
                } else {
                    n3->number[i] = 0xFF;
                }
            } else {
                n3->number[i] = n1->number[i];
            }
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


void big_int_sub2(big_int *n1, big_int *n2) {
    if (n1->sign != n2->sign) {
        if (n1->sign == '+') {
            n2->sign = '+';
            big_int *n4 = (big_int_add(n1, n2));
            n2->sign = '-';
            n1->sign = n4->sign;
            n1->length = n4->length;
            memmove(n1->number, n4->number, n4->length);
            big_int_free(n4);
            big_int_dlz(n1);
        } else {
            n2->sign = '-';
            big_int *n4 = (big_int_add(n2, n1));
            n2->sign = '+';
            n1->sign = n4->sign;
            n1->length = n4->length;
            memmove(n1->number, n4->number, n4->length);
            big_int_free(n4);
            big_int_dlz(n1);
        }
    } else {
        int mx = (int) fmax(n1->length, n2->length), carry = 0;
        big_int *n3 = (big_int *) malloc(sizeof(big_int));
        n3->length = mx;
        n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number[0]));
        if (n3->number == NULL) { printf("memory error in big_int_sub2\n"); }
        int t = big_int_leq(n1, n2);
        if (t)big_int_swap(n1, n2);
        for (int i = 0; i < mx; i++) {
            if (i < n2->length) {
                if (n1->number[i] > n2->number[i]) {
                    n3->number[i] = n1->number[i] - n2->number[i] - carry;
                    carry = 0;
                }
                if (n1->number[i] == n2->number[i]) {
                    if (carry) {
                        n3->number[i] = 0xFF;
                    } else {
                        n3->number[i] = 0;
                    }
                }
                if (n1->number[i] < n2->number[i]) {
                    if (carry) {
                        n3->number[i] = 0xFF + n1->number[i] - n2->number[i];
                    } else {
                        n3->number[i] = 0x100 + n1->number[i] - n2->number[i];
                        carry = 1;
                    }
                }
            } else {
                if (carry) {
                    if (n1->number[i]) {
                        n3->number[i] = n1->number[i] - 1;
                        carry = 0;
                    } else {
                        n3->number[i] = 0xFF;
                    }
                } else {
                    n3->number[i] = n1->number[i];
                }
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
        n1->sign = n3->sign;
        n1->length = n3->length;
        memmove(n1->number, n3->number, n3->length);
        big_int_free(n3);
    }
}


big_int *big_int_euclid_binary(big_int *x, big_int *y) {
    big_int *zero = big_int_get("0");
    int k, n = 0;
    big_int *x0= big_int_copy(x);
    big_int *y0= big_int_copy(y);
    big_int *a = big_int_disj(x0, y0);
    if (!big_int_equal(a, zero)) {
        while ((a->number[0] & 1) != 1) {
            big_int_bin_shft_r(a);
            big_int_bin_shft_r(x0);
            big_int_bin_shft_r(y0);
            n++;
        }
    }
    big_int_dlz(x0);
    big_int_dlz(y0);
    while ((!big_int_leq(x0, zero)) && (!big_int_leq(y0, zero))) {
        if ((x0->number[0] & 1) == 1) {
            while ((y0->number[0] & 1) == 0) big_int_bin_shft_r(y0);
        } else {
            while ((x0->number[0] & 1) == 0) big_int_bin_shft_r(x0);
        }
        big_int_dlz(x0);
        big_int_dlz(y0);
        if (big_int_leq(y0, x0)) {
            big_int_sub2(x0, y0);
        } else {
            big_int_sub2(y0, x0);
        }
    }
    big_int_dlz(x0);
    big_int_dlz(y0);
    big_int *n3= big_int_add(x0,y0);
    big_int_bin_shft_l2(n3, n);
    big_int_free(x0);
    big_int_free(y0);
    big_int_free(a);
    big_int_free(zero);
    return n3;
}


big_int *big_int_mult(big_int *x0, big_int *y0) {
    int mx = (int) fmax(x0->length, y0->length);
    big_int *zero = big_int_get("0");
    big_int *n3 = (big_int *) malloc(sizeof(big_int));
    n3->length = mx * 2 + 1;
    n3->sign = '+';
//    big_int *x0 = big_int_copy(x);
//    big_int *y0 = big_int_copy(y);
    n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number[0]));
    if (x0->length >= y0->length) {
        while (!big_int_leq(y0, zero)) {
            if (y0->number[0] & 1) big_int_add2(n3, x0);
            big_int_bin_shft_r(y0);
            big_int_bin_shft_l(x0);

        }
    } else {
        while (!big_int_leq(x0, zero)) {
            if (x0->number[0] & 1) big_int_add2(n3, y0);
            big_int_bin_shft_r(x0);
            big_int_bin_shft_l(y0);
        }
    }

//    big_int_free(x0);
//
//    big_int_free(y0);

    big_int_free(zero);

    n3->sign = (x0->sign == y0->sign) ? '+' : '-';
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
    n3->number = (unsigned char *) calloc(n3->length, sizeof(n3->number[0]));
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
    memmove(res1->number, n3->number, n3->length);
    big_int_free(n3);
    big_int *n5 = big_int_mult(n2, res1);
    big_int *n4 = big_int_sub(n1, n5);
    big_int_free(n5);
    rmdr->sign = '+';
    rmdr->length = n4->length;
    memmove(rmdr->number, n4->number, n4->length);
    big_int_free(n4);
}


void big_int_div2(big_int *n1, big_int *n2, big_int *res1, big_int *rmdr) {
    big_int *r = big_int_get("0");
    big_int *q = big_int_get("0");
    for (int i = (n1->length) - 1; i >= 0; i--) {
        for (int bit = 7; bit >= 0; bit--) {
            big_int_bin_shft_l(r);
            big_int_set_bit(r, 0, ((n1->number[i]) & (1 << bit)) != 0);
            if (big_int_leq(n2, r)) {
                r->sign = '+';
                big_int_sub2(r, n2);
                big_int_set_bit(q, i * 8 + bit, 1);
            }
        }
    }
    res1->sign = (n1->sign == n2->sign) ? '+' : '-';
    res1->length = q->length;
    memmove(res1->number, q->number, q->length);
    big_int_free(q);
    rmdr->sign = '+';
    rmdr->length = r->length;
    memmove(rmdr->number, r->number, r->length);
    big_int_free(r);
}


big_int *big_int_rl_mod_pow(big_int *x, big_int *n, big_int *m) {
    big_int *ans = big_int_get("1");
    big_int *zero = big_int_get("0");
    big_int *x0 = big_int_copy(x);
    big_int *n0 = big_int_copy(n);
    big_int *m0 = big_int_copy(m);
    while (!big_int_leq(n0, zero)) {
        if ((n0->number[0]) & 1) {
            big_int *xmodm = big_int_get("0");
            big_int *trash = big_int_get("0");
            big_int_div2(x0, m0, trash, xmodm);
            big_int *n4 = big_int_mult(ans, xmodm);
            big_int_swap(ans, n4);
            big_int_free(n4);
            big_int_free(xmodm);
            big_int_free(trash);
        }
        big_int *cp_x0 = big_int_copy(x0);
        big_int *sq = big_int_mult(x0, cp_x0);
        big_int *sqmodm1 = big_int_get("0");
        big_int *trash1 = big_int_get("0");
        big_int_div2(sq, m0, trash1, sqmodm1);
        big_int_swap(x0, sqmodm1);
        big_int_bin_shft_r(n0);//n>>=1
        big_int_free(cp_x0);
        big_int_free(sq);
        big_int_free(sqmodm1);
        big_int_free(trash1);
    }
    big_int *fin = big_int_get("0");
    big_int_div2(ans, m0, zero, fin);
    big_int_free(zero);
    big_int_free(x0);
    big_int_free(m0);
    big_int_free(n0);
    big_int_free(ans);
    return fin;
}











int tst_add() {
    FILE *file = fopen("numbers.txt", "r");

    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);

    for (long i = 0; i < 100*100*100; i++) {

        fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
//        printf("n1=");
        big_int *n1 = big_int_get(binary);
//        big_int *n12 = big_int_copy(n1);
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
//        printf("ans1=");
        big_int *mod = big_int_get(binary);
//        big_int_print(ans1);

        fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans = big_int_get(binary);
//        big_int_print(n1);
//        printf("ans=");
//        printf("ans2=");
//        big_int_print(ans2);
//        printf("before mult\n");
//        printf("1");
        big_int *n3=big_int_rl_mod_pow(n1, n2,mod);
//        printf("2");
//        printf("n3 addr=%d\n",*(n3->number));
//        printf("after mult\n");
//        big_int_sub2(n12,n2);
//        big_int_add2(n12, n2);
//        printf("my ans1=");
//        big_int_print(my1);
//        printf("my ans2=");
//        big_int_print(my2);
//        printf("------------------------------\n");
        if ((!big_int_equal(ans, n3))) {
            printf("////////////////////////IMPOSTER i=%li//////////////\n", i);
//            printf("n1=");
//            big_int_print(n1);
//            printf("n2=");
//            big_int_print(n2);
////            printf("cnt=%d\n",cnt->number[0]);
////            printf("bit=%d\n",bit->number[0]);
//            printf("ans1=");
//            big_int_print(ans1);
//            printf("ans2=");
//            big_int_print(ans2);
//            printf("my1=");
//            big_int_print(my1);
//            printf("my2=");
//            big_int_print(my2);
//            printf("my2=");
//            big_int_print(n12);
//            printf("n3=");
//            big_int_print(n3);
//            printf("ans(n1**n2)%%n3=");
//            big_int_print(ans);
//            printf("my ans(n1**n2)%%n3=");
//            big_int_print(n4);
            break;
        }
        big_int_free(n1);
        big_int_free(n2);
        big_int_free(ans);
        big_int_free(mod);
        big_int_free(n3);
        if(i%100000==0){printf("i=%li\n",i);}
//        printf("---------------\n");
    }

    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    return 0;
}