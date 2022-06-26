#pragma once
#ifndef SET_HPP
# define SET_HPP

#include <functional>
#include <memory>
#include "internals/red_black_tree.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"

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

    typedef typename tree_type::const_iterator                iterator;
    typedef typename tree_type::const_iterator          const_iterator;

    typedef typename tree_type::const_reverse_iterator  reverse_iterator;
    typedef typename tree_type::const_reverse_iterator  const_reverse_iterator;

    typedef std::ptrdiff_t                              difference_type;
    typedef std::size_t                                 size_type;

    explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
        this->tree = new tree_type(comp, alloc);
    }

    template<typename InputIterator>
    set(
            InputIterator first,
            InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) {
        this->tree = new tree_type(comp, alloc);
        while (first != last) {
            tree->insert(*first);
            ++first;
        }
    }

    set(const set& other): tree(new tree_type(*other.tree)) { }

    set& operator=(const set& other) {
        *this->tree = *other.tree;
        return *this;
    }

    ~set() {
        delete this->tree;
    }

    size_type size() const {
        return this->tree->size();
    }

    iterator begin() {
        return iterator(this->tree->get_minimum());
    }

    const_iterator begin() const {
        return const_iterator(this->tree->get_minimum());
    }

    iterator end() {
        return iterator(this->tree->NIL);
    }

    const_iterator end() const {
        return const_iterator(this->tree->NIL);
    }

    // FIXME: it's running in O(2 logN)
    ft::pair<iterator, bool> insert(const value_type& val) {
        typename tree_type::Node* item = tree->search(val);
        if (item != tree->NIL)
            return ft::make_pair(iterator(item), false);

        node_type* newItem = tree->insert(val);
        return ft::make_pair(iterator(newItem), true);
    }

    iterator insert(iterator position, const value_type& val) {
        return this->tree->insert(position, val);
    }

    template<typename InputIterator>
    void insert(InputIterator first, InputIterator last) {
        if (first == last)
            return ;

        iterator hint = this->find(*first);
        while (first != last) {
            hint = this->insert(hint, *first);
            ++first;
        }
    }

    void erase(iterator position) {
        this->tree->remove(*position);
    }

    size_type erase(const value_type& val) {
        return this->tree->remove(val);
    }

    iterator find(const key_type& key) {
        return iterator(this->tree->search(key));
    }

    bool empty() const {
        return this->tree->is_empty();
    }

    size_type max_size() const {
        return this->tree->max_size();
    }
};

}

#endif // !SET_HPP
