#include "test_utils.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

#if REAL_STD //CREATE A REAL STL EXAMPLE
	namespace ft = std;
#else
	// #include <map.hpp>
	// #include <stack.hpp>
	#include <vector.hpp>
#endif

static void test_default_constructor(void) {
    println("\ntest vector default constructor");
    ft::vector<int> *vector1 = new ft::vector<int>();
    delete vector1;
}

static void test_allocator_constructor(void) {
    println("\ntest vector allocator constructor");

    class my_alloc: public std::allocator<int> { };

    my_alloc alloc;

    ft::vector<int> vector1(alloc);

}

template <typename T>
std::ostream& operator<<(std::ostream& out, const ft::vector<T>& vec)
{
    out << "[ ";
    typename ft::vector<T>::const_iterator it;
    for (it = vec.begin(); it < vec.end() - 1; it++) {
        out << *it << ", ";
    }
    out << *it << " ]" << std::endl;
    return out;
}

static void test_fill_constructor() {
    println("\ntest vector fill constructor");

    ft::vector<int> vec(3);
    std::cout << "ft::vector<int> vec(3)" << std::endl;
    std::cout << vec << std::endl;

    ft::vector<int> vec2(3, 4);
    std::cout << "ft::vector<int> vec(3, 4)" << std::endl;
    std::cout << vec2 << std::endl;
}

static void test_allocator(void) {
    println("\ntest vector default allocator");

    ft::vector<int> vector1;

    std::allocator<int> a = vector1.get_allocator();

    std::cout << "typeid(vector1.get_allocator()) == " << typeid(a).name() << std::endl;
}

static void test_push_back(void) {
    println("\ntest vector.push_back()");
    ft::vector<int> vect;

    for (int i = 0; i < 4; i++) {
        std::cout << "vect.size() == " << vect.size() << std::endl;
        std::cout << "vect.capacity() == " << vect.capacity() << std::endl;
        vect.push_back(20 - i);
    }

    int *addr = &*vect.begin();

    println("int *addr = &*vector1.begin();");

    std::cout << "*addr++ == " << *addr++ << ", ";
    std::cout << "*addr++ == " << *addr++ << ", ";
    std::cout << "*addr++ == " << *addr++ << std::endl;
}

static void test_max_size(void) {
    println("\ntest vector.max_size()");

    ft::vector<int> vect;
    std::cout << "vect.max_size(): " << vect.max_size() << std::endl;

    ft::vector<std::string> str_vect;
    std::cout << "vect.max_size(): " << str_vect.max_size() << std::endl;
}

static void test_n_constructor(void) {
    println("\ntest vector<int>(17)");

    ft::vector<int> vect(17);
    std::cout << "vect.size(): " << vect.size() << std::endl;
    std::cout << "vect.capacity(): " << vect.capacity() << std::endl;

    println("\ntest vector<string>(80)");
    ft::vector<std::string> str_vect(80);
    std::cout << "vect.size(): " << str_vect.size() << std::endl;
    std::cout << "vect.capacity(): " << str_vect.capacity() << std::endl;
}

static void test_n_and_type_constructor(void) {
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

static void test_const_iterator() {
    ft::vector<int> powers(6);
    ft::vector<float> fpowers(6);
    for (int i = 0; i < 6; i++) {
        powers.push_back(i * i);
    }
    ft::vector<int>::iterator it = powers.begin();
    ft::vector<int>::const_iterator const_it = powers.begin();
    ft::vector<float>::const_iterator const_float_it = fpowers.begin();
    const_it = it;

    (void)const_float_it;
    // shouldn't compile
    // const_float_it = const_it;
}

static void test_end() {
    ft::vector<int> powers(6);
    ft::vector<int>::iterator it = powers.begin();
    ft::vector<int>::iterator end = powers.end();

    long size = end - it;

    std::cout << "end - it == " << size << std::endl;
}

static void test_const_end() {
    ft::vector<int> powers(6);
    ft::vector<int>::const_iterator it = powers.begin();
    ft::vector<int>::const_iterator end = powers.end();

    long size = end - it;

    std::cout << "end - it == " << size << std::endl;
}

static void test_iterator_and_const_iterator_integration() {

    ft::vector<int> powers(6);
    ft::vector<int>::iterator it = powers.begin();
    ft::vector<int>::const_iterator cit = it;
    ft::vector<int>::iterator end = powers.end();
    ft::vector<int>::const_iterator cend = powers.end();
    const ft::vector<int> const_vector(5);

    cit = it;
    cend = end;

    ft::vector<int>::const_iterator const_it = const_vector.begin();

    long size = end - it;

    std::cout << "end - it == " << size << std::endl;
    // shoudln't compile
    // it = cit;
    // end = cend;
    // ft::vector<int>::iterator normal_it = const_vector.begin();
    (void)const_it;
}

void testVector(void) {
    test_default_constructor();
    test_allocator_constructor();
    test_fill_constructor();
    test_allocator();
    test_push_back();
    test_max_size();
    test_n_constructor();
    test_n_and_type_constructor();
    test_end();
    test_const_iterator();
    test_const_end();
    test_iterator_and_const_iterator_integration();
}
