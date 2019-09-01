#ifndef TREE
#define TREE
#include "addrList.h"

typedef struct tree
{
    struct tree *parent;
    struct tree *child;
    struct tree *sibling;
    AddrList addresses;

    int id;
    int nrAddresses;

} * Tree;

Tree initTree(int n, int id, int idP, char *string);

Tree getIDNode(Tree root, int id);

Tree addExistingNode(Tree root, Tree node, int idP);

Tree addNode(Tree root, int n, int id, int idP, char *string);

void deleteTree(Tree root);

#endif