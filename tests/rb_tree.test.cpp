#include "test_utils.hpp"
#include "internals/red_black_tree.hpp"
#include <functional>
#include <map>
#include <ostream>
#include <iostream>
#include <utility>

typedef ft::RB_Tree_Node<const int, int> int_int_node;

typedef ft::RB_Tree<const int, int, std::_Identity<int> > int_int_tree;
typedef ft::RB_Tree<
    const int,
    std::pair<const int, int>,
    std::_Select1st<std::pair<const int, int> > > int_pair_tree;


template<typename T, typename U>
std::ostream& operator<<(std::ostream& out, const std::pair<T, U>& pair) {
    out << "pair[" << pair.first << ", " << pair.second << "]";
    return out;
}

template<typename T, typename U>
std::ostream& operator<<(std::ostream& out, const ft::RB_Tree_Node<T, U>& node) {
    out << "  node[" << node.key << ", " << node.value << "]" << std::endl;
    return out;
}

template<typename T, typename U>
void inorder_tree_walk(std::ostream& out, const ft::RB_Tree_Node<T, U>* node) {
    if (node == 0)
        return ;
    inorder_tree_walk(out, node->left);
    out << *node;
    inorder_tree_walk(out, node->right);
}

template<typename T, typename U, typename V>
std::ostream& operator<<(std::ostream& out, const ft::RB_Tree<T, U, V> &tree) {
    out << "[" << std::endl;

    // if (tree) {
    //
    // }

    const ft::RB_Tree_Node<T, U>* first = tree.get_minimum();
    const ft::RB_Tree_Node<T, U>* root = first;
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

    ft::RB_Tree_Node<const int, int>* result = tree.search(13);
    if (result)
        std::cout << "result: " << *result << std::endl;
    else
        std::cout << "13 not found" << std::endl;
}

void testRBTree() {
    test_default_constructor();
    test_dump_tree();
    test_insert_at_empty();
    test_get_minimum();
    test_search();
}
