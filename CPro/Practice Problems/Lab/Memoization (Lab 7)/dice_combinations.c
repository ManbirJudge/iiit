#include <stdio.h>

unsigned long long n_ways(unsigned long long n) {
    static unsigned long long cache[1000000] = {0};

    if (n == 1) return 1;

    if (cache[n] == 0) {
        for (int i = 1; i <= 6; i++) {
            if (i < n) cache[n] += n_ways(n - i);
            if (i == n) cache[n]++;
        }
        cache[n] %= 1000000007;
    }

    return cache[n];
}

int main(void) {
    unsigned long long int n;
    scanf("%llu", &n);

    printf("%llu\n", n_ways(n));

    return 0;
}