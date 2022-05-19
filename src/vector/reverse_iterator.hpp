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

        reverse_iterator(const reverse_iterator& other): current(other.current) {}

        template<typename _Other>
        reverse_iterator(const reverse_iterator<_Other> &other): current(other.base()) {}

        ~reverse_iterator() {}

        iterator_type base() const {
            return this->current;
        }

        reference operator*() const {
            return *(--iterator_type(current));
        }

        pointer operator->() const {
            return &*(--iterator_type(current));
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

        friend difference_type operator-(const reverse_iterator& lhs, const reverse_iterator& rhs) {
            return rhs.base() - lhs.base();
        }

        reverse_iterator& operator--() {
            ++this->current;
            return *this;
        }

        reverse_iterator operator--(int) {
            return reverse_iterator(this->current++);
        }

        reverse_iterator& operator-=(difference_type n) {
            this->current += n;
            return *this;
        }

        reference operator[](difference_type n) const {
            return this->base()[-n - 1];
        }

        template<typename _Other>
        friend difference_type operator-(const reverse_iterator& me, const reverse_iterator<_Other>& other) {
            return other.base() - me.base();
        }

    protected:
        _Iterator current;
    };

    template<typename _Iter>
    bool operator==(const reverse_iterator<_Iter>& lhs, const reverse_iterator<_Iter>& rhs) {
        return lhs.base() == rhs.base();
    }

    template<typename _Iter>
    bool operator!=(const reverse_iterator<_Iter>& lhs, const reverse_iterator<_Iter>& rhs) {
        return lhs.base() != rhs.base();
    }

    template<typename _Iter>
    bool operator<(const reverse_iterator<_Iter>& lhs, const reverse_iterator<_Iter>& rhs) {
        return lhs.base() > rhs.base();
    }

    template<typename _Iter>
    bool operator>(const reverse_iterator<_Iter>& lhs, const reverse_iterator<_Iter>& rhs) {
        return lhs.base() < rhs.base();
    }

    template<typename _Iter>
    bool operator<=(const reverse_iterator<_Iter>& lhs, const reverse_iterator<_Iter>& rhs) {
        return lhs.base() >= rhs.base();
    }

    template<typename _Iter>
    bool operator>=(const reverse_iterator<_Iter>& lhs, const reverse_iterator<_Iter>& rhs) {
        return lhs.base() <= rhs.base();
    }

    template<typename _IterL, typename _IterR>
    bool operator==(const reverse_iterator<_IterL>& lhs, const reverse_iterator<_IterR>& rhs) {
        return lhs.base() == rhs.base();
    }

    template<typename _IterL, typename _IterR>
    bool operator!=(const reverse_iterator<_IterL>& lhs, const reverse_iterator<_IterR>& rhs) {
        return lhs.base() != rhs.base();
    }

    template<typename _IterL, typename _IterR>
    bool operator<(const reverse_iterator<_IterL>& lhs, const reverse_iterator<_IterR>& rhs) {
        return lhs.base() > rhs.base();
    }

    template<typename _IterL, typename _IterR>
    bool operator>(const reverse_iterator<_IterL>& lhs, const reverse_iterator<_IterR>& rhs) {
        return lhs.base() < rhs.base();
    }

    template<typename _IterL, typename _IterR>
    bool operator<=(const reverse_iterator<_IterL>& lhs, const reverse_iterator<_IterR>& rhs) {
        return lhs.base() >= rhs.base();
    }

    template<typename _IterL, typename _IterR>
    bool operator>=(const reverse_iterator<_IterL>& lhs, const reverse_iterator<_IterR>& rhs) {
        return lhs.base() <= rhs.base();
    }

}

#endif // !REVERSE_ITERATOR_HPP
