#pragma once
#ifndef RED_BLACK_TREE_NODE_HPP
#define RED_BLACK_TREE_NODE_HPP

namespace ft {

#define IS_NILL(X) ((X) == (X)->left)
#define IS_NOT_NIL(X) ((X) != (X)->left)

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

    RBTreeNode* predecessor() {
        RBTreeNode* node = this;
        if (IS_NOT_NIL(node->left))
            return get_right_most(node->left);

        RBTreeNode* target = node->parent;
        while (IS_NOT_NIL(target) && node == target->left) {
            node = target;
            target = target->parent;
        }

        return target;
    }

    const RBTreeNode* predecessor() const {
        RBTreeNode* node = this;
        if (IS_NOT_NIL(node->left))
            return get_right_most(node->left);

        RBTreeNode* target = node->parent;
        while (IS_NOT_NIL(target) && node == target->left) {
            node = target;
            target = target->parent;
        }

        return target;
    }

    RBTreeNode* successor() {
        RBTreeNode* node = this;
        if (IS_NOT_NIL(node->right))
            return get_left_most(node->right);

        RBTreeNode* target = node->parent;
        while (IS_NOT_NIL(target) && node == target->right) {
            node = target;
            target = target->parent;
        }

        return target;
    }

    const RBTreeNode* successor() const {
        const RBTreeNode* node = this;
        if (IS_NOT_NIL(node->right))
            return get_left_most(node->right);

        RBTreeNode* target = node->parent;
        while (IS_NOT_NIL(target) && node == target->right) {
            node = target;
            target = target->parent;
        }

        return target;
    }

    static RBTreeNode* get_left_most(RBTreeNode* item) {
        while(IS_NOT_NIL(item->left))
            item = item->left;
        return item;
    }

    static const RBTreeNode* get_left_most(const RBTreeNode* item) {
        while(IS_NOT_NIL(item->left))
            item = item->left;
        return item;
    }

    static RBTreeNode* get_right_most(RBTreeNode* item)  {
        while(IS_NOT_NIL(item->right))
            item = item->right;
        return item;
    }

    static const RBTreeNode* get_right_most(const RBTreeNode* item)  {
        while(IS_NOT_NIL(item->right))
            item = item->right;
        return item;
    }
};

}

#endif // !RED_BLACK_TREE_NODE_HPP
