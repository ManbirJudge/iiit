#include <stdio.h>
#include <string.h>

int main(void) {
    int n;
    scanf("%d", &n);

    char t1[101] = {0};
    char t2[101] = {0};

    int g1 = 0, g2 = 0;
    
    char cur[101];
    for (int i = 0; i < n; i++) {
        scanf("%s", cur);

        if (t1[0] == 0) {
            strcpy(t1, cur);
            g1 = 1;
        } else if (strcmp(t1, cur) == 0) {
            g1++;
        } else if (t2[0] == 0) {
            strcpy(t2, cur);
            g2 = 1;
        } else {
            g2++;
        }
    }

    printf("%s\n", (g1 > g2) ? t1 : t2);

    return 0;
}
