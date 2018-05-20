#include "Treap.h"
#include <bits/stdc++.h>
using namespace std;

void Treap::insert(Data key)
{
    m_root=insertNode(m_root,key);
}

void Treap:: getTitle()
{
    std::cout<<"Treap\n\n"<<std::endl;
}

Data Treap::getMax ()
{
    std::list<Data> temp;
    inorder(m_root, temp);

    return temp.back();
}

Data Treap::getMin ()
{
    std::list<Data> temp;
    inorder(m_root, temp);

    return temp.front();

}

TreapNode* Treap::find(const Data& key)
{
    return search(m_root, key);
}

void Treap::remove(const Data& key)
{
    m_root=deleteNode(m_root, key);
}

void Treap:: update(Data old_d, Data new_d)
{
    remove(old_d);
    insert(new_d);
}

TreapNode* Treap::rightRotate(TreapNode *y)
{
    TreapNode *x = y->left,  *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Return new root
    return x;
}

TreapNode* Treap::leftRotate(TreapNode *x)
{
    TreapNode *y = x->right, *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Return new root
    return y;
}

/* Utility function to add a new key */
TreapNode* Treap::newNode(const Data& key)
{
    TreapNode* temp = new TreapNode;
    temp->key = key;
    temp->priority = rand()%100;
    temp->left = temp->right = NULL;
    return temp;
}

// C function to search a given key in a given BST
TreapNode* Treap::search(TreapNode* root, const Data& key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key)
       return root;

    // Key is greater than root's key
    if (root->key < key)
       return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}

/* Recursive implementation of insertion in Treap */
TreapNode* Treap::insertNode(TreapNode* root, const Data& key)
{
    // If root is NULL, create a new node and return it
    if (!root)
        return newNode(key);

    // If key is smaller than root
    if (key <= root->key)
    {
        // Insert in left subtree
        root->left = insertNode(root->left, key);

        // Fix Heap property if it is violated
        if (root->left->priority > root->priority)
        {
            root = rightRotate(root);
        }
    }
    else  // If key is greater
    {
        // Insert in right subtree
        root->right = insertNode(root->right, key);

        // Fix Heap property if it is violated
        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }

    return root;
}

/* Recursive implementation of Delete() */
TreapNode* Treap::deleteNode(TreapNode* root, const Data& key)
{
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // IF KEY IS AT ROOT

    // If left is NULL
    else if (root->left == NULL)
    {
        TreapNode *temp = root->right;
        delete(root);
        root = temp;  // Make right child as root
    }

    // If Right is NULL
    else if (root->right == NULL)
    {
        TreapNode *temp = root->left;
        delete(root);
        root = temp;  // Make left child as root
    }

    // If ksy is at root and both left and right are not NULL
    else if (root->left->priority < root->right->priority)
    {
        root = leftRotate(root);
        root->left = deleteNode(root->left, key);
    }
    else
    {
        root = rightRotate(root);
        root->right = deleteNode(root->right, key);
    }

    return root;
}
void Treap :: inorder(TreapNode* root, std::list<Data>& templist)
{
    if (root)
    {
        inorder(root->left, templist);
        templist.push_back(root->key);

        inorder(root->right, templist);
    }
}



