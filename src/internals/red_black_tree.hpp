#pragma once
#include <iostream>
#include <memory>
#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <ostream>
#include "internals/red_black_tree_node.hpp"

namespace ft {

#define NIL 0

template<
    typename Key,
    typename Value,
    typename KeyOfValue,
    typename _Allocator = std::allocator<Value> >
class RBTree {

public:
    typedef RBTreeNode<Key, Value>      Node;
    typedef std::allocator<Node>        NodeAllocator;
    typedef Key                         key_type;
    typedef Value                       value_type;
    typedef _Allocator                  allocator_type;

    RBTree(): root(NIL), allocator(allocator_type()) { }

    void insert(const value_type& data) {
        Node* new_node = create_node(data);

        Node* iter = this->root;
        Node* parent = NIL;
        while (iter != NIL) {
            parent = iter;

            if (new_node->key < iter->key) {
                iter = iter->left;
            } else {
                iter = iter->right;
            }
        }
        new_node->parent = parent;

        if (parent == NIL) {
            this->root = new_node;
        } else if (new_node->key < parent->key) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
        new_node->left = NIL;
        new_node->right = NIL;
        new_node->black = false;
    }

    void remove(const key_type& key) {
        Node* node = search_node(this->root, key);
        if (node == NIL) {
            return;
        }

        Node* parent = node->parent;

        if (parent == NIL) {
            this->root = NIL;
        } else {
            if (parent->left == node)
                parent->left = NIL;
            else 
                parent->right = NIL;
        }
        this->node_allocator.destroy(node);
        this->node_allocator.deallocate(node, 1);
    }

    Node* search(const key_type& key) {
        return search_node(this->root, key);
    }

    Node* get_minimum() {
        return get_left_most(this->root);
    }

    const Node* get_minimum() const {
        return get_left_most(this->root);
    }

    Node* get_maximum() {
        return get_right_most(this->root);
    } 

    const Node* get_maximum() const {
        return get_right_most(this->root);
    } 

    Node* get_predecessor(Node* node) {
        if (node->left != NIL)
            return get_right_most(node->left);

        Node* target = node->parent;
        while (target != NIL && node == target->left)
        {
            node = target;
            target = target->parent;
        }

        return target;
    }

    Node* get_successor(Node* node) {
        if (node->right != NIL)
            return get_left_most(node->right);

        Node* target = node->parent;
        while (target != NIL && node == target->right)
        {
            node = target;
            target = target->parent;
        }

        return target;
    }

    bool is_empty() const {
        return this->root == NIL;
    }

private:

    Node* get_left_most(Node* item) const {
        while(item->left != NIL)
            item = item->left;
        return item;
    }

    Node* get_right_most(Node* item) const {
        while(item->right != NIL)
            item = item->right;
        return item;
    }

    Node* create_node(const value_type& data) {
        Node* new_node = this->node_allocator.allocate(1);
        this->node_allocator.construct(new_node, Node(KeyOfValue()(data), data));
        this->allocator.construct(&new_node->value, data);
        return new_node;
    }

    Node* search_node(Node* current_root, const key_type& key) {
        if (current_root == 0 || current_root->key == key)
            return current_root;
        else if (key < current_root->key)
            return search_node(current_root->left, key);
        else 
            return search_node(current_root->right, key);
    }

private:
    Node*           root;
    allocator_type  allocator;
    NodeAllocator   node_allocator;
};

}

#endif // !RED_BLACK_TREE_HPP
