#pragma once
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "vector/iterator.hpp"
#include <memory>

namespace ft
{

template <typename T, typename Alloc = std::allocator<T> >
class vector
{
    typedef ft::vector<T, Alloc> _Self;
public:
    typedef T                                           value_type;
    typedef std::allocator<T>                           allocator_type;
    typedef std::size_t                                 size_type;

    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;

    typedef ft::VectorIterator<pointer, _Self>                 iterator;
    typedef ft::VectorIterator<const_pointer, _Self>           const_iterator;

    // default constructor
    vector(const allocator_type& alloc = allocator_type()) {
        this->data = 0;
        this->num_items = 0;
        this->current_capacity = 0;
        this->max_capacity = this->allocator.max_size();
        this->allocator = alloc;
    }

    // fill constructor
    vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
        this->num_items = n;
        this->current_capacity = n;
        this->allocator = alloc;
        this->max_capacity = alloc.max_size();

        this->data = this->allocator.allocate(n);

        for (size_type i = 0; i < this->num_items; i++) {
            this->allocator.construct(this->data + i, val);
        }
    }

    // copy
    vector(const vector &other) {
        *this = other;
    }

    // destructor
    ~vector() {
        // TODO: investigar pq o tamanho aqui não importa
        this->allocator.deallocate(data, 1);
    }

    // assignment operator
    vector &operator=(const vector &other) {
        this->current_capacity = other.current_capacity;
        this->allocator = other.allocator;
        this->num_items = other.num_items;
        this->data = this->allocator.allocate(this->current_capacity);

        for (size_type i = 0; i < this->num_items; i++) {
            this->allocator.construct(this->data + i, other.data[i]);
        }
    }

    allocator_type get_allocator(void) const {
        return this->allocator;
    }

    size_type size(void) const {
        return this->num_items;
    }

    size_type max_size(void) {
        return this->max_capacity;
    }

    size_type capacity(void) {
        return this->current_capacity;
    }

    void push_back(int x) {
        if (this->data == 0) {
            this->data = this->allocator.allocate(1);
            this->current_capacity = 1;
        } else if (this->num_items + 1 > this->current_capacity) {
            grow_vector();
        }

        this->data[this->num_items] = x;
        this->num_items++;
    }

    // iterator things
    iterator begin(void) {
        return VectorIterator<pointer, _Self>(this->data);
    }

    iterator end(void) {
        return VectorIterator<pointer, _Self>(this->data + this->num_items);
    }

    const_iterator begin(void) const {
        return VectorIterator<const_pointer, _Self >(this->data);
    }

    const_iterator end(void) const {
        return VectorIterator<const_pointer, _Self>(this->data + this->num_items);
    }

private:
    T *data;

    size_type num_items;
    size_type current_capacity;
    size_type max_capacity;

    allocator_type allocator;

    void copy_data(T* dest, T* src) {

        for (size_type i = 0; i < this->num_items; i++) {
            this->allocator.construct(dest + i, src[i]);
        }
    }
    void destroy_data(T* _data, size_type n) {
        for (size_type i = 0; i < n; i++) {
            this->allocator.destroy(_data + i);
        }
    }

    void grow_vector(void) {
        T* oldData = this->data;

        if (this->current_capacity * 2 < this->current_capacity)
            throw std::bad_alloc();

        this->data = this->allocator.allocate(this->current_capacity * 2);
        this->copy_data(this->data, oldData);
        this->current_capacity = this->current_capacity * 2;
        this->destroy_data(oldData, this->num_items);
        this->allocator.deallocate(oldData, this->num_items);

    }
};

}

#endif // !VECTOR_HPP
