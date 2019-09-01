#ifndef TASK1
#define TASK1
#include "tree.h"
#include "waitList.h"

Tree addOrphan(Tree root, WaitList waitList, int idP, char *buffer);

void printChildren(Tree root, FILE *file);

void printTask1(Tree root, FILE *file);

Tree task1Main();

#endif