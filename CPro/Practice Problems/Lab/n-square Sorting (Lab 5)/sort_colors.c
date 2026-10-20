void sortColors(int* nums, int numsSize) {
    int n0 = 0;    
    int n1 = 0;    
    int n2 = 0;

    for (int i = 0; i < numsSize; i++) {
        switch (nums[i]) {
            case 0: n0++; break;
            case 1: n1++; break;
            case 2: n2++; break;
        }
    }

    n1 += n0;
    n2 += n1;

    for (int i = 0; i < numsSize; i++) {
        if (i < n0) nums[i] = 0;
        else if (i < n1) nums[i] = 1;
        else if (i < n2) nums[i] = 2;
    }
}