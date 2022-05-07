#pragma once
#ifndef VECTOR_ITERATOR_TPP
#define VECTOR_ITERATOR_TPP

#include "vector/iterator.hpp"

template <typename T>
ft::VectorIterator<T>::VectorIterator() {
}

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
typename ft::VectorIterator<T>::pointer ft::VectorIterator<T>::operator->(void) {
    return &*this->p;
}

#endif // !VECTOR_ITERATOR_TPP
