#pragma once
#ifndef VECTOR_ITERATOR_TPP
#define VECTOR_ITERATOR_TPP

#include "vector/iterator.hpp"

template <typename T>
ft::VectorIterator<T>::VectorIterator() { }

template <typename T>
ft::VectorIterator<T>::VectorIterator(ft::VectorIterator<T>::pointer _p) {
    this->p = _p;
}

template <typename T>
ft::VectorIterator<T>::VectorIterator(const ft::VectorIterator<T>& other) {
    this->p = other.p;
}

template <typename T>
bool ft::VectorIterator<T>::operator==(const ft::VectorIterator<T>& other) {
    return this->p == other.p;
}

template <typename T>
bool ft::VectorIterator<T>::operator!=(const ft::VectorIterator<T>& other) {
    return this->p != other.p;
}

template <typename T>
typename ft::VectorIterator<T>::reference ft::VectorIterator<T>::operator*() const {
    return *this->p;
};

template <typename T>
typename ft::VectorIterator<T>::pointer ft::VectorIterator<T>::operator->(void) const {
    return &*this->p;
}

template <typename T>
typename ft::VectorIterator<T> ft::VectorIterator<T>::operator++(int) {
    ft::VectorIterator<T> copy(*this);
    this->p++;
    return copy;
}

template <typename T>
typename ft::VectorIterator<T>& ft::VectorIterator<T>::operator++() {
    this->p++;
    return *this;
}

template <typename T>
typename ft::VectorIterator<T> ft::VectorIterator<T>::operator--(int) {
    ft::VectorIterator<T> copy(*this);
    this->p--;
    return copy;
}

template <typename T>
typename ft::VectorIterator<T>& ft::VectorIterator<T>::operator--() {
    this->p--;
    return *this;
}

template <typename T>
ft::VectorIterator<T> ft::VectorIterator<T>::operator+(difference_type offset) const {
    return VectorIterator<T>(this->p + offset);
}

template <typename T>
ft::VectorIterator<T> ft::VectorIterator<T>::operator-(difference_type offset) const {
    return VectorIterator<T>(this->p - offset);
}

template <typename T>
typename ft::VectorIterator<T>::difference_type ft::VectorIterator<T>::operator-(const VectorIterator &other) const {
    return this->p - other.p;
}

template <typename T>
bool ft::VectorIterator<T>::operator<(const VectorIterator &other) const {
    return this->p < other.p;
}

template <typename T>
bool ft::VectorIterator<T>::operator>(const VectorIterator &other) const {
    return this->p > other.p;
}

template <typename T>
bool ft::VectorIterator<T>::operator<=(const VectorIterator &other) const {
    return this->p <= other.p;
}

template <typename T>
bool ft::VectorIterator<T>::operator>=(const VectorIterator &other) const {
    return this->p >= other.p;
}

template <typename T>
ft::VectorIterator<T>& ft::VectorIterator<T>::operator+=(difference_type offset) {
    this->p += offset;
    return *this;
}

template <typename T>
ft::VectorIterator<T>& ft::VectorIterator<T>::operator-=(difference_type offset) {
    this->p -= offset;
    return *this;
}

template <typename T>
typename ft::VectorIterator<T>::reference ft::VectorIterator<T>::operator[](difference_type offset) {
    return *(this->p + offset);
}

template <typename T>
ft::VectorIterator<T>
operator+(typename ft::VectorIterator<T>::difference_type num, const ft::VectorIterator<T> &other) {
    return other + num;
}


#endif // !VECTOR_ITERATOR_TPP
