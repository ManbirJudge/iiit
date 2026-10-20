#include <stdio.h>

void sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[max_idx])
                max_idx = j;
        }

        if (max_idx == i) continue;

        int tmp = arr[i];
        arr[i] = arr[max_idx];
        arr[max_idx] = tmp;
    }
}

int main(void) {
    int n;
    scanf("%d", &n);

    int S = 0;
    
    int coins[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", coins + i);
        S += coins[i];
    }
    
    sort(coins, n);
    
    int i;
    int mine = 0;
    int his = S;
    for (i = 0; i < n; i++) {
        if (mine > his) break;

        mine += coins[i];
        his  -= coins[i];
    }

    printf("%d\n", i);

    return 0;
}
