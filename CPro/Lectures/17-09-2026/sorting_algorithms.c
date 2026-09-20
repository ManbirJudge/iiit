#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void selection_sort(int *arr, int n) {
    int min_idx, tmp;

    for (int i = 0; i < n; i++) {
        min_idx = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        tmp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = tmp;
    }
}

void bubble_sort(int *arr, int n) {
    int tmp, swap;

    for (int i = n - 1; i > 0; i--) {
        swap = 0;
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swap = 1;
            }
        }
        if (!swap) break;
    }
}

void insertion_sort(int *arr, int n) {
    int tmp, j;
    for (int i = 1; i < n; i++) {
        tmp = arr[i];
        for (j = i - 1; j >= 0; j--) {
            if (arr[j] > tmp)
                arr[j + 1] = arr[j];
        }
        arr[j + 1] = arr[i];
    }
}

int main(void) {
    srand(time(NULL));

    int n;
    scanf("%d", &n);

    int *arr1 = malloc((size_t)n * sizeof(int));
    int *arr2 = malloc((size_t)n * sizeof(int));
    int *arr3 = malloc((size_t)n * sizeof(int));

    for (int i = 0; i < n; i++)
        arr1[i] = rand() % (n + 1);

    memcpy(arr2, arr1, (size_t)n * sizeof(int));
    memcpy(arr3, arr1, (size_t)n * sizeof(int));

    clock_t start1 = clock();
    selection_sort(arr1, n);
    clock_t end1 = clock();
    printf("Selection sort: %.3fs\n", (double)(end1 - start1) / CLOCKS_PER_SEC);
    
    clock_t start2 = clock();
    bubble_sort(arr2, n);
    clock_t end2 = clock();
    printf("Buuble sort:    %.3fs\n", (double)(end2 - start2) / CLOCKS_PER_SEC);
    
    clock_t start3 = clock();
    insertion_sort(arr3, n);
    clock_t end3 = clock();
    printf("Insertion sort: %.3fs\n", (double)(end3 - start3) / CLOCKS_PER_SEC);

    // for (int i = 0; i < n; i++)
    //     printf("%d ", arr[i]);
    // printf("\n");

    return 0;
}