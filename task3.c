#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "task3.h"
#include "addrList.h"
#define MAX 300

//citeste utilizatorii
Users *readUsers(int *n)
{
    FILE *file = fopen("users.in", "r");
    int i;

    //numarul de utilizatori
    fscanf(file, "%d", n);

    //alocare de memorie pentru utilizatori
    Users *users = (Users *)malloc((*n) * sizeof(struct users));

    //citirea fiecarui utilizator
    for (i = 0; i < *n; i++)
    {
        int id, idDNS;

        fscanf(file, "%d%d", &id, &idDNS);
        (users + i)->id = id;
        (users + i)->idDNS = idDNS;
    }

    fclose(file);
    return users;
}

//sterge serverul DNS picat din arbore
Tree deleteNode(Tree root, int id)
{
    Tree node = getIDNode(root, id);
    Tree parent = node->parent;
    Tree children = node->child;
    Tree lastChild = parent->child;

    //adaugare copii la parinte
    while (lastChild->sibling != NULL)
    {
        lastChild = lastChild->sibling;
    }
    lastChild->sibling = children;

    //eliminare nod din copiii parintelui
    if (parent->child->id == id)
    {
        parent->child = parent->child->sibling;
    }
    else
    {
        lastChild = parent->child;

        while (lastChild->sibling->id != id)
        {
            lastChild = lastChild->sibling;
        }
        lastChild->sibling = lastChild->sibling->sibling;
    }

    //schimbare parinte pentru copii
    while (children != NULL)
    {
        children->parent = parent;
        children = children->sibling;
    }

    deleteAddrList(node->addresses);
    free(node);
    return root;
}

Tree requests(Tree root, Users *users, int n, FILE *file, FILE *output)
{
    int nrQueries;
    int i, j, id, found;
    char c, buffer[MAX];
    Tree search;

    //numarul cererilor din partea utilizatorilor
    fscanf(file, "%d", &nrQueries);
    fgetc(file); // elimina '\n' de la sfarsitul randului

    for (i = 0; i < nrQueries; i++)
    {
        fscanf(file, "%c%d", &c, &id);

        //elimina ' ' in cazul 'q' sau '\n' in cazul 'f'
        fgetc(file);

        //daca este cerere de la utilizator
        if (c == 'q')
        {
            fgets(buffer, MAX, file);
            buffer[strlen(buffer) - 1] = '\0';

            //stabileste id-ul DNS-ului corespunzator utilizatorului
            for (j = 0; j < n; j++)
            {
                if ((users + j)->id == id)
                {
                    id = (users + j)->idDNS;
                    break;
                }
            }

            Tree tmp3 = root;
            search = getIDNode(root, id);
            found = 0;

            //cat timp nu se gaseste adresa in serverul DNS curent
            while (found == 0)
            {
                fprintf(output, "%d", search->id);
                AddrList tmp = search->addresses;

                //se cauta in adresa ceruta
                for (j = 0; j < search->nrAddresses; j++)
                {
                    if (strcmp(tmp->address, buffer) == 0)
                    {
                        found = 1;
                        fprintf(output, "\n");
                        break;
                    }

                    tmp = tmp->next;
                }

                //daca adresa nu se afla in serverul DNS curent, este adaugata
                if (found == 0)
                {
                    //spatiul dupa fiecare caracter
                    fprintf(output, " ");

                    search->nrAddresses++;
                    search->addresses = addAddrList(search->addresses, buffer);
                }

                search = search->parent;
            }
        }
        else if (c == 'f') //daca serverul pica (pentru Bonus)
        {
            search = getIDNode(root, id);

            //daca nodul nu este deja picat
            if (search != NULL)
            {
                for (j = 0; j < n; j++)
                {
                    //daca pica serverul DNS schimb idDNS cu cel al parintelui
                    if ((users + j)->idDNS == id)
                    {
                        (users + j)->idDNS = search->parent->id;
                    }
                }

                //sterge serverul DNS picat din arbore
                root = deleteNode(root, id);
            }
        }
    }

    return root;
}

Tree task3Main(Tree root)
{
    int n, i;
    FILE *file = fopen("queries.in", "r");
    FILE *output = fopen("queries.out", "w");
    Users *users = readUsers(&n);

    root = requests(root, users, n, file, output);

    fclose(file);
    fclose(output);

    //eliberare memorie pentru users
    free(users);

    return root;
}