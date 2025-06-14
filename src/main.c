#include <stdio.h>
#include "Util.h"
#include "Modules/TFTManager.h"
#include "Maths/Statistics.h"

typedef struct TestType
{
    int test1;
    char asd;
    char *qwe;
} TestType;

int main()
{
    printf("test%d\n", 31);
    float asd[] = {
        1,
        213,
        434,
        31,
        12,
        5,
        34,
        1,
        2,
    };

    printf("\n%f", Median(asd, 9));

    TFTDisplay_Create(21, 18, 22);

    while (1)
    {
    }

    return 0;
}
