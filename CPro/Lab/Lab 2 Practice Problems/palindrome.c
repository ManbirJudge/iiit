#include <stdio.h>

unsigned long long reverse(unsigned long long n) {
    unsigned long long reversed = 0;

    while (n != 0) {
        int last_digit = n % 10;  // get the last digit
        reversed = reversed * 10 + last_digit;  // append the last digit to reversed
        n /= 10;  // drop/remove the last digit
    }

    return reversed;
}

int main(void) {
    unsigned long long n;
    scanf("%llu", &n);

    unsigned long long reversed = reverse(n);

    if (n == reversed) printf("Palindrome\n");
    else printf("Not Palindrome\n");
    printf("%llu\n", reversed);

    return 0;
}
