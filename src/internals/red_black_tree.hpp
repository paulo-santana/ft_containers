#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

namespace ft {

template<typename T>
class RB_Tree {

public:
    RB_Tree() { }


private:
    class RB_Node {

        T       data;
        RB_Node* parent;
        RB_Node* left;
        RB_Node* right;
    };

};

}

#endif // !RED_BLACK_TREE_HPP
