#include "my_set.hpp"
#include <iostream>
#include <string>
#include <algorithm>

int main() {
    MySet<int> first;
    std::cout << "first after () " << first << std::endl << std::endl;

    first.insert(33);
    std::cout << "first after insert 33 " << first << std::endl << std::endl;

    first.insert(44);
    std::cout << "first after insert 44 " << first << std::endl << std::endl;
    first.insert(33);
    std::cout << "first after insert 33 " << first << std::endl << std::endl;
    first.insert(55);
    std::cout << "first after insert 55 " << first << std::endl << std::endl;

    MySet<int> second;
    second = first;
    std::cout << "second after first copy " << second << std::endl << std::endl;

    MySet<int> third;
    third = MySet<int>(5);
    std::cout << "third after = to (5) " << third << std::endl << std::endl;

    MySet<int> forth(second);
    std::cout << "forth after 2 copy " << forth << std::endl << std::endl;
    forth = forth;
    std::cout << "forth after = to itself " << forth << std::endl << std::endl;


    MySet<int> fifth;
    for (int i = 40; i < 50; i++) {
        fifth.insert(i);
    }
    std::cout << "fifth after for " << fifth << std::endl << std::endl;

    std::cout << "union of 1 and 5 " << setUnion(first, fifth) << std::endl << std::endl;

    fifth.extend(first);
    std::cout << "fifth after extend " << fifth << std::endl << std::endl;

    first.extend(fifth);
    std::cout << "first after extend " << first << std::endl << std::endl;

    std::cout << "diff    of 1 and 2 " << setDifference(first, second)
              << std::endl << std::endl;

    first.erase(second);
    std::cout << "first after rm sec " << first << std::endl << std::endl;

    first.erase(48);
    std::cout << "first after rm 48  " << first << std::endl << std::endl;

    MySet<int> sixth;
    for (int i = 10; i < 20; i++) {
        sixth.insert(i);
    }
    std::cout << "sixth after for " << sixth << std::endl << std::endl;

    MySet<int> seventh;
    for (int i = 15; i < 25; i++) {
        seventh.insert(i);
    }
    std::cout << "seventh after for " << seventh << std::endl << std::endl;

    std::cout << "union of 6 and 7 " << setUnion(sixth, seventh) << std::endl << std::endl;
    std::cout << "diff  of 6 and 7 " << setDifference(sixth, seventh)
              << std::endl << std::endl;
    std::cout << "inter of 6 and 7 " << setIntersection(sixth, seventh)
              << std::endl << std::endl;

    return 0;
}
