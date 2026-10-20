#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define IS_ALPHANUMERIC(x) (('a' <= (x) && (x) <= 'z') || ('A' <= (x) && (x) <= 'Z') || ('0' <= (x) && (x) <= '9'))
#define TO_LOWER(x) (('A' <= (x) && (x) <= 'Z') ? ((x) - 'A' + 'a') : (x))

bool isPalindrome(char* s) {
    size_t n = strlen(s);

    char *last = s + n - 1;

    char* a = s;
    char* b = last;
    
    while (a <= b) {
        while (!IS_ALPHANUMERIC(*a) && a < last) a++;
        while (!IS_ALPHANUMERIC(*b) && b > s) b--;

        if (a >= b) return true;

        // if (!IS_ALPHANUMERIC(*a) && !IS_ALPHANUMERIC(*b)) return true;
        // if (!IS_ALPHANUMERIC(*a) || !IS_ALPHANUMERIC(*b)) continue; 

        printf("Comparing %c and %c.\n", *a, *b);

        if (TO_LOWER(*a) != TO_LOWER(*b)) return false;

        a++;
        b--;
    }

    return true;
}

int main(int argc, char **argv) {
    printf("%d\n", isPalindrome(argv[1]));

    return 0;
}