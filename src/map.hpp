#pragma once
#ifndef MAP_HPP
#define MAP_HPP

#include "internals/red_black_tree.hpp"
#include "map/RBTreeIterator.hpp"
#include "pair.hpp"

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
    typedef Key                                                 key_type;
    typedef Value                                               mapped_type;
    typedef ft::pair<const Key, Value>                          value_type;
    typedef Compare                                             key_compare; 
    typedef std::size_t                                         size_type;
private:
    typedef RBTree<key_type, value_type, std::_Select1st<value_type>, key_compare, Allocator> tree_type;
    typedef typename tree_type::Node node_type;

    tree_type tree;
    key_compare key_comparator;
public:
    typedef std::allocator<value_type>                            allocator_type;

    typedef typename tree_type::iterator iterator;
    typedef typename tree_type::const_iterator const_iterator;
    // typedef RBTreeIterator<const Key, value_type>                 iterator;
    // typedef RBTreeConstIterator<const Key, value_type>            const_iterator;

    explicit map(
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) :
        tree(),
        key_comparator(comp),
        num_items(0),
        allocator(alloc)
    { }

    template<typename InputIterator>
    map (InputIterator first, InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()):
        tree(),
        key_comparator(comp),
        num_items(0),
        allocator(alloc)
    {
        while (first != last) {
            tree.insert(*first);
            ++first;
        }
    }

    ~map() {}

    size_type size() const {
        return this->tree.size();
    }

    iterator begin() {
        return iterator(tree.get_minimum());
    }

    const_iterator begin() const {
        return const_iterator(tree.get_minimum());
    }

    iterator end() {
        return iterator(tree.NIL);
    }

    ft::pair<iterator, bool> insert(const value_type& val) {
        typename tree_type::Node* item = tree.search(val.first);
        if (item != tree.NIL)
            return ft::make_pair(iterator(item), false);

        node_type* newItem = tree.insert(val);
        Key* key = const_cast<Key*>(&tree.NIL->value.first);
        num_items++;
        *key = num_items;
        return ft::make_pair(iterator(newItem), true);
    }

private:
    size_type num_items;

    allocator_type allocator;
};

}

#endif // !MAP_HPP
