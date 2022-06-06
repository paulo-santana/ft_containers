#include "test_utils.hpp"
#include <ostream>

#if REAL_STD
    namespace ft = std;
#else
    #include "pair.hpp"
#endif

template<typename T, typename U>
std::ostream& operator<<(std::ostream& out, const ft::pair<T, U>& pair)
{
    out << "pair[" << pair.first << ", " << pair.second << "]";
    return out;
}

static void test_default_constructor() {
    println("test pair default constructor");

    ft::pair<const int, int> item;

    std::cout << item << std::endl;
}

static void test_copy_constructor() {
    println("test pair copy constructor");

    ft::pair<const int, int> item;
    item.second = 3;

    ft::pair<const int, float> copy(item);
    std::cout << copy << std::endl;
}

static void test_initialization_constructor() {
    println("test pair initialization constructor");

    ft::pair<const std::string, int> item("first", 42);
    std::cout << item << std::endl;
}

// this operator is completely useless in c++ 98
static void test_assignment_operator() {
    println("test pair assignment operator");

    ft::pair<std::string, int> item("first", 42);
    ft::pair<const std::string, int> other("second", 82);

    item = other;
    std::cout << item << std::endl;
}

static void test_relational_operators() {
    println("test pair relational operators");

    ft::pair<std::string, int> empty;
    ft::pair<std::string, int> some("a handful", 30);
    ft::pair<std::string, int>   greater_key("greater", 30);
    ft::pair<std::string, int> greater_value("greater", 42);

    std::cout << "empty == empty -> " << (empty == empty) << std::endl;
    std::cout << "empty == some -> " << (empty == some) << std::endl;
    std::cout << "different values are equal -> " << (greater_key == greater_value) << std::endl;

    std::cout << "empty != empty -> " << (empty != empty) << std::endl;
    std::cout << "empty != some -> " << (empty != some) << std::endl;
    std::cout << "different values are different -> " << (greater_key != greater_value) << std::endl;

    std::cout << "empty < empty -> "               << (empty < empty)               << std::endl;
    std::cout << "empty < some -> "                << (empty < some)                << std::endl;
    std::cout << "some < empty -> "                << (some < empty)                << std::endl;
    std::cout << "greater key < some -> "          << (greater_key < some)          << std::endl;
    std::cout << "some < greater key -> "          << (some < greater_key)          << std::endl;
    std::cout << "greater key < greater value -> " << (greater_key < greater_value) << std::endl;
    std::cout << "greater value < greater key -> " << (greater_value < greater_key) << std::endl;

    std::cout << "empty <= empty -> "               << (empty <= empty)               << std::endl;
    std::cout << "empty <= some -> "                << (empty <= some)                << std::endl;
    std::cout << "some <= empty -> "                << (some <= empty)                << std::endl;
    std::cout << "greater key <= some -> "          << (greater_key <= some)          << std::endl;
    std::cout << "some <= greater key -> "          << (some <= greater_key)          << std::endl;
    std::cout << "greater key <= greater value -> " << (greater_key <= greater_value) << std::endl;
    std::cout << "greater value <= greater key -> " << (greater_value <= greater_key) << std::endl;

    std::cout << "empty > empty -> "               << (empty > empty)               << std::endl;
    std::cout << "empty > some -> "                << (empty > some)                << std::endl;
    std::cout << "some > empty -> "                << (some > empty)                << std::endl;
    std::cout << "greater key > some -> "          << (greater_key > some)          << std::endl;
    std::cout << "some > greater key -> "          << (some > greater_key)          << std::endl;
    std::cout << "greater key > greater value -> " << (greater_key > greater_value) << std::endl;
    std::cout << "greater value > greater key -> " << (greater_value > greater_key) << std::endl;

    std::cout << "empty >= empty -> "               << (empty >= empty)               << std::endl;
    std::cout << "empty >= some -> "                << (empty >= some)                << std::endl;
    std::cout << "some >= empty -> "                << (some >= empty)                << std::endl;
    std::cout << "greater key >= some -> "          << (greater_key >= some)          << std::endl;
    std::cout << "some >= greater key -> "          << (some >= greater_key)          << std::endl;
    std::cout << "greater key >= greater value -> " << (greater_key >= greater_value) << std::endl;
    std::cout << "greater value >= greater key -> " << (greater_value >= greater_key) << std::endl;
}

static void test_cplusplus_relational_operators()
{
  ft::pair<int,char> foo (10,'z');
  ft::pair<int,char> bar (90,'a');

  if (foo==bar) std::cout << "foo and bar are equal\n";
  if (foo!=bar) std::cout << "foo and bar are not equal\n";
  if (foo< bar) std::cout << "foo is less than bar\n";
  if (foo> bar) std::cout << "foo is greater than bar\n";
  if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

static void test_make_pair() {
    println("test make_pair()");

    ft::pair<int, int> result = ft::make_pair(10, 20);

    std::cout << "ft::make_pair(10, 20): " << result << std::endl;
}

void testPair() {
    test_default_constructor();
    test_copy_constructor();
    test_initialization_constructor();
    test_assignment_operator();

    test_relational_operators();
    test_cplusplus_relational_operators();
    test_make_pair();
}
