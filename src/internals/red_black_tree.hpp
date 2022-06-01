#pragma once
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
class RB_Tree {

public:
    typedef RB_Tree_Node<Key, Value>    RB_Node;
    typedef std::allocator<RB_Node>     RB_Node_allocator;
    typedef Key                         key_type;
    typedef Value                       value_type;
    typedef _Allocator                  allocator_type;

    RB_Tree(): root(NIL), allocator(allocator_type()) { }

    void insert(const value_type& data) {
        RB_Node* new_node = create_node(data);

        RB_Node* iter = this->root;
        RB_Node* parent = NIL;
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

    RB_Node* search(const key_type& key) {
        return search_node(this->root, key);
    }

    RB_Node* get_minimum() {
        return get_left_most(this->root);
    }

    const RB_Node* get_minimum() const {
        return get_left_most(this->root);
    }

    RB_Node* get_maximum() {
        return get_right_most(this->root);
    } 

    const RB_Node* get_maximum() const {
        return get_right_most(this->root);
    } 

    RB_Node* get_predecessor(RB_Node* node) {
        if (node->left != NIL)
            return get_right_most(node->left);

        RB_Node* target = node->parent;
        while (target != NIL && node == target->left)
        {
            node = target;
            target = target->parent;
        }

        return target;
    }

    RB_Node* get_successor(RB_Node* node) {
        if (node->right != NIL)
            return get_left_most(node->right);

        RB_Node* target = node->parent;
        while (target != NIL && node == target->right)
        {
            node = target;
            target = target->parent;
        }

        return target;
    }

private:

    RB_Node* get_left_most(RB_Node* item) const {
        while(item->left != NIL)
            item = item->left;
        return item;
    }

    RB_Node* get_right_most(RB_Node* item) const {
        while(item->right != NIL)
            item = item->right;
        return item;
    }

    RB_Node* create_node(const value_type& data) {
        RB_Node* new_node = this->node_allocator.allocate(1);
        this->node_allocator.construct(new_node, RB_Node(KeyOfValue()(data), data));
        this->allocator.construct(&new_node->value, data);
        return new_node;
    }

    RB_Node* search_node(RB_Node* current_root, const key_type& key) {
        if (current_root == 0 || current_root->key == key)
            return current_root;
        else if (key < current_root->key)
            return search_node(current_root->left, key);
        else 
            return search_node(current_root->right, key);
    }

private:
    RB_Node*            root;
    allocator_type      allocator;
    RB_Node_allocator   node_allocator;
};

}

#endif // !RED_BLACK_TREE_HPP
