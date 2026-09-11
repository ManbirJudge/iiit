#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);

    const int n_bits = sizeof(n) * 8;

    int pwd = 0;
    for (int j = 1; j < n_bits - 1; j++) {
        if (((n >> (j - 1)) & 7) == 2) // shift n to get the 3 bits to right-most position, get the 3 bits, compare them to desired (010)
            pwd |= 1 << j;
    }

    printf("%d\n", pwd);
    
    return 0;
}