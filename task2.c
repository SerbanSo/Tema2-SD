#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "addrList.h"
#include "task2.h"

//se insereaza adresele copilului la parinte
void insertAddresses(Tree parent, Tree child)
{
    AddrList parentList = parent->addresses;
    AddrList childList = child->addresses;
    int i, ok, j;

    //se parcurg toate adresele copilui si sunt adaugate la adresele parintelui
    for (i = 0; i < child->nrAddresses; i++)
    {
        AddrList tmp = parentList;

        ok = 0;
        //se cauta adresa curenta a copilului in adresele parintelui
        for (j = 0; j < parent->nrAddresses; j++)
        {
            if (strcmp(childList->address, tmp->address) == 0)
            {
                ok = 1;
                break;
            }

            tmp = tmp->next;
        }

        //daca adresa nu se afla in lista parintelui, este adaugata
        if (ok == 0)
        {
            parent->nrAddresses++;
            parent->addresses = addAddrList(parent->addresses, childList->address);
        }

        childList = childList->next;
    }
}

//parcurge recursiv arborele (pentru a incepe inserarile de la copii)
//si adauga adresele copiilor la parinti
void childSearch(Tree root)
{
    if (root != NULL)
    {
        if (root->child != NULL)
        {
            childSearch(root->child);
        }

        if (root->sibling != NULL)
        {
            childSearch(root->sibling);
        }

        if (root->parent != NULL)
        {
            insertAddresses(root->parent, root);
        }
    }
}

//afisarea in fisier a nodurilor arborelui urmate de adresele sale
void printTask2(Tree root, FILE *file)
{
    if (root != NULL)
    {
        fprintf(file, "%d", root->id);
        int i;
        AddrList tmp = root->addresses;

        for (i = 0; i < root->nrAddresses; i++)
        {
            fprintf(file, " %s", tmp->address);
            tmp = tmp->next;
        }

        fprintf(file, "\n");

        if (root->child != NULL)
        {
            printTask2(root->child, file);
        }

        if (root->sibling != NULL)
        {
            printTask2(root->sibling, file);
        }
    }
}

Tree task2Main(Tree root)
{
    FILE *file = fopen("hierarchy.out", "w");

    //porneste de la fii cei mai de jos si adauga adresele la parinti
    childSearch(root);

    printTask2(root, file);

    fclose(file);
    return root;
}