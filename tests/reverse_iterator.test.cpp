#if REAL_STD
# include <vector>
# include <iterator>

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
    reverse_iterator rit;

    int values[] = {21, 42, 84};
    iterator it(values);
    reverse_iterator rit_init(it);

    reverse_iterator rit_copy(rit);

    (void)rit;
    (void)rit_copy;
}

void testReverseIterator(void) {
    test_reverse_iterator_constructors();
}
