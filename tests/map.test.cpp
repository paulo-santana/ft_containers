#include <map>
#include <iostream>
#include <utility>

#if REAL_STD
    namespace ft = std;
#endif

void testMap() {
    std::map<int, std::string> map;

    map.insert(std::make_pair(1, "empty"));
    
    std::map<int, std::string>::iterator begin = map.begin();
    // int first = begin->first;
    std::string second = begin->second;
    std::pair<const int, std::string> p = *begin;

    second = p.second;

    // if (first == second) {
    //     std::cout << "true? " << true << std::endl;
    // }
}
