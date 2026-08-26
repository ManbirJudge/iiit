#include <stdio.h>

int main() {
    char chr = 'a';
    printf("Before: %c\n", chr);
    chr -= 32;
    printf("After: %c\n", chr);
    return 0;
}
