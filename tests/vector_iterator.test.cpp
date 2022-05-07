#include "test_utils.hpp"
#include <iostream>

#if !REAL_STD

#include "vector/iterator.hpp"

#endif // REAL_STD

void test_vector_iterator_dereference(void) {

    println("\ntest VectorIterator *it");
    #if REAL_STD
    {
        std::cout << "*it: 21" << std::endl;
    }
    #else
    {
        int values[] = {42, 21, 84};
        ft::VectorIterator<int> it(values);

        std::cout << "*it: " << *it << std::endl;
    }
    #endif
}

void testVectorIterator(void) {

    test_vector_iterator_dereference();

}
