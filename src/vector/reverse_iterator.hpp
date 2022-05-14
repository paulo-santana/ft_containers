#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "internals/iterator_base.hpp"
#include "iterator_traits.hpp"
#include <iostream>

namespace ft {

template<typename _Iterator>
class reverse_iterator
: public ft::iterator<
  typename ft::iterator_traits<_Iterator>::iterator_category,
  typename ft::iterator_traits<_Iterator>::value_type,
  typename ft::iterator_traits<_Iterator>::difference_type,
  typename ft::iterator_traits<_Iterator>::pointer,
  typename ft::iterator_traits<_Iterator>::reference
  >
{
public:
    reverse_iterator(): current() {}
    explicit reverse_iterator(_Iterator iter): current(iter) {}
    reverse_iterator(const reverse_iterator &other): current(other.current) {}
    ~reverse_iterator() {}

protected:
    _Iterator current;
};

}

#endif // !REVERSE_ITERATOR_HPP
