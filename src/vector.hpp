#pragma once
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <algorithm>
#include <cstddef>
#include <stdexcept>

#include "iterator_traits.hpp"
#include "vector/iterator.hpp"
#include "enable_if.hpp"
#include "type_traits.hpp"
#include "reverse_iterator.hpp"

#include "equal.hpp"
#include "lexicographical_compare.hpp"

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
    typedef ptrdiff_t                                   difference_type;

    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;

    typedef ft::VectorIterator<pointer, _Self>          iterator;
    typedef ft::VectorIterator<const_pointer, _Self>    const_iterator;
    typedef ft::reverse_iterator<iterator>              reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;

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
        fill_construct(n, val, alloc);
    }

    // range constructor
    template<typename InputIterator>
    vector(InputIterator start, InputIterator end, const allocator_type& alloc = allocator_type()) {
        typedef typename ft::is_integral<InputIterator>::type integral;
        range_construct_dispatch(start, end, alloc, integral());
    }

private:
    void fill_construct(size_type n, const value_type& val, const allocator_type& alloc) {
        this->num_items = n;
        this->current_capacity = n;
        this->allocator = alloc;
        this->max_capacity = alloc.max_size();

        this->data = this->allocator.allocate(n);

        for (size_type i = 0; i < this->num_items; i++) {
            this->allocator.construct(this->data + i, val);
        }
    }

    template<typename IntegralValue>
    void range_construct_dispatch(IntegralValue n, IntegralValue val, const allocator_type& alloc,
            ft::true_type) {
        fill_construct(n, val, alloc);
    }

    template<typename InputIterator>
    void range_construct_dispatch(InputIterator start, InputIterator end, const allocator_type& alloc,
            ft::false_type) {
        typedef typename ft::iterator_traits<InputIterator>::iterator_category category;

        range_construct_dispatch(start, end, alloc, category());
    }

    template<typename InputIterator>
    void range_construct_dispatch(InputIterator start, InputIterator end, const allocator_type& alloc, std::input_iterator_tag) {
        this->num_items = 0;
        this->current_capacity = 0;
        this->allocator = alloc;
        this->max_capacity = alloc.max_size();
        this->data = 0;

        while (start != end) {
            this->push_back(*start);
            ++start;
        }
    }

    template<typename ForwardIterator>
    void range_construct_dispatch(ForwardIterator start, ForwardIterator end, const allocator_type& alloc, std::forward_iterator_tag) {
        size_type size = std::distance(start, end);
        this->num_items = size;
        this->current_capacity = size;
        this->allocator = alloc;
        this->max_capacity = alloc.max_size();

        this->data = this->allocator.allocate(size);
        for(size_type i = 0; i < size; ++i, ++start) {
            this->allocator.construct(this->data + i, *start);
        }
    }

public:

    // copy
    vector(const vector &other) {
        this->current_capacity = other.current_capacity;
        this->num_items = other.num_items;
        this->allocator = allocator_type();
        this->max_capacity = this->allocator.max_size();

        if (other.data == 0) {
            this->data = 0;
            return;
        }
        this->data = this->allocator.allocate(other.current_capacity);
        this->shift_construct_backwards(other.data,
                other.data + other.num_items,
                this->data + this->num_items);
    }

    // destructor
    ~vector() {
        this->destroy_data(this->data, this->num_items);
        // TODO: investigar pq o tamanho aqui não importa
        this->allocator.deallocate(data, 1);
    }

    // assignment operator
    vector &operator=(const vector &other) {
        this->assign(other.begin(), other.end());
        return *this;
    }

    allocator_type get_allocator(void) const {
        return this->allocator;
    }

    bool empty(void) const {
        return this->num_items == 0;
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

    reverse_iterator rbegin(void) {
        return reverse_iterator(this->end());
    }

    const_reverse_iterator rbegin(void) const {
        return const_reverse_iterator(this->end());
    }

    reverse_iterator rend(void) {
        return reverse_iterator(this->begin());
    }

    const_reverse_iterator rend(void) const {
        return const_reverse_iterator(this->begin());
    }

    void resize(size_type n, value_type val = value_type()) {
        if (n == this->num_items)
            return;

        if (n < this->num_items) {
            size_type index = n;
            this->destroy_data(this->data + index, this->num_items - index);

        } else {
            if (n < this->current_capacity * 2)
                this->grow_vector(this->current_capacity * 2);
            else
                this->grow_vector(n);
            size_type index = this->num_items;
            while (index < n) {
                this->allocator.construct(&this->data[index], val);
                index++;
            }
        }
        this->num_items = n;
    }

    void reserve(size_type n) {
        if (n > this->max_size())
            throw std::length_error("vector::reserve");
        if (n <= this->current_capacity)
            return;

        this->grow_vector(n);
    }

    reference at(size_type n) {
        if (n >= this->size())
            throw std::out_of_range("index out of range");

        return this->data[n];
    }

    const_reference at(size_type n) const {
        if (n >= this->size())
            throw std::out_of_range("index out of range");

        return this->data[n];
    }

    reference front() {
        return *this->data;
    }

    const_reference front() const {
        return *this->data;
    }

    reference back() {
        return *(this->data + this->num_items - 1);
    }

    const_reference back() const {
        return *(this->data + this->num_items - 1);
    }

    reference operator[](size_type n) {
        return this->data[n];
    }

    const_reference operator[](size_type n) const {
        return this->data[n];
    }

    void assign(size_type n, const value_type& val) {
        fill_assign(n, val);
    }

    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last) {
        typedef typename ft::is_integral<InputIterator>::type integral;

        assign_dispatch(first, last, integral());
    }

