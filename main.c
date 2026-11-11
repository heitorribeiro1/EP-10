#include "team.h"
#include "teamlist.h"
#include <stdio.h>

static int utf8_continuation_bytes(const char *s) {
    int n = 0;
    for (const unsigned char *p = (const unsigned char *)s; *p; p++)
        if ((*p & 0xC0) == 0x80)
            n++;
    return n;
}

int main(void) {
    FILE *f = fopen("teams.csv", "rt");
    if (f == NULL)
        return 1;

    TeamList *tl = tl_create();

    int id;
    char name[50];
    while (fscanf(f, "%d,%49[^\n]", &id, name) == 2) {
        Team *t = team_create(id, name);
        tl_append(tl, t);
    }
    fclose(f);

    printf("ID  Time            V   E   D   GM  GS  S   PG\n");
    for (int i = 0; i < tl_size(tl); i++) {
        Team *t = tl_get(tl, i);
        int goal_diff = team_goals_scored(t) - team_goals_conceded(t);
        int points = 3 * team_wins(t) + team_draws(t);
        printf("%-3d %-15s", team_id(t), team_name(t));
        for (int j = 0; j < utf8_continuation_bytes(team_name(t)); j++)
            putchar(' ');
        printf(" %-3d %-3d %-3d %-3d %-3d %-3d %-3d\n",
               team_wins(t), team_draws(t), team_losses(t),
               team_goals_scored(t), team_goals_conceded(t),
               goal_diff, points);
    }

    tl_free(tl);
    return 0;
}
