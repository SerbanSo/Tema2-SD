#ifndef TASK3
#define TASK3
#include "tree.h"

typedef struct users
{
    int id;
    int idDNS;
} Users;

Users *readUsers(int *n);

Tree deleteNode(Tree root, int id);

Tree requests(Tree root, Users *users, int n, FILE *file, FILE *output);

Tree task3Main(Tree root);

#endif