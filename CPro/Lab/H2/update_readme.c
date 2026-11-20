#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[21];
    int proj;
    int points;
} Entry;

typedef struct {
    char name[21];
    int n_proj;
    int total_pts;
} Entry2;

int cmp(const void *x, const void *y) {
    const Entry *a = x;
    const Entry *b = y;

    int alpha_order = strcmp(a->name, b->name); 

    if (alpha_order != 0) return alpha_order;               // different name
    else if (a->proj != b->proj) return a->proj - b->proj;  // same name, different project
    else return a->points - b->points;                      // same name and project, different points
}

int cmp2(const void *x, const void *y) {
    const Entry2 *a = x;
    const Entry2 *b = y;

    if (a->total_pts != b->total_pts) return b->total_pts - a->total_pts;  // different points
    else if (a->n_proj != b->n_proj) return a->n_proj - b->n_proj;         // same points, different number of projects
    else return strcmp(a->name, b->name);                                  // same points and projects, different name
}

int main(void) {
    int N;
    scanf("%d", &N);

    Entry entries[100000];
    for (int i = 0; i < N; i++) {
        scanf("%s %d %d",
            entries[i].name,
            &entries[i].proj,
            &entries[i].points
        );
    }

    qsort(entries, N, sizeof(Entry), cmp);

    // count distinct people
    int n_distinct_ppl = 1;
    for (int i = 1; i < N; i++) {
        if (strcmp(entries[i].name, entries[i - 1].name) != 0) n_distinct_ppl++;
    }
    printf("%d\n", n_distinct_ppl);

    // generating new entries
    int x = 0;
    Entry2 entries2[n_distinct_ppl];

    int n_proj = 1;
    int total = 0;

    for (int i = 1; i < N; i++) {
        if (strcmp(entries[i].name, entries[i - 1].name) != 0) {  // new person
            total += entries[i - 1].points;

            entries2[x] = (Entry2){
                .n_proj = n_proj,
                .total_pts = total
            };
            strcpy(entries2[x].name, entries[i - 1].name);
            x++;

            n_proj = 1;
            total = 0;
        } else if (entries[i].proj != entries[i - 1].proj) {  // new project
            total += entries[i - 1].points;
            n_proj++;
        }
    }
    total += entries[N - 1].points;
    entries2[n_distinct_ppl - 1] = (Entry2){
        .n_proj = n_proj,
        .total_pts = total
    };
    strcpy(entries2[n_distinct_ppl - 1].name, entries[N - 1].name);

    // sort final entries
    qsort(entries2, n_distinct_ppl, sizeof(Entry2), cmp2);

    // output
    for (int i = 0; i < n_distinct_ppl; i++) {
        printf("%s %d %d\n",
            entries2[i].name,
            entries2[i].total_pts,
            entries2[i].n_proj
        );
    }

    return 0;
}