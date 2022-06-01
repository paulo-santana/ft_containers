#include "test_utils.hpp"
#include "internals/red_black_tree.hpp"
#include <functional>
#include <map>
#include <ostream>
#include <iostream>
#include <sys/types.h>
#include <utility>

typedef ft::RBTreeNode<const int, int> int_int_node;

typedef ft::RBTree<const int, int, std::_Identity<int> > int_int_tree;
typedef ft::RBTree<
    const int,
    std::pair<const int, int>,
    std::_Select1st<std::pair<const int, int> > > int_pair_tree;


template<typename T, typename U>
std::ostream& operator<<(std::ostream& out, const std::pair<T, U>& pair) {
    out << "pair[" << pair.first << ", " << pair.second << "]";
    return out;
}

template<typename T, typename U>
std::ostream& operator<<(std::ostream& out, const ft::RBTreeNode<T, U>& node) {
    out << "  node[" << node.key << ", " << node.value << "]";
    return out;
}

template<typename T, typename U>
void inorder_tree_walk(std::ostream& out, const ft::RBTreeNode<T, U>* node) {
    if (node == 0)
        return ;
    inorder_tree_walk(out, node->left);
    out << *node << std::endl;
    inorder_tree_walk(out, node->right);
}

template<typename T, typename U, typename V>
std::ostream& operator<<(std::ostream& out, const ft::RBTree<T, U, V> &tree) {
    out << "[" << std::endl;

    // if (tree) {
    //
    // }

    const ft::RBTreeNode<T, U>* first = tree.get_minimum();
    const ft::RBTreeNode<T, U>* root = first;
    while (root->parent != 0)
        root = root->parent;
    
    inorder_tree_walk<T, U>(out, root);
    out << "]";

    return out;
}

static void test_default_constructor() {
    println("test RB Tree default constructor");

    int_int_tree tree;
    std::cout << "at least it compiles" << std::endl;
}

static void test_dump_tree() {
    println("test dump tree");

    int_pair_tree tree ;
    tree.insert(std::make_pair(3, 4));
    tree.insert(std::make_pair(2, 3));
    tree.insert(std::make_pair(4, 6));
    std::cout << "tree dump: " << tree << std::endl;
}

static void test_insert_at_empty() {
    println("test RB Tree first insertion");

    int_int_tree tree;
    tree.insert(1);
    std::cout << "It probably works" << std::endl;
}

static void test_get_minimum() {
    println("test RB Tree get_first()");

    int_int_tree tree;
    tree.insert(3);
    tree.insert(8);
    tree.insert(6);
    tree.insert(2);
    int_int_node* min = tree.get_minimum();
    std::cout << "first item: "
#if REAL_STD
        << 2
#else
        << min->value
#endif
        << std::endl;
    (void)min;
}

static void test_search() {
    println("test RB Tree search");

    int_int_tree tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(25);
    tree.insert(37);
    tree.insert(21);
    tree.insert(19);
    tree.insert(13);

#if REAL_STD
    std::cout << "result:  node[19, 19]" << std::endl;
#else
    ft::RBTreeNode<const int, int>* result = tree.search(19);
    std::cout << "result:" << *result << std::endl;
#endif
}

static void test_node_successor() {
    println("test RB Node successor");

    int_int_tree tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(25);
    tree.insert(37);
    tree.insert(21);
    tree.insert(19);
    tree.insert(13);
    int_int_tree::Node* node = tree.search(13);
    
    std::cout << "tree: " << tree << std::endl;
#if REAL_STD
    std::cout << "result:  node[19, 19]" << std::endl;
    std::cout << "result:  node[20, 20]" << std::endl;
    std::cout << "result:  node[21, 21]" << std::endl;
    std::cout << "result:  node[25, 25]" << std::endl;
    std::cout << "result:  node[30, 30]" << std::endl;
    std::cout << "result:  node[37, 37]" << std::endl;
    (void)node;
#else
    int_int_tree::Node* result = tree.get_successor(node);
    for (int i = 0; i < 10 && result != 0; i++) {
        std::cout << "result:" << *result << std::endl;
        result = tree.get_successor(result);
    }
#endif
}

static void test_node_predecessor() {
    println("test RB Node predecessor");

    int_int_tree tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(25);
    tree.insert(37);
    tree.insert(21);
    tree.insert(19);
    tree.insert(13);
    int_int_tree::Node* node = tree.search(37);
    
    std::cout << "tree: " << tree << std::endl;
#if REAL_STD
    std::cout << "result:  node[30, 30]" << std::endl;
    std::cout << "result:  node[25, 25]" << std::endl;
    std::cout << "result:  node[21, 21]" << std::endl;
    std::cout << "result:  node[20, 20]" << std::endl;
    std::cout << "result:  node[19, 19]" << std::endl;
    std::cout << "result:  node[13, 13]" << std::endl;
    (void)node;
#else
    int_int_tree::Node* result = tree.get_predecessor(node);
    for (int i = 0; i < 10 && result != 0; i++) {
        std::cout << "result:" << *result << std::endl;
        result = tree.get_predecessor(result);
    }
#endif

}

static void test_remove() {
    println("test RB Tree remove");

    int_int_tree tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(25);
    tree.insert(37);
    tree.insert(21);
    tree.insert(19);
    tree.insert(13);

    tree.remove(13);

}

void testRBTree() {
    test_default_constructor();
    test_dump_tree();
    test_insert_at_empty();
    test_get_minimum();
    test_search();
    test_remove();

    test_node_successor();
    test_node_predecessor();
}
