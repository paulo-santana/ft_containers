#pragma once
#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "internals/red_black_tree_node.hpp"
#include "iterator_traits.hpp"
#include <iterator>
#include "internals/iterator_base.hpp"

namespace ft {

// for a map, Value is ft::pair
// for a map, Value is ft::pair
// so value_type is a pair
template<typename Key, typename Value>
class RBTreeIterator {

public:
    typedef Key                             key_type; // pair.first;
    typedef Value                           value_type; // pair {first, second}
    typedef Value*                          pointer;
    typedef Value&                          reference;
    typedef RBTreeNode<Key, Value>          node_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;

    RBTreeIterator(): _M_node() { }

    RBTreeIterator(const RBTreeIterator& other): _M_node(other._M_node) { }

    RBTreeIterator(node_type* node): _M_node(node) {}

    RBTreeIterator& operator=(const RBTreeIterator& other) {
        this->_M_node = other._M_node;
    }

    ~RBTreeIterator() { }

    reference operator*() const {
        return _M_node->value;
    }

    pointer operator->() const {
        return &_M_node->value;
    }

    // ++iter
    RBTreeIterator& operator++() {
        // _M_node++;
        // _M_node = _M_node->successor();
        return *this;
    }

    // iter++
    RBTreeIterator operator++(int) {
        RBTreeIterator tmp = *this;
        _M_node = _M_node->successor();
        return tmp;
    }
    node_type* _M_node;
};

}

#endif // !MAP_ITERATOR_HPP
