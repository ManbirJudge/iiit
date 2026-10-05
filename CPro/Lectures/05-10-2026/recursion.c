#include <stdio.h>

int power(int n, int p) {  // DOUBT: can it be optimized further?
    if (p == 0) return 1;

    if (p % 2 == 0) {
        int x = power(n, p / 2);
        return x * x;
    } else return n * power(n, p - 1);
}

// int power_naive(int n, int p) {
//     if (p == 0) return 1;
//     return n * power(n, p - 1);
// }

int sod(int n) {
    if (n < 10) return n;
    return (n % 10) + sod(n / 10);
}

int fib(int n) {
    static int mem[100] = {0};  // 0, 1 indices are never used...

    if (n == 0 || n == 1) return n;

    if (n > 100)
        return fib(n - 1) + fib(n - 2);
    else {
        if (mem[n] == 0) mem[n] = fib(n - 1) + fib(n - 2);
        return mem[n];
    }
}

int main(void) {
    int n, p;

    printf("n = ");
    scanf("%d", &n);
    printf("p = ");
    scanf("%d", &p);

    printf("n^p = %d\n", power(n, p));
    printf("sum of digits of n = %d\n", sod(n));
    printf("nth number in Fibonacci sequence = %d\n", fib(n));

    return 0;
}