#include "my_set.hpp"
#include <iostream>
#include <string>

int main() {
    MySet<int> first(5);
    MySet<int> second = MySet<int>(5);
    MySet<int> third = getSet<int>();
    MySet<int> forth(third);
    first = forth;
    std::cout << "first  size is " << first.getSize() << std::endl;
    std::cout << "second size is " << second.getSize() << std::endl;
    std::cout << "third  size is " << third.getSize() << std::endl;
    std::cout << "forth  size is " << forth.getSize() << std::endl;

    return 0;
}
