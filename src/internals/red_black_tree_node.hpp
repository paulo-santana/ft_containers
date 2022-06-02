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
        color(RED) {}

    RBTreeNode(const RBTreeNode& other):
        key(other.key),
        value(other.value),
        parent(other.parent),
        left(other.left),
        right(other.right),
        color(other.color) {}

    RBTreeNode(const Value& data):
        value(data),
        color(RED) {}

    RBTreeNode(const Key& key, const Value& data):
        key(key),
        value(data),
        color(RED) {}
};

}

#endif // !RED_BLACK_TREE_NODE_HPP
