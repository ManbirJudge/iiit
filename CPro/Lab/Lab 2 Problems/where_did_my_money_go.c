#include <stdio.h>

int main(void) {
    int N, M, L, X;
    scanf("%d", &N);
    int jc_items[N];
    for (int i = 0; i < N; i++) scanf("%d", jc_items + i); 
    scanf("%d", &M);
    int vc_items[M];
    for (int i = 0; i < M; i++) scanf("%d", vc_items + i); 
    scanf("%d", &L);
    int m_items[L];
    for (int i = 0; i < L; i++) scanf("%d", m_items + i);
    scanf("%d", &X);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < L; k++) {
                if (jc_items[i] + vc_items[j] + m_items[k] == X) {
                    printf("Yes\n");
                    return 0;
                }
            }
        }
    }

    printf("No\n");
    return 0;
}