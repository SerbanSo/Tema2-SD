#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task1.h"
#define MAX 500

//adauga in arbore orfanii
Tree addOrphan(Tree root, WaitList waitList, int idP, char *buffer)
{
    WaitList list = waitList;

    while (list != NULL)
    {
        if (list->idParent == idP)
        {
            //adauga orfanul in arbore
            root = addExistingNode(root, list->node, idP);

            //dupa ce adauga un orfan adauga si copii acestuia (tot orfani)
            root = addOrphan(root, waitList, list->node->id, buffer);
        }

        list = list->next;
    }

    return root;
}

//printeaza in fisier copiii unui parinte
void printChildren(Tree root, FILE *file)
{
    if (root->child != NULL)
    {
        root = root->child;

        while (root != NULL)
        {
            fprintf(file, " %d", root->id);
            root = root->sibling;
        }
    }
}

//parcurge recursiv arborele si printeaza in fisier parintii urmati de copii
void printTask1(Tree root, FILE *file)
{
    if (root != NULL)
    {
        fprintf(file, "%d", root->id);

        printChildren(root, file);

        fprintf(file, "\n");

        if (root->child != NULL)
        {
            root = root->child;
            printTask1(root, file);

            while (root->sibling != NULL)
            {
                printTask1(root->sibling, file);
                root = root->sibling;
            }
        }
    }
}

Tree task1Main()
{
    FILE *file = fopen("tree.in", "r");
    FILE *output = fopen("tree.out", "w");
    Tree root = NULL;
    WaitList waitList = NULL;
    int i, n, id, idParent, nrAddres;
    char buffer[MAX];

    //numarul de servere DNS
    fscanf(file, "%d", &n);

    for (i = 0; i < n; i++)
    {
        fscanf(file, "%d%d%d", &id, &idParent, &nrAddres);
        fgetc(file); // elimina spatiul ramas intre nr de adrese si adrese
        fgets(buffer, MAX, file);

        //elimina '\n' din buffer
        buffer[strlen(buffer) - 1] = '\0';

        //daca parintele nodului citit nu exista
        if (idParent != -1 && getIDNode(root, idParent) == NULL)
        {
            //initializez nodul si il introduc in lista de asteptare
            Tree tmp = initTree(nrAddres, id, idParent, buffer);

            //lista de asteptare a nodurilor orfane
            waitList = addWaitList(waitList, tmp, idParent);
        }
        else
        {
            //introduc nodul in arbore
            root = addNode(root, nrAddres, id, idParent, buffer);

            //se verifica daca nodul nou introdus este tatal vreunui nod orfan
            root = addOrphan(root, waitList, id, buffer);
        }
    }

    printTask1(root, output);
    fclose(output);

    fclose(file);
    deleteWaitList(waitList);
    return root;
}