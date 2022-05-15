#include "test_utils.hpp"
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#if REAL_STD

#include <vector>
namespace ft = std;

#else

# include "vector/iterator.hpp"
# include "vector.hpp"

#endif

typedef ft::vector<int>::iterator               int_iterator;
typedef ft::vector<int>::const_iterator         int_const_iterator;
typedef ft::vector<std::string>::iterator       string_iterator;
typedef ft::vector<std::string>::const_iterator string_const_iterator;

static void test_vector_iterator_constructors(void) {
    println("\ntest VectorIterator constructors");

    int_iterator* it = new int_iterator();
    std::cout << "*it = new VectorIterator(): OK" << std::endl;

    int_iterator anotherIt(*it);
    std::cout << "VectorIterator(*it): OK" << std::endl;

    int_iterator otherIt = *it;
    std::cout << "otherIt = *it: OK" << std::endl;

    (void)anotherIt;
    (void)otherIt;
}

static void test_vector_iterator_equality(void) {
    int values[] = {42, 21, 84};

    int_iterator it(values);
    int_iterator otherIt(values);
    int_iterator differentIt(values + 1);

    println("\ntest VectorIterator operator ==");
    std::cout << "it == otherIt: " << std::boolalpha << (it == otherIt) << std::endl;
    std::cout << "it == differentIt: " << std::boolalpha << (it == differentIt) << std::endl;

    println("\ntest VectorIterator operator !=");
    std::cout << "it != otherIt: " << std::boolalpha << (it != otherIt) << std::endl;
    std::cout << "it != differentIt: " << std::boolalpha << (it != differentIt) << std::endl;
}

static void test_vector_iterator_dereference(void) {
    std::string strings[] = {"HI!", "BYE!"};
    int values[] = {42, 21, 84};

    string_iterator strIt(strings);
    int_iterator it(values);

    println("\ntest VectorIterator operator *");

    std::cout << "*it: " << *it << std::endl;

    println("\ntest VectorIterator operator ->");

    std::cout << "strIt->size(): " << strIt->size() << std::endl;

}

static void test_vector_iterator_increment(void) {
    int values[] = {42, 21, 84};

    int_iterator it(values);

    println("\ntest VectorIterator operator ++");

    std::cout << "*++it == " << *++it << std::endl;
    std::cout << "*it++ == " << *it++ << std::endl;
    std::cout << "*it++ == " << *it++ << std::endl;
}

static void test_vector_iterator_decrement(void) {
    int values[] = {42, 21, 84};

    int_iterator it(values + 2);

    println("\ntest VectorIterator operator --");

    std::cout << "*--it == " << *--it << std::endl;
    std::cout << "*it-- == " << *it-- << std::endl;
    std::cout << "*it-- == " << *it-- << std::endl;
}

static void test_vector_iterator_arithmetic() {

    int values[] = {42, 21, 84, 22};

    int_iterator it(values);
    int_iterator itend(values + 3);

    println("\ntest VectorIterator operator + int");
    for (int i = 0; i < 4; i++) {
        std::cout << "*(it + "<< i << ") == " << *(it + i) << std::endl;
    }

    println("\ntest int + VectorIterator");
    for (int i = 0; i < 4; i++) {
        std::cout << "*(it + "<< i << ") == " << *(i + it) << std::endl;
    }

    println("\ntest VectorIterator operator - int");

    for (int i = 0; i < 4; i++) {
        std::cout << "*(itend - "<< i << ") == " << *(itend - i) << std::endl;
    }

    println("\ntest VectorIterator - VectorIterator");
    std::cout << "itend - it == " << (itend - it) << std::endl;
}

