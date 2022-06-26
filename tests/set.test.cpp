#include "test_utils.hpp"
#include <set>

#if REAL_STD
    namespace ft = std;

#else

#include "set.hpp"
#include "vector.hpp"
#include "pair.hpp"

#endif

static void test_default_constructor() {
    println("test set default constructor");

    ft::set<int> small_set;

    (void)small_set;
    println("at least it compiles");
}

void testSet() {
    test_default_constructor();
}
