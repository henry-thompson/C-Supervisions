#include "factorial.hpp"
#include <iostream>

int main() {
    std::cout << "Factorial 0: " << ht367::Factorial<0>::FACTORIAL << std::endl;
    std::cout << "Factorial 1: " << ht367::Factorial<1>::FACTORIAL << std::endl;
    std::cout << "Factorial 4: " << ht367::Factorial<4>::FACTORIAL << std::endl;
}