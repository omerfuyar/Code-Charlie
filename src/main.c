#include <stdio.h>
#include "Util.h"
#include "Modules/TFTManager.h"

typedef struct TestType
{
    int test1;
    char asd;
    char *qwe;
} TestType;

int main()
{
    printf("test%d", 31);

    TFTDisplay_Create(21, 18, 22);

    while (1)
    {
    }

    return 0;
}
