# PYP 2022 - Solution
## Question 1
```
#include <stdio.h>

int main(void) {
    int n;
    
    printf("Enter number: ");
    scanf("%d", &n);

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += 2 * i + 1;

    printf("Sum = %d\n", sum);

    return 0;
}
```

## Question 2
double (8), int (4), short (2), char (1)

## Question 3
Two reasons -
1. 1's complement represtation contains `+0` and `-0`, while 2's complement representation as only one `0`. This makes comparison easier in the latter case.
2. Handling the carry out of sign-bit position during addition (required in 1's complement represation) requires extra logic gates.

## Question 4
```
4 0
```

## Question 5
DIY

## Question 6
DIY

## Question 7
```
#include <stdio.h>

int main(void) {
    if (printf("Hello world")) {}
}
```