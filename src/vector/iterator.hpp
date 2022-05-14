#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "enable_if.hpp"
#include "internals/iterator_base.hpp"
#include "iterator_traits.hpp"


namespace ft {

template <typename T, typename _Container>
class VectorIterator : public ft::iterator<std::random_access_iterator_tag, T>
{
    typedef typename ft::iterator<std::random_access_iterator_tag, T> _Base;
    typedef VectorIterator<T, _Container> _Self;

    typedef ft::iterator_traits<T> my_traits;

public:

    typedef typename my_traits::value_type          value_type;
    typedef typename my_traits::pointer             pointer;
    typedef typename my_traits::reference           reference;
    typedef typename my_traits::difference_type     difference_type;
    typedef typename my_traits::iterator_category   iterator_category;

    VectorIterator() : p(T()) { }

    explicit VectorIterator(const T& _p) : p(_p) { }

    template<typename _Iter>
    VectorIterator(const VectorIterator<_Iter, 
            typename ft::enable_if<
            (std::__are_same<_Iter, typename _Container::pointer>::__value),
            _Container>::type>& _p)
    : p(_p.base()) { }

    ~VectorIterator() {};

    reference operator*() const { return *this->p; }
    pointer operator->() const { return this->p; }

    bool operator==(const VectorIterator &other) const { return p == other.base(); }
    bool operator!=(const VectorIterator &other) const { return p != other.base(); }

    VectorIterator& operator++() {
        this->p++;
        return *this;
    };
    VectorIterator operator++(int) {
        VectorIterator copy(*this);
        this->p++;
        return copy;
    }
    VectorIterator& operator--() {
        this->p--;
        return *this;
    };
    VectorIterator operator--(int) {
        VectorIterator copy(*this);
        this->p--;
        return copy;
    }

    VectorIterator operator+(difference_type offset) const {
        return VectorIterator(this->p + offset);
    }

    VectorIterator operator-(difference_type offset) const {
        return VectorIterator(this->p - offset);
    }

    difference_type operator-(const VectorIterator& other) const {
        return this->p - other.base();
    }

    bool operator<(const VectorIterator& other) const {
        return this->p < other.base();
    }

    bool operator>(const VectorIterator& other) const {
        return this->p > other.base();
    }

    bool operator<=(const VectorIterator& other) const {
        return this->p <= other.base();
    }

    bool operator>=(const VectorIterator& other) const {
        return this->p >= other.base();
    }

    VectorIterator& operator+=(difference_type offset) {
        this->p += offset;
        return *this;
    }

    VectorIterator& operator-=(difference_type offset) {
        this->p -= offset;
        return *this;

    }

    reference operator[](difference_type offset) const {
        return this->p[offset];
    }

    friend VectorIterator operator+(difference_type offset, const _Self& me) {
        return me + offset;
    }

    const T& base() const {
        return this->p;
    }

protected:
    T p;
};

}

#endif // !ITERATOR
