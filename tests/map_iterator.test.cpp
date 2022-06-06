#include <map>
#include <utility>
#include <iostream>
# include "test_utils.hpp"
# include "tests.hpp"

#if 1
  namespace ft = std;
  typedef ft::map<int, int>           int_int_map;
  typedef ft::map<int, int>::iterator int_int_iterator;


#else
# include "internals/red_black_tree_node.hpp"
# include "map/RBTreeIterator.hpp"
# include "map.hpp"
# include "pair.hpp"
  typedef ft::map<int, int>             int_int_map;
  typedef ft::map<int, int>::iterator   int_int_iterator;

#endif

template<typename T, typename U>
std::ostream& operator<<(std::ostream& out, const ft::pair<T, U>& pair)
{
    out << "pair[" << pair.first << ", " << pair.second << "]";
    return out;
}

static void test_constructors(void) {
    println("\ntest RBTreeIterator constructors");

    int_int_iterator* it = new int_int_iterator();
    std::cout << "*it = new RBTreeIterator(): OK" << std::endl;

    int_int_iterator anotherIt(*it);
    std::cout << "RBTreeIterator(*it): OK" << std::endl;

    int_int_iterator otherIt = *it;
    std::cout << "otherIt = *it: OK" << std::endl;

    (void)anotherIt;
    (void)otherIt;
    delete it;
}

// static void test_equality(void) {
//     int values[] = {42, 21, 84};
//
//     int_int_iterator it(values);
//     int_int_iterator otherIt(values);
//     int_int_iterator differentIt(values + 1);
//
//     println("\ntest VectorIterator operator ==");
//     std::cout << "it == otherIt: " << std::boolalpha << (it == otherIt) << std::endl;
//     std::cout << "it == differentIt: " << std::boolalpha << (it == differentIt) << std::endl;
//
//     println("\ntest VectorIterator operator !=");
//     std::cout << "it != otherIt: " << std::boolalpha << (it != otherIt) << std::endl;
//     std::cout << "it != differentIt: " << std::boolalpha << (it != differentIt) << std::endl;
// }
//
// static void test_dereference(void) {
//     std::string strings[] = {"HI!", "BYE!"};
//     int values[] = {42, 21, 84};
//
//     int_int_iterator strIt(strings);
//     int_int_iterator it(values);
//
//     println("\ntest VectorIterator operator *");
//
//     std::cout << "*it: " << *it << std::endl;
//
//     println("\ntest VectorIterator operator ->");
//
//     std::cout << "strIt->size(): " << strIt->size() << std::endl;
//
// }

static void test_increment(void) {
    int_int_map map;

    map.insert(ft::make_pair(1, 1));
    int_int_iterator it = map.begin();

    println("\ntest VectorIterator operator ++");

    // Cannot increment value of type 'int_int_iterator' (aka 'map<int, int>')
    std::cout << "*++it == " << *++it << std::endl;
    std::cout << "*it++ == " << *it++ << std::endl;
    std::cout << "*it++ == " << *it++ << std::endl;
}

