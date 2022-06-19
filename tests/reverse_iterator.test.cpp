#include "test_utils.hpp"
#include <iostream>

#if REAL_STD
# include <vector>
# include <iterator>

namespace ft = std;

#else // !REAL_STD
# include "vector.hpp"
# include "reverse_iterator.hpp"

#endif // REAL_STD
       //
typedef ft::vector<float>                         float_vector;
typedef ft::vector<float>::iterator               float_iterator;
typedef ft::vector<float>::const_iterator         float_const_iterator;
typedef ft::vector<float>::reverse_iterator       float_reverse_iterator;
typedef ft::vector<float>::const_reverse_iterator float_const_reverse_iterator;

typedef ft::vector<int>                         int_vector;
typedef ft::vector<int>::iterator               int_iterator;
typedef ft::vector<int>::const_iterator         int_const_iterator;
typedef ft::vector<int>::reverse_iterator       int_reverse_iterator;
typedef ft::vector<int>::const_reverse_iterator int_const_reverse_iterator;

typedef ft::vector<std::string>                         string_vector;
typedef ft::vector<std::string>::iterator               string_iterator;
typedef ft::vector<std::string>::const_iterator         string_const_iterator;
typedef ft::vector<std::string>::reverse_iterator       string_reverse_iterator;
typedef ft::vector<std::string>::const_reverse_iterator string_const_reverse_iterator;

static void test_reverse_iterator_constructors() {
    println("\ntest reverse iterator constructors");
    int_reverse_iterator rit;

    int values[] = {21, 42, 84};
    int_iterator it(values);
    int_reverse_iterator rit_init(it);

    int_reverse_iterator rit_copy(rit);

    (void)rit;
    (void)rit_copy;
}

static void test_base() {
    println("\ntest reverse iterator base()");
    int values[] = {21, 42, 84};
    int_iterator it(values);
    int_reverse_iterator rit(it);

    int_iterator base = rit.base();

    std::cout << "*base -> " << *base << std::endl;
    std::cout << "*it -> " << *it << std::endl;
    std::cout << "*base == *it: " << (*base == *it) << std::endl;
}

static void test_dereference_operator() {
    println("\ntest reverse iterator operator*");

    int values[] = {21, 42, 84};
    int_iterator it(values + 2);
    int_reverse_iterator rit(it);

    int value = *rit;
    std::cout << "value -> " << value << std::endl;
}

static void test_addition_operator() {
    println("\ntest reverse iterator operator+");

    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int_iterator it(values + 5);
    int_reverse_iterator rit(it);

    int value = *(rit + 2);
    std::cout << "*(rit + 2) -> " << value << std::endl;
    value = *(3 + rit);
    std::cout << "*(3 + rit) -> " << value << std::endl;
}

static void test_increment_operator() {
    println("\ntest reverse iterator operator++");

    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int_iterator it(values + 7);
    int_reverse_iterator rit(it);

    int value = *++rit;
    std::cout << "*++rit -> " << value << std::endl;
    value = *rit++;
    std::cout << "*rit++ -> " << value << std::endl;
    value = *rit;
    std::cout << "*rit -> " << value << std::endl;
}

static void test_compound_assignment_operator() {
    println("\ntest reverse iterator operators += and -=");

    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int_iterator it(values + 5);
    int_reverse_iterator rit(it);

    std::cout << "*rit -> " << *rit << std::endl;
    rit += 2;
    std::cout << "rit += 2 -> " << *rit << std::endl;
    rit -= 3;
    std::cout << "rit -= 3 -> " << *rit << std::endl;
}

static void test_subtraction_operator() {
    println("\ntest reverse iterator operator-");

    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int_iterator it(values + 2);
    int_reverse_iterator rit(it);
    int_reverse_iterator rit2(it + 3);

    std::cout << "*rit -> " << *rit << std::endl;
    std::cout << "*(rit - 2) -> " << *(rit - 2) << std::endl;
    std::cout << "*(rit - 5) -> " << *(rit - 5) << std::endl;
    std::cout << "rit - rit2 -> " << rit - rit2 << std::endl;
}

static void test_decrement_operator() {
    println("\ntest reverse iterator operator--");

    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int_iterator it(values + 2);
    int_reverse_iterator rit(it);

    for (int i = 0; i < 7; i++) {
        if (i % 2 == 0)
            std::cout << "*rit-- -> " << *rit-- << std::endl;
        else
            std::cout << "*--rit -> " << *--rit << std::endl;
    }

}

