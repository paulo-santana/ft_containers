#include "test_utils.hpp"
#include <algorithm>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>
#include <limits>

#if REAL_STD //CREATE A REAL STL EXAMPLE
	namespace ft = std;
#else
	// #include <map.hpp>
	// #include <stack.hpp>
	#include <vector.hpp>
#endif

template <typename T>
std::ostream& operator<<(std::ostream& out, const ft::vector<T>& vec)
{
    out << "[ ";
    if (vec.size() == 0) {
        out << "]";
        return out;
    }
    typename ft::vector<T>::const_iterator it;
    for (it = vec.begin(); it < vec.end() - 1; it++) {
        out << *it << ", ";
    }
    out << *it << " ]";
    return out;
}

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

static void test_fill_constructor() {
    println("\ntest vector fill constructor");

    ft::vector<int> vec(3);
    std::cout << "ft::vector<int> vec(3)" << std::endl;
    std::cout << vec << std::endl;

    ft::vector<int> vec2(3, 4);
    std::cout << "ft::vector<int> vec(3, 4)" << std::endl;
    std::cout << vec2 << std::endl;
}

static void test_range_constructor() {
    println("test vector range constructor");
    ft::vector<int> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(2);

    ft::vector<int>::iterator start = vec.begin();
    ft::vector<int>::iterator end = vec.end();

    ft::vector<int> vec_range(start, end);
    std::cout << "vec_range -> " << vec_range << std::endl;
    std::cout << "capacity: " << vec_range.capacity() << std::endl;
    std::cout << "size: " << vec_range.size() << std::endl;
}

static void test_copy_constructor() {
    println("test vector copy constructor");
    ft::vector<std::string> strs;
    strs.push_back("string 1");
    strs.push_back("string 2");
    strs.push_back("string 3");

    std::cout << "strs -> " << strs << std::endl;
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

    ft::vector<std::string> string_vec;
    string_vec.push_back("teste 1");
    string_vec.push_back("teste 2");
    string_vec.push_back("teste 3");

    std::cout << "vect -> " << vect << std::endl;
}

