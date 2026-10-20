#include <stdio.h>

long long int decimal_2_base3(long long int n, int *c) {
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

int main(void) {
    long long int a, b;
    scanf("%lld %lld", &a, &b);

    int n_a = 0, n_b = 0;

    a = decimal_2_base3(a, &n_a);
    b = decimal_2_base3(b, &n_b);

    long long int c = 0;

    long long int p = 1;  // place value
    int n = (n_a > n_b) ? n_a : n_b;
    for (int i = 0; i < n; i++) {
        long long int d_a = (a / p) % 10;
        long long int d_b = (b / p) % 10;

        long long int d_c = (d_a + d_b) % 3;
        c += d_c * p;

        p *= 10;
    }

    c = base3_2_decimal(c);

    printf("%lld\n", c);
    
    return 0;
}