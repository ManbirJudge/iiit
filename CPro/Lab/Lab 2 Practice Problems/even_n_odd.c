#include <stdio.h>

int main(void) {
    unsigned long long n;
    scanf("%llu", &n);

    unsigned long long S_even = 0, S_odd = 0;
    
    unsigned long long fib_last_last = 0;
    unsigned long long fib_last = 1;

    if (n == 1) {
        // nothing
    } else if (n == 2) {
        S_odd = 1;
    } else {
        S_odd = 1;

        unsigned long long cur;
        for (unsigned long long i = 3; i <= n; i++) {
            cur = fib_last + fib_last_last;

            if (cur % 2 == 0) S_even += cur;
            else S_odd += cur;

            fib_last_last = fib_last;
            fib_last = cur;
        }
    }

    printf("%llu\n%llu\n", S_even, S_odd);

    return 0;
}
