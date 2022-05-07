#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "vector/iterator.hpp"

namespace ft
{
    template <typename T, typename Alloc = std::allocator<T> >
    class vector
    {
    public:
        typedef int                     value_type;
        typedef std::allocator<T>       allocator_type;

        typedef std::size_t             size_type;

        typedef ft::VectorIterator<T>   iterator;
        typedef ft::VectorIterator<T>   const_iterator;

        // default constructor
        vector(const allocator_type& alloc = allocator_type());

        // fill
        vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

        // copy
        vector(const vector &other);

        vector &operator=(const vector &other);
        ~vector();

        allocator_type get_allocator(void) const;

        size_type size(void);
        size_type capacity(void);

        void push_back(int x);

        // iterator
        iterator begin(void);
        iterator end(void);
        const iterator begin(void) const;

    private:
        T *data;

        size_type num_items;
        size_type current_capacity;
        size_type max_size;

        allocator_type allocator;

        void copy_data(T* dest, T* src);
        void destroy_data(T* _data, size_type n);
        void grow_vector(void);
    };

#include "vector/vector.tpp"
}

#endif // !VECTOR_HPP
