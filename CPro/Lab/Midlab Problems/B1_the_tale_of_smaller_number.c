#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);

    int nums[n];
    for (int i = 0; i < n; i++)
        scanf("%d", nums + i);

    int freq[101];   // freq[x - 1] = number of elements less than equal to (x - 1) = number of elements less than x
    for (int i = 0; i < n; i++)
        freq[nums[i]]++;
    for (int i = 1; i <= 100; i++)
        freq[i] += freq[i - 1];

    int x;
    for (int i = 0; i < n; i++) {
        x = nums[i];
        if (x == 0) printf("0 ");
        else printf("%d ", freq[x - 1]);
    }
    printf("\n");

    return 0;
}