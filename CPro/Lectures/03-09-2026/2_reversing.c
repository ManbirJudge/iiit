#include <stdio.h>

int main(void) {
    int arr[] = {4, 5, 6, 1};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Before: ");
    for (size_t i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    // Approach 1:
    // int tmp;
    // for (size_t i = 0; i < (n / 2); i++) {
    //     tmp = arr[i];
    //     arr[i] = arr[n - i - 1];
    //     arr[n - i - 1] = tmp; 
    // }

    // Approach 2:
    size_t j = 0, k = n - 1;
    int tmp;
    while (j < k) {
        int tmp = arr[j];
        arr[j] = arr[k];
        arr[k] = tmp;

        j++;
        k--;
    }

    printf("After: ");
    for (size_t i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}