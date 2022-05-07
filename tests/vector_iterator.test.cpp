#include "test_utils.hpp"
#include <iostream>
#include <string>

#if REAL_STD

#include <vector>

#else
#include "vector/iterator.hpp"

#endif // REAL_STD

void test_vector_iterator_constructors(void) {
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

void test_vector_iterator_equality(void) {
    println("\ntest VectorIterator operator ==");

#if REAL_STD
    std::cout << "it == otherIt: true" << std::endl;
    std::cout << "it == differentIt: false" << std::endl;

    println("\ntest VectorIterator operator !=");
    std::cout << "it != otherIt: false" << std::endl;
    std::cout << "it != differentIt: true" << std::endl;
   
#else
    int values[] = {42, 21, 84};
    ft::VectorIterator<int> it(values);
    ft::VectorIterator<int> otherIt(values);
    ft::VectorIterator<int> differentIt(values + 1);

    std::cout << "it == otherIt: " << std::boolalpha << (it == otherIt) << std::endl;
    std::cout << "it == differentIt: " << std::boolalpha << (it == differentIt) << std::endl;

    println("\ntest VectorIterator operator !=");
    std::cout << "it != otherIt: " << std::boolalpha << (it != otherIt) << std::endl;
    std::cout << "it != differentIt: " << std::boolalpha << (it != differentIt) << std::endl;
#endif
}

void test_vector_iterator_dereference(void) {
    println("\ntest VectorIterator *it");

#if REAL_STD
    std::cout << "*it: 42" << std::endl;

    println("\ntest VectorIterator it->property");
    std::vector<std::string> strings;
    strings.push_back("HI!");
    strings.push_back("BYE!");
    std::vector<std::string>::iterator strIt = strings.begin();
    std::cout << "strIt->size(): " << strIt->size() << std::endl;
   
#else
    int values[] = {42, 21, 84};
    ft::VectorIterator<int> it(values);

    std::cout << "*it: " << *it << std::endl;


    println("\ntest VectorIterator it->property");
    std::string strings[] = {"HI!", "BYE!"};
    ft::VectorIterator<std::string> strIt(strings);

    std::cout << "strIt->size(): " << strIt->size() << std::endl;

#endif
}

void testVectorIterator(void) {

    test_vector_iterator_constructors();
    test_vector_iterator_equality();
    test_vector_iterator_dereference();

}
