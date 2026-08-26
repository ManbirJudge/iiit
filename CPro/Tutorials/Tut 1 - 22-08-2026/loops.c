#include <stdio.h>
#include <limits.h>

int main(void) {
    int arr[4];

    int max = 0;
    int min = INT_MAX;

    for (int i = 0; i < 4; i++) {
        printf("Cost of chocolate %d : ", i + 1);
        scanf("%d", &arr[i]);

        if (arr[i] > max) max = arr[i];
    }


    for (int i = 3; i >= 0; i--) {
        if (arr[i] < min) min = arr[i];
    }

    printf("Max cost: %d\n", max);
    printf("Min cost: %d\n", min);

    return 0;
}
