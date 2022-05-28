#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft {

template <typename Iter1, typename Iter2>
bool lexicographical_compare(
        Iter1 first1, Iter1 last1,
        Iter2 first2, Iter2 last2) {

    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) return true;
        else if (*first2 < *first1) return false;
        ++first1;
        ++first2;
    }
    return (first1 == last1 && first2 != last2);
}

template <typename Iter1, typename Iter2, typename Compare>
bool lexicographical_compare(
        Iter1 first1, Iter1 last1,
        Iter2 first2, Iter2 last2, Compare pred) {

    while (first1 != last1 && first2 != last2) {
        if (pred(*first1, *first2)) return true;
        else if (pred(*first2, *first1)) return false;
        ++first1;
        ++first2;
    }
    return (first1 == last1 && first2 != last2);
}

}

#endif // !LEXICOGRAPHICAL_COMPARE_HPP
