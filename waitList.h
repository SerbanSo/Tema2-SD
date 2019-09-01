#ifndef WAITLIST
#define WAITLIST
#include "tree.h"

typedef struct waitList
{
    struct tree *node;
    struct waitList *next;

    int idParent;
} * WaitList;

WaitList initWaitList(Tree node, int idParent);

WaitList addWaitList(WaitList list, Tree node, int idParent);

void deleteWaitList(WaitList waitList);

#endif