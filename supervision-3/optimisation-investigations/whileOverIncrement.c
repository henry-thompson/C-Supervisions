#include <stdio.h>

int main()
{
    int i = __INT_MAX__;
    while (i++) printf("%d\n", i);

    return 0;
}