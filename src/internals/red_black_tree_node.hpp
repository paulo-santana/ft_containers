#pragma once
#ifndef RED_BLACK_TREE_NODE_HPP
#define RED_BLACK_TREE_NODE_HPP

namespace ft {

template<typename Key, typename Value>
class RB_Tree_Node {

public:
    Key             key;
    Value           value;

    RB_Tree_Node*   parent;
    RB_Tree_Node*   left;
    RB_Tree_Node*   right;

    bool            black;

    RB_Tree_Node():
        key(Key()),
        value(Value()),
        parent(),
        left(),
        right(),
        black(false) {}

    RB_Tree_Node(const RB_Tree_Node& other):
        key(other.key),
        value(other.value),
        parent(other.parent),
        left(other.left),
        right(other.right),
        black(other.black) {}

    RB_Tree_Node(const Value& data):
        value(data), parent(), left(), right(), black(false) {}

    RB_Tree_Node(const Key& key, const Value& data):
        key(key),
        value(data),
        parent(),
        left(),
        right(),
        black(false) {}
};

}

#endif // !RED_BLACK_TREE_NODE_HPP
