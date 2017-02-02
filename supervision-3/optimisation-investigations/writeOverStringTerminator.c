#include <stdio.h>

int main()
{
    char c1[2] = "x";
    char c2[3] = "ho";
    c1[1] = 'y';
    printf("%s\n", c1);
    return 0;
}