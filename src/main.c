#include <stdio.h>
#include "Util.h"

int main()
{
    LinkedList *myList = LinkedList_Create(sizeof(int));

    int data = 10;
    LinkedList_Add(myList, &data);

    while (1)
    {
    }

    return 0;
}