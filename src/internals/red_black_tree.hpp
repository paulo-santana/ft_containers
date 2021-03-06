#pragma once
#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP


#include "reverse_iterator.hpp"
#include "map/RBTreeIterator.hpp"
#include "internals/red_black_tree_node.hpp"

namespace ft {

#define IS_LEFT_CHILD(X) (X) == (X)->parent->left
#define IS_RIGHT_CHILD(X) (X) == (X)->parent->right

template<
    typename Key,
    typename Value,
    typename KeyOfValue,
    typename Compare,
    typename _Allocator = std::allocator<Value> >
class RBTree {
    Compare                                         keyCompare;

public:

    typedef RBTreeNode<Key, Value>                  Node;
    typedef std::allocator<Node>                    NodeAllocator;
    typedef Key                                     key_type;
    typedef typename NodeAllocator::size_type       size_type;
    typedef Value                                   value_type;
    typedef _Allocator                              allocator_type;

    typedef RBTreeIterator<Key, value_type>         iterator;
    typedef RBTreeConstIterator<Key, value_type>    const_iterator;
    typedef ft::reverse_iterator<iterator>          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

    Node*                                           NIL;

    RBTree(const Compare& comp = Compare(), const allocator_type& alloc = allocator_type()):
        keyCompare(comp),
        NIL(&_leaf),
        _leaf(),
        root(NIL),
        allocator(alloc),
        num_items(0),
        last(NIL)
    { }

    RBTree(const RBTree& other):
        keyCompare(other.keyCompare),
        NIL(&_leaf),
        _leaf(),
        root(NIL),
        allocator(allocator_type()),
        num_items(other.num_items),
        last(NIL)
    {
        this->root = this->copy_subtree(other.root, other.NIL);
        this->root->parent = NIL;
        this->last = get_maximum();
    }

    ~RBTree() {
        this->clear();
    }

    Node* get_root() {
        return this->root;
    }

    const Node* get_root() const {
        return this->root;
    }

    RBTree& operator=(const RBTree& other) {
        this->clear();
        this->root = this->copy_subtree(other.root, other.NIL);
        this->root->parent = NIL;
        this->num_items = other.num_items;
        this->last = get_maximum();
        return *this;
    }

    Node* insert(const value_type& data) {
        Node* new_node = create_node(data);

        if (this->root == this->NIL) {
            this->root = new_node;
            new_node->color = COLOR_BLACK;
            new_node->parent = NIL;
            this->num_items++;
            this->last = new_node;
            return new_node;
        }
        // Node* iter = this->root;
        Node* parent = find_parent(this->root, KeyOfValue()(data));
        new_node->parent = parent;

        if (parent == NIL) {
            this->root = new_node;
        } else if (keyCompare(new_node->key, parent->key)) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
        this->num_items++;
        insert_fixup(new_node);
        this->NIL->parent = this->root;
        this->root->parent = this->NIL;
        if (last == NIL || Compare()(last->key, new_node->key))
            last = new_node;
        return new_node;
    }

    iterator insert(const_iterator _pos, const value_type& data) {
        Node* node = const_cast<Node*>(_pos._M_node);
        return insert(iterator(node), data);
    }

    iterator insert(iterator position, const value_type& data) {

        key_type key = KeyOfValue()(data);
        Node* parent = find_parent(position._M_node, key);

        if (parent != NIL && parent->key == key) {
            return position;
        }

        Node* new_node = create_node(data);

        new_node->parent = parent;
        if (parent == NIL) {
            this->root = new_node;
        } else if (keyCompare(new_node->key, parent->key)) {
            parent->left = new_node;
        } else if (keyCompare(parent->key, new_node->key)){
            parent->right = new_node;
        }
        this->num_items++;
        insert_fixup(new_node);
        this->NIL->parent = this->root;
        this->root->parent = this->NIL;
        if (last == NIL || keyCompare(last->key, new_node->key))
            last = new_node;
        return iterator(new_node);
    }

    Node* find_parent(Node* hint, key_type key) {
        // if hint is NIL, search from the top
        if (hint != NIL && keyCompare(hint->key, key)) {
            Node* successor = hint->successor();
            // hint was the last element
            if (successor == NIL) 
                return hint;
            // new_node is right after the hint (hint.successor() > new_node)
            if (keyCompare(key, successor->key)) {
                if (successor->left == NIL)
                    return successor;
                return hint;
            }
        }
        // hint was not optimal, search from the top
        Node* iter = this->root;
        Node* parent = NIL;

        while (iter != NIL) {
            parent = iter;

            if (keyCompare(key, iter->key)) {
                iter = iter->left;
            } else {
                iter = iter->right;
            }
        }
        return parent;
    }

