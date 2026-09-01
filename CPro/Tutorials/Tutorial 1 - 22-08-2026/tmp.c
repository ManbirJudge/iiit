#include <stdio.h>
#include <limits.h> 

int main(void) {
    int i;
    printf("Number: ");
    scanf("%d", &i);

    printf("Last: %d\n", i % 10);

    while (i > 9) i /= 10;
    printf("First: %d\n", i);

    return 0;
}
