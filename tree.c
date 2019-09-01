#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

//initializare arbore
Tree initTree(int n, int id, int idP, char *string)
{
    Tree new = (Tree)malloc(sizeof(struct tree));
    int i;
    char *buffer = strtok(string, " ");

    new->id = id;
    new->parent = NULL;
    new->child = NULL;
    new->sibling = NULL;
    new->nrAddresses = n;
    new->addresses = NULL;

    //introducere adrese in lista de adrese
    for (i = 0; i < new->nrAddresses; i++)
    {
        new->addresses = addAddrList(new->addresses, buffer);
        buffer = strtok(NULL, " ");
    }

    return new;
}

//cauta(recursiv) in arbore nodul cu id-ul specificat
Tree getIDNode(Tree root, int id)
{
    if (root != NULL)
    {
        //daca nodul este cel cautat il returnez
        if (root->id == id)
        {
            return root;
        }

        Tree tmp = NULL;

        //daca gasesc nodul in copil il returnez
        tmp = getIDNode(root->child, id);
        if (tmp != NULL)
        {
            return tmp;
        }

        //daca gasesc nodul in frate il returnez
        tmp = getIDNode(root->sibling, id);
        if (tmp != NULL)
        {
            return tmp;
        }
    }

    return NULL;
}

//adaugare nod deja existent(orfan)
Tree addExistingNode(Tree root, Tree node, int idP)
{
    //se cauta parintele nodului ce trebuie inserat
    Tree tmp = getIDNode(root, idP);

    //se face conexiunea intre parinte si copil
    if (tmp->child == NULL)
    {
        tmp->child = node;
        node->parent = tmp;
    }
    else
    {
        node->parent = tmp;
        tmp = tmp->child;
        while (tmp->sibling != NULL)
        {
            tmp = tmp->sibling;
        }

        tmp->sibling = node;
    }

    return root;
}

//adauga nod nou
Tree addNode(Tree root, int n, int id, int idP, char *string)
{
    Tree new = initTree(n, id, idP, string);
    Tree parent, child;

    if (idP == -1)
    {
        //daca id-ul parintelui este -1 inseamna ca nodul e radacina
        return new;
    }
    else
    {
        //se cauta parintele nodului ce trebuie inserat
        parent = getIDNode(root, idP);
        new->parent = parent;
        child = parent->child;

        //se face conexiunea intre parinte si copil
        if (child == NULL)
        {
            parent->child = new;
        }
        else
        {
            while (child->sibling != NULL)
            {
                child = child->sibling;
            }

            child->sibling = new;
        }
    }

    return root;
}

//stergere completa a arborelui
void deleteTree(Tree root)
{
    if (root != NULL)
    {
        if (root->child != NULL)
        {
            deleteTree(root->child);
        }

        if (root->sibling != NULL)
        {
            deleteTree(root->sibling);
        }

        //sterge adresele nodului curent din arbore
        deleteAddrList(root->addresses);
        free(root);
    }
}