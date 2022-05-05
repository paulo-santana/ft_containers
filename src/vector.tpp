#include "vector.hpp"

template <typename T>
ft::vector<T>::vector(const vector::allocator_type& alloc) {
    this->allocator = alloc;
}

template <typename T>
ft::vector<T>::vector(const vector& other) {
    (void)other;
}

template <typename T>
typename ft::vector<T>::allocator_type ft::vector<T>::get_allocator(void) const {
    return this->allocator;
}
