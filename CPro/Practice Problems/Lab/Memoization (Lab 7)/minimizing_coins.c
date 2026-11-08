#include <limits.h>
#include <stdio.h>

int func(int c[], int n, int x) {
    static int cache[1000000] = {0};

    if (cache[x] != 0) return cache[x];

    int min = -1;

    int _;
    for (int i = 0; i < n; i++) {
        if (c[i] == x) {
            return cache[x] = 1;
        } else if (c[i] < x) {
            _ = func(c, n, x - c[i]);
            if (_ == -1) continue;
            if (_ < min || min == -1) min = _;
        }
    }

    if (min == -1) {
        return cache[x] = -1;
    } else {
        return cache[x] = min + 1;
    }
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