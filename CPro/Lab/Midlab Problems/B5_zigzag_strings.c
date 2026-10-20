#include <stdio.h>
#include <string.h>

int main(void) {
    char s[1001];
    scanf("%s", s);

    int R;
    scanf("%d", &R);

    int n = strlen(s);

    int _a = (R == 1) ? 1 : (2 * (R - 1));  // gap of first and last row
    for (int i = 0; i < R; i++) {
        int _b1 = (i == 0 || i == R - 1) ? _a : _a - (2 * i);  // even gap of this row
        int _b2 = (i == 0 || i == R - 1) ? _a : (_a - _b1);    // odd gap of this row

        int _off = i;  // i is initial off for this row
        int j = 0;
        while (_off < n) {
            printf("%c", s[_off]);

            _off += (j % 2 == 0) ? _b1 : _b2;
            j++;
        }
    }
    printf("\n");

    return 0;
}