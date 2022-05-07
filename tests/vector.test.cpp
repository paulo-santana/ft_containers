#include <iostream>
#include <algorithm>
#include <memory>
#include <sstream>

#include "test_utils.hpp"

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

void test_vector_default_constructor(void) {
    println("\ntest vector default constructor");
    ft::vector<int> *vector1 = new ft::vector<int>();
    delete vector1;
}

void test_vector_allocator_constructor(void) {
    println("\ntest vector allocator constructor");

    class my_alloc: public std::allocator<int> { };

    my_alloc alloc;

    ft::vector<int> vector1(alloc);
    std::vector<int> vector2(alloc);

}

void test_vector_allocator(void) {
    println("\ntest vector default allocator");
    ft::vector<int> vector1;
    std::vector<int> vector2;

    std::allocator<int> a = vector1.get_allocator();
    std::allocator<int> b = vector2.get_allocator();

    assertEquals(a, b, "allocator1 == allocator2");
}

void test_vector_push_back(void) {
    println("\ntest vector.push_back()");
    ft::vector<int> vector1;
    std::vector<int> vector2;

    int size1, size2;
    int capacity1, capacity2;

    for (int i = 0; i < 4; i++) {
        size1 = vector1.size();
        size2 = vector2.size();
        assertEquals(size1, size2, "size1 == size2");
        capacity1 = vector1.capacity();
        capacity2 = vector2.capacity();
        assertEquals(capacity1, capacity2, "capacity1 == capacity2");
        vector1.push_back(20 - i);
        vector2.push_back(20 - i);
    }

    int *addr1 = &*vector1.begin();
    int *addr2 = &*vector2.begin();

    println("int *addr1 = &*vector1.begin();");
    println("int *addr2 = &*vector2.begin();");
    assertEquals(*addr1++, *addr2++, "*addr1++ == *addr2++");
    assertEquals(*addr1++, *addr2++, "*addr1++ == *addr2++");
    assertEquals(*addr1++, *addr2++, "*addr1++ == *addr2++");
}

void test_vector_max_size(void) {
    println("\ntest vector.max_size()");

    ft::vector<int> vect;
    std::cout << "vect.max_size(): " << vect.max_size() << std::endl;

    ft::vector<std::string> str_vect;
    std::cout << "vect.max_size(): " << str_vect.max_size() << std::endl;
}

void test_vector_n_constructor(void) {
    println("\ntest vector<int>(17)");

    ft::vector<int> vect(17);
    std::cout << "vect.size(): " << vect.size() << std::endl;
    std::cout << "vect.capacity(): " << vect.capacity() << std::endl;

    println("\ntest vector<string>(80)");
    ft::vector<std::string> str_vect(80);
    std::cout << "vect.size(): " << str_vect.size() << std::endl;
    std::cout << "vect.capacity(): " << str_vect.capacity() << std::endl;
}

void test_vector_n_and_type_constructor(void) {
    println("\ntest vector<int>(3, 80)");

    ft::vector<int> vect(3, 80);
    std::cout << "vect.size(): " << vect.size() << std::endl;
    std::cout << "vect.capacity(): " << vect.capacity() << std::endl;

    int* it = &*vect.begin();
    for (int i = 0; i < 3; i++) {
        std::cout << *it++ << ", ";
    }
    std::cout << std::endl;

    println("\ntest vector<int>(3, 80)");

    ft::vector<std::string> str_vect(5, "default");
    std::cout << "vect.size(): " << str_vect.size() << std::endl;
    std::cout << "vect.capacity(): " << str_vect.capacity() << std::endl;

    std::string* sit = &*str_vect.begin();
    for (int i = 0; i < 5; i++) {
        std::cout << *sit++ << ", ";
    }
    std::cout << std::endl;
}

void testVector(void) {
    ft::vector<int> vector1 = ft::vector<int>();
    std::vector<int> vector2 = std::vector<int>();
    assertEquals(vector1.size(), vector2.size(), "vector.size() == 0");

    test_vector_default_constructor();
    test_vector_allocator_constructor();
    test_vector_allocator();
    test_vector_push_back();
    test_vector_max_size();
    test_vector_n_constructor();
    test_vector_n_and_type_constructor();
}
