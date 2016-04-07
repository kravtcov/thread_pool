#include "my_set.hpp"
#include <iostream>
#include <string>
#include <algorithm>

int main() {
    // default constructor
    MySet<int> first(1);

    // default constructor
    MySet<int> second = MySet<int>(2);

    // move constructor
    MySet<int> third = std::move(MySet<int>(3));

    // copy constructor
    MySet<int> forth(third);

    // copy assignment operator
    first = forth;

    // move assignment operator
    second = getSet<int>();

    std::cout << "first  size is " << first.getSize() << std::endl;
    std::cout << "second size is " << second.getSize() << std::endl;
    std::cout << "third  size is " << third.getSize() << std::endl;
    std::cout << "forth  size is " << forth.getSize() << std::endl;

    return 0;
}
