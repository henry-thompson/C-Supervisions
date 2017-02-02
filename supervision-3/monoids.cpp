#include "monoids.hpp"
#include <iostream>
#include <vector>

using namespace ht367::monoids;

void testIntAddConcat() 
{
    intAddMonoid_t int1AddMonoid(1);
    intAddMonoid_t int2AddMonoid(2);
    intAddMonoid_t int3AddMonoid(3);

    std::vector<intAddMonoid_t> monoids(0);
    monoids.push_back(int1AddMonoid);
    monoids.push_back(int2AddMonoid);
    monoids.push_back(int3AddMonoid);

    std::cout << "1 + 2 + 3 = " << concat(monoids).getValue() << std::endl; 
}

void testIntMultiplyConcat() 
{
    intMultMonoid_t int3AddMonoid(3);
    intMultMonoid_t int4AddMonoid(4);
    intMultMonoid_t int5AddMonoid(5);

    std::vector<intMultMonoid_t> monoids(0);
    monoids.push_back(int3AddMonoid);
    monoids.push_back(int4AddMonoid);
    monoids.push_back(int5AddMonoid);

    std::cout << "3 * 4 * 5 = " << concat(monoids).getValue() << std::endl; 
}

int main() {
    testIntAddConcat();
    testIntMultiplyConcat();

    return 0;
}