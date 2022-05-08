#include "test_utils.hpp"
#include <iostream>
#include <string>
#include <vector>

#if REAL_STD

#else
# include "vector/iterator.hpp"
#endif // REAL_STD

typedef std::vector<int>::iterator std_int_iterator ;

static void test_vector_iterator_constructors(void) {
    println("\ntest VectorIterator constructors");

#if REAL_STD
    std::cout << "*it = new VectorIterator(): OK" << std::endl;
    std::cout << "new VectorIterator(*it): OK" << std::endl;
    std::cout << "otherIt = *it: OK" << std::endl;
#else
    ft::VectorIterator<int> *it = new ft::VectorIterator<int>();
    std::cout << "*it = new VectorIterator(): OK" << std::endl;

    ft::VectorIterator<int> *anotherIt = new ft::VectorIterator<int>(*it);
    std::cout << "new VectorIterator(*it): OK" << std::endl;

    ft::VectorIterator<int> otherIt = *it;
    std::cout << "otherIt = *it: OK" << std::endl;

    (void)anotherIt;
#endif
}

static void test_vector_iterator_equality(void) {
    int values[] = {42, 21, 84};

#if REAL_STD
    std_int_iterator it(values);
    std_int_iterator otherIt(values);
    std_int_iterator differentIt(values + 1);
#else
    ft::VectorIterator<int> it(values);
    ft::VectorIterator<int> otherIt(values);
    ft::VectorIterator<int> differentIt(values + 1);
#endif


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

#if REAL_STD
    std::vector<std::string>::iterator strIt(strings);
    std::vector<int>::iterator it(values);
#else
    ft::VectorIterator<std::string> strIt(strings);
    ft::VectorIterator<int> it(values);
#endif
    println("\ntest VectorIterator operator *");

    std::cout << "*it: " << *it << std::endl;

    println("\ntest VectorIterator operator ->");

    std::cout << "strIt->size(): " << strIt->size() << std::endl;

}

static void test_vector_iterator_increment(void) {
    int values[] = {42, 21, 84};

#if REAL_STD
    std_int_iterator it(values);
#else
    ft::VectorIterator<int> it(values);
#endif
    println("\ntest VectorIterator operator ++");

    std::cout << "*++it == " << *++it << std::endl;
    std::cout << "*it++ == " << *it++ << std::endl;
    std::cout << "*it++ == " << *it++ << std::endl;
}

static void test_vector_iterator_decrement(void) {
    int values[] = {42, 21, 84};

#if REAL_STD
    std_int_iterator it(values + 2);
#else
    ft::VectorIterator<int> it(values + 2);
#endif
    println("\ntest VectorIterator operator --");

    std::cout << "*--it == " << *--it << std::endl;
    std::cout << "*it-- == " << *it-- << std::endl;
    std::cout << "*it-- == " << *it-- << std::endl;
}

static void test_vector_iterator_arithmetic() {

    int values[] = {42, 21, 84, 22};
#if REAL_STD
    std_int_iterator it(values);
    std_int_iterator itend(values + 3);
#else
    ft::VectorIterator<int> it(values);
    ft::VectorIterator<int> itend(values + 3);
#endif

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
#if REAL_STD
    std_int_iterator it(values);
    std_int_iterator itend(values + 3);
#else
    ft::VectorIterator<int> it(values);
    ft::VectorIterator<int> itend(values + 3);
#endif

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
#if REAL_STD
    std_int_iterator it(values);
    std_int_iterator itend(values + 3);
#else
    ft::VectorIterator<int> it(values);
    ft::VectorIterator<int> itend(values + 3);
#endif

    println("\ntest VectorIterator operator +=");
    it += 2;
    std::cout << "it += 2 == " << *it << std::endl;

    println("\ntest VectorIterator operator -=");
    itend -= 2;
    std::cout << "itend -= 2 == " << *it << std::endl;

}

static void test_vector_iterator_offset_dereference() {
    int values[] = {42, 21, 84, 22};
#if REAL_STD
    std_int_iterator it(values);
    std_int_iterator itend(values + 3);
#else
    ft::VectorIterator<int> it(values);
    ft::VectorIterator<int> itend(values + 3);
#endif

    println("\ntest VectorIterator operator []");
    for (int i = 0; i < 4; i++) {
        std::cout << "it[" << i << "] == " << it[i] << std::endl;
    }
    for (int i = 0; i > -4; i--) {
        std::cout << "itend[" << i << "] == " << itend[i] << std::endl;
    }

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
}
