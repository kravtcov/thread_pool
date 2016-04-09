#include "my_set.hpp"
#include <iostream>
#include <string>
#include <algorithm>

int main() {
    MySet<int> first;
    std::cout << "first after () " << first << std::endl << std::endl;

    first.insert(33);
    std::cout << "first after 33 " << first << std::endl << std::endl;

    first.insert(44);
    std::cout << "first after 44 " << first << std::endl << std::endl;
    first.insert(33);
    std::cout << "first after 33 " << first << std::endl << std::endl;
    first.insert(55);
    std::cout << "first after 55 " << first << std::endl << std::endl;

    return 0;
}
