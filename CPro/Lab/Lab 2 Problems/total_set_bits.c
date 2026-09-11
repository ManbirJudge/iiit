#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);

    size_t t_count = 0;

    size_t j, n_bits = sizeof(n) * 8;
    for (int i = 1; i <= n; i++) {
        for (j = 0; j < n_bits; j++)
            t_count += (i >> j) & 1;
    }

    printf("%zu\n", t_count);

    return 0;
}