#include "teamlist.h"
#include <stdlib.h>

typedef struct node {
    Team *team;
    struct node *next;
    struct node *prev;
} Node;

struct teamlist {
    Node *first;
    Node *last;
    int size;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(TeamList));
    tl->first = NULL;
    tl->last = NULL;
    tl->size = 0;
    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    Node *n = malloc(sizeof(Node));
    n->team = t;
    n->next = NULL;
    n->prev = tl->last;
    if (tl->last != NULL)
        tl->last->next = n;
    else
        tl->first = n;
    tl->last = n;
    tl->size++;
}

int tl_size(TeamList *tl) {
    return tl->size;
}

Team *tl_get(TeamList *tl, int i) {
    Node *n = tl->first;
    for (int k = 0; k < i; k++)
        n = n->next;
    return n->team;
}

void tl_free(TeamList *tl) {
    Node *n = tl->first;
    while (n != NULL) {
        Node *next = n->next;
        team_free(n->team);
        free(n);
        n = next;
    }
    free(tl);
}
