#pragma once
#include <new>
#ifndef VECTOR_TPP
# define VECTOR_TPP

#include "../vector.hpp"
#include "vector/iterator.hpp"

template <typename T, typename Alloc>
ft::vector<T, Alloc>::vector(const vector::allocator_type& alloc) {
    this->data = 0;
    this->num_items = 0;
    this->current_capacity = 0;
    this->max_size = this->allocator.max_size();
    this->allocator = alloc;
}

template <typename T, typename Alloc>
ft::vector<T, Alloc>::vector(const vector& other) {
    this->current_capacity = other.current_capacity;
    this->allocator = other.allocator;
    this->num_items = other.num_items;
    this->data = this->allocator.allocate(this->current_capacity);

    for (size_type i = 0; i < this->num_items; i++) {
        this->allocator.construct(this->data + i, other.data[i]);
    }
}

template <typename T, typename Alloc>
typename ft::vector<T, Alloc>::allocator_type ft::vector<T, Alloc>::get_allocator(void) const {
    return this->allocator;
}

template <typename T, typename Alloc>
ft::vector<T, Alloc>::~vector(void) {
    this->allocator.deallocate(data, 1);
}

template <typename T, typename Alloc>
typename ft::vector<T, Alloc>::size_type ft::vector<T, Alloc>::size(void) {
    return this->num_items;
}

template <typename T, typename Alloc>
typename ft::vector<T, Alloc>::size_type ft::vector<T, Alloc>::capacity(void) {
    return this->current_capacity;
}

template <typename T, typename Alloc>
void ft::vector<T, Alloc>::copy_data(T* dest, T* src) {

    for (size_type i = 0; i < this->num_items; i++) {
        this->allocator.construct(dest + i, src[i]);
    }
}

template <typename T, typename Alloc>
void ft::vector<T, Alloc>::grow_vector() {
    T* oldData = this->data;

    if (this->current_capacity * 2 < this->current_capacity)
        throw std::bad_alloc();

    this->data = this->allocator.allocate(this->current_capacity * 2);
    this->copy_data(this->data, oldData);
    this->current_capacity = this->current_capacity * 2;
}

template <typename T, typename Alloc>
void ft::vector<T, Alloc>::push_back(int x) {
    if (this->data == 0) {
        this->data = this->allocator.allocate(1);
        this->current_capacity = 1;
    } else if (this->num_items + 1 > this->current_capacity) {
        grow_vector();
    }

    this->data[this->num_items] = x;
    this->num_items++;
}

template <typename T, typename Alloc>
typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::begin() {
    return VectorIterator<T>(this->data);
}


#endif // !VECTOR_TPP
