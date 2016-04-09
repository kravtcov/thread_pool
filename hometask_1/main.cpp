#include "my_set.hpp"
#include <iostream>
#include <string>
#include <algorithm>

int main() {
    MySet<int> first;
    first.insert(33);
    first.insert(44);
    first.insert(33);

    std::cout << "first size is " << first.getSize() << std::endl;

    return 0;
}
