# PYP 2023 - Solution
## Section A
### Question 1
```
#include <stdio.h>

int main(void) {
    int n;
    printf("Number: ");
    scanf("%d", &n);

    int fact = 1;
    for (int i = n; i > 0; i--)
        fact *= i;

    printf("Factorial = %d\n", fact);

    return 0;
}
```

### Question 2
DIY

### Question 3
DIY [easy]

### Question 5
[]

### Question 6
**Prerequisite -** Binomial theorem and simplification of bionomial coefficients.
```
#include <stdio.h>

int main(void) {
    int n;
    printf("Number: ");
    scanf("%d", &n);

    int max_row_w = n + n - 1; 

    for (int i = 0; i < n; i++) {
        int pad = n - i - 1;
        printf("%*.s", pad, "");

        int i_C_j = 1;
        for (int j = 0; j <= i; j++) {
            printf("%d ", i_C_j);
            i_C_j = i_C_j * (i - j) / (j + 1);
        }

        printf("\n");
    }

    return 0;
}
```

## Section B
### Question 1
```
#include <stdio.h>

int main(void) {
    int n;
    
    printf("Enter number: ");
    scanf("%d", &n);

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += 2 * i;

    printf("Sum = %d\n", sum);

    return 0;
}
```
### Question 2
[]

### Question 3
DIY [easy]

### Question 4
[]

### Question 5
```
#include <stdio.h>

int main(void) {
    int n;
    printf("Rows: ");
    scanf("%d", &n);

    int max_row_w = n + n - 1; 

    for (int i = 0; i < n; i++) {
        int pad = n - i - 1;
        printf("%*.s", pad, "");

        int i_C_j = 1;
        for (int j = 0; j <= i; j++) {
            printf("%d ", i + j + 1);
        }

        printf("\n");
    }

    return 0;
}
```

### Question 6
DIY [easy]