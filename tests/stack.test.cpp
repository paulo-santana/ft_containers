#include <stack>
#include "test_utils.hpp"

#if REAL_STD //CREATE A REAL STL EXAMPLE
	namespace ft = std;
#else
	#include <stack.hpp>
#endif

static void test_stack_default_constructor() {
    println("test stack default constructor");

    ft::stack<int> stack;

    std::cout << "stack.size(): " << stack.size() << std::endl;

}

void testStack() {
    test_stack_default_constructor();

}
