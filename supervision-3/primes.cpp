#include <iostream>
#include "primes.hpp"

int main()
{
    std::cout << "1 is prime: " << ht367::IsPrime<1>::ISPRIME << std::endl;
    std::cout << "2 is prime: " << ht367::IsPrime<2>::ISPRIME << std::endl;
    std::cout << "3 is prime: " << ht367::IsPrime<3>::ISPRIME << std::endl;
    std::cout << "811 is prime: " << ht367::IsPrime<811>::ISPRIME << std::endl;
}