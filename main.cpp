#include <iostream>
#include <algorithm>
#include <sstream>

#include "tests/tests.hpp"

#ifndef REAL_STD
# define REAL_STD 0
#endif // !REAL_STD

#if REAL_STD //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	// #include <map.hpp>
	// #include <stack.hpp>
	#include <vector>
	#include <vector.hpp>
#endif

int main (void)
{
    if (REAL_STD)
        std::cout << "STD containers" << std::endl;
    else
        std::cout << "FT containers" << std::endl;

    testVector();
}
