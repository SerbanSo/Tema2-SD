#include <stdio.h>
#include <stdlib.h>
#include "waitList.h"

//initializare lista de asteptare
WaitList initWaitList(Tree node, int idParent)
{
    WaitList new = (WaitList)malloc(sizeof(struct waitList));

    new->node = node;
    new->idParent = idParent;
    new->next = NULL;

    return new;
}

//adauga la sfarsitul listei de asteptare
WaitList addWaitList(WaitList list, Tree node, int idParent)
{
    WaitList new = initWaitList(node, idParent);
    WaitList tmp = list;

    if (list == NULL)
    {
        return new;
    }

    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = new;

    return list;
}

//sterge toata lista de asteptare
void deleteWaitList(WaitList waitList)
{
    WaitList tmp;

    while (waitList != NULL)
    {
        tmp = waitList;
        waitList = waitList->next;
        free(tmp);
    }
}