    void remove_direct_node(Node* z) {
        Node* y = z;
        bool y_original_color = y->color;

        Node* x;
        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = Node::get_left_most(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y != z->right) {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;

            } else {
                x->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (y_original_color == COLOR_BLACK)
            remove_fixup(x);
        this->NIL->parent = this->root;
        this->root->parent = this->NIL;
        if (z == last)
            last = z->predecessor();
        this->node_allocator.destroy(z);
        this->node_allocator.deallocate(z, 1);
        this->num_items--;
    }

    int remove(const key_type& key) {
        Node* node = search_node(this->root, key);
        if (node == NIL) {
            return 0;
        }
        remove_direct_node(node);
        return 1;
    }

    size_type erase(iterator position) {
        remove_direct_node(position._M_node);
        return 1;
    }

    void erase(iterator first, iterator last) {
        while (first != last) {
            this->erase(first++);
        }
        return ;
    }

    void erase(const_iterator first, const_iterator last) {
        Node* firstNode = const_cast<Node*>(first._M_node);
        Node* lastNode = const_cast<Node*>(last._M_node);
        erase(iterator(firstNode), iterator(lastNode));
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

    size_type size() const {
        return this->num_items;
    }

    size_type max_size() const {
        return this->node_allocator.max_size();
    }

    bool is_empty() const {
        return this->root == NIL;
    }

    void clear() {
        flush(this->root);
        this->root = NIL;
    }

    Node* get_last() const {
        return this->last;
    }

    iterator lower_bound(const key_type& key) {
        Node* node = this->root;
        Node* lbound = NIL;
        while (node != NIL) {
            if (!keyCompare(node->key, key)) {
                lbound = node;
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return iterator(lbound);
    }

    iterator upper_bound(const key_type& key) {
        Node* node = this->root;
        Node* lbound = NIL;
        while (node != NIL) {
            if (keyCompare(key, node->key)) {
                lbound = node;
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return iterator(lbound);
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
        return new_node;
    }

    Node* search_node(Node* current_root, const key_type& key) {
        if (current_root == NIL || current_root->key == key)
            return current_root;
        else if (keyCompare(key, current_root->key))
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
        while (node->parent->color == COLOR_RED) {

            if (IS_LEFT_CHILD(node->parent)) {
                uncle = node->parent->parent->right;
                if (uncle->color == COLOR_RED) {
                    node->parent->color = COLOR_BLACK;
                    uncle->color = COLOR_BLACK;
                    node->parent->parent->color = COLOR_RED;
                    node = node->parent->parent;

                } else {
                    if (IS_RIGHT_CHILD(node)) {
                        node = node->parent;
                        left_rotate(node);
                    }
                    node->parent->color = COLOR_BLACK;
                    node->parent->parent->color = COLOR_RED;
                    right_rotate(node->parent->parent);
                }
            } else {
                uncle = node->parent->parent->left;
                if (uncle->color == COLOR_RED) {
                    node->parent->color = COLOR_BLACK;
                    uncle->color = COLOR_BLACK;
                    node->parent->parent->color = COLOR_RED;
                    node = node->parent->parent;

                } else {
                    if (IS_LEFT_CHILD(node)) {
                        node = node->parent;
                        right_rotate(node);
                    }
                    node->parent->color = COLOR_BLACK;
                    node->parent->parent->color = COLOR_RED;
                    left_rotate(node->parent->parent);
                }
            }
        }
        this->root->color = COLOR_BLACK;
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

        while (x != this->root && x->color == COLOR_BLACK) {
            if (IS_LEFT_CHILD(x)) {
                w = x->parent->right;

                if (w->color == COLOR_RED) {
                    w->color = COLOR_BLACK;
                    x->parent->color = COLOR_RED;
                    left_rotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == COLOR_BLACK && w->right->color == COLOR_BLACK) {
                    w->color = COLOR_RED;
                    x = x->parent;

                } else {
                    if (w->right->color == COLOR_BLACK) {
                        w->left->color = COLOR_BLACK;
                        w->color = COLOR_RED;
                        right_rotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = COLOR_BLACK;
                    w->right->color = COLOR_BLACK;
                    left_rotate(x->parent);
                    x = this->root;
                }
            } else {
                w = x->parent->left;
                if (w->color == COLOR_RED) {
                    w->color = COLOR_BLACK;
                    x->parent->color = COLOR_RED;
                    right_rotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == COLOR_BLACK && w->left->color == COLOR_BLACK) {
                    w->color = COLOR_RED;
                    x = x->parent;

                } else {
                    if (w->left->color == COLOR_BLACK) {
                        w->right->color = COLOR_BLACK;
                        w->color = COLOR_RED;
                        left_rotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = COLOR_BLACK;
                    w->left->color = COLOR_BLACK;
                    right_rotate(x->parent);
                    x = this->root;
                }
            }
        }
        x->color = COLOR_BLACK;
    }

    Node* copy_subtree(Node* node, Node* node_nil) {
        if (node == node_nil)
            return NIL;
        Node* new_node = copy_node(node);
        new_node->left = copy_subtree(node->left, node_nil);
        new_node->right = copy_subtree(node->right, node_nil);
        if (new_node->left != NIL)
            new_node->left->parent = new_node;
        if (new_node->right != NIL)
            new_node->right->parent = new_node;
        return new_node;
    }

    Node* copy_node(Node* src) {
        Node* new_node = this->node_allocator.allocate(1);
        this->node_allocator.construct(new_node, *src);
        return new_node;
    }

private:
    Node                _leaf;
    Node*               root;
    allocator_type      allocator;
    size_type           num_items;
    NodeAllocator       node_allocator;

    Node*               last;
};

}

#endif // !RED_BLACK_TREE_HPP
