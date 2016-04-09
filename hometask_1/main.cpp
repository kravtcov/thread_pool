#include "my_set.hpp"
#include <iostream>
#include <string>
#include <algorithm>

int main() {
    MySet<int> first;
    first.append(33);
    first.append(44);
    first.append(33);

    std::cout << "first size is " << first.getSize() << std::endl;

    return 0;
}
