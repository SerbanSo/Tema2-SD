#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"

int main()
{
    Tree root;
    
    //Task 1
    root = task1Main();

    //Task 2
    root = task2Main(root);

    //Task 3 + Bonus
    root = task3Main(root);

    //eliberare memorie arbore
    deleteTree(root);

    return 0;
}