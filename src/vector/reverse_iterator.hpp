#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "internals/iterator_base.hpp"
#include "iterator_traits.hpp"

namespace ft {

template<typename _Iter>
class reverse_iterator
: public ft::iterator<
  typename ft::iterator_traits<_Iter>::iterator_category,
  typename ft::iterator_traits<_Iter>::value_type,
  typename ft::iterator_traits<_Iter>::difference_type,
  typename ft::iterator_traits<_Iter>::pointer,
  typename ft::iterator_traits<_Iter>::reference
  >
{
public:
    reverse_iterator(): current() {}
    reverse_iterator(const reverse_iterator &other): current(other.current) {}
    ~reverse_iterator() {}

protected:
    _Iter current;
};

}

#endif // !REVERSE_ITERATOR_HPP
