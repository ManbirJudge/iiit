#include <stdio.h>
#include <string.h>
#include <limits.h>

// NOTE: very proud of this because I was able to get the 'quite good' logic in the class itself! (finished all 3 in 1 hr 10 min!)

int main(void) {
    char s[100001];
    scanf("%s", s);

    int f[26] = {0};
    for (int i = 0, n = strlen(s); i < n; i++)
        f[s[i] - 'a']++;

    int min_f = INT_MAX;
    for (int i = 0; i < 26; i++) {
        if (f[i] == 0) continue;
        if (f[i] < min_f) min_f = f[i];
    }

    int c = 0;

    for (int i = 0; i < 26; i++) {  // maybe: we can reduce the total number of iterations?
        for (int j = 0; j < 26; j++) {
            if (i == j) continue;

            if (f[i] == f[j]) {
                if (f[i] == 0) continue;

                if (min_f == 0) {
                    c += f[j]; 
                    f[j] = 0;
                } else {
                    c += f[j] - min_f + 1;
                    f[j] = --min_f;
                }
            }
        }
    }

    printf("%d\n", c);

    return 0;
}