#include <iterator>

#if REAL_STD
# include <vector>

 typedef std::vector<int>                   vector;
 typedef std::vector<int>::iterator         iterator;
 typedef std::reverse_iterator<iterator>    reverse_iterator;

#else
# include <vector.hpp>
# include <vector/reverse_iterator.hpp>

 typedef ft::vector<int>                   vector;
 typedef ft::vector<int>::iterator         iterator;
 typedef ft::reverse_iterator<iterator>    reverse_iterator;

#endif // REAL_STD

static void test_reverse_iterator_constructors() {
    reverse_iterator rit = reverse_iterator();

    (void)rit;
}

void testReverseIterator(void) {
    test_reverse_iterator_constructors();
}
