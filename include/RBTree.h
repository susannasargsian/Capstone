#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H
#include "Data.h"
#include "Base.h"



enum Color {RED, BLACK, DOUBLE_BLACK};

struct Node
{
    Data data;
    int color;
    Node *left, *right, *parent;

    explicit Node(Data);
};

class RBTree : public Base
{
    public:
        RBTree();
        void insert(Data);
        void remove(const Data& );
        void update(Data, Data);
        Data getMax();
        Data getMin();

        void merge(RBTree);
        void getTitle();
    private:
        Node *root;
    protected:
        void rotateLeft(Node *&);
        void rotateRight(Node *&);
        void fixInsertRBTree(Node *&);
        void fixDeleteRBTree(Node *&);
        void inorderBST(Node *&);
        void preorderBST(Node *&);
        int getColor(Node *&);
        void setColor(Node *&, int);
        Node *minValueNode(Node *&);
        Node *maxValueNode(Node *&);
        Node* insertBST(Node *&, Node *&);
        Node* deleteBST(Node *&, Data);
        int getBlackHeight(Node *);
        void inorder();
        void preorder();

};


#endif //RED_BLACK_TREE_RBTREE_H
