#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 0 'a' -> 
// 1 'b' ->
// ...
// 25 'z' ->
int new_vals[26];

int cmp(const void *a, const void *b) {
    const char *A = a;
    const char *B = b;

    int l1 = strlen(A);
    int l2 = strlen(B);
    int l_min = l1 < l2 ? l1 : l2;

    for (int i = 0; i < l_min; i++) {
        if (A[i] != B[i]) return new_vals[A[i] - 'a'] - new_vals[B[i] - 'a'];
    }
    
    return l1 - l2;
    // return (l2 < l1) - (l1 < l2);
}

int main(void) {
    char order[27];
    int N;

    scanf("%s", order);
    scanf("%d", &N);
    
    char words[N][101];

    for (int i = 0; i < N; i++)
        scanf("%s", words[i]);

    for (int i = 0; i < 26; i++)
        new_vals[order[i] - 'a'] = i;

    qsort(words, N, sizeof(words[0]), cmp);
    
    for (int i = 0; i < N; i++)
        printf("%s\n", words[i]);

    return 0;
}