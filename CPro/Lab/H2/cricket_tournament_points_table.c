#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    char name[21];
    int P, W, L, T;

    int pts;
    float NRR;

    int _runs_scored, _runs_conceded;
    float _overs_faced, _overs_bowled;
} Team;

int find_team(Team *teams, int team_count, char *team_name) {
    for (int i = 0; i < team_count; i++) {
        if (strcmp(teams[i].name, team_name) == 0) return i;
    }
    return -1;
}

int cmp_float(float a, float b) {
    if (fabs(a - b) < 1e-9) return 0;
    else return (a > b) - (a < b);
}

int cmp_team(const void *a, const void *b) {
    const Team *team_a = a;
    const Team *team_b = b;

    if (team_a->pts != team_b->pts) return team_b->pts - team_a->pts;

    int nrr_cmp = cmp_float(team_a->NRR, team_b->NRR);
    if (nrr_cmp != 0) return -nrr_cmp;

    return strcmp(team_a->name, team_b->name);
}

int main(void) {
    int M;
    scanf("%d", &M);

    int team_count = 0;
    Team teams[100] = {0};

    char team_a[21];
    char team_b[21];
    int runs_a, runs_b;
    int overs_a, overs_b;
    int balls_a, balls_b;
    for (int i = 0; i < M; i++) {
        scanf("%s %d %d.%d %s %d %d.%d",
            team_a, &runs_a, &overs_a, &balls_a,
            team_b, &runs_b, &overs_b, &balls_b
        );

        int idx_a = find_team(teams, team_count, team_a);
        int idx_b = find_team(teams, team_count, team_b);

        if (idx_a == -1) {
            strcpy(teams[team_count].name, team_a);
            idx_a = team_count;
            team_count++;
        }
        if (idx_b == -1) {
            strcpy(teams[team_count].name, team_b);
            idx_b = team_count;
            team_count++;
        }

        float actual_overs_a = overs_a + (float)balls_a / 6.f;  // 6. -> double, 6.f -> float
        float actual_overs_b = overs_b + (float)balls_b / 6.f;

        teams[idx_a].P++;
        teams[idx_b].P++;

        teams[idx_a]._runs_scored += runs_a;
        teams[idx_a]._overs_faced += actual_overs_a;
        teams[idx_a]._runs_conceded += runs_b;
        teams[idx_a]._overs_bowled += actual_overs_b;
        
        teams[idx_b]._runs_scored += runs_b;
        teams[idx_b]._overs_faced += actual_overs_b;
        teams[idx_b]._runs_conceded += runs_a;
        teams[idx_b]._overs_bowled += actual_overs_a;

        if (runs_a > runs_b) {
            teams[idx_a].W++;
            teams[idx_b].L++;
        } else if (runs_a < runs_b) {
            teams[idx_a].L++;
            teams[idx_b].W++;
        } else {
            teams[idx_a].T++;
            teams[idx_b].T++;
        }
    }

    for (int i = 0; i < team_count; i++) {
        teams[i].pts = teams[i].W * 2 + teams[i].T * 1;
        teams[i].NRR = (teams[i]._runs_scored / teams[i]._overs_faced) - (teams[i]._runs_conceded / teams[i]._overs_bowled);
    }

    qsort(teams, team_count, sizeof(Team), cmp_team);
    
    printf("Team P W L T Pts NRR\n");
    for (int i = 0; i < team_count; i++) {
        const Team t = teams[i];
        printf("%s %d %d %d %d %d %+.3f\n",
            t.name,
            t.P, t.W, t.L, t.T,
            t.pts,
            t.NRR
        );
    }

    return 0;
}