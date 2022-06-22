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
    typedef std::allocator<value_type>                          allocator_type;

    typedef typename tree_type::iterator iterator;
    typedef typename tree_type::const_iterator const_iterator;
    typedef typename tree_type::reverse_iterator                reverse_iterator;
    typedef typename tree_type::const_reverse_iterator          const_reverse_iterator;

    explicit map(
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) :
        tree(),
        key_comparator(comp),
        num_items(0),
        allocator(alloc)
    { }

    template<typename InputIterator>
    map(InputIterator first, InputIterator last,
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

    map(const map& other) :
        tree(),
        key_comparator(other.key_comparator),
        num_items(0),
        allocator(allocator_type())
    {
        const_iterator first = other.begin();
        const_iterator last = other.end();

        while (first != last) {
            tree.insert(*first);
            ++first;
        }
    }

    map& operator=(const map& other) {
        this->tree = other.tree;
        return *this;
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

    const_iterator end() const {
        return iterator(tree.NIL);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    bool empty() const {
        return this->size() == 0;
    }

    size_type max_size() {
        return this->tree.max_size();
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

    iterator insert(iterator position, const value_type& val) {
        return tree.insert(position, val);
    }

    template<typename InputIterator>
    void insert(InputIterator first, InputIterator last) {
        if (first == last)
            return ;

        iterator hint = this->find(first->first);
        while (first != last) {
            hint = this->insert(hint, *first);
            ++first;
        }
    }

    // The insert operation returns an iterator to the new inserted element,
    // or to the old element that already existed.
    // We only need to return the value field of the map.
    mapped_type& operator[](const key_type& key) {
        ft::pair<iterator, bool> inserted = this->insert(ft::make_pair(key, mapped_type()));
        return inserted.first->second;
    }

    iterator find (const key_type& key) {
        return iterator(this->tree.search(key));
    }

    void erase(iterator position) {
        this->tree.remove(position->first);
    }

private:
    size_type num_items;

    allocator_type allocator;
};

}

#endif // !MAP_HPP
