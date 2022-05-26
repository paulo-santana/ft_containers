#pragma once
#ifndef EQUAL_HPP
#define EQUAL_HPP

namespace ft {

template <typename Iter1, typename Iter2>
bool equal(Iter1 first, Iter1 last, Iter2 other) {
    while (first != last) {
        if (!(*first == *other)) {
            return false;
        }
        ++first;
        ++other;
    }
    return true;
}

template <typename Iter1, typename Iter2, typename BinaryPredicate>
bool equal(Iter1 first, Iter1 last, Iter2 other, BinaryPredicate are_equal) {
    while (first != last) {
        if (!are_equal(*first, *other)) {
            return false;
        }
        ++first;
        ++other;
    }
    return true;
}

}

#endif // !EQUAL_HPP
