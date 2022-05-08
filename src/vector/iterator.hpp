#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "internals/iterator_base.hpp"
#include <string>

namespace ft {

    template <typename T>
    class VectorIterator : public ft::iterator<ft::random_access_iterator_tag, T>
    {
            typedef typename ft::iterator<ft::random_access_iterator_tag, T> _Base;
            typedef VectorIterator<T> _Self;

        public:

            typedef typename _Base::value_type          value_type;
            typedef typename _Base::pointer             pointer;
            typedef typename _Base::reference           reference;
            typedef typename _Base::difference_type     difference_type;
            typedef typename _Base::iterator_category   iterator_category;

            VectorIterator();
            VectorIterator(pointer _p);
            VectorIterator(const VectorIterator &);
            VectorIterator &operator=(const VectorIterator &);
            ~VectorIterator() {};

            bool                operator==(const VectorIterator &);
            bool                operator!=(const VectorIterator &);
            pointer             operator->(void);
            VectorIterator      operator++(int);
            VectorIterator&     operator++();
            VectorIterator      operator--(int);
            VectorIterator&     operator--();

            VectorIterator      operator+(difference_type) const ;
            VectorIterator      operator-(difference_type) const ;
            difference_type     operator-(const VectorIterator&) const ;

            reference operator*() const {
                return *this->p;
            }

        private:
            pointer p;
    };


    template <typename T>
    ft::VectorIterator<T>
    operator+(typename ft::VectorIterator<T>::difference_type num, const ft::VectorIterator<T> &other);

#include "vector/iterator.tpp"
}

#endif // !ITERATOR
