#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "addrList.h"

//initializare a listei
AddrList initAddrList(char *buffer)
{
    AddrList new = (AddrList)malloc(sizeof(struct addrList));

    new->next = NULL;
    new->address = strdup(buffer);

    return new;
}

//adauga la sfarsitul listei
AddrList addAddrList(AddrList list, char *buffer)
{
    AddrList new = initAddrList(buffer);
    AddrList tmp = list;

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

//sterge intreaga lista
void deleteAddrList(AddrList list)
{
    AddrList tmp;

    while (list != NULL)
    {
        tmp = list;
        list = list->next;
        free(tmp->address);
        free(tmp);
    }
}