#pragma once
#ifndef SET_HPP
# define SET_HPP

#include <functional>
#include <memory>
#include "internals/red_black_tree.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template<
    typename T,
    typename Compare = std::less<T>,
    typename Alloc = std::allocator<T> >
class set {
    typedef ft::RBTree<T, T, std::_Identity<T>, Compare>    tree_type;
    typedef typename tree_type::Node                        node_type;

    tree_type* tree;

public:
    typedef T                                           key_type;
    typedef T                                           value_type;
    typedef Compare                                     key_compare;
    typedef Compare                                     value_compare;

    typedef std::allocator<T>                           allocator_type;
    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;

    typedef typename tree_type::iterator                iterator;
    typedef typename tree_type::const_iterator          const_iterator;

    typedef ft::reverse_iterator<iterator>              reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;

    typedef std::ptrdiff_t                              difference_type;
    typedef std::size_t                                 size_type;

    explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
        this->tree = new tree_type(comp, alloc);
    }

    size_type size() const {
        return this->tree->size();
    }
};

}

#endif // !SET_HPP