static void test_vector_iterator_relational() {

    int values[] = {42, 21, 84, 22};

    int_iterator it(values);
    int_iterator itend(values + 3);

    println("\ntest VectorIterator operator <");
    std::cout << "it < end == " << std::boolalpha << (it < itend) << std::endl;
    std::cout << "end < it == " << std::boolalpha << (itend < it) << std::endl;

    println("\ntest VectorIterator operator >");
    std::cout << "it > end == " << std::boolalpha << (it > itend) << std::endl;
    std::cout << "end > it == " << std::boolalpha << (itend > it) << std::endl;

    println("\ntest VectorIterator operator <=");
    std::cout << "it <= it == " << std::boolalpha << (it <= it) << std::endl;
    std::cout << "it <= end == " << std::boolalpha << (it <= itend) << std::endl;
    std::cout << "end <= it == " << std::boolalpha << (itend <= it) << std::endl;

    println("\ntest VectorIterator operator >=");
    std::cout << "it >= it == " << std::boolalpha << (it >= it) << std::endl;
    std::cout << "it >= end == " << std::boolalpha << (it >= itend) << std::endl;
    std::cout << "end >= it == " << std::boolalpha << (itend >= it) << std::endl;
}

static void test_vector_iterator_compound_assignment() {
    int values[] = {42, 21, 84, 22};

    int_iterator it(values);
    int_iterator itend(values + 3);

    println("\ntest VectorIterator operator +=");
    it += 2;
    std::cout << "it += 2 == " << *it << std::endl;

    println("\ntest VectorIterator operator -=");
    itend -= 2;
    std::cout << "itend -= 2 == " << *it << std::endl;

}

static void test_vector_iterator_offset_dereference() {
    int values[] = {42, 21, 84, 22};

    int_iterator it(values);
    int_iterator itend(values + 3);

    println("\ntest VectorIterator operator []");
    for (int i = 0; i < 4; i++) {
        std::cout << "it[" << i << "] == " << it[i] << std::endl;
    }
    for (int i = 0; i > -4; i--) {
        std::cout << "itend[" << i << "] == " << itend[i] << std::endl;
    }

}

static void test_vector_iterator_const_integration() {
    int values[] = {42, 21, 84, 22};

    int_iterator it(values + 1);
    int_const_iterator cit(values + 2);

    println("\ntest iterator and const_iterator");

    std::cout << "cit == it -> " << (cit == it) << std::endl;
    std::cout << "cit != it -> " << (cit != it) << std::endl;
    std::cout << "cit - it -> "  << (cit - it) << std::endl;
    std::cout << "cit < it -> "  << (cit < it) << std::endl;
    std::cout << "cit > it -> "  << (cit > it) << std::endl;
    std::cout << "cit <= it -> " << (cit <= it) << std::endl;
    std::cout << "cit >= it -> " << (cit >= it) << std::endl;
    std::cout << "cit + 1 -> "   << *(cit + 1) << std::endl;
    std::cout << "cit - 1 -> "   << *(cit - 1) << std::endl;

    std::cout << "it == cit -> " << (it == cit) << std::endl;
    std::cout << "it != cit -> " << (it != cit) << std::endl;
    std::cout << "it - cit -> "  << (it - cit) << std::endl;
    std::cout << "it < cit -> "  << (it < cit) << std::endl;
    std::cout << "it > cit -> "  << (it > cit) << std::endl;
    std::cout << "it <= cit -> " << (it <= cit) << std::endl;
    std::cout << "it >= cit -> " << (it >= cit) << std::endl;
    std::cout << "it + 1 -> "   << *(it + 1) << std::endl;
    std::cout << "it - 1 -> "   << *(it - 1) << std::endl;

    // shouldn't compile
    // int_iterator dummy = cit - 3;
    // std::string strings[] = {"a", "b", "c", "d", "e"};
    // string_const_iterator sit(strings);
    // std::cout << "cit == sit -> " << (cit == sit) << std::endl;
}

void testVectorIterator(void) {

    test_vector_iterator_constructors();
    test_vector_iterator_equality();
    test_vector_iterator_dereference();

    test_vector_iterator_increment();
    test_vector_iterator_decrement();

    test_vector_iterator_arithmetic();
    test_vector_iterator_relational();

    test_vector_iterator_compound_assignment();

    test_vector_iterator_offset_dereference();

    test_vector_iterator_const_integration();
}
