#include <stdio.h>

int main(void) {
    char str[51];

    printf("Enter string of length 50 or less: ");
    scanf("%s", str);

    for (int i = 0, n = strlen(str); i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            printf("%s\n", );
        }
    }
}
