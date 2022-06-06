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

    ~RBTree() {
        this->clear();
    }

    Node* get_root() {
        return this->root;
    }

    const Node* get_root() const {
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

        Node* y = node;
        bool y_original_color = y->color;

        Node* x;
        if (node->left == NIL) {
            x = node->right;
            transplant(node, node->right);
        } else if (node->right == NIL) {
            x = node->left;
            transplant(node, node->left);
        } else {
            y = Node::get_left_most(node->right);
            y_original_color = y->color;
            x = y->right;

            if (y != node->right) {
                transplant(y, y->right);
                y->right = node->right;
                y->right->parent = y;

            } else {
                x->parent = y;
                transplant(node, y);
                y->left = node->left;
                y->left->parent = y;
                y->color = node->color;
            }
        }
        if (y_original_color == BLACK)
            remove_fixup(x);
        this->node_allocator.destroy(node);
        this->node_allocator.deallocate(node, 1);
    }

    Node* search(const key_type& key) {
        return search_node(this->root, key);
    }

    Node* get_minimum() {
        return Node::get_left_most(this->root);
    }

    const Node* get_minimum() const {
        return Node::get_left_most(this->root);
    }

    Node* get_maximum() {
        return Node::get_right_most(this->root);
    } 

    const Node* get_maximum() const {
        return Node::get_right_most(this->root);
    } 


    bool is_empty() const {
        return this->root == NIL;
    }

    void clear() {
        flush(this->root);
    }


private:

    void flush(Node* node) {
        if (node == NIL)
            return ;
        flush(node->left);
        flush(node->right);
        this->node_allocator.destroy(node);
        this->node_allocator.deallocate(node, 1);
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
       (X)   ->   (Y)   
       / \        / \   
     (Y)  c      a  (X) 
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

    void transplant(Node* target, Node* replacement) {
        if (target->parent == NIL) {
            this->root = replacement;
        } else if (IS_LEFT_CHILD(target)) {
            target->parent->left = replacement;
        } else  {
            target->parent->right = replacement;
        }
        replacement->parent = target->parent;
    }

    void remove_fixup(Node* x) {
        Node* w;

        while (x != this->root && x->color == BLACK) {
            if (IS_LEFT_CHILD(x)) {
                w = x->parent->right;

                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    left_rotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;

                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        right_rotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    left_rotate(x->parent);
                    x = this->root;
                }
            } else {
                w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    right_rotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;

                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        left_rotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    right_rotate(x->parent);
                    x = this->root;
                }
            }
        }
        x->color = BLACK;
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