static void test_max_size(void) {
    println("\ntest vector.max_size()");

    ft::vector<int> vect;
    std::cout << "vect.max_size(): " << vect.max_size() << std::endl;

    ft::vector<std::string> str_vect;
    std::cout << "str_vect.max_size(): " << str_vect.max_size() << std::endl;
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

    std::cout << "vect -> " << vect << std::endl;

    println("\ntest vector<int>(3, 80)");

    ft::vector<std::string> str_vect(5, "default");
    std::cout << "vect.size(): " << str_vect.size() << std::endl;
    std::cout << "vect.capacity(): " << str_vect.capacity() << std::endl;

    std::cout << "str_vect -> " << str_vect << std::endl;
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

static void test_rbegin() {
    println("test vector.rbegin()");

    ft::vector<int> powers;
    for (int i = 9; i < 15; i++) {
        powers.push_back(i * i);
    }

    const ft::vector<int> const_powers = powers;
    ft::vector<int>::reverse_iterator rit = powers.rbegin();
    ft::vector<int>::const_reverse_iterator crit = const_powers.rbegin();

    std::cout << "rbegin() -> ";
    for (int i = 9; i < 15; i++) {
        std::cout << *rit++ << "|" << *crit++ << ", ";
    }
    std::cout << std::endl;
}

static void test_rend() {
    println("test vector.rend()");

    ft::vector<std::string> strs;
    strs.push_back("massa");
    strs.push_back("daora");
    strs.push_back("blz");

    const ft::vector<std::string> const_strs = strs;
    ft::vector<std::string>::reverse_iterator rend = strs.rend();
    ft::vector<std::string>::const_reverse_iterator crend = const_strs.rend();

    std::cout << "rend() -> ";
    for (int i = 0; i < 3; i++) {
        std::cout << *--rend << "|" << *--crend << ", ";
    }
    std::cout << std::endl;
}

static void test_resize() {
    println("test vector.resize()");

    ft::vector<int> numbers(5, 3);
    ft::vector<int> vec_zero;
    
    std::cout << "numbers(5, 3): " << numbers << std::endl;
    numbers.resize(7, 7);
    std::cout << "\nnumbers.resize(7, 7): " << numbers << std::endl;
    std::cout << "numbers.capacity(): " << numbers.capacity() << std::endl;
    std::cout << "numbers.size(): " << numbers.size() << std::endl;
    numbers.resize(3);
    std::cout << "\nnumbers.resize(3): " << numbers << std::endl;
    std::cout << "numbers.capacity(): " << numbers.capacity() << std::endl;
    std::cout << "numbers.size(): " << numbers.size() << std::endl;
    numbers.resize(30, 9);
    std::cout << "numbers.resize(30, 9): " << numbers << std::endl;
    std::cout << "numbers.capacity(): " << numbers.capacity() << std::endl;
    std::cout << "numbers.size(): " << numbers.size() << std::endl;
    vec_zero.resize(0);
    std::cout << "\nvec_zero.resize(0): " << vec_zero << std::endl;
    std::cout << "vec_zero.capacity(): " << vec_zero.capacity() << std::endl;
    std::cout << "vec_zero.size(): " << vec_zero.size() << std::endl;
}

// https://cplusplus.com/reference/vector/vector/resize/
static void test_cplusplus_resize() {
  ft::vector<int> myvector;

  // set some initial content:
  for (int i=1;i<10;i++) myvector.push_back(i);

  myvector.resize(5);
  myvector.resize(8,100);
  myvector.resize(12);

  std::cout << "myvector contains:";
  for (unsigned long i=0;i < myvector.size();i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

}

static void test_empty() {
    println("test vector.empty()");

    ft::vector<int> empty_vec;
    std::cout << "empty_vec.empty(): " << empty_vec.empty() << std::endl;

    ft::vector<int> full_vec(3, 5);
    std::cout << "full_vec.empty(): " << full_vec.empty() << std::endl;
    full_vec.resize(0);
    std::cout << "full_vec.resize(0) is empty? " << full_vec.empty() << std::endl;
}

// https://cplusplus.com/reference/vector/vector/reserve/
static void test_reserve() {
    println("test vector.reserve()");

    ft::vector<int> small(5);

    std::cout << "small.capacity(): " << small.capacity() << std::endl;
    small.reserve(3);
    std::cout << "small.reserve(3): " << small.capacity() << std::endl;
    small.reserve(8);
    std::cout << "small.reserve(8): " << small.capacity() << std::endl;
    small.reserve(1027);
    std::cout << "small.reserve(1027): " << small.capacity() << std::endl;

    try {
        small.reserve(10000000000);
    } catch (std::exception& e) {
        std::cout << "can't reserve 10000000000: " << e.what() << std::endl;
    }

    try {
        unsigned long max_size = small.max_size();
        small.reserve(max_size + 1);
    } catch (std::length_error& e) {
        std::cout << "can't reserve more than max_size(): " << e.what() << std::endl;
    }

}

static void test_cplusplus_reserve()
{
  ft::vector<int>::size_type sz;

  ft::vector<int> foo;
  sz = foo.capacity();
  std::cout << "making foo grow:\n";
  for (int i=0; i<100; ++i) {
    foo.push_back(i);
    if (sz!=foo.capacity()) {
      sz = foo.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

  ft::vector<int> bar;
  sz = bar.capacity();
  bar.reserve(100);   // this is the only difference with foo above
  std::cout << "making bar grow:\n";
  for (int i=0; i<100; ++i) {
    bar.push_back(i);
    if (sz!=bar.capacity()) {
      sz = bar.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }
}

static void test_offset_operator() {
    println("test vector operator[]");
    ft::vector<int> ints;

    for (int i = 0; i < 5; i++) {
        ints.push_back(i * 17);
    }

    for (int i = 0; i < 5; i++) {
        std::cout << "ints[" << i << "] -> " << ints[i] << std::endl;
    }
    const ft::vector<int> cints(ints);

    for (int i = 0; i < 5; i++) {
        std::cout << "cints[" << i << "] -> " << cints[i] << std::endl;
    }
}

void testVector(void) {
    test_default_constructor();
    test_allocator_constructor();
    test_fill_constructor();
    test_range_constructor();
    test_copy_constructor();
    test_allocator();
    test_push_back();
    test_max_size();
    test_n_constructor();
    test_n_and_type_constructor();
    test_end();
    test_const_iterator();
    test_const_end();
    test_iterator_and_const_iterator_integration();
    test_rbegin();
    test_rend();
    test_resize();
    test_cplusplus_resize();
    test_empty();
    test_reserve();
    test_cplusplus_reserve();
    test_offset_operator();
}
