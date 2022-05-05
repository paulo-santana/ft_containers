#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft
{
    template <typename T>
    class vector
    {
    public:
        typedef int                 value_type;
        typedef std::allocator<T>   allocator_type;

        typedef std::size_t         size_type;

        // default constructor
        vector(const allocator_type& alloc = allocator_type());

        // fill
        vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

        // copy
        vector(const vector &other);

        vector &operator=(const vector &other);
        ~vector();

        allocator_type get_allocator(void) const;

    private:
        T *data;

        allocator_type allocator;
    };

}

#endif // !VECTOR_HPP
