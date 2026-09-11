#include <stdio.h>

int main(void) {
    long long int n;
    scanf("%lld", &n);

    size_t n_iter = 0;

    while (n > 9) {
        long long int new_n = 0;

        while (n > 0) {
            new_n += n % 10;
            n /= 10;
        }

        n = new_n;
        n_iter++;
    }

    printf("%zu\n%lld\n", n_iter, n);

    return 0;
}