#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "Data.h"
#include "Base.h"


struct tree_node
{
    int red;
    Data data;
     tree_node *link[2];
};

struct rb_tree
{
     tree_node *root;
};

class RedBlackTree : public Base
{
    rb_tree* root;
     public:
        RedBlackTree();
        void insert(Data);
        void remove(const Data& );
        void update(Data, Data);
        Data getMax();
        Data getMin();
        void getTitle();

     private:
        int is_red( tree_node *root);
        tree_node *tree_single( tree_node *root, int dir);
        tree_node *tree_double( tree_node *root, int dir);
        tree_node *make_node(Data data);
        int tree_insert( rb_tree *tree, Data data);
        int tree_remove( rb_tree *tree, Data data);
        int tree_rb_assert( tree_node *root);
        tree_node* maximum_node( rb_tree *root);
        tree_node* minimum_node( rb_tree *root);
};
#endif //RED_BLACK_TREE_H




