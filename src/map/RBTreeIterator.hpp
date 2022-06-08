#pragma once
#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "internals/red_black_tree_node.hpp"
#include "iterator_traits.hpp"
#include <iterator>
#include "internals/iterator_base.hpp"

namespace ft {

// for a map, Value is ft::pair
// so value_type is a pair
// for a set, Value is Key
// Value = const pair<>
template<typename Key, typename Value>
class RBTreeIterator {

public:
    typedef Key                             key_type;
    typedef Value                           value_type;
    typedef Value*                          pointer;
    typedef Value&                          reference;
    typedef RBTreeNode<Key, Value>          node_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;

    node_type* _M_node;

    RBTreeIterator(): _M_node() { }

    node_type* base() const {
        return _M_node;
    }

    RBTreeIterator(const RBTreeIterator& other) : _M_node(other.base()) { }

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

    bool operator==(const RBTreeIterator& other) {
        return _M_node == other._M_node;
    }

    bool operator!=(const RBTreeIterator& other) {
        return _M_node != other._M_node;
    }

    RBTreeIterator& operator++() {
        _M_node = _M_node->successor();
        return *this;
    }

    RBTreeIterator operator++(int) {
        RBTreeIterator tmp = *this;
        _M_node = _M_node->successor();
        return tmp;
    }

    RBTreeIterator& operator--() {
        _M_node = _M_node->predecessor();
        return *this;
    }

    RBTreeIterator operator--(int) {
        RBTreeIterator tmp = *this;
        _M_node = _M_node->predecessor();
        return tmp;
    }
};

template<typename Key, typename Value>
class RBTreeConstIterator {

    typedef RBTreeIterator<Key, Value>      iterator;

public:
    typedef Key                             key_type;
    typedef Value                           value_type;
    typedef const Value*                    pointer;
    typedef const Value&                    reference;
    typedef const RBTreeNode<Key, Value>    node_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;

    node_type* _M_node;

    RBTreeConstIterator(): _M_node() { }

    RBTreeConstIterator(const iterator& other): _M_node(other._M_node) { }

    RBTreeConstIterator(const RBTreeConstIterator& other): _M_node(other._M_node) { }

    RBTreeConstIterator(node_type* node): _M_node(node) {}

    RBTreeConstIterator& operator=(const RBTreeConstIterator& other) {
        this->_M_node = other._M_node;
    }

    ~RBTreeConstIterator() { }

    reference operator*() const {
        return _M_node->value;
    }

    pointer operator->() const {
        return &_M_node->value;
    }

    friend bool operator==(const RBTreeConstIterator& me, const RBTreeConstIterator& other) {
        return me._M_node == other._M_node;
    }

    friend bool operator!=(const RBTreeConstIterator& me, const RBTreeConstIterator& other) {
        return me._M_node != other._M_node;
    }

    RBTreeConstIterator& operator++() {
        _M_node = _M_node->successor();
        return *this;
    }

    RBTreeConstIterator operator++(int) {
        RBTreeConstIterator tmp = *this;
        _M_node = _M_node->successor();
        return tmp;
    }

    RBTreeConstIterator& operator--() {
        _M_node = _M_node->predecessor();
        return *this;
    }

    RBTreeConstIterator operator--(int) {
        RBTreeConstIterator tmp(*this);
        _M_node = _M_node->predecessor();
        return tmp;
    }
};

}

#endif // !MAP_ITERATOR_HPP
