#include "teamlist.h"
#include <stdlib.h>

struct teamlist {
    int size;
    int capacity;
    Team **data;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(TeamList));
    tl->size = 0;
    tl->capacity = 4;
    tl->data = malloc(tl->capacity * sizeof(Team *));
    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    if (tl->size == tl->capacity) {
        tl->capacity *= 2;
        tl->data = realloc(tl->data, tl->capacity * sizeof(Team *));
    }
    tl->data[tl->size++] = t;
}

int tl_size(TeamList *tl) {
    return tl->size;
}

Team *tl_get(TeamList *tl, int i) {
    return tl->data[i];
}

void tl_free(TeamList *tl) {
    for (int i = 0; i < tl->size; i++)
        team_free(tl->data[i]);
    free(tl->data);
    free(tl);
}
