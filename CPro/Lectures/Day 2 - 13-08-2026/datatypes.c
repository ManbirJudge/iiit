#include <stdio.h>

int main() {
    printf("char      = %zu\n", sizeof(char));
    printf("\n");
    printf("short     = %zu\n", sizeof(short));
    printf("short int = %zu\n", sizeof(short int));
    printf("\n");
    printf("int       = %zu\n", sizeof(int));
    printf("\n");
    printf("long      = %zu\n", sizeof(long));
    printf("long int  = %zu\n", sizeof(long int));
    printf("long long = %zu\n", sizeof(long long));
    printf("\n");
    printf("float     = %zu\n", sizeof(float));
    printf("double    = %zu\n", sizeof(double));

    return 0;
}