// static void test_decrement(void) {
//     int values[] = {42, 21, 84};
//
//     int_int_iterator it(values + 2);
//
//     println("\ntest VectorIterator operator --");
//
//     std::cout << "*--it == " << *--it << std::endl;
//     std::cout << "*it-- == " << *it-- << std::endl;
//     std::cout << "*it-- == " << *it-- << std::endl;
// }
//
// static void test_arithmetic() {
//
//     int values[] = {42, 21, 84, 22};
//
//     int_int_iterator it(values);
//     int_int_iterator itend(values + 3);
//
//     println("\ntest VectorIterator operator + int");
//     for (int i = 0; i < 4; i++) {
//         std::cout << "*(it + "<< i << ") == " << *(it + i) << std::endl;
//     }
//
//     println("\ntest int + VectorIterator");
//     for (int i = 0; i < 4; i++) {
//         std::cout << "*(it + "<< i << ") == " << *(i + it) << std::endl;
//     }
//
//     println("\ntest VectorIterator operator - int");
//
//     for (int i = 0; i < 4; i++) {
//         std::cout << "*(itend - "<< i << ") == " << *(itend - i) << std::endl;
//     }
//
//     println("\ntest VectorIterator - VectorIterator");
//     std::cout << "itend - it == " << (itend - it) << std::endl;
// }
//
// static void test_relational() {
//
//     int values[] = {42, 21, 84, 22};
//
//     int_int_iterator it(values);
//     int_int_iterator itend(values + 3);
//
//     println("\ntest VectorIterator operator <");
//     std::cout << "it < end == " << std::boolalpha << (it < itend) << std::endl;
//     std::cout << "end < it == " << std::boolalpha << (itend < it) << std::endl;
//
//     println("\ntest VectorIterator operator >");
//     std::cout << "it > end == " << std::boolalpha << (it > itend) << std::endl;
//     std::cout << "end > it == " << std::boolalpha << (itend > it) << std::endl;
//
//     println("\ntest VectorIterator operator <=");
//     std::cout << "it <= it == " << std::boolalpha << (it <= it) << std::endl;
//     std::cout << "it <= end == " << std::boolalpha << (it <= itend) << std::endl;
//     std::cout << "end <= it == " << std::boolalpha << (itend <= it) << std::endl;
//
//     println("\ntest VectorIterator operator >=");
//     std::cout << "it >= it == " << std::boolalpha << (it >= it) << std::endl;
//     std::cout << "it >= end == " << std::boolalpha << (it >= itend) << std::endl;
//     std::cout << "end >= it == " << std::boolalpha << (itend >= it) << std::endl;
// }
//
// static void test_compound_assignment() {
//     int values[] = {42, 21, 84, 22};
//
//     int_int_iterator it(values);
//     int_int_iterator itend(values + 3);
//
//     println("\ntest VectorIterator operator +=");
//     it += 2;
//     std::cout << "it += 2 == " << *it << std::endl;
//
//     println("\ntest VectorIterator operator -=");
//     itend -= 2;
//     std::cout << "itend -= 2 == " << *it << std::endl;
//
// }
//
// static void test_offset_dereference() {
//     int values[] = {42, 21, 84, 22};
//
//     int_int_iterator it(values);
//     int_int_iterator itend(values + 3);
//
//     println("\ntest VectorIterator operator []");
//     for (int i = 0; i < 4; i++) {
//         std::cout << "it[" << i << "] == " << it[i] << std::endl;
//     }
//     for (int i = 0; i > -4; i--) {
//         std::cout << "itend[" << i << "] == " << itend[i] << std::endl;
//     }
//
// }
//
// static void test_const_integration() {
//     int values[] = {42, 21, 84, 22};
//
//     int_int_iterator it(values + 1);
//     int_const_iterator cit(values + 2);
//
//     println("\ntest iterator and const_iterator");
//
//     std::cout << "cit == it -> " << (cit == it) << std::endl;
//     std::cout << "cit != it -> " << (cit != it) << std::endl;
//     std::cout << "cit - it -> "  << (cit - it) << std::endl;
//     std::cout << "cit < it -> "  << (cit < it) << std::endl;
//     std::cout << "cit > it -> "  << (cit > it) << std::endl;
//     std::cout << "cit <= it -> " << (cit <= it) << std::endl;
//     std::cout << "cit >= it -> " << (cit >= it) << std::endl;
//     std::cout << "cit + 1 -> "   << *(cit + 1) << std::endl;
//     std::cout << "cit - 1 -> "   << *(cit - 1) << std::endl;
//
//     std::cout << "it == cit -> " << (it == cit) << std::endl;
//     std::cout << "it != cit -> " << (it != cit) << std::endl;
//     std::cout << "it - cit -> "  << (it - cit) << std::endl;
//     std::cout << "it < cit -> "  << (it < cit) << std::endl;
//     std::cout << "it > cit -> "  << (it > cit) << std::endl;
//     std::cout << "it <= cit -> " << (it <= cit) << std::endl;
//     std::cout << "it >= cit -> " << (it >= cit) << std::endl;
//     std::cout << "it + 1 -> "   << *(it + 1) << std::endl;
//     std::cout << "it - 1 -> "   << *(it - 1) << std::endl;
//
//     // shouldn't compile
//     // int_iterator dummy = cit - 3;
//     // std::string strings[] = {"a", "b", "c", "d", "e"};
//     // string_const_iterator sit(strings);
//     // std::cout << "cit == sit -> " << (cit == sit) << std::endl;
// }

void testMapIterator(void) {

    test_constructors();
    // test_equality();
    // test_dereference();
    //
    test_increment();
    // test_decrement();
    //
    // test_arithmetic();
    // test_relational();
    //
    // test_compound_assignment();
    //
    // test_offset_dereference();
    //
    // test_const_integration();
}
