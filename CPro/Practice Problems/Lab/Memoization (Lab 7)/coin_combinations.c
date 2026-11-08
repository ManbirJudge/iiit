#include <limits.h>
#include <stdio.h>

#define MOD 1000000007

int func(int c[], int n, int x) {
    static int cache[1000000] = {0};

    if (x == 0) return 1;
    if (cache[x] != 0) return cache[x];

    unsigned long long ans = 0;

    for (int i = 0; i < n; i++) {
        if (c[i] <= x) {
            ans += func(c, n, x - c[i]);
            ans %= MOD;
        }
    }

    return cache[x] = ans;
}

int main(void) {
    int n, x;
    scanf("%d %d", &n, &x);

    int c[n];
    for (int i = 0; i < n; i++)
        scanf("%d", c + i);

    printf("%d\n", func(c, n, x));

    return 0;
}