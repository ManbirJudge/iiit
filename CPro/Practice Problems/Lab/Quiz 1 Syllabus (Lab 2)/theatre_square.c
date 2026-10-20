#include <stdio.h>

// NOTE: requires a bit of ~~meth~~ math

int main(void) {
    long long int n, m, a;

    scanf("%lld %lld %lld", &n, &m, &a);

    long long int x = ((n + a - 1) / a) * ((m + a - 1) / a);

    printf("%lld\n", x);

    return 0;
}