#include "Data.h"
#include <bits/stdc++.h>
using namespace std;


struct TreapNode
{
    Data key;
    int priority;
    TreapNode *left;
    TreapNode *right;
};

 class Treap
 {
    public:
        void insert(Data);
        void remove(const Data& );
        void update(Data, Data);
        Data getMax ();
        Data getMin ();

        TreapNode* find(const Data& );
        Treap():m_root(0){};
        ~Treap(){};
        void getTitle();

    private:
        TreapNode *rightRotate(TreapNode *);
        TreapNode *leftRotate(TreapNode *);
        // Utility function to add a new key
        TreapNode* newNode(const Data&);
        // C function to search a given key in a given BST
        TreapNode* search(TreapNode*, const Data&);
        // Recursive implementation of insertion in Treap
        TreapNode* insertNode(TreapNode*, const Data&);
        // Recursive implementation of Delete() */
        TreapNode* deleteNode(TreapNode*, const Data&);
        void inorder(TreapNode*, std::list<Data>&);

    private:
            TreapNode* m_root;


};



