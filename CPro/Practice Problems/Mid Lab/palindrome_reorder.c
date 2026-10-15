#include <stdio.h>
#include <string.h>

void print_chars(char c, int n) {
    for (int i = 0; i < n; i++)
        putchar(c);
}

int main(void) {
    char str[1000001];
    scanf("%s", str);

    int f[26] = {0};
    
    int n = strlen(str);
    for (int i = 0; i < n; i++)
        f[str[i] - 'A']++;
    
    int odd_f_idx = -1;
    for (int i = 0; i < 26; i++) {
        if (f[i] % 2 == 1) {
            if (odd_f_idx == -1)
                odd_f_idx = i;
            else {
                printf("NO SOLUTION\n");
                return 0;
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (i == odd_f_idx) continue;
        if (f[i] == 0) continue;
        print_chars(i + 'A', f[i] / 2);
    }
    if (odd_f_idx != -1) {
        print_chars(odd_f_idx + 'A', f[odd_f_idx]);
    }
    for (int i = 25; i >= 0; i--) {
        if (i == odd_f_idx) continue;
        if (f[i] == 0) continue;
        print_chars(i + 'A', f[i] / 2);
    }

    return 0;
}
