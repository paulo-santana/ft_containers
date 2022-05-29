#include <map>
#include <iostream>
#include <utility>

#if REAL_STD
    namespace ft = std;
#endif

void testMap() {
    std::map<int, int> map;

    map.insert(std::make_pair(1, 3));
    
    std::map<int, int>::iterator begin = map.begin();
    int first = begin->first;
    int second = begin->second;

    if (first == second) {
        std::cout << "true? " << true << std::endl;
    }
}
