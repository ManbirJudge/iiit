#include <stdio.h>

int main(void) {
    int a = 11, b = 12, mul = 0;

    if (a % 2 == 1) mul += b;

    while (a >= 1) {
        a = a >> 1;
        b = b << 1;

        if (a % 2 == 1) mul += b;
    }

    printf("%d\n", mul);

    return 0;
}
