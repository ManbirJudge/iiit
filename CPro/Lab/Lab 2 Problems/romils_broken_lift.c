#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);

    int floors[n];
    for (int i = 0; i < n; i++)
        scanf("%d", floors + i);

    int cur = floors[0];
    for (int i = 1; i < n; i++) {
        int nxt = floors[i];

        if (cur < nxt) {
            for (int j = cur; j < nxt; j++)
                printf("%d ", j);
        } else {
            for (int j = cur; j > nxt; j--)
                printf("%d ", j);
        }

        cur = nxt;
    }
    printf("%d\n", cur);  // last floor

    return 0;
}