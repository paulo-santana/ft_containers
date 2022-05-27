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
    println("test stack.empty()");

    ft::vector<int> vec(8, 8);
    int_stack stack;

    std::cout << "stack.empty() -> " << stack.empty() << std::endl;

    int_stack full(vec);
    std::cout << "full.empty() -> " << full.empty() << std::endl;
}

static void test_size() {
    println("test stack.size()");

    ft::vector<int> vec(8, 8);
    int_stack stack;

    std::cout << "stack.size() -> " << stack.size() << std::endl;

    int_stack full(vec);
    std::cout << "full.size() -> " << full.size() << std::endl;
}


static void test_top() {
    println("test stack.top()");

    ft::vector<int> vec;
    for (int i = 0; i < 8; i++) {
        vec.push_back(i * i);
    }

    // segfaults
    // int_stack stack;
    // std::cout << "empty.top() -> " << stack.top() << std::endl;

    int_stack full(vec);
    std::cout << "full.top() -> " << full.top() << std::endl;
}

static void test_push() {
    println("test stack.push()");

    int_stack stack;

    for (int i = 0; i < 8; i++)
    {
        stack.push(2 * i);
        std::cout << "stack.push() -> " << stack.top() << std::endl;
    }

}

static void test_pop() {
    println("test stack.pop()");

    ft::vector<int> vec;
    for (int i = 0; i < 5; i++) {
        vec.push_back(3 * i + 1);
    }

    int_stack stack(vec);

    std::cout << "stack.top() -> " << stack.top() << std::endl;
    
    while (stack.empty()) 
    {
        stack.pop();
        std::cout << "stack.pop() -> " << stack.top() << std::endl;
    }
}

void testStack() {
    test_stack_default_constructor();
    test_stack_wrapper_constructor();
    test_empty();

    test_size();
    test_top();
    test_push();
    test_pop();
}
