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
    typedef _Iterator                                                   iterator_type;
    typedef typename ft::iterator_traits<_Iterator>::iterator_category  iterator_category;
    typedef typename ft::iterator_traits<_Iterator>::value_type         value_type;
    typedef typename ft::iterator_traits<_Iterator>::difference_type    difference_type;
    typedef typename ft::iterator_traits<_Iterator>::pointer            pointer;
    typedef typename ft::iterator_traits<_Iterator>::reference          reference;

    reverse_iterator(): current() {}
    explicit reverse_iterator(iterator_type iter): current(iter) {}
    reverse_iterator(const reverse_iterator &other): current(other.current) {}
    ~reverse_iterator() {}

    iterator_type base() const {
        return this->current;
    }

    reference operator*() const {
        return *(--iterator_type(current));
    }

    reverse_iterator operator+(difference_type n) const {
        return reverse_iterator(this->base() - n);
    }

    friend reverse_iterator operator+(difference_type n, const reverse_iterator& me) {
        return me + n;
    }

    reverse_iterator& operator++() {
        --this->current;
        return *this;
    }

    reverse_iterator operator++(int) {
        reverse_iterator tmp = *this;
        ++*this;
        return tmp;
    }
    
    reverse_iterator& operator+=(difference_type n) {
        this->current -= n;
        return *this;
    }

    reverse_iterator operator-(difference_type n) {
        return reverse_iterator(this->base() + n);
    }
    
    reverse_iterator& operator-=(difference_type n) {
        this->current += n;
        return *this;
    }

protected:
    _Iterator current;
};

}

#endif // !REVERSE_ITERATOR_HPP