static void test_arrow_dereference_operator() {
    println("\ntest reverse iterator operator->");

    std::string strings[] = {"algol", "bcpl", "crystal", "d", "erlang"};

    string_iterator it(strings + 5);
    string_reverse_iterator rit(it);

    const char *cstr;
    for (int i = 0; i < 5; i++) {
        cstr = rit++->c_str();
        std::cout << cstr << std::endl;
    }
    cstr = rit->c_str();
}

static void test_offset_operator() {
    println("\ntest reverse iterator operator--");

    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int_iterator it(values + 8);
    int_reverse_iterator rit(it);

    for (int i = 0; i < 7; i++) {
        std::cout << "rit[ " << i << "] -> " << rit[i] << std::endl;
    }
}

static void test_relational_operators() {
    println("\ntest reverse iterator relational operators");
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int_iterator it(values + 5);
    int_reverse_iterator rit(it);
    int_reverse_iterator rit2(it);
    int_reverse_iterator rit3(it + 3);

    std::cout << "rit == rit2 -> " << (rit == rit2) << std::endl;
    std::cout << "rit == rit3 -> " << (rit == rit3) << std::endl;
    std::cout << "rit != rit2 -> " << (rit != rit2) << std::endl;
    std::cout << "rit != rit3 -> " << (rit != rit3) << std::endl;
    std::cout << "rit < rit2 -> " << (rit < rit2) << std::endl;
    std::cout << "rit < rit3 -> " << (rit < rit3) << std::endl;
    std::cout << "rit > rit2 -> " << (rit > rit2) << std::endl;
    std::cout << "rit > rit3 -> " << (rit > rit3) << std::endl;
    std::cout << "rit <= rit2 -> " << (rit <= rit2) << std::endl;
    std::cout << "rit <= rit3 -> " << (rit <= rit3) << std::endl;
    std::cout << "rit >= rit2 -> " << (rit >= rit2) << std::endl;
    std::cout << "rit >= rit3 -> " << (rit >= rit3) << std::endl;
}

static void test_const_integration() {
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int_iterator it(values + 5);
    int_const_iterator cit(values + 5);
    int_reverse_iterator rit(it);
    // shouldn't compile
    //int_reverse_iterator rit2(cit);
    int_const_reverse_iterator crit(cit);

    println("\ntest reverse_iterator and const_reverse_iterator");

    std::cout << "cit == it -> " << (crit == rit) << std::endl;
    std::cout << "cit != it -> " << (crit != rit) << std::endl;
    std::cout << "cit - it -> "  << (crit - rit) << std::endl;
    std::cout << "cit < it -> "  << (crit < rit) << std::endl;
    std::cout << "cit > it -> "  << (crit > rit) << std::endl;
    std::cout << "cit <= it -> " << (crit <= rit) << std::endl;
    std::cout << "cit >= it -> " << (crit >= rit) << std::endl;
    std::cout << "cit + 1 -> "   << *(crit + 1) << std::endl;
    std::cout << "cit - 1 -> "   << *(crit - 1) << std::endl;

    std::cout << "it == cit -> " << (rit == crit) << std::endl;
    std::cout << "it != cit -> " << (rit != crit) << std::endl;
    std::cout << "it - cit -> "  << (rit - crit) << std::endl;
    std::cout << "it < cit -> "  << (rit < crit) << std::endl;
    std::cout << "it > cit -> "  << (rit > crit) << std::endl;
    std::cout << "it <= cit -> " << (rit <= crit) << std::endl;
    std::cout << "it >= cit -> " << (rit >= crit) << std::endl;
    std::cout << "it + 1 -> "   << *(rit + 1) << std::endl;
    std::cout << "it - 1 -> "   << *(rit - 1) << std::endl;
    
    // shouldn't compile
    // string_reverse_iterator srit;
    // string_const_reverse_iterator scrit;
    // bool equal = (crit == scrit);
    // equal = (rit == scrit);
    // equal = it == srit;
    // (void)equal;
}

void testReverseIterator(void) {
    test_reverse_iterator_constructors();
    test_base();
    test_dereference_operator();
    test_addition_operator();
    test_increment_operator();
    test_compound_assignment_operator();
    test_subtraction_operator();
    test_decrement_operator();
    test_arrow_dereference_operator();
    test_offset_operator();
    test_relational_operators();
    test_const_integration();
}
