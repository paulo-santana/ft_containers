#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "internals/iterator_base.hpp"

namespace ft {

    template <typename T>
    class VectorIterator : public ft::iterator<ft::random_access_iterator_tag, T>
    {
        public:
            typedef typename ft::iterator<ft::random_access_iterator_tag, T> _Base;

            typedef typename _Base::value_type          value_type;
            typedef typename _Base::pointer             pointer;
            typedef typename _Base::reference           reference;
            typedef typename _Base::iterator_category   iterator_category;

            VectorIterator();
            VectorIterator(pointer _p);
            VectorIterator(const VectorIterator &);
            VectorIterator &operator=(const VectorIterator &);
            ~VectorIterator() {};

            bool operator==(const VectorIterator &);
            bool operator!=(const VectorIterator &);
            pointer operator->(void);
            VectorIterator<T> operator++(int);
            VectorIterator<T>& operator++();

            reference operator*() const {
                return *this->p;
            }

        private:
            pointer p;
    };

#include "./iterator.tpp"
}


#endif // !ITERATOR
