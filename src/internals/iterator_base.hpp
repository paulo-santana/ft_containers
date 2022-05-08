#ifndef ITERATOR_BASE_HPP
#define ITERATOR_BASE_HPP


#include <cstddef>
namespace ft {

template <
    typename Category,
    typename T,
    typename Distance = std::ptrdiff_t,
    typename Pointer = T*,
    typename Reference = T&
    >
struct iterator
{
    typedef T value_type;
    typedef Pointer pointer;
    typedef Reference reference;
    typedef Category iterator_category;
    typedef Distance difference_type;
};

}

#endif // !ITERATOR_BASE_HPP
