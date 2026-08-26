#include <stdio.h>

int main() {
    int a, b = 5, c = 8;

    printf("Enter two numbers: ");
    scanf("%d%d", &a, &c);

    printf("The sum is: %d\n", a + b);
    printf("Are 'b' and 'c' equal: %d\n", b == c);

    printf("Pre-incremented a = %d\n", a++);
    printf("Post-incremented c = %d\n", ++c);

    printf("Test 1: %d\n", b += c);
    printf("Test 2: %d\n", b = a + c);

    return 0;
}
