void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int idx_min = i;
        int min = arr[i];

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < min) {
                idx_min = j;
                min = arr[j];
            }
        }

        if (idx_min == i) continue;

        arr[idx_min] = arr[i];
        arr[i] = min;
    }
}