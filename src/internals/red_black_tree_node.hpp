#pragma once
#ifndef RED_BLACK_TREE_NODE_HPP
#define RED_BLACK_TREE_NODE_HPP

namespace ft {

template<typename Key, typename Value>
class RBTreeNode {


#define RED false
#define BLACK true

public:
    Key           key;
    Value         value;

    RBTreeNode*   parent;
    RBTreeNode*   left;
    RBTreeNode*   right;

    bool          color;

    RBTreeNode():
        key(Key()),
        value(Value()),
        parent(this),
        left(this),
        right(this),
        color(BLACK) {}

    RBTreeNode(const RBTreeNode& other):
        key(other.key),
        value(other.value),
        parent(other.parent),
        left(other.left),
        right(other.right),
        color(other.color) {}

    RBTreeNode(const Value& data, const RBTreeNode* NIL):
        value(data),
        parent(NIL),
        left(NIL),
        right(NIL),
        color(RED) {}

    RBTreeNode(const Key& key, const Value& data, RBTreeNode* NIL):
        key(key),
        value(data),
        parent(NIL),
        left(NIL),
        right(NIL),
        color(RED) {}
};

}

#endif // !RED_BLACK_TREE_NODE_HPP
