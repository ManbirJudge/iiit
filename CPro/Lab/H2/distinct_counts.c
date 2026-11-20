#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char str[21];
} Entry;

int cmp(const void *x, const void *y) {
    const Entry *a = x;
    const Entry *b = y;

    int alpha_order = strcmp(a->str, b->str); 

    if (alpha_order != 0) return alpha_order;
    else return a->id - b->id;
}

int main(void) {
    int N;
    scanf("%d", &N);

    Entry *entries = malloc(N * sizeof(Entry));

    for (int i = 0; i < N; i++) {
        scanf("%d %s",
            &entries[i].id,
            entries[i].str
        );
    }

    // ---
    qsort(entries, N, sizeof(Entry), cmp);
    
    // ---
    int distinct_count = 1;

    for (int i = 1; i < N; i++) {
        if (strcmp(entries[i].str, entries[i - 1].str) != 0) {  // strings not equal
            printf("%s %d\n", entries[i - 1].str, distinct_count);
            distinct_count = 1;
        } else if (entries[i].id != entries[i - 1].id) {
            distinct_count++;
        }
    }
    printf("%s %d\n", entries[N - 1].str, distinct_count);

    // ---
    free(entries);
    
    return 0;
}