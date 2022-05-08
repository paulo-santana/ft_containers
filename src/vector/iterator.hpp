#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "internals/iterator_base.hpp"
#include "iterator_traits.hpp"
#include <string>

namespace ft {

template <typename T>
    class VectorIterator : public ft::iterator<std::random_access_iterator_tag, T>
{
    typedef typename ft::iterator<std::random_access_iterator_tag, T> _Base;
    typedef VectorIterator<T> _Self;

    typedef ft::iterator_traits<_Self> my_traits;

public:

    typedef typename my_traits::value_type          value_type;
    typedef typename my_traits::pointer             pointer;
    typedef typename my_traits::reference           reference;
    typedef typename my_traits::difference_type     difference_type;
    typedef typename my_traits::iterator_category   iterator_category;

    VectorIterator();
    VectorIterator(pointer _p);
    VectorIterator(const VectorIterator &);
    VectorIterator &operator=(const VectorIterator &);
    ~VectorIterator() {};

    reference           operator*(void) const ;
    pointer             operator->(void) const ;

    bool                operator==(const VectorIterator &) const ;
    bool                operator!=(const VectorIterator &) const ;
    VectorIterator      operator++(int);
    VectorIterator&     operator++();
    VectorIterator      operator--(int);
    VectorIterator&     operator--();

    VectorIterator      operator+(difference_type) const ;
    VectorIterator      operator-(difference_type) const ;
    difference_type     operator-(const VectorIterator&) const ;

    bool                operator<(const VectorIterator&) const ;
    bool                operator>(const VectorIterator&) const ;
    bool                operator<=(const VectorIterator&) const ;
    bool                operator>=(const VectorIterator&) const ;

    VectorIterator&     operator+=(difference_type) ;
    VectorIterator&     operator-=(difference_type) ;

    reference           operator[](difference_type) const ;

    template<class C>
        friend VectorIterator operator+(difference_type, VectorIterator);

private:
    pointer p;
};

#include "vector/iterator.tpp"
}

#endif // !ITERATOR
