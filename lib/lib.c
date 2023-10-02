//
// Created by lolikion on 01.10.23.
//
#include "lib.h"
#include <stdio.h>

//ok
int euclid(int a, int b) {
    int t;
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}


//ok
int euclid_recursive(int a, int b) {
    return a ? euclid_recursive(b % a, a) : b;
}


//ok
int euclid_extended(int a, int b, int *x, int *y) {
    int q, r = b, a11 = 1, a12 = 0, a21 = 0, a22 = 1, b11, b21, n = 0;
    while (r) {
        b = r;
        q = a / b;
        r = a - b * q;
        b11 = a11;
        b21 = a21;
        a11 = a11 * q + a12;
        a12 = b11;
        a21 = a21 * q + a22;
        a22 = b21;
        n++;
        a = b;
    }
    *x = (n % 2) ? a22 * (-1) : a22;
    *y = (n % 2) ? a12 : a12 * (-1);
    return b;
}


//ok
int mul_inverse(int e, int m) {
    int x, y;
    int gcd = euclid_extended(e, m, &x, &y);
    if (gcd > 1) return 0;
    return (x % m + m) % m;
}


//ok
int linear_diophantine(int *a, int *result, int n, int c) {
    int gcd = a[0], x;
    *result = 1;
    for (int i = 1; i < n; i++) {
        gcd = euclid_extended(gcd, a[i], &x, &result[i]);
        for (int j = 0; j < i; j++) {
            result[j] *= x;
        }
    }
    if (c % gcd) {
        return -1;
    } else {
        int m = c / gcd;
        for (int i = 0; i < n; i++) {
            result[i] *= m;
        }
        return 0;
    }
}


//ok
long long rl_mod_pow(int x, long long n, int m) {
    int ans = 1;
    while (n) {
        if (n & 1) ans *= x % m;
        x = (x * x) % m;
        n >>= 1;
    }
    return ans % m;
}


//ok
int lr_mod_pow(int x, long long y, int m) {
    int bit = 1;
    long long y2 = y;
    while (y2) {
        y2 >>= 1;
        bit <<= 1;
    }
    y2 = 1;
    for (bit; bit; bit >>= 1) {
        y2 = (y2 * y2) % m;
        if (y & bit) y2 *= x % m;
    }
    return y2 % m;
}


//ok
int euclid_binary(int x, int y) {
    int a, n = 0;
    a = x | y;
    while ((a & 1) != 1) {
        a >>= 1;
        x >>= 1;
        y >>= 1;
        n++;
    }

    while (x * y) {
        if ((x & 1) == 1) {
            while ((y & 1) == 0) y >>= 1;
        } else {
            while ((x & 1) == 0) x >>= 1;
        }
        if (x >= y) x = x - y;
        else y = y - x;

    }
    return (x + y) >> n;
}


//ok
int chinese_remainder(const int *a, const int *m, int k) {
    int m_big = m[0];
    int x = 0;

    for (int i = 1; i < k; i++) {
        if (euclid_binary(m_big, m[i]) != 1) return -1;
        m_big *= m[i];
    }

    for (int i = 0; i < k; i++) {
        int M = mul_inverse(m_big / m[i], m[i]);
        if (M == 0) return -1;
        x += a[i] * (m_big / m[i]) * M;
    }
    return x % m_big;
}


//ok
int chinese_remainder_iterative(const int *a, const int *m, int k) {
    int x = a[0], u, v, lcm = m[0];
    for (int i = 1; i < k; i++) {
        if (euclid_extended(m[i], lcm, &u, &v) != 1) return -1;
        x = x * m[i] * u + a[i] * lcm * v;
        lcm *= m[i];
    }
    return (x % lcm + lcm) % lcm;
}