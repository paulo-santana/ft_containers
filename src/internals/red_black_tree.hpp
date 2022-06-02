#pragma once
#include <iostream>
#include <memory>
#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <ostream>
#include "internals/red_black_tree_node.hpp"

namespace ft {

#define IS_LEFT_CHILD(X) (X) == (X)->parent->left
#define IS_RIGHT_CHILD(X) (X) == (X)->parent->right

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

    static Node*                               NIL;

    RBTree():
        root(NIL),
        allocator(allocator_type()) { }

    Node* get_root() {
        return this->root;
    }

    void insert(const value_type& data) {
        Node* new_node = create_node(data);

        if (this->root == this->NIL) {
            this->root = new_node;
            new_node->color = BLACK;
            new_node->parent = NIL;
            return ;
        }
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
        insert_fixup(new_node);
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
        this->node_allocator.construct(new_node, Node(KeyOfValue()(data), data, NIL));
        this->allocator.construct(&new_node->value, data);
        return new_node;
    }

    Node* search_node(Node* current_root, const key_type& key) {
        if (current_root == NIL || current_root->key == key)
            return current_root;
        else if (key < current_root->key)
            return search_node(current_root->left, key);
        else 
            return search_node(current_root->right, key);
    }

    /*
       |           |
       X     ->    Y
      / \         / \   
     a   Y       X   c
        / \     / \
       b   c   a   b
   */ 
    void left_rotate(Node* nodeX) {
        Node* nodeY = nodeX->right;

        nodeX->right = nodeY->left;
        if (nodeY->left != NIL) {
            nodeY->left->parent = nodeX;
        }

        nodeY->parent = nodeX->parent;
        if (nodeX->parent == NIL) {
            this->root = nodeY;
        } else if (IS_LEFT_CHILD(nodeX)) {
            nodeX->parent->left = nodeY;
        } else {
            nodeX->parent->right = nodeY;
        }
        nodeY->left = nodeX;
        nodeX->parent = nodeY;
    }

    /*
        |          |    
        X    ->    Y    
       / \        / \   
      Y   c      a   X  
     / \            / \ 
    a   b          b   c
    */ 
    void right_rotate(Node* nodeX) {
        Node* nodeY = nodeX->left;

        nodeX->left = nodeY->right;
        if (nodeY->right != NIL) {
            nodeY->right->parent = nodeX;
        }

        nodeY->parent = nodeX->parent;
        if (nodeX->parent == NIL) {
            this->root = nodeY;
        } else if (IS_RIGHT_CHILD(nodeX)) {
            nodeX->parent->right = nodeY;
        } else {
            nodeX->parent->left = nodeY;
        }
        nodeY->right = nodeX;
        nodeX->parent = nodeY;
    }

    void insert_fixup(Node* node) {
        Node* uncle = NIL;
        while (node->parent->color == RED) {

            if (IS_LEFT_CHILD(node->parent)) {
                uncle = node->parent->parent->right;
                if (uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;

                } else {
                    if (IS_RIGHT_CHILD(node)) {
                        node = node->parent;
                        left_rotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    right_rotate(node->parent->parent);
                }
            } else {
                uncle = node->parent->parent->left;
                if (uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;

                } else {
                    if (IS_LEFT_CHILD(node)) {
                        node = node->parent;
                        right_rotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    left_rotate(node->parent->parent);
                }
            }
        }
        this->root->color = BLACK;
    }
private:
    static Node         _leaf;
    Node*               root;
    allocator_type      allocator;
    NodeAllocator       node_allocator;
};

template<typename T, typename U, typename V, typename W>
typename RBTree<T, U, V, W>::Node RBTree<T, U, V, W>::_leaf = RBTree<T, U, V, W>::Node();

template<typename T, typename U, typename V, typename W>
typename RBTree<T, U, V, W>::Node* RBTree<T, U, V, W>::NIL = &RBTree<T, U, V, W>::_leaf;
}

#endif // !RED_BLACK_TREE_HPP
