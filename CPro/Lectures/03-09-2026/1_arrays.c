#include <stdio.h>

int main(void) {
    int arr1[] = {4, 5, 9, 10};
    int arr2[5];  // unintialized values may be 0 or garbage - depends on the system
    int arr3[6] = {5, 6};  // also true here

    arr3[2] = 7;

    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("Array 1: ");
    for (size_t i = 0; i < n1; i++) printf("%d ", arr1[i]);
    printf("\n");

    printf("Array 2: ");
    for (size_t i = 0; i < n2; i++) printf("%d ", arr2[i]);
    printf("\n");
    
    printf("Array 3: ");
    for (size_t i = 0; i < n3; i++) printf("%d ", arr3[i]);
    printf("\n");
    
    int n4 = 3;
    int arr4[n4]; // = {6, 7} is invalid. it's part of the C standard

    printf("Array 4: ");
    for (size_t i = 0; i < n4; i++) printf("%d ", arr4[i]);
    printf("\n");

    return 0;
}