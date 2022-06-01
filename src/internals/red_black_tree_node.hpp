#pragma once
#ifndef RED_BLACK_TREE_NODE_HPP
#define RED_BLACK_TREE_NODE_HPP

namespace ft {

#define NIL 0

template<typename Key, typename Value>
class RBTreeNode {

#define NIL 0

public:
    Key           key;
    Value         value;

    RBTreeNode*   parent;
    RBTreeNode*   left;
    RBTreeNode*   right;

    bool          black;

    RBTreeNode():
        key(Key()),
        value(Value()),
        parent(NIL),
        left(NIL),
        right(NIL),
        black(false) {}

    RBTreeNode(const RBTreeNode& other):
        key(other.key),
        value(other.value),
        parent(other.parent),
        left(other.left),
        right(other.right),
        black(other.black) {}

    RBTreeNode(const Value& data):
        value(data), parent(NIL), left(NIL), right(NIL), black(false) {}

    RBTreeNode(const Key& key, const Value& data):
        key(key),
        value(data),
        parent(NIL),
        left(NIL),
        right(NIL),
        black(false) {}
};

}

#endif // !RED_BLACK_TREE_NODE_HPP
