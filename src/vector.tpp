#include "vector.hpp"

template <typename T>
ft::vector<T>::vector(const vector::allocator_type& alloc) {
    this->allocator = alloc;
    this->data = this->allocator.allocate(1);
}

template <typename T>
ft::vector<T>::vector(const vector& other) {
    this->allocator = other.allocator;
    this->data = this->allocator.allocate(20);
}

template <typename T>
typename ft::vector<T>::allocator_type ft::vector<T>::get_allocator(void) const {
    return this->allocator;
}

template <typename T>
ft::vector<T>::~vector(void) {
    this->allocator.deallocate(data, 1);
}
