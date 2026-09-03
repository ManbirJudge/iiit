#include <stdio.h>

int main(void) {
    // PROBLEM: An array of size n, should contain numbers from 1 to n - 1. Find the missing numbers.

    int arr[] = {2, 2, 4, 3, 5, 7};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    // Method 1: The Worst One
    // int found = 0;
    // for (size_t i = 1; i <= n; i++) {
    //     found = 0;
    //     for (size_t j = 0; j < n; j++) {
    //         if (arr[j] == i) {
    //             found = 1;
    //             break;
    //         }
    //     }
    //
    //     if (!found)
    //         printf("%zu is missing\n", i);
    // }

    // Method 2: Meth

    return 0;
}