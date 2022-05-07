#include "test_utils.hpp"
#include <iostream>

#if !REAL_STD

#include "vector/iterator.hpp"

#endif // REAL_STD

void test_vector_iterator_constructors(void) {
    println("\ntest VectorIterator()");

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

void test_vector_iterator_dereference(void) {
    println("\ntest VectorIterator *it");

#if REAL_STD
    std::cout << "*it: 21" << std::endl;
   
#else
    int values[] = {42, 21, 84};
    ft::VectorIterator<int> it(values);

    std::cout << "*it: " << *it << std::endl;
#endif
}

void testVectorIterator(void) {

    test_vector_iterator_constructors();
    test_vector_iterator_dereference();

}