private:
    template<typename Integral>
    void assign_dispatch(Integral n, Integral val, ft::true_type) {
        this->fill_assign(n, val);
    }

    template<typename Iterator>
    void assign_dispatch(Iterator first, Iterator last, ft::false_type) {
        typedef typename ft::iterator_traits<Iterator>::iterator_category category;
        this->range_assign(first, last, category());
    }

    void fill_assign(size_type n, const value_type& val) {

        bool mustReallocate = n > this->current_capacity;

        if (mustReallocate) {
            T* newBuffer = this->allocator.allocate(n);
            this->destroy_data(this->data, this->num_items);
            this->allocator.deallocate(this->data, this->current_capacity);
            this->data = newBuffer;
            this->current_capacity = n;

        } else {
            this->destroy_data(this->data, this->num_items);
        }
        for (size_type i = 0; i < n; i++) {
            this->allocator.construct(this->data + i, val);
        }

        this->num_items = n;
    }

    template<typename InputIterator>
    void range_assign(InputIterator first, InputIterator last, std::input_iterator_tag) {

        size_type new_size = 0;
        this->destroy_data(this->data, this->num_items);

        for (; new_size < this->num_items && first != last; new_size++, ++first) {
            this->allocator.construct(this->data + new_size, *first);
        }
        for (; first != last; ++first) {
            this->push_back(*first);
            ++new_size;
        }

        this->num_items = new_size;
    }

    template<typename ForwardIterator>
    void range_assign(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag) {
        size_type distance = static_cast<size_type>(last - first);
        bool mustReallocate = distance > this->current_capacity;
        if (mustReallocate) {
            T* newBuffer = this->allocator.allocate(distance);
            this->destroy_data(this->data, this->num_items);
            this->allocator.deallocate(this->data, this->current_capacity);
            this->data = newBuffer;
            this->current_capacity = distance;

        } else {
            this->destroy_data(this->data, this->num_items);
        }

        for (size_type i = 0; first != last; i++, first++) {
            this->allocator.construct(this->data + i, *first);
        }
        this->num_items = distance;
    }



public:
    void push_back(const value_type& x) {
        if (this->data == 0) {
            this->data = this->allocator.allocate(1);
            this->current_capacity = 1;
        } else if (this->num_items >= this->current_capacity) {
            grow_vector(this->current_capacity * 2);
        }

        allocator.construct(&this->data[this->num_items], x);
        this->num_items++;
    }

    void pop_back() {
        this->allocator.destroy(this->data + --this->num_items);
    }

    // insert a single element
    iterator insert(iterator position, const value_type& val) {
        pointer current_pos = position.base();
        pointer current_end = this->data + this->num_items;

        pointer target_ptr;

        if (this->num_items < this->current_capacity) {
            this->allocator.construct(current_end, *(current_end - 1));
            std::copy_backward(current_pos, current_end - 1, current_end);
            // this->allocator.construct(current_pos, val);
            *current_pos = val;
            target_ptr = current_pos;

        } else {
            target_ptr = insert_reallocating(current_pos, 1, val);
        }

        this->num_items++;
        return iterator(target_ptr);
    }

    // fill a range
    void insert(iterator position, size_type n, const value_type& val) {
        insert_fill(position, n, val);
    }

    // insert from a range
    template<typename InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last) {
        typedef typename ft::is_integral<InputIterator>::type isIntegral;

        insert_dispatch(position, first, last, isIntegral());
    }

