#include "my_set.hpp"
#include <iostream>
#include <string>
#include <algorithm>

int main() {
    MySet<int> first;
    std::cout << "first " << first << std::endl;

    first.insert(33);
    std::cout << "first " << first << std::endl;

    first.insert(44);
    first.insert(33);
    std::cout << "first " << first << std::endl;

    return 0;
}
