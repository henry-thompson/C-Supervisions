#include <iostream>

int main()
{
    int i = 0;
    int a = i++ + ++i;

    std::cout << a << std::endl;
    return 0;
}