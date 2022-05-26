#include <vector>
#include <stack>
#include "test_utils.hpp"

#if REAL_STD //CREATE A REAL STL EXAMPLE
	namespace ft = std;
#else
	#include <stack.hpp>
#endif

typedef ft::stack<int, ft::vector<int> > int_stack;
typedef ft::stack<std::string, ft::vector<std::string> > string_stack;

static void test_stack_default_constructor() {
    println("test stack default constructor");

    int_stack stack;

    std::cout << "stack.size(): " << stack.size() << std::endl;

}

static void test_stack_wrapper_constructor() {
    println("test stack wrapper constructor");

    ft::vector<int> vec(3, 2);
    int_stack stack(vec);

    std::cout << "stack.size(): " << stack.size() << std::endl;
}

static void test_empty() {
    println("test vector.empty()");

    ft::vector<int> vec(8, 8);
    int_stack stack;

    std::cout << "stack.empty() -> " << stack.empty() << std::endl;

    int_stack full(vec);
    std::cout << "full.empty() -> " << full.empty() << std::endl;
}

static void test_size() {
    println("test vector.empty()");

    ft::vector<int> vec(8, 8);
    int_stack stack;

    std::cout << "stack.size() -> " << stack.size() << std::endl;

    int_stack full(vec);
    std::cout << "full.size() -> " << full.size() << std::endl;
}

void testStack() {
    test_stack_default_constructor();
    test_stack_wrapper_constructor();
    test_empty();

    test_size();
}
