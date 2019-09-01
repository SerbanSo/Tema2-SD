#ifndef ADDRLIST
#define ADDRLIST

typedef struct addrList
{
    struct addrList *next;
    char *address;
} * AddrList;

AddrList initAddrList(char *buffer);

AddrList addAddrList(AddrList list, char *buffer);

void deleteAddrList(AddrList list);

#endif