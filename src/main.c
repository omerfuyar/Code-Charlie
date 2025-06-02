#include <stdio.h>
#include "Util.h"

typedef struct TestType
{
    int test1;
    char asd;
    char *qwe;
} TestType;

int main()
{
    ArrayList *myList = ArrayList_Create(sizeof(TestType *), 10);

    TestType dataO;
    TestType *data = &dataO;
    data->qwe = "asd";
    data->asd = 'q';
    ArrayList_Add(myList, data);

    printf("test char : %c\n", (*(TestType *)ArrayList_Get(myList, 0)).asd);
    (*(TestType *)ArrayList_Get(myList, 0)).asd = 'w';
    printf("test char : %c\n", (*(TestType *)ArrayList_Get(myList, 0)).asd);

    while (1)
    {
    }

    return 0;
}