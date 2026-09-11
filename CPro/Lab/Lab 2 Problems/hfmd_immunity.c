#include <stdio.h>

int main(void) {
    long long int n;
    scanf("%lld", &n);

    size_t n_5s = 0;  // number of 5s in prime factorization

    long long int d = 1;
    long long int q;
    for (int i = 1; i <= 100; i++) {
        d *= 5;
        q = n / d;

        if (q == 0) break;

        n_5s += q;
    }

    printf("%zu\n", n_5s);

    return 0;
}