#include "test_utils.hpp"
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <sstream>
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
    std::cout << "vector.size() -> " << vector1->size() << std::endl;
    std::cout << "vector.capacity() -> " << vector1->capacity() << std::endl;
    std::cout << "vector.empty() -> " << vector1->empty() << std::endl;
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

static void test_input_iterator_range_constructor() {
    println("test vector range constructor with input iterators");

    std::stringstream str;
    str << "32\n";
    str << "42\n";
    str << "52\n";
    std::istream_iterator<int> iter(str);

    ft::vector<int> target(iter, std::istream_iterator<int>());
    std::cout << "contents: " << target << std::endl;
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

    // valgrind n??o funciona com exce????es do operator new
    // try {
    //     small.reserve(10000000000);
    // } catch (std::exception& e) {
    //     std::cout << "can't reserve 10000000000: " << e.what() << std::endl;
    // }
    //
    // try {
    //     unsigned long max_size = small.max_size();
    //     small.reserve(max_size + 1);
    // } catch (std::length_error& e) {
    //     std::cout << "can't reserve more than max_size(): " << e.what() << std::endl;
    // }

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

static void test_at() {
    println("test vector.at()");

    ft::vector<int> ints;

    for (int i = 0; i < 5; i++) {
        ints.push_back(i * 17);
    }

    for (int i = 0; i < 5; i++) {
        std::cout << "ints.at(" << i << ") -> " << ints.at(i) << std::endl;
    }
    const ft::vector<int> cints(ints);

    for (int i = 0; i < 5; i++) {
        std::cout << "cints.at(" << i << ") -> " << cints.at(i) << std::endl;
    }

    try {
        int boom = ints.at(42);
        (void)boom;
    } catch (std::out_of_range& e) {
        std::cout << "std::out_of_range: can't access ints.at(42)" << std::endl;
    }
}

static void test_front() {
    println("test vector.front()");

    ft::vector<int> vec(1, 3);
    vec.push_back(42);
    vec.push_back(37);

    int first = vec.front();
    std::cout << "first: " << first << std::endl;
    const ft::vector<int> cvec(vec);
    first = cvec.front();
    std::cout << "const first: " << first << std::endl;
}

static void test_back() {
    println("test vector.back()");

    ft::vector<int> vec(1, 3);
    vec.push_back(42);
    vec.push_back(37);

    int last = vec.back();
    std::cout << "last: " << last << std::endl;
    const ft::vector<int> cvec(vec);
    last = cvec.back();
    std::cout << "const last: " << last << std::endl;
}

static void test_assign() {
    println("test vector.assign()");

    ft::vector<std::string> strings(10, "abelha");
    ft::vector<std::string> strings2;

    std::cout << "strings(10, 5) -> " << strings << std::endl;

    strings.assign(5, "joaozinho");
    strings2.assign(strings.begin(), strings.end());

    std::cout << "strings.assing(5, \"joaozinho\") -> " << strings << std::endl;
    std::cout << "strings.capacity() -> " << strings.capacity() << std::endl;

    strings.assign(15, "pedra");
    std::cout << "strings.assing(15, \"pedra\") -> " << strings << std::endl;
    std::cout << "strings.capacity() -> " << strings.capacity() << std::endl;

    strings.assign(45, "papel");
    std::cout << "strings.assing(45, \"papel\") -> " << strings << std::endl;
    std::cout << "strings.capacity() -> " << strings.capacity() << std::endl;
}

// https://www.cplusplus.com/reference/vector/vector/assign/
static void test_cplusplus_assign()
{
  ft::vector<int> first;
  ft::vector<int> second;
  ft::vector<int> third;

  first.assign(7,100);             // 7 ints with a value of 100

  ft::vector<int>::iterator it;
  it=first.begin()+1;

  second.assign(it,first.end()-1); // the 5 central values of first

  int myints[] = {1776,7,4};
  third.assign(myints,myints+3);   // assigning from array.

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of third: " << int (third.size()) << '\n';

}

static void test_input_iterator_assign() {
    println("test vector range assign with input iterators");

    ft::vector<int> target(8, 1);
    const char* strings[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

    std::stringstream str;
    for (int i = 0; i < 10; i++) {
        str << strings[i] + std::string("\n");
    }
    std::istream_iterator<int> iter(str);

    target.assign(iter, std::istream_iterator<int>());
    std::cout << "contents: " << target << std::endl;
    std::cout << "target.size(): " << target.size() << std::endl;
    std::cout << "target.capacity(): " << target.capacity() << std::endl;
}

static void test_pop_back() {
    println("test vector.pop_back()");

    ft::vector<std::string> strings(3, "test");

    std::cout << "strings -> " << strings << std::endl;
    while (!strings.empty()) {
        std::cout << "strings.pop_back() -> " << strings << std::endl;
        strings.pop_back();
    }
    std::cout << "strings.capacity() -> " << strings.capacity() << std::endl;
}

static void test_insert() {
    println("test vector.insert()");

    const char *contents[5] = {"ai sim", "beleza", "caraca", "daora", NULL};

    ft::vector<std::string> strings;
    ft::vector<std::string>::iterator it;

    for (int i = 0; contents[i] != NULL; i++) {
        it = strings.insert(strings.begin(), contents[i]);
        std::cout << "strings.insert(\"" << contents[i] << "\"): " << strings << std::endl;
        std::cout << "returned -> " << *it << std::endl;
        std::cout << "strings.capacity() -> " << strings.capacity() << std::endl;
        std::cout << "strings.size() -> " << strings.size() << std::endl;
    }
    it = strings.insert(strings.begin() + 2, "opa");
    std::cout << "strings.insert(\"opa\"): " << strings << std::endl;
    std::cout << "returned -> " << *it << std::endl;
    std::cout << "strings.capacity() -> " << strings.capacity() << std::endl;
    std::cout << "strings.size() -> " << strings.size() << std::endl;
}

static void test_fill_insert() {
    println("test fill vector.insert()");

    ft::vector<int> vec;

    vec.insert(vec.begin(), 10, 5);
    std::cout << "vec.insert(vec.begin(), 10, 5)" << std::endl;

    std::cout << "vec -> " << vec << std::endl;
    std::cout << "new size() -> " << vec.size() << std::endl;
    std::cout << "new capacity() -> " << vec.capacity() << std::endl;
    vec.reserve(20);

    std::cout << "vec.reserve(20)\nnew capacity -> "
        << vec.capacity() << std::endl;
    std::cout << "vec.insert((vec.begin() + 5), 7, 3)" << std::endl;
    vec.insert((vec.begin() + 5), 7, 3);

    std::cout << "vec -> " << vec << std::endl;
    std::cout << "new size() -> " << vec.size() << std::endl;
    std::cout << "new capacity() -> " << vec.capacity() << std::endl;

    vec.insert(vec.begin(), 7, 7);

    std::cout << "vec -> " << vec << std::endl;
    std::cout << "new size() -> " << vec.size() << std::endl;
    std::cout << "new capacity() -> " << vec.capacity() << std::endl;
}

static void test_fill_insert_string() {
    println("test fill vector.insert(position, amount, value)");

    ft::vector<std::string> strvec;

    strvec.insert(strvec.begin(), 5, "x");
    std::cout << "insert on empty vector" << std::endl;
    std::cout << strvec << std::endl;

    strvec.reserve(20);
    std::cout << "case   [xxxxx               ] -> " << strvec << std::endl;
    strvec.insert(strvec.begin() + 3, 9, "A");
    std::cout << "target [xxxAAAAAAAAAxx      ] -> " << strvec << std::endl;
    std::cout << "vec.size() -> " << strvec.size() << std::endl;
    std::cout << "vec.capacity() -> " << strvec.capacity() << std::endl;

    strvec.assign(strvec.size(), "x");
    std::cout << "case   [xxxxxxxxxxxxxx      ] -> " << strvec << std::endl;
    strvec.insert((strvec.begin() + 5), 4, "A");
    std::cout << "target [xxxxxAAAAxxxxxxxxx  ] -> " << strvec << std::endl;
    std::cout << "vec.size() -> " << strvec.size() << std::endl;
    std::cout << "vec.capacity() -> " << strvec.capacity() << std::endl;

    std::cout << "test growing factors" << std::endl;
    for (int i = 0; i < 30; i++) {
        ft::vector<std::string> intvec(4, "-");
        intvec.reserve(20);
        intvec.insert(intvec.begin() + 2, i, "x");

        std::cout << "insert 30 -> " << intvec << std::endl;
        std::cout << "intvec.size() -> " << intvec.size() << std::endl;
        std::cout << "intvec.capacity() -> " << intvec.capacity() << std::endl;
    }
}

static void test_range_insert() {

    println("test vector range insert");
    ft::vector<int> base_vec(8, 1);

    ft::vector<int> target(5, 0);
    target.reserve(20);

    target.insert(target.begin(), base_vec.begin(), base_vec.end());

    std::cout << "target -> " << target << std::endl;

    std::cout << "test growing factors" << std::endl;
    for (int i = 0; i < 30; i++) {
        ft::vector<int> intvec(i, 4);
        ft::vector<int> loop_target(4, 0);
        loop_target.reserve(20);
        loop_target.insert(loop_target.begin() + 2, intvec.begin(), intvec.end());

        std::cout << "insert " << i << " -> " << loop_target << std::endl;
        std::cout << "intvec.size() -> " << loop_target.size() << std::endl;
        std::cout << "intvec.capacity() -> " << loop_target.capacity() << std::endl;
    }
}

static void test_input_iterator_insert() {
    println("test vector range insert with input iterators");

    ft::vector<int> target(8, 1);

    std::stringstream str;
    str << "32\n";
    str << "42\n";
    str << "52\n";
    std::istream_iterator<int> iter(str);

    target.insert(target.begin() + 3, iter, std::istream_iterator<int>());
    std::cout << "contents: " << target << std::endl;
}

class Mock {
public:
    Mock(): index(0) {
        this->allocated_data = new int(3);
    }
    Mock(int i): index(i) {
        this->allocated_data = new int(i);
    }

    Mock(const Mock& other): index(other.index) {
        this->allocated_data = new int(*other.allocated_data);
    }

    Mock& operator=(const Mock& other) {
        delete this->allocated_data;
        this->index = other.index;
        this->allocated_data = new int(*other.allocated_data);
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Mock& me) {
        os << me.index;
        return os;
    }

    ~Mock() {
        std::cout << " [Mock " << index << " destructor called]" << std::endl;
        delete this->allocated_data;
    }
private:
    int index;
    int* allocated_data;
};

static void test_erase() {
    println("test vector erase");

    ft::vector<Mock> ints;
    for (int i = 0; i < 10; i++) {
        ints.push_back(Mock(i));
    }

    while (!ints.empty()) {
        ft::vector<Mock>::iterator begin = ints.begin();
        std::cout << "erase " << *begin;
        ft::vector<Mock>::iterator it = ints.erase(begin);
        std::cout << ": returned -> " << *it << std::endl;
    }
}

static void test_iterator_erase() {
    println("test vector range erase");

    ft::vector<Mock> vec;

    for (int i = 0; i < 8; i++) {
        vec.push_back(Mock(i * i));
    }

    ft::vector<Mock>::iterator pos = vec.erase(vec.begin() + 2, vec.end() - 2);

    std::cout << "vec.erase(begin, end) -> " << vec << std::endl;
    std::cout << "returned: " << *pos << std::endl;
}

static void test_swap() {
    println("test vector.swap()");

    ft::vector<int> vec1(4, 4);
    ft::vector<int> vec2(8, 7);

    std::cout << "vec1: " << vec1 << std::endl;
    std::cout << "vec2: " << vec2 << std::endl;
    ft::vector<int>::iterator it = vec1.begin();
    ft::vector<int>::iterator it2 = vec2.begin();
    vec1.swap(vec2);
    std::cout << "vec1.swap(vec2)" << std::endl;
    std::cout << "vec1: " << vec1 << std::endl;
    std::cout << "vec2: " << vec2 << std::endl;
    std::cout << "vec1.size(): " << vec1.size() << std::endl;
    std::cout << "vec2.size(): " << vec2.size() << std::endl;
    std::cout << "vec1.capacity(): " << vec1.capacity() << std::endl;
    std::cout << "vec2.capacity(): " << vec2.capacity() << std::endl;
    std::cout << "vec1.begin(): " << *vec1.begin() << std::endl;
    std::cout << "vec2.begin(): " << *vec2.begin() << std::endl;

    ft::vector<int>::iterator post_it = vec1.begin();
    ft::vector<int>::iterator post_it2 = vec2.begin();

    std::cout << "iterator points to new vector: " << (it == post_it2) << std::endl;
    std::cout << "iterator 2 points to new vector: " << (it2 == post_it) << std::endl;
}

static void test_clear() {
    println("test vector.clear()");

    ft::vector<Mock> vec(3, Mock(3));

    std::cout << "vec: " << vec << std::endl;
    std::cout << "vec.clear() " << std::endl;
    vec.clear();
    std::cout << "vec: " << vec << std::endl;
    std::cout << "vec.size(): " << vec.size() << std::endl;
    std::cout << "vec.capacity(): " << vec.capacity() << std::endl;
}

static void test_non_member_swap() {
    println("test vector non member swap()");

    ft::vector<int> vec1(4, 4);
    ft::vector<int> vec2(8, 7);

    std::cout << "vec1: " << vec1 << std::endl;
    std::cout << "vec2: " << vec2 << std::endl;
    ft::swap(vec1, vec2);
    std::cout << "vec1.swap(vec2)" << std::endl;
    std::cout << "vec1: " << vec1 << std::endl;
    std::cout << "vec2: " << vec2 << std::endl;
    std::cout << "vec1.size(): " << vec1.size() << std::endl;
    std::cout << "vec2.size(): " << vec2.size() << std::endl;
    std::cout << "vec1.capacity(): " << vec1.capacity() << std::endl;
    std::cout << "vec2.capacity(): " << vec2.capacity() << std::endl;
    std::cout << "vec1.begin(): " << *vec1.begin() << std::endl;
    std::cout << "vec2.begin(): " << *vec2.begin() << std::endl;
}

static void test_vector_relational_operators() {
    println("test vector relational operators");

    ft::vector<int> empty1, empty2;
    ft::vector<int> some1(5, 3), some2(5, 3);

    ft::vector<int> bigger1(6, 3);

    std::cout << "(empty1 == empty2): " << (empty1 == empty2) << std::endl;
    std::cout << "(empty1 != empty2): " << (empty1 != empty2) << std::endl;

    std::cout << "(some1 == some2): " << (some1 == some2) << std::endl;
    std::cout << "(some1 != some2): " << (some1 != some2) << std::endl;

    std::cout << "(empty1 == some2): " << (empty1 == some1) << std::endl;
    std::cout << "(empty1 != some2): " << (empty1 != some1) << std::endl;

    std::cout << "(some1 == bigger1): " << (some1 == bigger1) << std::endl;
    std::cout << "(some1 != bigger1): " << (some1 != bigger1) << std::endl;

    std::cout << "(empty1 < empty2): " << (empty1 < empty2) << std::endl;
    std::cout << "(empty1 > empty2): " << (empty1 > empty2) << std::endl;
    std::cout << "(empty1 <= empty2): " << (empty1 <= empty2) << std::endl;
    std::cout << "(empty1 >= empty2): " << (empty1 >= empty2) << std::endl;

    std::cout << "(some1 <  some2): " << (some1 < some2) << std::endl;
    std::cout << "(some1 >  some2): " << (some1 > some2) << std::endl;
    std::cout << "(some1 <= some2): " << (some1 <= some2) << std::endl;
    std::cout << "(some1 >= some2): " << (some1 >= some2) << std::endl;

    std::cout << "(empty1 <  some2): " << (empty1 < some2) << std::endl;
    std::cout << "(empty1 >  some2): " << (empty1 > some2) << std::endl;
    std::cout << "(empty1 <= some2): " << (empty1 <= some2) << std::endl;
    std::cout << "(empty1 >= some2): " << (empty1 >= some2) << std::endl;

    std::cout << "(some1 <  bigger1): " << (some1 <  bigger1) << std::endl;
    std::cout << "(some1 >  bigger1): " << (some1 >  bigger1) << std::endl;
    std::cout << "(some1 <= bigger1): " << (some1 <= bigger1) << std::endl;
    std::cout << "(some1 >= bigger1): " << (some1 >= bigger1) << std::endl;

    std::cout << "(some2 <  empty1): " << (some2 <  empty1) << std::endl;
    std::cout << "(some2 >  empty1): " << (some2 >  empty1) << std::endl;
    std::cout << "(some2 <= empty1): " << (some2 <= empty1) << std::endl;
    std::cout << "(some2 >= empty1): " << (some2 >= empty1) << std::endl;

    std::cout << "(bigger1 <  some1): " << (bigger1 <  some1) << std::endl;
    std::cout << "(bigger1 >  some1): " << (bigger1 >  some1) << std::endl;
    std::cout << "(bigger1 <= some1): " << (bigger1 <= some1) << std::endl;
    std::cout << "(bigger1 >= some1): " << (bigger1 >= some1) << std::endl;
}

void testVector(void) {
    test_default_constructor();
    test_allocator_constructor();
    test_fill_constructor();
    test_range_constructor();
    test_input_iterator_range_constructor();
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
    test_at();
    test_front();
    test_back();
    test_assign();
    test_cplusplus_assign();
    test_input_iterator_assign();
    test_pop_back();
    test_insert();
    test_fill_insert();
    test_fill_insert_string();
    test_range_insert();
    test_input_iterator_insert();
    test_erase();
    test_iterator_erase();
    test_swap();
    test_non_member_swap();
    test_clear();

    test_vector_relational_operators();
}
