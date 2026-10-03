#include <stdio.h>
#include <string.h>

// NOTE: easy

size_t int_to_str(size_t x, char *str) {
    size_t i = 0;

    while (x > 0) {
        str[i++] = (x % 10) + '0';
        x /= 10;
    }

    char reversed[i];
    memcpy(reversed, str, i);

    for (int j = 0; j < i; j++)
        str[j] = reversed[i - j - 1];

    return i;
}

int main(void) {
    char s[200001];
    scanf("%s", s);

    char res[400001] = {0};
    size_t res_idx = 0;
   
    char prev = s[0];
    size_t c = 1;
    for (size_t i = 1, n = strlen(s); i < n; i++) {
        if (s[i] == prev) c++;
        else {
            res[res_idx++] = prev;
            res_idx += int_to_str(c, res + res_idx);

            c = 1;
            prev = s[i];
        }
    }

    res[res_idx++] = prev;
    res_idx += int_to_str(c, res + res_idx);

    printf("%s\n", res);

    return 0;
}