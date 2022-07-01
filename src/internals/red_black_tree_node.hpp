#pragma once
#ifndef RED_BLACK_TREE_NODE_HPP
#define RED_BLACK_TREE_NODE_HPP

namespace ft {

#define IS_NILL(X) ((X) == (X)->nil)
#define IS_NOT_NIL(X) ((X) != (X)->nil)

template<typename Key, typename Value>
class RBTreeNode {

#define COLOR_RED false
#define COLOR_BLACK true

public:
    Key           key;
    Value         value;

    RBTreeNode*   parent;
    RBTreeNode*   left;
    RBTreeNode*   right;
    RBTreeNode*   nil;

    bool          color;

    RBTreeNode():
        key(Key()),
        value(Value()),
        parent(this),
        left(this),
        right(this),
        nil(this),
        color(COLOR_BLACK) {}

    RBTreeNode(const RBTreeNode& other):
        key(other.key),
        value(other.value),
        parent(other.parent),
        left(other.left),
        right(other.right),
        nil(other.nil),
        color(other.color) {}

    RBTreeNode(const Value& data, const RBTreeNode* NIL):
        value(data),
        parent(NIL),
        left(NIL),
        right(NIL),
        nil(NIL),
        color(COLOR_RED) {}

    RBTreeNode(const Key& key, const Value& data, RBTreeNode* NIL):
        key(key),
        value(data),
        parent(NIL),
        left(NIL),
        right(NIL),
        nil(NIL),
        color(COLOR_RED) {}

    RBTreeNode* predecessor() {
        RBTreeNode* node = this;
        if (IS_NILL(node))
            return (get_right_most(get_root(this)));
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
        const RBTreeNode* node = this;
        if (IS_NILL(node))
            return (get_right_most(get_root(this)));
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
        if (IS_NILL(node))
            return (get_right_most(get_root(this)));
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
        if (IS_NILL(this))
            return (get_right_most(get_root(this)));
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

    RBTreeNode* get_nil() {
        return nil;
    }

    const RBTreeNode* get_nil() const {
        return nil;
    }

    static RBTreeNode* get_root(RBTreeNode* node) {
        RBTreeNode* nil = node->nil;
        while (node->parent != nil) {
            node = node->parent;
        }
        return node;
    }

    static const RBTreeNode* get_root(const RBTreeNode* node) {
        const RBTreeNode* nil = node->nil;
        while (node->parent != nil) {
            node = node->parent;
        }
        return node;
    }
};

}

#endif // !RED_BLACK_TREE_NODE_HPP
