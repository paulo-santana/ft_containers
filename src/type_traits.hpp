#pragma once
#ifndef TYPE_TRATIS_HPP
#define TYPE_TRATIS_HPP

namespace ft {

struct true_type {};
struct false_type {};

template <class T>
struct is_integral {
    enum { value = 0 };
    typedef false_type type;
};

template<>
struct is_integral<bool> {
    enum { value = 1 };
    typedef true_type type;
};

template<>
struct is_integral<int> {
    enum { value = 1 };
    typedef true_type type;
};

template<>
struct is_integral<unsigned int> {
    enum { value = 1 };
    typedef true_type type;
};

template<>
struct is_integral<long> {
    enum { value = 1 };
    typedef true_type type;
};

template<>
struct is_integral<unsigned long> {
    enum { value = 1 };
    typedef true_type type;
};

}

#endif // !TYPE_TRATIS_HPP
