#include <iostream>

struct pair
{
    int x;
    int y;
};

pair f(int x, int y)
{
    pair p = { .x = x, .y = y };
    return p;
}

int main()
{
    int i = 0;
    pair p = f(i++, i++);

    std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
}