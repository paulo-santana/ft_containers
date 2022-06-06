#pragma once
#include "internals/red_black_tree.hpp"
#include "map/RBTreeIterator.hpp"
#include "pair.hpp"
#include <memory>
#ifndef MAP_HPP
#define MAP_HPP

#include <functional>

namespace ft {

// class `map<
// std::basic_string<char>,
// int,
// std::less<std::basic_string<char> >,
// std::allocator<std::pair<const std::basic_string<char>, int> > >`  
template<
    typename Key,
    typename Value,
    typename Compare = std::less<Key>,
    typename Allocator = std::allocator<ft::pair<const Key, Value> >
    >
class map {

public:
    typedef Key                                                   key_type;
    typedef Value                                                 mapped_type;
    typedef typename ft::pair<const Key, Value>                   value_type;
    typedef std::allocator<value_type>                            allocator_type;

    typedef RBTreeIterator<const Key, value_type>                 iterator;
    typedef RBTreeIterator<const Key, const value_type>           const_iterator;

    map(): tree() { }

    iterator begin() {
        return iterator(tree.get_minimum());
    }

    const_iterator begin() const {
        return const_iterator(tree.get_minimum());
    }

    ft::pair<iterator, bool> insert(const value_type& val) {
        typename tree_type::Node* item = tree.search(val.first);
        if (item != tree.NIL)
            return make_pair(iterator(item), false);

        typename tree_type::Node* newItem = tree.insert(val);
        return make_pair(iterator(newItem), true);
    }

private:
    typedef RBTree<const Key, value_type, std::_Select1st<value_type> > tree_type;

    tree_type tree;

};

}

#endif // !MAP_HPP