private:
    void insert_fill(iterator& position, size_type n, const value_type& val) {
        pointer current_pos = position.base();
        pointer current_end = this->data + this->num_items;

        if (this->num_items + n <= this->current_capacity) {
            for (size_type i = 0; i < n; i++) {
                this->allocator.construct(current_end + i, value_type());
            }

            std::copy_backward(current_pos, current_end, current_end + n);
            std::fill(current_pos, current_pos + n, val);

        } else {
            insert_reallocating(current_pos, n, val);
        }
        this->num_items += n;

    }

    template<typename OtherIterator>
    void insert_range(iterator& position, OtherIterator first, OtherIterator& last) {
        typedef typename ft::iterator_traits<OtherIterator>::iterator_category category;

        insert_range(position, first, last, category());
    }

    template<typename InputIterator>
    void insert_range(iterator& position, InputIterator& first, InputIterator& last, std::input_iterator_tag) {
        if (position == this->end()) {
            for (; first != last; ++first) {
                this->push_back(*first);
            }

        } else {
            vector tmp(first, last, this->get_allocator());
            insert(position, tmp.begin(), tmp.end());
        }
    }

    template<typename ForwardIterator>
    void insert_range(iterator& position, ForwardIterator& first, ForwardIterator &last, std::forward_iterator_tag) {
        pointer current_pos = position.base();
        pointer current_end = this->data + this->num_items;

        size_type n = std::distance(first, last);
        if (this->num_items + n <= this->current_capacity) {
            for (size_type i = 0; i < n; i++) {
                this->allocator.construct(current_end, value_type());
            }
            std::copy_backward(current_pos, current_end, current_end + n);
            std::copy(first, last, position);
        } else {
            pointer current_data = this->data;
            pointer target_ptr;

            this->current_capacity = calculate_new_size(n);

            pointer target_data = this->allocator.allocate(this->current_capacity);
            target_ptr = target_data + (current_pos - current_data);

            this->copy_data(target_data, current_data, current_pos);

            for (size_type i = 0; i < n; ++i, ++first) {
                this->allocator.construct(target_ptr + i, *first);
            }

            this->copy_data(target_ptr + n, current_pos, current_end);

            this->destroy_data(this->data, this->num_items);
            this->allocator.deallocate(this->data, this->num_items);
            this->data = target_data;

        }

        this->num_items += n;

    }

    template<typename Integral>
    void insert_dispatch(iterator& position, Integral& n, const Integral& val, ft::true_type) {
        insert_fill(position, n, val);
    }

    template<typename OtherIterator>
    void insert_dispatch(iterator& position, OtherIterator& first, OtherIterator& last, ft::false_type) {
        insert_range(position, first, last);
    }

    void shift_construct_backwards(pointer start, pointer end, pointer result) {
        while (start != end) {
            this->allocator.construct(--result, *--end);
        }
    }

    pointer insert_reallocating(pointer current_pos, size_type n, const value_type& val) {
        pointer current_data = this->data;
        pointer current_end = this->end().base();
        pointer target_ptr;

        this->current_capacity = calculate_new_size(n);

        pointer target_data = this->allocator.allocate(this->current_capacity);
        target_ptr = target_data + (current_pos - current_data);

        this->copy_data(target_data, current_data, current_pos);

        int i = n;

        while (i--)
            this->allocator.construct(target_ptr + i, val);

        this->copy_data(target_ptr + n, current_pos, current_end);

        this->destroy_data(this->data, this->num_items);
        this->allocator.deallocate(this->data, this->num_items);
        this->data = target_data;

        return target_ptr;

    }

public:
    iterator erase(iterator position) {
        pointer ptr = position.base();

        std::copy(ptr + 1, this->end().base(), ptr);
        this->allocator.destroy((this->end() - 1).base());

        this->num_items--;
        return iterator(ptr);
    }

    iterator erase(iterator first, iterator last) {
        pointer ptr = first.base();
        pointer last_ptr = last.base();

        size_type size = last_ptr - ptr;

        std::copy(last_ptr, end().base(), ptr);
        this->destroy_data(end().base() - size, size);
        this->num_items -= size;
        return iterator(ptr);
    }


    void swap(vector& other) {
        size_type size = this->num_items;
        size_type capacity = this->current_capacity;
        T* tmp = this->data;

        this->data = other.data;
        this->num_items = other.num_items;
        this->current_capacity = other.current_capacity;

        other.data = tmp;
        other.num_items = size;
        other.current_capacity = capacity;
    }

    void clear() {
        this->destroy_data(this->data, this->num_items);
        this->num_items = 0;
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

    void copy_data(T* dest, T* src, T* src_end) {
        int i = 0;
        while (src < src_end) {
            this->allocator.construct(dest + i, *src++);
            i++;
        }
    }

    void destroy_data(T* _data, size_type n) {
        for (size_type i = 0; i < n; i++) {
            this->allocator.destroy(_data + i);
        }
    }

    void grow_vector(size_type new_capacity) {
        T* oldData = this->data;

        if (new_capacity < this->current_capacity)
            throw std::bad_alloc();

        this->data = this->allocator.allocate(new_capacity);
        this->copy_data(this->data, oldData);
        this->current_capacity = new_capacity;
        this->destroy_data(oldData, this->num_items);
        this->allocator.deallocate(oldData, this->num_items);

    }

    size_type calculate_new_size(size_type incomingAmount) {
        size_type newSize;

        if (this->num_items + incomingAmount > this->num_items * 2)
            newSize = this->num_items + incomingAmount;
        else if (this->current_capacity == 0)
            newSize = incomingAmount;
        else
            newSize = this->num_items * 2;

        return newSize;
    }
};

template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}
template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(lhs == rhs);
}
template <class T, class Alloc>
bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(lhs > rhs);
}
template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return rhs < lhs;
}
template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(lhs < rhs);
}

template <class T, class Alloc>
void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y) {
    x.swap(y);
}

}

#endif // !VECTOR_HPP
