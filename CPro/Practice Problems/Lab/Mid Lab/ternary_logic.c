#include <stdio.h>

long long int decimal_2_base3(long long int n, long long int *c) {
    long long int m = 0;
    *c = 0;
    
    long long int p = 1;
    while (n > 0) {
        long long int r = n % 3;

        m += r * p;
        n /= 3;

        p *= 10;
        (*c)++;
    }

    return m;
}

long long int base3_2_decimal(long long int n) {
    long long int m = 0;
    
    long long int p = 1;
    while (n > 0) {
        m += (n % 10) * p;
        n /= 10;
        p *= 3;
    }

    return m;
}

long long int main(void) {
    // TODO: given a and c, find b such that 'a tor b = c'
    // operation tor is defined as: decimal value of digit-wise-modulo addition of a and b in base3

    long long int a, c;
    scanf("%lld %lld", &a, &c);

    long long int n_a = 0, n_c = 0;

    a = decimal_2_base3(a, &n_a);
    c = decimal_2_base3(c, &n_c);

    long long int b = 0;

    long long int p = 1;  // place value
    long long int n = (n_a > n_c) ? n_a : n_c;
    for (long long int i = 0; i < n; i++) {
        long long int d_a = (a / p) % 10;
        long long int d_c = (c / p) % 10;

        long long int d_b = (d_c - d_a + 3) % 3;
        b += d_b * p;

        p *= 10;
    }

    b = base3_2_decimal(b);

    printf("%lld\n", b);
    
    return 0;
}
